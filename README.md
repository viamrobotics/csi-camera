# viam-csi
> viam module for csi cams

![](./etc/viam-server.png)

___

### usage

1. Download appimage from releases page.
```bash
sudo wget http://packages.viam.com/apps/csi-camera/viam-csi-latest-aarch64.AppImage -O /usr/local/bin/viam-csi
```

```bash
sudo chmod 755 /usr/local/bin/viam-csi
```

2. Run [viam-server](https://docs.viam.com/installation/) with example config file [etc/app-config.json](https://github.com/seanavery/viam-csi/blob/master/etc/app-config.json). View [JETSON.md](./doc/JETSON.md) for componenet attribute options.

`viam-server` will automatically load the module. You can now head over to https://app.viam.com/ and view the control tab for the camera feed. If you do not see anything, check the logs tab for errors. 

___

### develop

View [DEVELOP.md](./doc/DEVELOP.md) for more information on how to build and run the module locally.

PRs and issues are welcome!

___

### support

- [x] [Nvidia Jetson](./doc/JETSON.md)
- [ ] Raspberry Pi
- [ ] Orange Pi
