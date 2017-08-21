#!/bin/bash
# SCRIPT TO DOWNLOAD AND USE THE SEQUENCE Crowd_PETS09/S2/L1 in WiseMnet++
#	- Downloads the sequence from source ftp://ftp.cs.rdg.ac.uk/pub/PETS2009
#	- Generates videos for each view
#	- Downloads groundtruth annotations from http://www-vpu.eps.uam.es/wisemnet/
#
# More info at http://www-vpu.eps.uam.es/wisemnet/
#
# Author: Juan C. SanMiguel (juancarlos.sanmiguel@uam.es)
# Date: June 2017

#framerate of video sequences (According to http://www.cvg.reading.ac.uk/PETS2009/a.html) - DO NOT CHANGE!
fps=7

#available views for the 'S2_L1' sequence - DO NOT CHANGE!
views=(1 3 4 5 6 7 8)

#codec to generate the videos - UNCOMMENT YOU OPTION
codec=mpeg4
#codec=rawvideo

# install ffmpeg if not available in the system
sudo apt-get install ffmpeg -y

# download PETS dataset from source
echo -n "#Downloading sequence Crowd_PETS09/S2/L1 from ftp.cs.rdg.ac.uk..."
wget -q ftp://ftp.cs.rdg.ac.uk/pub/PETS2009/Crowd_PETS09_dataset/a_data/Crowd_PETS09/S2_L1.tar.bz2 -O S2_L1.tar.bz2
echo "done!"

# decompress the downloaded archive
echo -n "#Uncompressing TAR file..."
tar -xf S2_L1.tar.bz2
#tar -xvf S2_L1.tar.bz2 #verbose mode 'on'
rm S2_L1.tar.bz2
echo "done!"

NVIEW=${#views[@]}
for v in $(seq 0 1 $((NVIEW-1)))

do
	view=${views[$v]}
	echo -n "#Generating video ./Crowd_PETS09/S2/L1/view00${view}_${fps}fps_${codec}.avi..."

	#conversion to video files
	ffmpeg -i ./Crowd_PETS09/S2/L1/Time_12-34/View_00${view}/frame_%04d.jpg -b:v 90000000 -c:v ${codec} -nostats -loglevel 0 -y tmp${view}.avi
	
	#change the framerate of video files
	ffmpeg -i tmp${view}.avi -c copy -an -r ${fps} -nostats -loglevel 0 -y ./Crowd_PETS09/S2/L1/view00${view}_${fps}fps_${codec}.avi

	#delete temporal file
	rm tmp${view}.avi
	echo "done!"
done

# get imageplane annotations and camera calibration for the 'S2_L1' sequence from http://www-vpu.eps.uam.es/wisemnet/
echo -n "#Downloading annotations for Crowd_PETS09/S2/L1 from www-vpu.eps.uam.es/wisemnet/..."
wget -q http://www-vpu.eps.uam.es/wisemnet/Crowd_PETS09_S2_L1_cam-calib_implane-init.zip -O Crowd_PETS09_S2_L1_cam-calib_implane-init.zip
echo  "done!"

echo -n "#Extracting annotations for Crowd_PETS09/S2/L1..."
unzip -qq -o Crowd_PETS09_S2_L1_cam-calib_implane-init.zip -d .
rm Crowd_PETS09_S2_L1_cam-calib_implane-init.zip
echo  "done!"
