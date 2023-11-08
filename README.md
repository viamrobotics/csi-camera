# viam-csi
> viam module for csi cams

![](./etc/viam-server.png)

___

### Getting Started

For user documentation, see [Add a CSI Camera as a Modular Resource](https://docs.viam.com/extend/modular-resources/examples/csi/).

You can view more platform specific details at [JETSON.md](./doc/JETSON.md) and [PI.md](./doc/PI.md).

_Note: On a Raspberry Pi, you must install GStreamer plugins before running the module._

_WARNING: There is a known issue for Debian Bookworm due to changes in the libcamerasrc plugin._

```bash
sudo apt install libcamera0 gstreamer1.0-x gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad
```

See [registry-app-config.json](./etc/registry-app-config.json) for how to configure with csi-cam appimage from registry.

___

### Latest

To install the latest development version of the module, run the following commands:
```bash
sudo wget http://packages.viam.com/apps/csi-camera/viam-csi-latest-aarch64.AppImage -O /usr/local/bin/csi-cam
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
