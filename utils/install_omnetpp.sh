#!/bin/bash
# SCRIPT TO INSTALL OMNETPP 5.0 FOR WISEMNET
#
# More info at http://www-vpu.eps.uam.es/wisemnet/
#
# Author: Juan C. SanMiguel (juancarlos.sanmiguel@uam.es)
# Date: June 2017

#locate in the home directory
cd ~ 

#install required packages
sudo apt-get install build-essential gcc g++ bison flex perl qt-default tcl-dev tk-dev libxml2-dev zlib1g-dev default-jre doxygen graphviz libwebkitgtk-3.0-0 openmpi-bin libopenmpi-dev -y

# Go to https://omnetpp.org/component/jdownloads/download/32-release-older-versions/2305-omnetpp-50-linux and download "OMNeT++ 5.0 (Linux)" in your home folder

#uncompress omnet
tar -xvzf omnetpp-5.0-src.tgz 

#set environment variables
sudo /bin/bash -c 'echo "export PATH=$PATH:~/omnetpp-5.0/bin" > ~/.bashrc'
sudo /bin/bash -c 'echo "export LD_LIBRARY_PATH=~/omnetpp-5.0/lib" > ~/.bashrc'

#configure omnetpp
cd omnetpp-5.0
setenv
./configure

#compile omnetpp sources
make 

#testing the installation
cd samples/dyna
./dyna
