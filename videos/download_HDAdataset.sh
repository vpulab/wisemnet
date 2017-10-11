#!/bin/bash
# SCRIPT TO DOWNLOAD AND USE THE SEQUENCES from "HDA" dataset in WiseMnet++
#	
# Currently the HDA dataset is publicly available only for registered users
# Please visit http://vislab.isr.ist.utl.pt/hda-dataset/ and request the user/pass 
# to download the dataset
#
# To be used by WiseMnet and the provided simulation files, the following directory 
# structure must exist:
#
#	- <videos/HDA_Dataset_V1.3/hda_annotations>
#	- <videos/HDA_Dataset_V1.3/hda_detections>
#	- <videos/HDA_Dataset_V1.3/hda_homographies>
#	- <videos/HDA_Dataset_V1.3/hda_image_sequences_matlab>
#		This folder must contain the video files corresponding to the cameras
#		+ videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/camera02.avi
#		+ videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/camera17.avi
#		+ videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/camera18.avi
#		+ videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/camera19.avi
#		+ videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/camera40.avi
#		+ videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/camera50.avi
#		+ videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/camera53.avi
#		+ videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/camera54.avi
#		+ videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/camera56.avi
#		+ videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/camera57.avi
#		+ videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/camera58.avi
#		+ videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/camera59.avi
#		+ videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/camera60.avi
#	The video files must be created manually by using the script "convert2vid_HDAdataset.m"
#	available at http://www-vpu.eps.uam.es/wisemnet/HDAdataset_utils.zip
#
# Author: Juan C. SanMiguel (juancarlos.sanmiguel@uam.es)
# Date: June 2017

