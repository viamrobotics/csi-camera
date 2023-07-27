# CMake
BUILD_DIR := ./build
INSTALL_DIR := $(BUILD_DIR)/AppDir
BIN_DIR := ./bin

# Docker
BASE_NAME := viam-cpp-jetson
BASE_TAG := 0.0.1
MOD_NAME := viam-csi-module
MOD_TAG := 0.0.1
TEST_NAME := viam-csi-tests
TESET_TAG := 0.0.1
L4T_TAG := 35.3.1

# Package
PACK_TAG := 0.0.1
APP_DIR := './build/AppDir'

# Module
# Builds/installs module.
.PHONY: build
build:
	rm -rf $(BUILD_DIR) | true && \
	mkdir -p build && \
	cd build && \
	cmake -DCMAKE_INSTALL_PREFIX=$(INSTALL_DIR) .. -G Ninja && \
	ninja -j $(shell nproc)

# Creates appimage cmake build.
package:
	cd etc && \
	appimage-builder --recipe viam-csi-jetson-arm64.yml

# Builds docker image with viam-cpp-sdk and helpers.
image-base:
	docker build -t $(BASE_NAME):$(BASE_TAG) \
		--memory=16g \
		--build-arg L4T_TAG=$(L4T_TAG) \
		-f ./etc/Dockerfile.base.jetson ./

# Builds docker image with viam-csi installed.
image-mod:
	docker build -t $(MOD_NAME):$(MOD_TAG) \
		--build-arg BASE_TAG=$(BASE_TAG) \
		--build-arg BASE_NAME=$(BASE_NAME) \
		-f ./etc/Dockerfile.mod.jetson ./

# Builds raw L4T docker image viam-csi appimage.
image-test:
	docker build -t $(TEST_NAME):$(TEST_TAG) \
		--build-arg L4T_TAG=$(L4T_TAG) \
		-f ./etc/Dockerfile.mod.jetson ./ \
	docker run \
		--device /dev/fuse \
		--cap-add SYS_ADMIN \
		-it $(TEST_NAME):$(TEST_TAG)

# Copies binary and appimage from container to host.
bin-mod:
	rm -rf $(BIN_DIR) | true && \
	mkdir -p $(BIN_DIR) && \
	docker stop viam-csi-bin | true && \
	docker rm viam-csi-bin | true && \
	docker run -d -it --name viam-csi-bin $(MOD_NAME):$(MOD_TAG) && \
	docker cp viam-csi-bin:/root/opt/src/csi-camera/build/viam-csi ./$(BIN_DIR) && \
	docker cp viam-csi-bin:/root/opt/src/csi-camera/etc/viam-csi-$(PACK_TAG)-aarch64.AppImage ./$(BIN_DIR) && \
	docker stop viam-csi-bin

# viam-csi-0.0.1-aarch64.AppImage
# SDK
.PHONY: build-sdk
build-sdk:
	cd viam-cpp-sdk && \
	mkdir -p build && \
	cd build && \
	cmake -DVIAMCPPSDK_USE_DYNAMIC_PROTOS=ON -DVIAMCPPSDK_OFFLINE_PROTO_GENERATION=ON .. -G Ninja && \
	ninja -j 2 && \
	sudo ninja install -j 2 && \
	sudo cp -r ./install/* /usr/local/

docker-sdk:
	docker build -t viam-cpp-sdk -f ./viam-cpp-sdk/etc/docker/Dockerfile.ubuntu.focal ./ && \
	docker run -it viam-cpp-sdk /bin/bash

# Tests
# Tests out package in a fresh container.
docker-tests:
	docker build \
		-t viam-csi-tests:$(IMAGE_TAG) \
		--build-arg TAG=$(L4T_VERSION) \
		-f ./etc/Dockerfile.test.jetson ./ && \
	docker run  \
		--device /dev/fuse \
		--cap-add SYS_ADMIN \
		-it \
		viam-csi-tests \
		/bin/bash

# docker-ci:
# 	docker buildx build \
# 		-f etc/Dockerfile.jetson \
# 		--platform linux/arm64 \
# 		-t viam-csi-ci:latest \
# 		--build-arg TAG=35.3.1 \
# 		./

# Utils
# Installs waveshare camera overrides on Jetson.
waveshare:
	mkdir -p gen && \
	wget https://www.waveshare.com/w/upload/e/eb/Camera_overrides.tar.gz -O gen/Camera_overrides.tar.gz && \
	tar -xvf gen/Camera_overrides.tar.gz -C gen && \
	sudo cp gen/camera_overrides.isp /var/nvidia/nvcam/settings/ && \
	sudo chmod 664 /var/nvidia/nvcam/settings/camera_overrides.isp && \
	sudo chown root:root /var/nvidia/nvcam/settings/camera_overrides.isp

# Installs Arducam IMX477 driver on Jetson.
arducam:
	mkdir -p gen && \
	cd gen && \
	wget https://github.com/ArduCAM/MIPI_Camera/releases/download/v0.0.3/install_full.sh && \
	chmod +x install_full.sh && \
	./install_full.sh -m imx477

# Restarts argus service on Jetson. Run this if argus is broken.
restart-argus:
	sudo systemctl stop nvargus-daemon && \
	sudo systemctl start nvargus-daemon && \
	sudo systemctl status nvargus-daemon
