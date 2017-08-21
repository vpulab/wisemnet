WiSE-MNet: Wireless Simulation Environment for Multimedia Networks.
============================================================

This repository contains the Wireless Simulation Environment for Multimedia Networks (WiSE-MNet). 

WiSE-MNet is based on Castalia/Omnet++ and enables the modeling of the communication layers, the sensing and distributed applications of Wireless multimedia sensor networks (WMSNs), i.e. networks with sensors capturing complex vectorial data, such as video and audio. The environment is designed to be flexible and extensible, and has a simple perception model that enables the simulation of distributed computer-vision algorithms at a high-level of abstraction.

The main features are:

* Standard operations: sensing, processing, communication, and decision making
* Wireless and Wired communication support
* Templates for fast prototyping
* Power-consumption models for smart-camera hardware
* Simulates realistic multi-camera networks with both realworld
and synthetic datasets

Click [here](http://www.eecs.qmul.ac.uk/~andrea/wise-mnet.html) to download the latest version of the simulator and the user guide. 


Please cite the following reference when using the simulator
 
```
Networked Computer Vision: the importance of a holistic simulator, 
J. SanMiguel, A Cavallaro
IEEE Computer, 50 (7): pp. 35-43, July 2017
```

Authors
-------
Current version:

* Juan C. SanMiguel (Universidad Autonoma of Madrid, juancarlos.sanmiguel@uam.es)
* Andrea Cavallaro (Queen Mary University of London, a.cavallaro@qmul.ac.uk)

Original version (WiseMnet 2011):

* Christian Nastasi (nastasichr@gmail.com)
* Andrea Cavallaro (Queen Mary University of London, a.cavallaro@qmul.ac.uk)

Documentation
------------

The documentation of the code is available at the file `doc/UserGuide-v1.2.pdf`. Additionally, documentation using doxygen style is provided in the directory 'doc/html' (see 'doc/html/index.html' for more information). 

Moreover, we provide tutorials via Youtube [[list]](https://www.youtube.com/playlist?list=PLXw9Diaj9Nhlt3XczwnoEavshvuwDC4N0)
* WiseMnet++ tutorial: fresh install from github [[video]](https://www.youtube.com/watch?v=2b153IlSWF0)
* WiseMnet++ tutorial: changing settings for a simulation [[video]](https://www.youtube.com/watch?v=YGMkfrgR3JI)
* WiseMnet++ tutorial: consensus multi-camera tracking [[video]](https://www.youtube.com/watch?v=NQX_dzY5h20&)
* WiseMnet++ tutorial: multi-camera visual processing [[video]](https://www.youtube.com/watch?v=-Xym_Xk-9OQ)

Required libraries and installation
-------------------------------

Wise-MNet requires the following libraries:

* OMNeT++ version 5.0 
* Castalia version 3 
* OpenCV version 3.2.0 
* Eigen3 version 3.2.92

Two installation scripts are provided `install_omnetpp.sh` and `install_opencv.sh`. Further installation instructions are available at `doc/UserGuide-v1.2.pdf`

License
-------

The simulator code and the documentation is available under the Academic Public License (same as OMNeT++ and Castalia). See the "LICENSE_WISE" for more information. 

 
Dataset downloading
--------------------------------

Currently, WiseMnet++ employs the following datasets:

* Sequence S2_L1 from Crowd_PETS09 dataset (7 views) [[link]](https://goo.gl/vOOkzr)
* Sequence AB_HARD from AVSS2007 dataset (1 view) [[link]](https://goo.gl/NeCuzY)
* Sequence CHAP from ICGLab6 dataset (4 view) [[link]](https://www.tugraz.at/institute/icg/research/team-bischof/lrs/downloads/lab6)

Sample bash scripts are provided to download the video frames and the associated data (groundtruth, calibration,...) in the directory `./videos`. These scripts prepare all data to be used directly in Wise-Mnet++.

Available algorithms in the simulator
----------------------------------

The list of available algorithms is given in the following table:

Algorithm | Type | Focus | Approach | Reference         
------------- | ------------- | ------------- | ------------- | ------------------
KCF: Kalman Consensus Filtering  | Tracker | Multi-camera single-target | Consensus-based | IEEE CDC 2009 [[link]](http://ieeexplore.ieee.org/document/4118472)
DPF: Distributed Particle Filter  | Tracker | Multi-camera single-target | Token-passing | IEEE SSPD 2011 [[link]](http://ieeexplore.ieee.org/document/6253415/)
ICF: Information Consensus Filtering  | Tracker | Multi-camera single-target | Consensus-based | IEEE TAC 2013 [[link]](http://ieeexplore.ieee.org/document/6576197/)
CAWC: Cost-AWare Collaborative tracking  | Tracker | Multi-camera single-target | Consensus-based | IEEE SENSORS J 2015 [[link]](http://ieeexplore.ieee.org/document/694578/)
MTIC: Multi-Target Information Consensus  | Tracker | Multi-camera multi-target | Consensus-based | IEEE TPAMI 2016 [[link]](http://ieeexplore.ieee.org/document/7286852/)
People detect&transmit | Detector | Single-camera | - | IEEE COMPUTER 2017 [[preprint]](http://www.eecs.qmul.ac.uk/~andrea/wise-mnet.html)

References using the simulator
--------------------------------
 
Currently, the simulator has been used in the following papers:
 

* **WiSE-MNet: an experimental environment for Wireless Multimedia Sensor Networks**, SSPD 2011, [[preprint]](http://www.eecs.qmul.ac.uk/~andrea/wise-mnet.html)

* **Distributed target tracking under realistic network conditions**, SSPD 2011, [[preprint]](http://www.eecs.qmul.ac.uk/~andrea/wise-mnet.html)

* **Cost-aware coalitions for collaborative tracking in resource-constrained camera networks**, IEEE Sen. Journal 2015 [[link]](http://ieeexplore.ieee.org/document/6945780),

* **Energy Consumption Models for Smart-Camera Networks**, IEEE TCSVT 2016 [[link]](http://ieeexplore.ieee.org/document/7517353/),

* **Networked Computer Vision: the importance of a holistic simulator**, IEEE COMPUTER 2017 [[preprint]](http://www.eecs.qmul.ac.uk/~andrea/wise-mnet.html)
