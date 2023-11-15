# viam-csi
> viam module for csi cams

![](./etc/viam-server.png)

___


## Getting Started

### Overview
Easily integrate CSI Cameras into your Viam projects using this camera module. For detailed user documentation, visit [Add a CSI Camera as a Modular Resource](https://docs.viam.com/extend/modular-resources/examples/csi/).

### Supported Modules
- **Nvidia Jetson**: Use the `csi-cam` module. [More Info](./doc/JETSON.md)
- **Raspberry Pi**: Use the `csi-cam-pi` module. [More Info](./doc/PI.md)


### Configuration
Configure `viam-server` with the csi-cam module using [registry-app-config.json](./etc/registry-app-config.json) as a reference.

___

### Latest

To install the latest development version of the module, run the following commands.

### For Jetson Devices
```bash
sudo wget http://packages.viam.com/apps/csi-camera/jetson/viam-csi-latest-aarch64.AppImage -O /usr/local/bin/csi-cam
```

### For Raspberry Pi devices:
```bash
sudo wget http://packages.viam.com/apps/csi-camera/pi/viam-csi-latest-aarch64.AppImage -O /usr/local/bin/csi-cam
```

### Set Permissions
```bash
sudo chmod 755 /usr/local/bin/csi-cam
```

Refer to [local-app-config.json](./etc/local-app-config.json) for configuration example with local `appimage`.
___

### Develop

Interested in contributing? Check out [DEVELOP.md](./doc/DEVELOP.md) for guidelines on how to build and run the module `locally` or using `docker`. We welcome Pull Requests and Issues!
