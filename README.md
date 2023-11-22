# CSI-CAM
> A Viam Module for CSI Cameras

![Viam Server](./etc/viam-server.png)

___


## Getting Started

### Overview
Easily integrate CSI Cameras into your Viam projects using this camera module. For detailed user documentation, visit [Add a CSI Camera as a Modular Resource](https://docs.viam.com/extend/modular-resources/examples/csi/).

### Supported Modules
- **Nvidia Jetson**: Use the `csi-cam` module. [More Info](./docs/JETSON.md)
- **Raspberry Pi**: Use the `csi-cam-pi` module. [More Info](./docs/PI.md)


### Configuration
Configure `viam-server` with the csi-cam module through the [Viam Module Registry](https://app.viam.com/registry) using [registry-app-config.json](./etc/registry-app-config.json) as a reference.

___

## Latest Version Installation

Install the latest development version of the module on your device with these commands:

### For Jetson Devices
```bash
sudo wget http://packages.viam.com/apps/csi-camera/jetson/viam-csi-latest-aarch64.AppImage -O /usr/local/bin/csi-cam
```

### For Raspberry Pi Devices
```bash
sudo wget http://packages.viam.com/apps/csi-camera/pi/viam-csi-latest-aarch64.AppImage -O /usr/local/bin/csi-cam
```

### Set Permissions
```bash
sudo chmod 755 /usr/local/bin/csi-cam
```

Refer to [local-app-config.json](./etc/local-app-config.json) for configuration example with local appimage.
___

## Development

Interested in contributing? Check out [DEVELOP.md](./docs/DEVELOP.md) for guidelines on how to build and run the module `locally` or using `docker`. We welcome Pull Requests and Issues!
