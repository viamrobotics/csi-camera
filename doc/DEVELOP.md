# Develop

### Local Setup

First, install dependencies for [viam-cpp-sdk](https://github.com/viamrobotics/viam-cpp-sdk).
See example [dockerfile](https://github.com/viamrobotics/viam-cpp-sdk/blob/main/etc/docker/Dockerfile.ubuntu.focal) for reference.


```
make build-sdk
```

```
make build
```

```
make package
```

___

### Docker Setup

```
make image-mod # create appimage
```

```
make bin-mod # copy appimage to bin
```

``` 
make image-test TARGET=pi 
make test-package TARGET=pi # test appimage in fresh debian bookworm image
```

```
make image-test TARGET=jetson
make test-package TARGET=jetson # test appimage in fresh L4T image
```
