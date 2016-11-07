from ubuntu:14.04

# Install prerequisites
run apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libopencv-dev \
    qt5-default

workdir /srv/
run git clone https://github.com/gstiebler/vision_workbench.git
run mkdir /srv/vision_workbench/obj
workdir /srv/vision_workbench/obj
run cmake /srv/vision_workbench/build
run make