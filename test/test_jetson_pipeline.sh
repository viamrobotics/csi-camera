gst-launch-1.0 nvarguscamerasrc sensor_id=0 \
    ! 'video/x-raw(memory:NVMM),width=1640,height=1232,framerate=30/1' \
    ! nvvidconv flip-method=0 ! video/x-raw,width=960,height=540 \
    ! nvjpegenc ! image/jpeg ! appsink name=appsink0 max-buffers=1
