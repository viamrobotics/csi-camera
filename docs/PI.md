# Raspberry Pi

## Dependencies

For the `csi-cam-pi` module, Gstreamer and Libcamera are bundled into the appimage. You do not need to install any dependencies.

Make sure that the `/boot/config.txt` is configured to detect the camera. See [this guide](https://www.raspberrypi.com/documentation/computers/camera_software.html) for more information. For example, if you are using the IMX 477, you should have the following lines in your `/boot/config.txt`:

```bash
camera_auto_detect=0
dtoverlay=imx477
```

___

## Camera Attributes

| Key Name    | Value Type | Description                                  |
|-------------|------------|----------------------------------------------|
| width_px    | Integer    | Width of the video in pixels (e.g., 1920).  |
| height_px   | Integer    | Height of the video in pixels (e.g., 1080). |
| frame_rate  | Integer    | Frames per second of the video (e.g., 30).  |
| debug       | Boolean    | Flag indicating debug mode (e.g., true).    |

___

## Tested Setups

| Device | OS | Camera | Provider |
|------------------|-----------------|-----------------|-----------------|
| Raspberry Pi 5 | Debian Bookworm | OV5647 | Arducam |
| Raspberry Pi 4B | Debian Bullseye | RPI GS Camera | Raspberry Pi |
| Raspberry Pi 4B | Debian Bookworm | IMX 477 | Arducam |

____

## Tools

| Tool | Description |
|------------------|-----------------|
| test_pi_pipeline.sh | Test script to see if GST and camera sensor are working. |
