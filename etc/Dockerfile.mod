ARG BASE_IMG

FROM ${BASE_IMG}

ENV DEBIAN_FRONTEND=noninteractive

# Install GST dev files
RUN apt-get update
RUN apt-get install -y gstreamer1.0-tools gstreamer1.0-alsa \
     gstreamer1.0-plugins-base gstreamer1.0-plugins-good \
     gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly \
     gstreamer1.0-libav
RUN apt-get install -y libgstreamer1.0-dev \
     libgstreamer-plugins-base1.0-dev \
     libgstreamer-plugins-good1.0-dev \
     libgstreamer-plugins-bad1.0-dev

# Install gtest
RUN apt-get -y install libgtest-dev

ADD ../ /root/opt/src/csi-camera
RUN cd /root/opt/src && \
    cd csi-camera && \
    make build && \
    make package TARGET=jetson
