#!/bin/bash
# SCRIPT TO DOWNLOAD AND USE THE SEQUENCES from "VOT2017" in WiseMnet++
#	- Downloads the sequences from source http://data.votchallenge.net/vot2017/vot2017.zip
#	- Already contains ground-truth so 
#
# More info at http://www-vpu.eps.uam.es/wisemnet/
#
# Author: Juan C. SanMiguel (juancarlos.sanmiguel@uam.es)
# Date: June 2017

# get VOT2017 dataset from http://data.votchallenge.net/vot2017/vot2017.zip
echo -n "#Downloading dataset from http://data.votchallenge.net/vot2017/vot2017.zip..."
wget --show-progress -q http://data.votchallenge.net/vot2017/vot2017.zip -O vot2017.zip 
echo "done!"

# decompress the downloaded archive
echo -n "#Uncompressing ZIP file..."
mkdir ./vot2017/
unzip -qq -o vot2017.zip -d ./vot2017/
rm vot2017.zip
echo "done!"
