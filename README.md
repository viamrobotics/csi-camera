# viam-csi
> viam module for csi cams

![](./etc/viam-server.png)

___

### Getting Started

For user documentation, see [Add a CSI Camera as a Modular Resource](https://docs.viam.com/extend/modular-resources/examples/csi/).

You can view more platform specific details at [JETSON.md](./doc/JETSON.md) and [PI.md](./doc/PI.md).

_Note: On a Raspberry Pi, you must install GStreamer plugins before running the module._

```bash
sudo apt install libgstreamer-plugins-base1.0-dev 
```

___

### Latest

To install the latest development version of the module, run the following commands:
```bash
sudo wget http://packages.viam.com/apps/csi-camera/viam-csi-latest-aarch64.AppImage -O /usr/local/bin/csi-cam
```

```bash
sudo chmod 755 /usr/local/bin/csi-cam
```

___

### Develop

View [DEVELOP.md](./doc/DEVELOP.md) for more information on how to build and run the module locally or in Docker. Pull Requests and Issues are welcome!

___

### Support

- [x] [Nvidia Jetson](./doc/JETSON.md)
- [x] [Raspberry Pi](./doc/PI.md)
- [ ] Orange Pi
