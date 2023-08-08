ARG BASE_TAG
ARG BASE_NAME
ARG HUB_USER

FROM ghcr.io/${HUB_USER}/${BASE_NAME}:${BASE_TAG}

# install GST dev files
RUN apt-get update
RUN apt-get install -y gstreamer1.0-tools gstreamer1.0-alsa \
     gstreamer1.0-plugins-base gstreamer1.0-plugins-good \
     gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly \
     gstreamer1.0-libav
RUN apt-get install -y libgstreamer1.0-dev \
     libgstreamer-plugins-base1.0-dev \
     libgstreamer-plugins-good1.0-dev \
     libgstreamer-plugins-bad1.0-dev

# install gtest
RUN apt-get -y install libgtest-dev

ADD ../ /root/opt/src/csi-camera
RUN cd /root/opt/src && \
    cd csi-camera && \
    make build && \
    make package
