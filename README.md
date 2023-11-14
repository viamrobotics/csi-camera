# viam-csi
> viam module for csi cams

![](./etc/viam-server.png)

___

### Getting Started

For user documentation, see [Add a CSI Camera as a Modular Resource](https://docs.viam.com/extend/modular-resources/examples/csi/).

There are now two module for CSI cameras, one for Nvidia Jetson `csi-cam` and one for Raspberry Pi `csi-cam-pi`. You can view more platform specific details at [JETSON.md](./doc/JETSON.md) and [PI.md](./doc/PI.md).

See [registry-app-config.json](./etc/registry-app-config.json) for how to configure with csi-cam appimage from registry.

___

### Latest

To install the latest development version of the module, run the following commands.

For Jetson devices:
```bash
sudo wget http://packages.viam.com/apps/csi-camera/jetson/viam-csi-latest-aarch64.AppImage -O /usr/local/bin/csi-cam
```
For Raspberry Pi devices:
```bash
sudo wget http://packages.viam.com/apps/csi-camera/pi/viam-csi-latest-aarch64.AppImage -O /usr/local/bin/csi-cam
```


```bash
sudo chmod 755 /usr/local/bin/csi-cam
```

See [local-app-config.json](./etc/local-app-config.json) for how to configure with local csi-cam appimage.
___

### Develop

View [DEVELOP.md](./doc/DEVELOP.md) for more information on how to build and run the module locally or in Docker. Pull Requests and Issues are welcome!

___

### Support

- [x] [Nvidia Jetson](./doc/JETSON.md)
- [x] [Raspberry Pi](./doc/PI.md)
- [ ] Orange Pi
