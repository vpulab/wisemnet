#!/bin/bash
# SCRIPT TO GENERATE DOCUMENTATION FOR WISEMENT
#
# More info at http://www-vpu.eps.uam.es/wisemnet/
#
# Author: Juan C. SanMiguel (juancarlos.sanmiguel@uam.es)
# Date: June 2017

#install required packages
sudo apt-get install doxygen -y

doxygen doxyfile.settings.cfg


