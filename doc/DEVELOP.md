# Develop

## Docker Setup

Docker is the preferred environment for development. The following commands are used for building and testing the application in Docker containers.

```bash
make image-mod TARGET=[pi/jetson] # Build binary and create appimage
```

```bash
make bin-mod TARGET=[pi/jetson] # Copy appimage to bin
```

```bash
make image-test TARGET=pi
make test-package TARGET=pi # Test appimage in fresh debian bookworm image
```

```bash
make image-test TARGET=jetson
make test-package TARGET=jetson # Test appimage in fresh L4T image
```

___

## Local Setup

For local development, first install the dependencies for the [viam-cpp-sdk](https://github.com/viamrobotics/viam-cpp-sdk). Refer to the example [dockerfile](https://github.com/viamrobotics/viam-cpp-sdk/blob/main/etc/docker/Dockerfile.ubuntu.focal) for guidance on setting up the environment.

```bash
make build-sdk # Compile and install viam-cpp-sdk
```

```bash
make dep TARGET=[pi/jetson] # Install platform specific dependencies
```

```bash
make build # Build binary
```

```bash
make package TARGET=[pi/jetson] # Build appiamge
```
