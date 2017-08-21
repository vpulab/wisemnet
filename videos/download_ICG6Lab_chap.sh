#!/bin/bash
# SCRIPT TO DOWNLOAD AND USE THE SEQUENCE 'chap' in WiseMnet++
#	- Downloads the sequence from source https://www.tugraz.at/institute/icg/research/team-bischof/lrs/downloads/lab6
#	- Generates videos for each view
#	- Downloads groundtruth annotations from http://www-vpu.eps.uam.es/wisemnet/
#
# More info at http://www-vpu.eps.uam.es/wisemnet/
#
# Author: Juan C. SanMiguel (juancarlos.sanmiguel@uam.es)
# Date: June 2017

# get ICGLab6 dataset from https://www.tugraz.at/institute/icg/research/team-bischof/lrs/downloads/lab6
echo -n "#Downloading dataset ICGLab6 from www.tugraz.at..."
wget -q https://files.icg.tugraz.at/f/7cdc2b0422/?raw=1 -O ICGLab6.zip
echo "done!"

# decompress the downloaded archive
echo -n "#Uncompressing ZIP file..."
unzip -qq -o ICGLab6.zip -d .
rm ICGLab6.zip
echo "done!"

# get imageplane annotations and camera calibration for the 'chap' sequence from http://www-vpu.eps.uam.es/wisemnet/
echo -n "#Downloading annotations for 'chap' sequence from www-vpu.eps.uam.es/wisemnet/..."
wget -q http://www-vpu.eps.uam.es/wisemnet/ICGLab6_chap_cam-calib_implane-init.zip -O ICGLab6_chap_cam-calib_implane-init.zip
echo  "done!"

echo -n "#Extracting annotations for 'chap' sequence..."
unzip -qq -o ICGLab6_chap_cam-calib_implane-init.zip -d .
rm ICGLab6_chap_cam-calib_implane-init.zip 
echo  "done!"
