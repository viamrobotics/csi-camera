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


### Docker Setup

```
make image-mod
```

```
make bin-mod
```
