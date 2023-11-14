# Develop

Docker is preferred environment for development and testing.
___

### Docker Setup

```
make image-mod TARGET=[pi/jetson]# create appimage
```

```
make bin-mod TARGET=[pi/jetson] # copy appimage to bin
```

```
make image-test TARGET=pi
make test-package TARGET=pi # test appimage in fresh debian bookworm image
```

```
make image-test TARGET=jetson
make test-package TARGET=jetson # test appimage in fresh L4T image
```

___

### Local Setup

First, install dependencies for [viam-cpp-sdk](https://github.com/viamrobotics/viam-cpp-sdk). See example [dockerfile](https://github.com/viamrobotics/viam-cpp-sdk/blob/main/etc/docker/Dockerfile.ubuntu.focal) for reference.


```
make build-sdk # compile and install viam-cpp-sdk
```

```
make dep TARGET=[pi/jetson] # install platform specific dependencies
```

```
make build # build binary
```

```
make package TARGET=[pi/jetson] # build appiamge
```
