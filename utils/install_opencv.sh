#!/bin/bash
# SCRIPT TO INSTALL OPENCV 3.2.0 FOR WISEMNET
#
# More info at http://www-vpu.eps.uam.es/wisemnet/
#
# Author: Juan C. SanMiguel (juancarlos.sanmiguel@uam.es)
# Date: June 2017

#locate in the home directory
cd ~ 

#install required packages
sudo apt-get -y install build-essential cmake git libgtk2.0-dev pkg-config python-dev python-numpy libdc1394-22 libdc1394-22-dev libjpeg-dev libpng12-dev libjasper-dev libavcodec-dev libavformat-dev libswscale-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev libtbb-dev libqt4-dev libfaac-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev x264 v4l-utils unzip libeigen3-dev=3.2.92

#download and uncompressopencv 3.2.0
wget https://github.com/opencv/opencv/archive/3.2.0.tar.gz && mv 3.2.0.tar.gz opencv-3.2.0.tar.gz
tar -zxvf opencv-3.2.0.tar.gz 

#download and uncompress additional opencv modules
wget https://github.com/opencv/opencv_contrib/archive/3.2.0.zip && mv 3.2.0.zip opencv_contrib-3.2.0.zip
unzip opencv_contrib-3.2.0.zip -d opencv-3.2.0/

#create build directory and makefile
cv ./opencv-3.2.0
mkdir build 
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -DWITH_OPENGL=ON -DWITH_VTK=ON -DWITH_TBB=ON -DWITH_GDAL=ON -DWITH_XINE=ON -DBUILD_EXAMPLES=ON  -DBUILD_TIFF=ON -D BUILD_PYTHON_SUPPORT=ON -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-3.2.0/modules ..

#compile OpenCV sources
make 
sudo make install

sudo /bin/bash -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig

#check whether the OpenCV library paths are correctly installed
pkg-config opencv --cflags 
pkg-config opencv --libs 
pkg-config --modversion opencv
