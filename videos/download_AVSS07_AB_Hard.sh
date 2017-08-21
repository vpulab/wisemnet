#!/bin/bash
# SCRIPT TO DOWNLOAD AND USE THE SEQUENCE 'AB_HARD_dix' in WiseMnet++
#	- Downloads the sequence from source ftp://motinas.elec.qmul.ac.uk
#	- Generates videos for each view
#	- Downloads groundtruth annotations from http://www-vpu.eps.uam.es/wisemnet/
#
# More info at http://www-vpu.eps.uam.es/wisemnet/
#
# Author: Juan C. SanMiguel (juancarlos.sanmiguel@uam.es)
# Date: June 2017

# get AVSS2007 dataset from ftp://motinas.elec.qmul.ac.uk
echo -n "#Downloading sequence AVSS_AB_Hard_Divx from ftp://motinas.elec.qmul.ac.uk..."
wget -q ftp://motinas.elec.qmul.ac.uk/pub/iLids/AVSS_AB_Hard_Divx.avi -O AVSS_AB_Hard_Divx.avi
echo "done!"

# move the downloaded file
echo -n "#Moving file..."
mv AVSS_AB_Hard_Divx.avi ./AVSS07/AVSS_AB_Hard_Divx.avi
echo "done!"
