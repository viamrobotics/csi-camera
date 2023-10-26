# Raspberry Pi

### Dependencies

On a Raspberry Pi, you must install GStreamer plugins before running the module.

```bash
sudo apt install libgstreamer-plugins-base1.0-dev 
```

### Camera Attributes

| Key Name    | Value Type | Description                                  |
|-------------|------------|----------------------------------------------|
| width_px    | Integer    | Width of the video in pixels (e.g., 1920).  |
| height_px   | Integer    | Height of the video in pixels (e.g., 1080). |
| frame_rate  | Integer    | Frames per second of the video (e.g., 30).  |
| debug       | Boolean    | Flag indicating debug mode (e.g., true).    |

___

### Tested Setups

| Device | OS | Camera | Provider |
|------------------|-----------------|-----------------|-----------------|
| Raspberry Pi 4B | Debian Bullseye | RPI GS Camera | Raspberry Pi |
| Raspberry Pi 4B | Debian Bookworm | IMX 477 | Arducam |

____

### Tools

| Tool | Description |
|------------------|-----------------|
| test_pi_pipeline.sh | Test script to see if GST and camera sensor are working. |
