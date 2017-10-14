#
# OMNeT++/OMNEST Makefile for wisemnet-v1.4
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/include/eigen3 -I/usr/include/libxml2 -lxml2 -lopencv_tracking -lopencv_videoio -lopencv_objdetect -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -lopencv_video -lopencv_core -lopencv_features2d -- wise/src/utils/gmm/c-gmm/c-gmm-64bit.a
#

# Name of target to be created (-o option)
TARGET = wisemnet-v1.4$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(QTENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)
#USERIF_LIBS = $(QTENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I/usr/local/include/opencv \
    -I/usr/local/include/opencv2 \
    -I/usr/include/eigen3 \
    -I/usr/include/libxml2 \
    -I. \
    -Icastalia \
    -Icastalia/Simulations \
    -Icastalia/Simulations/BANtest \
    -Icastalia/Simulations/BridgeTest \
    -Icastalia/Simulations/Parameters \
    -Icastalia/Simulations/Parameters/MAC \
    -Icastalia/Simulations/Parameters/Radio \
    -Icastalia/Simulations/Parameters/SensorDevice \
    -Icastalia/Simulations/Parameters/WirelessChannel \
    -Icastalia/Simulations/Parameters/WirelessChannel/BANmodels \
    -Icastalia/Simulations/connectivityMap \
    -Icastalia/Simulations/radioTest \
    -Icastalia/Simulations/simpleAggregation \
    -Icastalia/Simulations/valuePropagation \
    -Icastalia/Simulations/valueReporting \
    -Icastalia/scripts \
    -Icastalia/src \
    -Icastalia/src/helpStructures \
    -Icastalia/src/node \
    -Icastalia/src/node/application \
    -Icastalia/src/node/application/bridgeTest \
    -Icastalia/src/node/application/connectivityMap \
    -Icastalia/src/node/application/simpleAggregation \
    -Icastalia/src/node/application/throughputTest \
    -Icastalia/src/node/application/valuePropagation \
    -Icastalia/src/node/application/valueReporting \
    -Icastalia/src/node/communication \
    -Icastalia/src/node/communication/mac \
    -Icastalia/src/node/communication/mac/baselineBanMac \
    -Icastalia/src/node/communication/mac/bypassMac \
    -Icastalia/src/node/communication/mac/mac802154 \
    -Icastalia/src/node/communication/mac/tMac \
    -Icastalia/src/node/communication/mac/tunableMac \
    -Icastalia/src/node/communication/radio \
    -Icastalia/src/node/communication/routing \
    -Icastalia/src/node/communication/routing/bypassRouting \
    -Icastalia/src/node/communication/routing/multipathRingsRouting \
    -Icastalia/src/node/mobilityManager \
    -Icastalia/src/node/mobilityManager/lineMobilityManager \
    -Icastalia/src/node/mobilityManager/noMobilityManager \
    -Icastalia/src/node/resourceManager \
    -Icastalia/src/physicalProcess \
    -Icastalia/src/physicalProcess/carsPhysicalProcess \
    -Icastalia/src/physicalProcess/customizablePhysicalProcess \
    -Icastalia/src/wirelessChannel \
    -Idoc \
    -Idoc/html \
    -Idoc/html/search \
    -Idoc/manual \
    -Idoc/manual/figures \
    -Idoc/pdfs \
    -Imodels \
    -Imodels/COM \
    -Imodels/CPU \
    -Imodels/SEN \
    -Iutils \
    -Ivideos \
    -Ivideos/Crowd_PETS09 \
    -Ivideos/Crowd_PETS09/S2 \
    -Ivideos/Crowd_PETS09/S2/L1 \
    -Ivideos/Crowd_PETS09/S2/L1/Groundtruth \
    -Ivideos/HDA_Dataset_V1.3 \
    -Ivideos/HDA_Dataset_V1.3/hda_annotations \
    -Ivideos/HDA_Dataset_V1.3/hda_detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/FPClass \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera17 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera17/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera18 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera18/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera19 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera19/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera40 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera40/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera50 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera50/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera53 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera53/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera54 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera54/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera56 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera56/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera57 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera57/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera58 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera58/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera59 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera59/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera60 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera60/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera17 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera17/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera18 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera18/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera19 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera19/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera40 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera40/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera50 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera50/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera53 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera53/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera54 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera54/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera56 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera56/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera57 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera57/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera58 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera58/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera59 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera59/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera60 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera60/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera17 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera17/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera18 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera18/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera19 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera19/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera40 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera40/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera50 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera50/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera53 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera53/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera54 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera54/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera56 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera56/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera57 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera57/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera58 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera58/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera59 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera59/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera60 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera60/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/Toy3 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/Toy3/camera60 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/Toy3/camera60/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/Toy8 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/Toy8/camera60 \
    -Ivideos/HDA_Dataset_V1.3/hda_detections/Toy8/camera60/Detections \
    -Ivideos/HDA_Dataset_V1.3/hda_docs \
    -Ivideos/HDA_Dataset_V1.3/hda_homographies \
    -Ivideos/HDA_Dataset_V1.3/hda_image_sequences_matlab \
    -Ivideos/HDA_Dataset_V1.3/hda_sample_train_data \
    -Ivideos/HDA_Dataset_V1.3/hda_sample_train_data_toy3 \
    -Ivideos/HDA_Dataset_V1.3/hda_sample_train_data_toy8 \
    -Ivideos/ICGLab6 \
    -Ivideos/ICGLab6/calibration \
    -Ivideos/ICGLab6/chap \
    -Ivideos/ICGLab6/chap/Groundtruth \
    -Ivideos/vot2017 \
    -Ivideos/vot2017/ants1 \
    -Ivideos/vot2017/ants3 \
    -Ivideos/vot2017/bag \
    -Ivideos/vot2017/ball1 \
    -Ivideos/vot2017/ball2 \
    -Ivideos/vot2017/basketball \
    -Ivideos/vot2017/birds1 \
    -Ivideos/vot2017/blanket \
    -Ivideos/vot2017/bmx \
    -Ivideos/vot2017/bolt1 \
    -Ivideos/vot2017/bolt2 \
    -Ivideos/vot2017/book \
    -Ivideos/vot2017/butterfly \
    -Ivideos/vot2017/car1 \
    -Ivideos/vot2017/conduction1 \
    -Ivideos/vot2017/crabs1 \
    -Ivideos/vot2017/crossing \
    -Ivideos/vot2017/dinosaur \
    -Ivideos/vot2017/drone1 \
    -Ivideos/vot2017/drone_across \
    -Ivideos/vot2017/drone_flip \
    -Ivideos/vot2017/fernando \
    -Ivideos/vot2017/fish1 \
    -Ivideos/vot2017/fish2 \
    -Ivideos/vot2017/fish3 \
    -Ivideos/vot2017/flamingo1 \
    -Ivideos/vot2017/frisbee \
    -Ivideos/vot2017/girl \
    -Ivideos/vot2017/glove \
    -Ivideos/vot2017/godfather \
    -Ivideos/vot2017/graduate \
    -Ivideos/vot2017/gymnastics1 \
    -Ivideos/vot2017/gymnastics2 \
    -Ivideos/vot2017/gymnastics3 \
    -Ivideos/vot2017/hand \
    -Ivideos/vot2017/handball1 \
    -Ivideos/vot2017/handball2 \
    -Ivideos/vot2017/helicopter \
    -Ivideos/vot2017/iceskater1 \
    -Ivideos/vot2017/iceskater2 \
    -Ivideos/vot2017/leaves \
    -Ivideos/vot2017/matrix \
    -Ivideos/vot2017/motocross1 \
    -Ivideos/vot2017/motocross2 \
    -Ivideos/vot2017/nature \
    -Ivideos/vot2017/pedestrian1 \
    -Ivideos/vot2017/rabbit \
    -Ivideos/vot2017/racing \
    -Ivideos/vot2017/road \
    -Ivideos/vot2017/shaking \
    -Ivideos/vot2017/sheep \
    -Ivideos/vot2017/singer2 \
    -Ivideos/vot2017/singer3 \
    -Ivideos/vot2017/soccer1 \
    -Ivideos/vot2017/soccer2 \
    -Ivideos/vot2017/soldier \
    -Ivideos/vot2017/tiger \
    -Ivideos/vot2017/traffic \
    -Ivideos/vot2017/wiper \
    -Ivideos/vot2017/zebrafish1 \
    -Iwise \
    -Iwise/simulations \
    -Iwise/simulations/Tutorial_ICIP17 \
    -Iwise/simulations/wiseMultiCameraPeriodicApp_DPF \
    -Iwise/simulations/wiseMultiCameraPeriodicApp_DPF/res \
    -Iwise/simulations/wiseMultiCameraPeriodicApp_ICF \
    -Iwise/simulations/wiseMultiCameraPeriodicApp_ICF/res \
    -Iwise/simulations/wiseMultiCameraPeriodicApp_ICF/scripts \
    -Iwise/simulations/wiseMultiCameraPeriodicApp_KCF \
    -Iwise/simulations/wiseMultiCameraPeriodicApp_KCF/res \
    -Iwise/simulations/wiseMultiCameraPeriodicApp_KCF/scripts \
    -Iwise/simulations/wiseMultiCameraPeriodicApp_MTIC \
    -Iwise/simulations/wiseTest \
    -Iwise/simulations/wiseTest/res \
    -Iwise/src \
    -Iwise/src/node \
    -Iwise/src/node/application \
    -Iwise/src/node/application/wiseBaseApp \
    -Iwise/src/node/application/wiseBaseAppTest \
    -Iwise/src/node/application/wiseCameraApp \
    -Iwise/src/node/application/wiseCameraAppTest \
    -Iwise/src/node/application/wiseCameraPeriodicApp \
    -Iwise/src/node/application/wiseCameraPeriodicAppDet \
    -Iwise/src/node/application/wiseCameraPeriodicAppTest \
    -Iwise/src/node/application/wiseCameraPeriodicAppTracker \
    -Iwise/src/node/application/wiseMultiCameraPeriodicApp_DPF \
    -Iwise/src/node/application/wiseMultiCameraPeriodicApp_ICF \
    -Iwise/src/node/application/wiseMultiCameraPeriodicApp_KCF \
    -Iwise/src/node/application/wiseMultiCameraPeriodicApp_MTIC \
    -Iwise/src/node/application/wiseMultiCameraPeriodicApp_ReID \
    -Iwise/src/node/resourceManager \
    -Iwise/src/node/sensorManager \
    -Iwise/src/node/sensorManager/sensorManager \
    -Iwise/src/node/sensorManager/wiseCameraManager \
    -Iwise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler \
    -Iwise/src/node/sensorManager/wiseEmptySensorManager \
    -Iwise/src/utils \
    -Iwise/src/utils/gmm \
    -Iwise/src/utils/gmm/c-gmm \
    -Iwise/src/utils/libMvtnorm \
    -Iwise/src/utils/libMvtnorm/libMvtnorm \
    -Iwise/src/utils/pft \
    -Iwise/src/wirelessChannel \
    -Iwise/src/world \
    -Iwise/src/world/gui \
    -Iwise/src/world/gui/opencv \
    -Iwise/src/world/physicalProcess \
    -Iwise/src/world/physicalProcess/wiseMovingTarget \
    -Iwise/src/world/physicalProcess/wiseVideoFile \
    -Iwise/src/world/terrain \
    -Iwise/src/world/terrain/wiseTerrainCalibrated \
    -Iwise/src/world/terrain/wiseTerrainEmpty

# Additional object and library files to link with
EXTRA_OBJS = wise/src/utils/gmm/c-gmm/c-gmm-64bit.a

# Additional libraries (-L, -l options)
LIBS =  -lxml2 -lopencv_tracking -lopencv_videoio -lopencv_objdetect -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -lopencv_video -lopencv_core -lopencv_features2d

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = \
    $O/castalia/src/helpStructures/CastaliaModule.o \
    $O/castalia/src/helpStructures/DebugInfoWriter.o \
    $O/castalia/src/helpStructures/OmnetCompatibility.o \
    $O/castalia/src/helpStructures/TimerService.o \
    $O/castalia/src/node/application/VirtualApplication.o \
    $O/castalia/src/node/application/bridgeTest/BridgeTest.o \
    $O/castalia/src/node/application/connectivityMap/ConnectivityMap.o \
    $O/castalia/src/node/application/simpleAggregation/SimpleAggregation.o \
    $O/castalia/src/node/application/throughputTest/ThroughputTest.o \
    $O/castalia/src/node/application/valuePropagation/ValuePropagation.o \
    $O/castalia/src/node/application/valueReporting/ValueReporting.o \
    $O/castalia/src/node/communication/mac/VirtualMac.o \
    $O/castalia/src/node/communication/mac/baselineBanMac/BaselineBANMac.o \
    $O/castalia/src/node/communication/mac/bypassMac/BypassMAC.o \
    $O/castalia/src/node/communication/mac/mac802154/Mac802154.o \
    $O/castalia/src/node/communication/mac/tMac/TMAC.o \
    $O/castalia/src/node/communication/mac/tunableMac/TunableMAC.o \
    $O/castalia/src/node/communication/radio/Radio.o \
    $O/castalia/src/node/communication/radio/RadioSupportFunctions.o \
    $O/castalia/src/node/communication/routing/VirtualRouting.o \
    $O/castalia/src/node/communication/routing/bypassRouting/BypassRouting.o \
    $O/castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRouting.o \
    $O/castalia/src/node/mobilityManager/VirtualMobilityManager.o \
    $O/castalia/src/node/mobilityManager/lineMobilityManager/LineMobilityManager.o \
    $O/castalia/src/node/mobilityManager/noMobilityManager/NoMobilityManager.o \
    $O/castalia/src/node/resourceManager/ResourceManager.o \
    $O/castalia/src/physicalProcess/carsPhysicalProcess/CarsPhysicalProcess.o \
    $O/castalia/src/physicalProcess/customizablePhysicalProcess/CustomizablePhysicalProcess.o \
    $O/castalia/src/wirelessChannel/WirelessChannelTemporal.o \
    $O/castalia/src/wirelessChannel/WirelessChannel.o \
    $O/wise/src/node/application/wiseBaseApp/WiseBaseApp.o \
    $O/wise/src/node/application/wiseBaseAppTest/WiseBaseAppTest.o \
    $O/wise/src/node/application/wiseCameraApp/WiseCameraApp.o \
    $O/wise/src/node/application/wiseCameraAppTest/WiseCameraAppTest.o \
    $O/wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicApp.o \
    $O/wise/src/node/application/wiseCameraPeriodicAppDet/WiseCameraPeriodicAppDet.o \
    $O/wise/src/node/application/wiseCameraPeriodicAppTest/WiseCameraPeriodicAppTest.o \
    $O/wise/src/node/application/wiseCameraPeriodicAppTracker/WiseCameraPeriodicAppTracker.o \
    $O/wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/WiseMultiCameraPeriodicApp_DPF.o \
    $O/wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICF_utils.o \
    $O/wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICF.o \
    $O/wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/WiseMultiCameraPeriodicApp_KCF.o \
    $O/wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTIC_utils.o \
    $O/wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTIC.o \
    $O/wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/WiseMultiCameraPeriodicApp_ReID.o \
    $O/wise/src/node/resourceManager/WiseResourceManager.o \
    $O/wise/src/node/resourceManager/WiseResourceManager_utils.o \
    $O/wise/src/node/sensorManager/WiseBaseSensorManager.o \
    $O/wise/src/node/sensorManager/sensorManager/SensorManager.o \
    $O/wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.o \
    $O/wise/src/node/sensorManager/wiseCameraManager/xmlUtil.o \
    $O/wise/src/node/sensorManager/wiseCameraManager/cameraModel.o \
    $O/wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetections.o \
    $O/wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideo.o \
    $O/wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.o \
    $O/wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorManager.o \
    $O/wise/src/utils/PropertyFileReader.o \
    $O/wise/src/utils/WiseDebug.o \
    $O/wise/src/utils/WiseUtils.o \
    $O/wise/src/utils/WiseGTreader.o \
    $O/wise/src/utils/gmm/wise_utils_gmm.o \
    $O/wise/src/wirelessChannel/WiseDummyWirelessChannel.o \
    $O/wise/src/world/gui/WiseGuiWorld.o \
    $O/wise/src/world/gui/opencv/WiseGuiWorldOpencv.o \
    $O/wise/src/world/physicalProcess/WiseBasePhysicalProcess.o \
    $O/wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTarget.o \
    $O/wise/src/world/physicalProcess/wiseVideoFile/WiseVideoFile.o \
    $O/wise/src/world/terrain/WiseBaseTerrain.o \
    $O/wise/src/world/terrain/wiseTerrainCalibrated/WiseTerrainCalibrated.o \
    $O/wise/src/world/terrain/wiseTerrainEmpty/WiseTerrainEmpty.o \
    $O/castalia/src/helpStructures/TimerServiceMessage_m.o \
    $O/castalia/src/node/application/ApplicationPacket_m.o \
    $O/castalia/src/node/application/valueReporting/ValueReportingPacket_m.o \
    $O/castalia/src/node/communication/mac/MacPacket_m.o \
    $O/castalia/src/node/communication/mac/baselineBanMac/BaselineMacPacket_m.o \
    $O/castalia/src/node/communication/mac/bypassMac/BypassMacPacket_m.o \
    $O/castalia/src/node/communication/mac/mac802154/Mac802154Packet_m.o \
    $O/castalia/src/node/communication/mac/tMac/TMacPacket_m.o \
    $O/castalia/src/node/communication/mac/tMac/TMacControlMessage_m.o \
    $O/castalia/src/node/communication/mac/tunableMac/TunableMacPacket_m.o \
    $O/castalia/src/node/communication/mac/tunableMac/TunableMacControl_m.o \
    $O/castalia/src/node/communication/radio/RadioControlMessage_m.o \
    $O/castalia/src/node/communication/routing/RoutingPacket_m.o \
    $O/castalia/src/node/communication/routing/bypassRouting/BypassRoutingPacket_m.o \
    $O/castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingControl_m.o \
    $O/castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingPacket_m.o \
    $O/castalia/src/node/mobilityManager/MobilityManagerMessage_m.o \
    $O/castalia/src/node/resourceManager/ResourceManagerMessage_m.o \
    $O/castalia/src/physicalProcess/PhysicalProcessMessage_m.o \
    $O/castalia/src/wirelessChannel/WirelessChannelMessages_m.o \
    $O/wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.o \
    $O/wise/src/node/application/wiseCameraAppTest/WiseCameraAppTestPacket_m.o \
    $O/wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.o \
    $O/wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/WiseMultiCameraPeriodicApp_DPFPacket_m.o \
    $O/wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICFPacket_m.o \
    $O/wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/WiseMultiCameraPeriodicApp_KCFPacket_m.o \
    $O/wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTICPacket_m.o \
    $O/wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/WiseMultiCameraPeriodicApp_ReIDPacket_m.o \
    $O/wise/src/node/resourceManager/WiseResourceManagerMessage_m.o \
    $O/wise/src/node/sensorManager/WiseSensorManagerMessage_m.o \
    $O/wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.o \
    $O/wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.o \
    $O/wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.o \
    $O/wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.o \
    $O/wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorMessage_m.o \
    $O/wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.o \
    $O/wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.o \
    $O/wise/src/world/physicalProcess/wiseVideoFile/WiseVideoFileMessage_m.o

# Message files
MSGFILES = \
    castalia/src/helpStructures/TimerServiceMessage.msg \
    castalia/src/node/application/ApplicationPacket.msg \
    castalia/src/node/application/valueReporting/ValueReportingPacket.msg \
    castalia/src/node/communication/mac/MacPacket.msg \
    castalia/src/node/communication/mac/baselineBanMac/BaselineMacPacket.msg \
    castalia/src/node/communication/mac/bypassMac/BypassMacPacket.msg \
    castalia/src/node/communication/mac/mac802154/Mac802154Packet.msg \
    castalia/src/node/communication/mac/tMac/TMacPacket.msg \
    castalia/src/node/communication/mac/tMac/TMacControlMessage.msg \
    castalia/src/node/communication/mac/tunableMac/TunableMacPacket.msg \
    castalia/src/node/communication/mac/tunableMac/TunableMacControl.msg \
    castalia/src/node/communication/radio/RadioControlMessage.msg \
    castalia/src/node/communication/routing/RoutingPacket.msg \
    castalia/src/node/communication/routing/bypassRouting/BypassRoutingPacket.msg \
    castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingControl.msg \
    castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingPacket.msg \
    castalia/src/node/mobilityManager/MobilityManagerMessage.msg \
    castalia/src/node/resourceManager/ResourceManagerMessage.msg \
    castalia/src/physicalProcess/PhysicalProcessMessage.msg \
    castalia/src/wirelessChannel/WirelessChannelMessages.msg \
    wise/src/node/application/wiseBaseApp/WiseBaseAppPacket.msg \
    wise/src/node/application/wiseCameraAppTest/WiseCameraAppTestPacket.msg \
    wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket.msg \
    wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/WiseMultiCameraPeriodicApp_DPFPacket.msg \
    wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICFPacket.msg \
    wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/WiseMultiCameraPeriodicApp_KCFPacket.msg \
    wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTICPacket.msg \
    wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/WiseMultiCameraPeriodicApp_ReIDPacket.msg \
    wise/src/node/resourceManager/WiseResourceManagerMessage.msg \
    wise/src/node/sensorManager/WiseSensorManagerMessage.msg \
    wise/src/node/sensorManager/sensorManager/SensorManagerMessage.msg \
    wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage.msg \
    wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage.msg \
    wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage.msg \
    wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorMessage.msg \
    wise/src/world/physicalProcess/WisePhysicalProcessMessage.msg \
    wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage.msg \
    wise/src/world/physicalProcess/wiseVideoFile/WiseVideoFileMessage.msg

# SM files
SMFILES =

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)
SMCOPTS =

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders smheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

%_sm.cc %_sm.h: %.sm
	$(qecho) SMC: $<
	$(Q)$(SMC) -c++ -suffix cc $(SMCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

smheaders: $(SMFILES:.sm=_sm.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f wisemnet-v1.4 wisemnet-v1.4.exe libwisemnet-v1.4.so libwisemnet-v1.4.a libwisemnet-v1.4.dll libwisemnet-v1.4.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h ./*_sm.cc ./*_sm.h
	$(Q)-rm -f castalia/*_m.cc castalia/*_m.h castalia/*_sm.cc castalia/*_sm.h
	$(Q)-rm -f castalia/Simulations/*_m.cc castalia/Simulations/*_m.h castalia/Simulations/*_sm.cc castalia/Simulations/*_sm.h
	$(Q)-rm -f castalia/Simulations/BANtest/*_m.cc castalia/Simulations/BANtest/*_m.h castalia/Simulations/BANtest/*_sm.cc castalia/Simulations/BANtest/*_sm.h
	$(Q)-rm -f castalia/Simulations/BridgeTest/*_m.cc castalia/Simulations/BridgeTest/*_m.h castalia/Simulations/BridgeTest/*_sm.cc castalia/Simulations/BridgeTest/*_sm.h
	$(Q)-rm -f castalia/Simulations/Parameters/*_m.cc castalia/Simulations/Parameters/*_m.h castalia/Simulations/Parameters/*_sm.cc castalia/Simulations/Parameters/*_sm.h
	$(Q)-rm -f castalia/Simulations/Parameters/MAC/*_m.cc castalia/Simulations/Parameters/MAC/*_m.h castalia/Simulations/Parameters/MAC/*_sm.cc castalia/Simulations/Parameters/MAC/*_sm.h
	$(Q)-rm -f castalia/Simulations/Parameters/Radio/*_m.cc castalia/Simulations/Parameters/Radio/*_m.h castalia/Simulations/Parameters/Radio/*_sm.cc castalia/Simulations/Parameters/Radio/*_sm.h
	$(Q)-rm -f castalia/Simulations/Parameters/SensorDevice/*_m.cc castalia/Simulations/Parameters/SensorDevice/*_m.h castalia/Simulations/Parameters/SensorDevice/*_sm.cc castalia/Simulations/Parameters/SensorDevice/*_sm.h
	$(Q)-rm -f castalia/Simulations/Parameters/WirelessChannel/*_m.cc castalia/Simulations/Parameters/WirelessChannel/*_m.h castalia/Simulations/Parameters/WirelessChannel/*_sm.cc castalia/Simulations/Parameters/WirelessChannel/*_sm.h
	$(Q)-rm -f castalia/Simulations/Parameters/WirelessChannel/BANmodels/*_m.cc castalia/Simulations/Parameters/WirelessChannel/BANmodels/*_m.h castalia/Simulations/Parameters/WirelessChannel/BANmodels/*_sm.cc castalia/Simulations/Parameters/WirelessChannel/BANmodels/*_sm.h
	$(Q)-rm -f castalia/Simulations/connectivityMap/*_m.cc castalia/Simulations/connectivityMap/*_m.h castalia/Simulations/connectivityMap/*_sm.cc castalia/Simulations/connectivityMap/*_sm.h
	$(Q)-rm -f castalia/Simulations/radioTest/*_m.cc castalia/Simulations/radioTest/*_m.h castalia/Simulations/radioTest/*_sm.cc castalia/Simulations/radioTest/*_sm.h
	$(Q)-rm -f castalia/Simulations/simpleAggregation/*_m.cc castalia/Simulations/simpleAggregation/*_m.h castalia/Simulations/simpleAggregation/*_sm.cc castalia/Simulations/simpleAggregation/*_sm.h
	$(Q)-rm -f castalia/Simulations/valuePropagation/*_m.cc castalia/Simulations/valuePropagation/*_m.h castalia/Simulations/valuePropagation/*_sm.cc castalia/Simulations/valuePropagation/*_sm.h
	$(Q)-rm -f castalia/Simulations/valueReporting/*_m.cc castalia/Simulations/valueReporting/*_m.h castalia/Simulations/valueReporting/*_sm.cc castalia/Simulations/valueReporting/*_sm.h
	$(Q)-rm -f castalia/scripts/*_m.cc castalia/scripts/*_m.h castalia/scripts/*_sm.cc castalia/scripts/*_sm.h
	$(Q)-rm -f castalia/src/*_m.cc castalia/src/*_m.h castalia/src/*_sm.cc castalia/src/*_sm.h
	$(Q)-rm -f castalia/src/helpStructures/*_m.cc castalia/src/helpStructures/*_m.h castalia/src/helpStructures/*_sm.cc castalia/src/helpStructures/*_sm.h
	$(Q)-rm -f castalia/src/node/*_m.cc castalia/src/node/*_m.h castalia/src/node/*_sm.cc castalia/src/node/*_sm.h
	$(Q)-rm -f castalia/src/node/application/*_m.cc castalia/src/node/application/*_m.h castalia/src/node/application/*_sm.cc castalia/src/node/application/*_sm.h
	$(Q)-rm -f castalia/src/node/application/bridgeTest/*_m.cc castalia/src/node/application/bridgeTest/*_m.h castalia/src/node/application/bridgeTest/*_sm.cc castalia/src/node/application/bridgeTest/*_sm.h
	$(Q)-rm -f castalia/src/node/application/connectivityMap/*_m.cc castalia/src/node/application/connectivityMap/*_m.h castalia/src/node/application/connectivityMap/*_sm.cc castalia/src/node/application/connectivityMap/*_sm.h
	$(Q)-rm -f castalia/src/node/application/simpleAggregation/*_m.cc castalia/src/node/application/simpleAggregation/*_m.h castalia/src/node/application/simpleAggregation/*_sm.cc castalia/src/node/application/simpleAggregation/*_sm.h
	$(Q)-rm -f castalia/src/node/application/throughputTest/*_m.cc castalia/src/node/application/throughputTest/*_m.h castalia/src/node/application/throughputTest/*_sm.cc castalia/src/node/application/throughputTest/*_sm.h
	$(Q)-rm -f castalia/src/node/application/valuePropagation/*_m.cc castalia/src/node/application/valuePropagation/*_m.h castalia/src/node/application/valuePropagation/*_sm.cc castalia/src/node/application/valuePropagation/*_sm.h
	$(Q)-rm -f castalia/src/node/application/valueReporting/*_m.cc castalia/src/node/application/valueReporting/*_m.h castalia/src/node/application/valueReporting/*_sm.cc castalia/src/node/application/valueReporting/*_sm.h
	$(Q)-rm -f castalia/src/node/communication/*_m.cc castalia/src/node/communication/*_m.h castalia/src/node/communication/*_sm.cc castalia/src/node/communication/*_sm.h
	$(Q)-rm -f castalia/src/node/communication/mac/*_m.cc castalia/src/node/communication/mac/*_m.h castalia/src/node/communication/mac/*_sm.cc castalia/src/node/communication/mac/*_sm.h
	$(Q)-rm -f castalia/src/node/communication/mac/baselineBanMac/*_m.cc castalia/src/node/communication/mac/baselineBanMac/*_m.h castalia/src/node/communication/mac/baselineBanMac/*_sm.cc castalia/src/node/communication/mac/baselineBanMac/*_sm.h
	$(Q)-rm -f castalia/src/node/communication/mac/bypassMac/*_m.cc castalia/src/node/communication/mac/bypassMac/*_m.h castalia/src/node/communication/mac/bypassMac/*_sm.cc castalia/src/node/communication/mac/bypassMac/*_sm.h
	$(Q)-rm -f castalia/src/node/communication/mac/mac802154/*_m.cc castalia/src/node/communication/mac/mac802154/*_m.h castalia/src/node/communication/mac/mac802154/*_sm.cc castalia/src/node/communication/mac/mac802154/*_sm.h
	$(Q)-rm -f castalia/src/node/communication/mac/tMac/*_m.cc castalia/src/node/communication/mac/tMac/*_m.h castalia/src/node/communication/mac/tMac/*_sm.cc castalia/src/node/communication/mac/tMac/*_sm.h
	$(Q)-rm -f castalia/src/node/communication/mac/tunableMac/*_m.cc castalia/src/node/communication/mac/tunableMac/*_m.h castalia/src/node/communication/mac/tunableMac/*_sm.cc castalia/src/node/communication/mac/tunableMac/*_sm.h
	$(Q)-rm -f castalia/src/node/communication/radio/*_m.cc castalia/src/node/communication/radio/*_m.h castalia/src/node/communication/radio/*_sm.cc castalia/src/node/communication/radio/*_sm.h
	$(Q)-rm -f castalia/src/node/communication/routing/*_m.cc castalia/src/node/communication/routing/*_m.h castalia/src/node/communication/routing/*_sm.cc castalia/src/node/communication/routing/*_sm.h
	$(Q)-rm -f castalia/src/node/communication/routing/bypassRouting/*_m.cc castalia/src/node/communication/routing/bypassRouting/*_m.h castalia/src/node/communication/routing/bypassRouting/*_sm.cc castalia/src/node/communication/routing/bypassRouting/*_sm.h
	$(Q)-rm -f castalia/src/node/communication/routing/multipathRingsRouting/*_m.cc castalia/src/node/communication/routing/multipathRingsRouting/*_m.h castalia/src/node/communication/routing/multipathRingsRouting/*_sm.cc castalia/src/node/communication/routing/multipathRingsRouting/*_sm.h
	$(Q)-rm -f castalia/src/node/mobilityManager/*_m.cc castalia/src/node/mobilityManager/*_m.h castalia/src/node/mobilityManager/*_sm.cc castalia/src/node/mobilityManager/*_sm.h
	$(Q)-rm -f castalia/src/node/mobilityManager/lineMobilityManager/*_m.cc castalia/src/node/mobilityManager/lineMobilityManager/*_m.h castalia/src/node/mobilityManager/lineMobilityManager/*_sm.cc castalia/src/node/mobilityManager/lineMobilityManager/*_sm.h
	$(Q)-rm -f castalia/src/node/mobilityManager/noMobilityManager/*_m.cc castalia/src/node/mobilityManager/noMobilityManager/*_m.h castalia/src/node/mobilityManager/noMobilityManager/*_sm.cc castalia/src/node/mobilityManager/noMobilityManager/*_sm.h
	$(Q)-rm -f castalia/src/node/resourceManager/*_m.cc castalia/src/node/resourceManager/*_m.h castalia/src/node/resourceManager/*_sm.cc castalia/src/node/resourceManager/*_sm.h
	$(Q)-rm -f castalia/src/physicalProcess/*_m.cc castalia/src/physicalProcess/*_m.h castalia/src/physicalProcess/*_sm.cc castalia/src/physicalProcess/*_sm.h
	$(Q)-rm -f castalia/src/physicalProcess/carsPhysicalProcess/*_m.cc castalia/src/physicalProcess/carsPhysicalProcess/*_m.h castalia/src/physicalProcess/carsPhysicalProcess/*_sm.cc castalia/src/physicalProcess/carsPhysicalProcess/*_sm.h
	$(Q)-rm -f castalia/src/physicalProcess/customizablePhysicalProcess/*_m.cc castalia/src/physicalProcess/customizablePhysicalProcess/*_m.h castalia/src/physicalProcess/customizablePhysicalProcess/*_sm.cc castalia/src/physicalProcess/customizablePhysicalProcess/*_sm.h
	$(Q)-rm -f castalia/src/wirelessChannel/*_m.cc castalia/src/wirelessChannel/*_m.h castalia/src/wirelessChannel/*_sm.cc castalia/src/wirelessChannel/*_sm.h
	$(Q)-rm -f doc/*_m.cc doc/*_m.h doc/*_sm.cc doc/*_sm.h
	$(Q)-rm -f doc/html/*_m.cc doc/html/*_m.h doc/html/*_sm.cc doc/html/*_sm.h
	$(Q)-rm -f doc/html/search/*_m.cc doc/html/search/*_m.h doc/html/search/*_sm.cc doc/html/search/*_sm.h
	$(Q)-rm -f doc/manual/*_m.cc doc/manual/*_m.h doc/manual/*_sm.cc doc/manual/*_sm.h
	$(Q)-rm -f doc/manual/figures/*_m.cc doc/manual/figures/*_m.h doc/manual/figures/*_sm.cc doc/manual/figures/*_sm.h
	$(Q)-rm -f doc/pdfs/*_m.cc doc/pdfs/*_m.h doc/pdfs/*_sm.cc doc/pdfs/*_sm.h
	$(Q)-rm -f models/*_m.cc models/*_m.h models/*_sm.cc models/*_sm.h
	$(Q)-rm -f models/COM/*_m.cc models/COM/*_m.h models/COM/*_sm.cc models/COM/*_sm.h
	$(Q)-rm -f models/CPU/*_m.cc models/CPU/*_m.h models/CPU/*_sm.cc models/CPU/*_sm.h
	$(Q)-rm -f models/SEN/*_m.cc models/SEN/*_m.h models/SEN/*_sm.cc models/SEN/*_sm.h
	$(Q)-rm -f utils/*_m.cc utils/*_m.h utils/*_sm.cc utils/*_sm.h
	$(Q)-rm -f videos/*_m.cc videos/*_m.h videos/*_sm.cc videos/*_sm.h
	$(Q)-rm -f videos/Crowd_PETS09/*_m.cc videos/Crowd_PETS09/*_m.h videos/Crowd_PETS09/*_sm.cc videos/Crowd_PETS09/*_sm.h
	$(Q)-rm -f videos/Crowd_PETS09/S2/*_m.cc videos/Crowd_PETS09/S2/*_m.h videos/Crowd_PETS09/S2/*_sm.cc videos/Crowd_PETS09/S2/*_sm.h
	$(Q)-rm -f videos/Crowd_PETS09/S2/L1/*_m.cc videos/Crowd_PETS09/S2/L1/*_m.h videos/Crowd_PETS09/S2/L1/*_sm.cc videos/Crowd_PETS09/S2/L1/*_sm.h
	$(Q)-rm -f videos/Crowd_PETS09/S2/L1/Groundtruth/*_m.cc videos/Crowd_PETS09/S2/L1/Groundtruth/*_m.h videos/Crowd_PETS09/S2/L1/Groundtruth/*_sm.cc videos/Crowd_PETS09/S2/L1/Groundtruth/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/*_m.cc videos/HDA_Dataset_V1.3/*_m.h videos/HDA_Dataset_V1.3/*_sm.cc videos/HDA_Dataset_V1.3/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_annotations/*_m.cc videos/HDA_Dataset_V1.3/hda_annotations/*_m.h videos/HDA_Dataset_V1.3/hda_annotations/*_sm.cc videos/HDA_Dataset_V1.3/hda_annotations/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/FPClass/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/FPClass/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/FPClass/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/FPClass/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera17/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera17/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera17/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera17/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera17/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera17/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera17/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera17/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera18/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera18/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera18/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera18/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera18/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera18/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera18/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera18/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera19/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera19/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera19/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera19/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera19/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera19/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera19/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera19/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera40/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera40/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera40/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera40/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera40/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera40/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera40/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera40/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera50/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera50/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera50/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera50/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera50/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera50/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera50/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera50/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera53/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera53/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera53/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera53/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera53/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera53/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera53/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera53/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera54/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera54/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera54/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera54/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera54/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera54/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera54/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera54/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera56/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera56/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera56/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera56/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera56/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera56/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera56/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera56/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera57/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera57/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera57/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera57/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera57/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera57/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera57/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera57/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera58/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera58/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera58/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera58/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera58/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera58/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera58/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera58/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera59/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera59/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera59/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera59/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera59/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera59/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera59/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera59/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera60/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera60/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera60/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera60/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera60/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera60/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera60/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera60/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera17/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera17/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera17/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera17/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera17/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera17/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera17/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera17/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera18/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera18/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera18/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera18/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera18/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera18/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera18/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera18/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera19/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera19/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera19/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera19/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera19/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera19/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera19/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera19/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera40/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera40/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera40/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera40/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera40/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera40/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera40/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera40/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera50/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera50/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera50/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera50/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera50/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera50/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera50/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera50/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera53/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera53/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera53/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera53/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera53/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera53/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera53/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera53/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera54/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera54/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera54/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera54/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera54/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera54/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera54/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera54/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera56/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera56/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera56/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera56/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera56/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera56/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera56/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera56/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera57/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera57/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera57/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera57/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera57/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera57/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera57/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera57/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera58/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera58/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera58/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera58/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera58/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera58/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera58/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera58/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera59/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera59/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera59/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera59/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera59/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera59/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera59/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera59/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera60/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera60/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera60/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera60/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera60/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera60/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera60/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera60/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera17/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera17/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera17/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera17/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera17/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera17/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera17/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera17/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera18/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera18/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera18/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera18/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera18/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera18/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera18/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera18/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera19/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera19/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera19/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera19/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera19/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera19/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera19/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera19/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera40/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera40/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera40/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera40/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera40/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera40/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera40/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera40/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera50/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera50/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera50/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera50/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera50/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera50/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera50/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera50/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera53/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera53/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera53/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera53/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera53/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera53/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera53/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera53/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera54/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera54/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera54/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera54/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera54/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera54/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera54/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera54/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera56/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera56/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera56/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera56/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera56/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera56/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera56/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera56/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera57/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera57/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera57/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera57/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera57/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera57/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera57/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera57/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera58/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera58/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera58/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera58/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera58/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera58/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera58/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera58/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera59/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera59/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera59/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera59/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera59/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera59/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera59/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera59/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera60/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera60/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera60/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera60/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera60/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera60/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera60/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera60/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/Toy3/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/Toy3/*_m.h videos/HDA_Dataset_V1.3/hda_detections/Toy3/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/Toy3/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/Toy3/camera60/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/Toy3/camera60/*_m.h videos/HDA_Dataset_V1.3/hda_detections/Toy3/camera60/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/Toy3/camera60/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/Toy3/camera60/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/Toy3/camera60/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/Toy3/camera60/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/Toy3/camera60/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/Toy8/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/Toy8/*_m.h videos/HDA_Dataset_V1.3/hda_detections/Toy8/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/Toy8/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/Toy8/camera60/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/Toy8/camera60/*_m.h videos/HDA_Dataset_V1.3/hda_detections/Toy8/camera60/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/Toy8/camera60/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_detections/Toy8/camera60/Detections/*_m.cc videos/HDA_Dataset_V1.3/hda_detections/Toy8/camera60/Detections/*_m.h videos/HDA_Dataset_V1.3/hda_detections/Toy8/camera60/Detections/*_sm.cc videos/HDA_Dataset_V1.3/hda_detections/Toy8/camera60/Detections/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_docs/*_m.cc videos/HDA_Dataset_V1.3/hda_docs/*_m.h videos/HDA_Dataset_V1.3/hda_docs/*_sm.cc videos/HDA_Dataset_V1.3/hda_docs/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_homographies/*_m.cc videos/HDA_Dataset_V1.3/hda_homographies/*_m.h videos/HDA_Dataset_V1.3/hda_homographies/*_sm.cc videos/HDA_Dataset_V1.3/hda_homographies/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/*_m.cc videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/*_m.h videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/*_sm.cc videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_sample_train_data/*_m.cc videos/HDA_Dataset_V1.3/hda_sample_train_data/*_m.h videos/HDA_Dataset_V1.3/hda_sample_train_data/*_sm.cc videos/HDA_Dataset_V1.3/hda_sample_train_data/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_sample_train_data_toy3/*_m.cc videos/HDA_Dataset_V1.3/hda_sample_train_data_toy3/*_m.h videos/HDA_Dataset_V1.3/hda_sample_train_data_toy3/*_sm.cc videos/HDA_Dataset_V1.3/hda_sample_train_data_toy3/*_sm.h
	$(Q)-rm -f videos/HDA_Dataset_V1.3/hda_sample_train_data_toy8/*_m.cc videos/HDA_Dataset_V1.3/hda_sample_train_data_toy8/*_m.h videos/HDA_Dataset_V1.3/hda_sample_train_data_toy8/*_sm.cc videos/HDA_Dataset_V1.3/hda_sample_train_data_toy8/*_sm.h
	$(Q)-rm -f videos/ICGLab6/*_m.cc videos/ICGLab6/*_m.h videos/ICGLab6/*_sm.cc videos/ICGLab6/*_sm.h
	$(Q)-rm -f videos/ICGLab6/calibration/*_m.cc videos/ICGLab6/calibration/*_m.h videos/ICGLab6/calibration/*_sm.cc videos/ICGLab6/calibration/*_sm.h
	$(Q)-rm -f videos/ICGLab6/chap/*_m.cc videos/ICGLab6/chap/*_m.h videos/ICGLab6/chap/*_sm.cc videos/ICGLab6/chap/*_sm.h
	$(Q)-rm -f videos/ICGLab6/chap/Groundtruth/*_m.cc videos/ICGLab6/chap/Groundtruth/*_m.h videos/ICGLab6/chap/Groundtruth/*_sm.cc videos/ICGLab6/chap/Groundtruth/*_sm.h
	$(Q)-rm -f videos/vot2017/*_m.cc videos/vot2017/*_m.h videos/vot2017/*_sm.cc videos/vot2017/*_sm.h
	$(Q)-rm -f videos/vot2017/ants1/*_m.cc videos/vot2017/ants1/*_m.h videos/vot2017/ants1/*_sm.cc videos/vot2017/ants1/*_sm.h
	$(Q)-rm -f videos/vot2017/ants3/*_m.cc videos/vot2017/ants3/*_m.h videos/vot2017/ants3/*_sm.cc videos/vot2017/ants3/*_sm.h
	$(Q)-rm -f videos/vot2017/bag/*_m.cc videos/vot2017/bag/*_m.h videos/vot2017/bag/*_sm.cc videos/vot2017/bag/*_sm.h
	$(Q)-rm -f videos/vot2017/ball1/*_m.cc videos/vot2017/ball1/*_m.h videos/vot2017/ball1/*_sm.cc videos/vot2017/ball1/*_sm.h
	$(Q)-rm -f videos/vot2017/ball2/*_m.cc videos/vot2017/ball2/*_m.h videos/vot2017/ball2/*_sm.cc videos/vot2017/ball2/*_sm.h
	$(Q)-rm -f videos/vot2017/basketball/*_m.cc videos/vot2017/basketball/*_m.h videos/vot2017/basketball/*_sm.cc videos/vot2017/basketball/*_sm.h
	$(Q)-rm -f videos/vot2017/birds1/*_m.cc videos/vot2017/birds1/*_m.h videos/vot2017/birds1/*_sm.cc videos/vot2017/birds1/*_sm.h
	$(Q)-rm -f videos/vot2017/blanket/*_m.cc videos/vot2017/blanket/*_m.h videos/vot2017/blanket/*_sm.cc videos/vot2017/blanket/*_sm.h
	$(Q)-rm -f videos/vot2017/bmx/*_m.cc videos/vot2017/bmx/*_m.h videos/vot2017/bmx/*_sm.cc videos/vot2017/bmx/*_sm.h
	$(Q)-rm -f videos/vot2017/bolt1/*_m.cc videos/vot2017/bolt1/*_m.h videos/vot2017/bolt1/*_sm.cc videos/vot2017/bolt1/*_sm.h
	$(Q)-rm -f videos/vot2017/bolt2/*_m.cc videos/vot2017/bolt2/*_m.h videos/vot2017/bolt2/*_sm.cc videos/vot2017/bolt2/*_sm.h
	$(Q)-rm -f videos/vot2017/book/*_m.cc videos/vot2017/book/*_m.h videos/vot2017/book/*_sm.cc videos/vot2017/book/*_sm.h
	$(Q)-rm -f videos/vot2017/butterfly/*_m.cc videos/vot2017/butterfly/*_m.h videos/vot2017/butterfly/*_sm.cc videos/vot2017/butterfly/*_sm.h
	$(Q)-rm -f videos/vot2017/car1/*_m.cc videos/vot2017/car1/*_m.h videos/vot2017/car1/*_sm.cc videos/vot2017/car1/*_sm.h
	$(Q)-rm -f videos/vot2017/conduction1/*_m.cc videos/vot2017/conduction1/*_m.h videos/vot2017/conduction1/*_sm.cc videos/vot2017/conduction1/*_sm.h
	$(Q)-rm -f videos/vot2017/crabs1/*_m.cc videos/vot2017/crabs1/*_m.h videos/vot2017/crabs1/*_sm.cc videos/vot2017/crabs1/*_sm.h
	$(Q)-rm -f videos/vot2017/crossing/*_m.cc videos/vot2017/crossing/*_m.h videos/vot2017/crossing/*_sm.cc videos/vot2017/crossing/*_sm.h
	$(Q)-rm -f videos/vot2017/dinosaur/*_m.cc videos/vot2017/dinosaur/*_m.h videos/vot2017/dinosaur/*_sm.cc videos/vot2017/dinosaur/*_sm.h
	$(Q)-rm -f videos/vot2017/drone1/*_m.cc videos/vot2017/drone1/*_m.h videos/vot2017/drone1/*_sm.cc videos/vot2017/drone1/*_sm.h
	$(Q)-rm -f videos/vot2017/drone_across/*_m.cc videos/vot2017/drone_across/*_m.h videos/vot2017/drone_across/*_sm.cc videos/vot2017/drone_across/*_sm.h
	$(Q)-rm -f videos/vot2017/drone_flip/*_m.cc videos/vot2017/drone_flip/*_m.h videos/vot2017/drone_flip/*_sm.cc videos/vot2017/drone_flip/*_sm.h
	$(Q)-rm -f videos/vot2017/fernando/*_m.cc videos/vot2017/fernando/*_m.h videos/vot2017/fernando/*_sm.cc videos/vot2017/fernando/*_sm.h
	$(Q)-rm -f videos/vot2017/fish1/*_m.cc videos/vot2017/fish1/*_m.h videos/vot2017/fish1/*_sm.cc videos/vot2017/fish1/*_sm.h
	$(Q)-rm -f videos/vot2017/fish2/*_m.cc videos/vot2017/fish2/*_m.h videos/vot2017/fish2/*_sm.cc videos/vot2017/fish2/*_sm.h
	$(Q)-rm -f videos/vot2017/fish3/*_m.cc videos/vot2017/fish3/*_m.h videos/vot2017/fish3/*_sm.cc videos/vot2017/fish3/*_sm.h
	$(Q)-rm -f videos/vot2017/flamingo1/*_m.cc videos/vot2017/flamingo1/*_m.h videos/vot2017/flamingo1/*_sm.cc videos/vot2017/flamingo1/*_sm.h
	$(Q)-rm -f videos/vot2017/frisbee/*_m.cc videos/vot2017/frisbee/*_m.h videos/vot2017/frisbee/*_sm.cc videos/vot2017/frisbee/*_sm.h
	$(Q)-rm -f videos/vot2017/girl/*_m.cc videos/vot2017/girl/*_m.h videos/vot2017/girl/*_sm.cc videos/vot2017/girl/*_sm.h
	$(Q)-rm -f videos/vot2017/glove/*_m.cc videos/vot2017/glove/*_m.h videos/vot2017/glove/*_sm.cc videos/vot2017/glove/*_sm.h
	$(Q)-rm -f videos/vot2017/godfather/*_m.cc videos/vot2017/godfather/*_m.h videos/vot2017/godfather/*_sm.cc videos/vot2017/godfather/*_sm.h
	$(Q)-rm -f videos/vot2017/graduate/*_m.cc videos/vot2017/graduate/*_m.h videos/vot2017/graduate/*_sm.cc videos/vot2017/graduate/*_sm.h
	$(Q)-rm -f videos/vot2017/gymnastics1/*_m.cc videos/vot2017/gymnastics1/*_m.h videos/vot2017/gymnastics1/*_sm.cc videos/vot2017/gymnastics1/*_sm.h
	$(Q)-rm -f videos/vot2017/gymnastics2/*_m.cc videos/vot2017/gymnastics2/*_m.h videos/vot2017/gymnastics2/*_sm.cc videos/vot2017/gymnastics2/*_sm.h
	$(Q)-rm -f videos/vot2017/gymnastics3/*_m.cc videos/vot2017/gymnastics3/*_m.h videos/vot2017/gymnastics3/*_sm.cc videos/vot2017/gymnastics3/*_sm.h
	$(Q)-rm -f videos/vot2017/hand/*_m.cc videos/vot2017/hand/*_m.h videos/vot2017/hand/*_sm.cc videos/vot2017/hand/*_sm.h
	$(Q)-rm -f videos/vot2017/handball1/*_m.cc videos/vot2017/handball1/*_m.h videos/vot2017/handball1/*_sm.cc videos/vot2017/handball1/*_sm.h
	$(Q)-rm -f videos/vot2017/handball2/*_m.cc videos/vot2017/handball2/*_m.h videos/vot2017/handball2/*_sm.cc videos/vot2017/handball2/*_sm.h
	$(Q)-rm -f videos/vot2017/helicopter/*_m.cc videos/vot2017/helicopter/*_m.h videos/vot2017/helicopter/*_sm.cc videos/vot2017/helicopter/*_sm.h
	$(Q)-rm -f videos/vot2017/iceskater1/*_m.cc videos/vot2017/iceskater1/*_m.h videos/vot2017/iceskater1/*_sm.cc videos/vot2017/iceskater1/*_sm.h
	$(Q)-rm -f videos/vot2017/iceskater2/*_m.cc videos/vot2017/iceskater2/*_m.h videos/vot2017/iceskater2/*_sm.cc videos/vot2017/iceskater2/*_sm.h
	$(Q)-rm -f videos/vot2017/leaves/*_m.cc videos/vot2017/leaves/*_m.h videos/vot2017/leaves/*_sm.cc videos/vot2017/leaves/*_sm.h
	$(Q)-rm -f videos/vot2017/matrix/*_m.cc videos/vot2017/matrix/*_m.h videos/vot2017/matrix/*_sm.cc videos/vot2017/matrix/*_sm.h
	$(Q)-rm -f videos/vot2017/motocross1/*_m.cc videos/vot2017/motocross1/*_m.h videos/vot2017/motocross1/*_sm.cc videos/vot2017/motocross1/*_sm.h
	$(Q)-rm -f videos/vot2017/motocross2/*_m.cc videos/vot2017/motocross2/*_m.h videos/vot2017/motocross2/*_sm.cc videos/vot2017/motocross2/*_sm.h
	$(Q)-rm -f videos/vot2017/nature/*_m.cc videos/vot2017/nature/*_m.h videos/vot2017/nature/*_sm.cc videos/vot2017/nature/*_sm.h
	$(Q)-rm -f videos/vot2017/pedestrian1/*_m.cc videos/vot2017/pedestrian1/*_m.h videos/vot2017/pedestrian1/*_sm.cc videos/vot2017/pedestrian1/*_sm.h
	$(Q)-rm -f videos/vot2017/rabbit/*_m.cc videos/vot2017/rabbit/*_m.h videos/vot2017/rabbit/*_sm.cc videos/vot2017/rabbit/*_sm.h
	$(Q)-rm -f videos/vot2017/racing/*_m.cc videos/vot2017/racing/*_m.h videos/vot2017/racing/*_sm.cc videos/vot2017/racing/*_sm.h
	$(Q)-rm -f videos/vot2017/road/*_m.cc videos/vot2017/road/*_m.h videos/vot2017/road/*_sm.cc videos/vot2017/road/*_sm.h
	$(Q)-rm -f videos/vot2017/shaking/*_m.cc videos/vot2017/shaking/*_m.h videos/vot2017/shaking/*_sm.cc videos/vot2017/shaking/*_sm.h
	$(Q)-rm -f videos/vot2017/sheep/*_m.cc videos/vot2017/sheep/*_m.h videos/vot2017/sheep/*_sm.cc videos/vot2017/sheep/*_sm.h
	$(Q)-rm -f videos/vot2017/singer2/*_m.cc videos/vot2017/singer2/*_m.h videos/vot2017/singer2/*_sm.cc videos/vot2017/singer2/*_sm.h
	$(Q)-rm -f videos/vot2017/singer3/*_m.cc videos/vot2017/singer3/*_m.h videos/vot2017/singer3/*_sm.cc videos/vot2017/singer3/*_sm.h
	$(Q)-rm -f videos/vot2017/soccer1/*_m.cc videos/vot2017/soccer1/*_m.h videos/vot2017/soccer1/*_sm.cc videos/vot2017/soccer1/*_sm.h
	$(Q)-rm -f videos/vot2017/soccer2/*_m.cc videos/vot2017/soccer2/*_m.h videos/vot2017/soccer2/*_sm.cc videos/vot2017/soccer2/*_sm.h
	$(Q)-rm -f videos/vot2017/soldier/*_m.cc videos/vot2017/soldier/*_m.h videos/vot2017/soldier/*_sm.cc videos/vot2017/soldier/*_sm.h
	$(Q)-rm -f videos/vot2017/tiger/*_m.cc videos/vot2017/tiger/*_m.h videos/vot2017/tiger/*_sm.cc videos/vot2017/tiger/*_sm.h
	$(Q)-rm -f videos/vot2017/traffic/*_m.cc videos/vot2017/traffic/*_m.h videos/vot2017/traffic/*_sm.cc videos/vot2017/traffic/*_sm.h
	$(Q)-rm -f videos/vot2017/wiper/*_m.cc videos/vot2017/wiper/*_m.h videos/vot2017/wiper/*_sm.cc videos/vot2017/wiper/*_sm.h
	$(Q)-rm -f videos/vot2017/zebrafish1/*_m.cc videos/vot2017/zebrafish1/*_m.h videos/vot2017/zebrafish1/*_sm.cc videos/vot2017/zebrafish1/*_sm.h
	$(Q)-rm -f wise/*_m.cc wise/*_m.h wise/*_sm.cc wise/*_sm.h
	$(Q)-rm -f wise/simulations/*_m.cc wise/simulations/*_m.h wise/simulations/*_sm.cc wise/simulations/*_sm.h
	$(Q)-rm -f wise/simulations/Tutorial_ICIP17/*_m.cc wise/simulations/Tutorial_ICIP17/*_m.h wise/simulations/Tutorial_ICIP17/*_sm.cc wise/simulations/Tutorial_ICIP17/*_sm.h
	$(Q)-rm -f wise/simulations/wiseMultiCameraPeriodicApp_DPF/*_m.cc wise/simulations/wiseMultiCameraPeriodicApp_DPF/*_m.h wise/simulations/wiseMultiCameraPeriodicApp_DPF/*_sm.cc wise/simulations/wiseMultiCameraPeriodicApp_DPF/*_sm.h
	$(Q)-rm -f wise/simulations/wiseMultiCameraPeriodicApp_DPF/res/*_m.cc wise/simulations/wiseMultiCameraPeriodicApp_DPF/res/*_m.h wise/simulations/wiseMultiCameraPeriodicApp_DPF/res/*_sm.cc wise/simulations/wiseMultiCameraPeriodicApp_DPF/res/*_sm.h
	$(Q)-rm -f wise/simulations/wiseMultiCameraPeriodicApp_ICF/*_m.cc wise/simulations/wiseMultiCameraPeriodicApp_ICF/*_m.h wise/simulations/wiseMultiCameraPeriodicApp_ICF/*_sm.cc wise/simulations/wiseMultiCameraPeriodicApp_ICF/*_sm.h
	$(Q)-rm -f wise/simulations/wiseMultiCameraPeriodicApp_ICF/res/*_m.cc wise/simulations/wiseMultiCameraPeriodicApp_ICF/res/*_m.h wise/simulations/wiseMultiCameraPeriodicApp_ICF/res/*_sm.cc wise/simulations/wiseMultiCameraPeriodicApp_ICF/res/*_sm.h
	$(Q)-rm -f wise/simulations/wiseMultiCameraPeriodicApp_ICF/scripts/*_m.cc wise/simulations/wiseMultiCameraPeriodicApp_ICF/scripts/*_m.h wise/simulations/wiseMultiCameraPeriodicApp_ICF/scripts/*_sm.cc wise/simulations/wiseMultiCameraPeriodicApp_ICF/scripts/*_sm.h
	$(Q)-rm -f wise/simulations/wiseMultiCameraPeriodicApp_KCF/*_m.cc wise/simulations/wiseMultiCameraPeriodicApp_KCF/*_m.h wise/simulations/wiseMultiCameraPeriodicApp_KCF/*_sm.cc wise/simulations/wiseMultiCameraPeriodicApp_KCF/*_sm.h
	$(Q)-rm -f wise/simulations/wiseMultiCameraPeriodicApp_KCF/res/*_m.cc wise/simulations/wiseMultiCameraPeriodicApp_KCF/res/*_m.h wise/simulations/wiseMultiCameraPeriodicApp_KCF/res/*_sm.cc wise/simulations/wiseMultiCameraPeriodicApp_KCF/res/*_sm.h
	$(Q)-rm -f wise/simulations/wiseMultiCameraPeriodicApp_KCF/scripts/*_m.cc wise/simulations/wiseMultiCameraPeriodicApp_KCF/scripts/*_m.h wise/simulations/wiseMultiCameraPeriodicApp_KCF/scripts/*_sm.cc wise/simulations/wiseMultiCameraPeriodicApp_KCF/scripts/*_sm.h
	$(Q)-rm -f wise/simulations/wiseMultiCameraPeriodicApp_MTIC/*_m.cc wise/simulations/wiseMultiCameraPeriodicApp_MTIC/*_m.h wise/simulations/wiseMultiCameraPeriodicApp_MTIC/*_sm.cc wise/simulations/wiseMultiCameraPeriodicApp_MTIC/*_sm.h
	$(Q)-rm -f wise/simulations/wiseTest/*_m.cc wise/simulations/wiseTest/*_m.h wise/simulations/wiseTest/*_sm.cc wise/simulations/wiseTest/*_sm.h
	$(Q)-rm -f wise/simulations/wiseTest/res/*_m.cc wise/simulations/wiseTest/res/*_m.h wise/simulations/wiseTest/res/*_sm.cc wise/simulations/wiseTest/res/*_sm.h
	$(Q)-rm -f wise/src/*_m.cc wise/src/*_m.h wise/src/*_sm.cc wise/src/*_sm.h
	$(Q)-rm -f wise/src/node/*_m.cc wise/src/node/*_m.h wise/src/node/*_sm.cc wise/src/node/*_sm.h
	$(Q)-rm -f wise/src/node/application/*_m.cc wise/src/node/application/*_m.h wise/src/node/application/*_sm.cc wise/src/node/application/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseBaseApp/*_m.cc wise/src/node/application/wiseBaseApp/*_m.h wise/src/node/application/wiseBaseApp/*_sm.cc wise/src/node/application/wiseBaseApp/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseBaseAppTest/*_m.cc wise/src/node/application/wiseBaseAppTest/*_m.h wise/src/node/application/wiseBaseAppTest/*_sm.cc wise/src/node/application/wiseBaseAppTest/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraApp/*_m.cc wise/src/node/application/wiseCameraApp/*_m.h wise/src/node/application/wiseCameraApp/*_sm.cc wise/src/node/application/wiseCameraApp/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraAppTest/*_m.cc wise/src/node/application/wiseCameraAppTest/*_m.h wise/src/node/application/wiseCameraAppTest/*_sm.cc wise/src/node/application/wiseCameraAppTest/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraPeriodicApp/*_m.cc wise/src/node/application/wiseCameraPeriodicApp/*_m.h wise/src/node/application/wiseCameraPeriodicApp/*_sm.cc wise/src/node/application/wiseCameraPeriodicApp/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraPeriodicAppDet/*_m.cc wise/src/node/application/wiseCameraPeriodicAppDet/*_m.h wise/src/node/application/wiseCameraPeriodicAppDet/*_sm.cc wise/src/node/application/wiseCameraPeriodicAppDet/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraPeriodicAppTest/*_m.cc wise/src/node/application/wiseCameraPeriodicAppTest/*_m.h wise/src/node/application/wiseCameraPeriodicAppTest/*_sm.cc wise/src/node/application/wiseCameraPeriodicAppTest/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraPeriodicAppTracker/*_m.cc wise/src/node/application/wiseCameraPeriodicAppTracker/*_m.h wise/src/node/application/wiseCameraPeriodicAppTracker/*_sm.cc wise/src/node/application/wiseCameraPeriodicAppTracker/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/*_m.cc wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/*_m.h wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/*_sm.cc wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/*_m.cc wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/*_m.h wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/*_sm.cc wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/*_m.cc wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/*_m.h wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/*_sm.cc wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/*_m.cc wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/*_m.h wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/*_sm.cc wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/*_m.cc wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/*_m.h wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/*_sm.cc wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/*_sm.h
	$(Q)-rm -f wise/src/node/resourceManager/*_m.cc wise/src/node/resourceManager/*_m.h wise/src/node/resourceManager/*_sm.cc wise/src/node/resourceManager/*_sm.h
	$(Q)-rm -f wise/src/node/sensorManager/*_m.cc wise/src/node/sensorManager/*_m.h wise/src/node/sensorManager/*_sm.cc wise/src/node/sensorManager/*_sm.h
	$(Q)-rm -f wise/src/node/sensorManager/sensorManager/*_m.cc wise/src/node/sensorManager/sensorManager/*_m.h wise/src/node/sensorManager/sensorManager/*_sm.cc wise/src/node/sensorManager/sensorManager/*_sm.h
	$(Q)-rm -f wise/src/node/sensorManager/wiseCameraManager/*_m.cc wise/src/node/sensorManager/wiseCameraManager/*_m.h wise/src/node/sensorManager/wiseCameraManager/*_sm.cc wise/src/node/sensorManager/wiseCameraManager/*_sm.h
	$(Q)-rm -f wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/*_m.cc wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/*_m.h wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/*_sm.cc wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/*_sm.h
	$(Q)-rm -f wise/src/node/sensorManager/wiseEmptySensorManager/*_m.cc wise/src/node/sensorManager/wiseEmptySensorManager/*_m.h wise/src/node/sensorManager/wiseEmptySensorManager/*_sm.cc wise/src/node/sensorManager/wiseEmptySensorManager/*_sm.h
	$(Q)-rm -f wise/src/utils/*_m.cc wise/src/utils/*_m.h wise/src/utils/*_sm.cc wise/src/utils/*_sm.h
	$(Q)-rm -f wise/src/utils/gmm/*_m.cc wise/src/utils/gmm/*_m.h wise/src/utils/gmm/*_sm.cc wise/src/utils/gmm/*_sm.h
	$(Q)-rm -f wise/src/utils/gmm/c-gmm/*_m.cc wise/src/utils/gmm/c-gmm/*_m.h wise/src/utils/gmm/c-gmm/*_sm.cc wise/src/utils/gmm/c-gmm/*_sm.h
	$(Q)-rm -f wise/src/utils/libMvtnorm/*_m.cc wise/src/utils/libMvtnorm/*_m.h wise/src/utils/libMvtnorm/*_sm.cc wise/src/utils/libMvtnorm/*_sm.h
	$(Q)-rm -f wise/src/utils/libMvtnorm/libMvtnorm/*_m.cc wise/src/utils/libMvtnorm/libMvtnorm/*_m.h wise/src/utils/libMvtnorm/libMvtnorm/*_sm.cc wise/src/utils/libMvtnorm/libMvtnorm/*_sm.h
	$(Q)-rm -f wise/src/utils/pft/*_m.cc wise/src/utils/pft/*_m.h wise/src/utils/pft/*_sm.cc wise/src/utils/pft/*_sm.h
	$(Q)-rm -f wise/src/wirelessChannel/*_m.cc wise/src/wirelessChannel/*_m.h wise/src/wirelessChannel/*_sm.cc wise/src/wirelessChannel/*_sm.h
	$(Q)-rm -f wise/src/world/*_m.cc wise/src/world/*_m.h wise/src/world/*_sm.cc wise/src/world/*_sm.h
	$(Q)-rm -f wise/src/world/gui/*_m.cc wise/src/world/gui/*_m.h wise/src/world/gui/*_sm.cc wise/src/world/gui/*_sm.h
	$(Q)-rm -f wise/src/world/gui/opencv/*_m.cc wise/src/world/gui/opencv/*_m.h wise/src/world/gui/opencv/*_sm.cc wise/src/world/gui/opencv/*_sm.h
	$(Q)-rm -f wise/src/world/physicalProcess/*_m.cc wise/src/world/physicalProcess/*_m.h wise/src/world/physicalProcess/*_sm.cc wise/src/world/physicalProcess/*_sm.h
	$(Q)-rm -f wise/src/world/physicalProcess/wiseMovingTarget/*_m.cc wise/src/world/physicalProcess/wiseMovingTarget/*_m.h wise/src/world/physicalProcess/wiseMovingTarget/*_sm.cc wise/src/world/physicalProcess/wiseMovingTarget/*_sm.h
	$(Q)-rm -f wise/src/world/physicalProcess/wiseVideoFile/*_m.cc wise/src/world/physicalProcess/wiseVideoFile/*_m.h wise/src/world/physicalProcess/wiseVideoFile/*_sm.cc wise/src/world/physicalProcess/wiseVideoFile/*_sm.h
	$(Q)-rm -f wise/src/world/terrain/*_m.cc wise/src/world/terrain/*_m.h wise/src/world/terrain/*_sm.cc wise/src/world/terrain/*_sm.h
	$(Q)-rm -f wise/src/world/terrain/wiseTerrainCalibrated/*_m.cc wise/src/world/terrain/wiseTerrainCalibrated/*_m.h wise/src/world/terrain/wiseTerrainCalibrated/*_sm.cc wise/src/world/terrain/wiseTerrainCalibrated/*_sm.h
	$(Q)-rm -f wise/src/world/terrain/wiseTerrainEmpty/*_m.cc wise/src/world/terrain/wiseTerrainEmpty/*_m.h wise/src/world/terrain/wiseTerrainEmpty/*_sm.cc wise/src/world/terrain/wiseTerrainEmpty/*_sm.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES) $(SM_CC_FILES)  ./*.cc castalia/*.cc castalia/Simulations/*.cc castalia/Simulations/BANtest/*.cc castalia/Simulations/BridgeTest/*.cc castalia/Simulations/Parameters/*.cc castalia/Simulations/Parameters/MAC/*.cc castalia/Simulations/Parameters/Radio/*.cc castalia/Simulations/Parameters/SensorDevice/*.cc castalia/Simulations/Parameters/WirelessChannel/*.cc castalia/Simulations/Parameters/WirelessChannel/BANmodels/*.cc castalia/Simulations/connectivityMap/*.cc castalia/Simulations/radioTest/*.cc castalia/Simulations/simpleAggregation/*.cc castalia/Simulations/valuePropagation/*.cc castalia/Simulations/valueReporting/*.cc castalia/scripts/*.cc castalia/src/*.cc castalia/src/helpStructures/*.cc castalia/src/node/*.cc castalia/src/node/application/*.cc castalia/src/node/application/bridgeTest/*.cc castalia/src/node/application/connectivityMap/*.cc castalia/src/node/application/simpleAggregation/*.cc castalia/src/node/application/throughputTest/*.cc castalia/src/node/application/valuePropagation/*.cc castalia/src/node/application/valueReporting/*.cc castalia/src/node/communication/*.cc castalia/src/node/communication/mac/*.cc castalia/src/node/communication/mac/baselineBanMac/*.cc castalia/src/node/communication/mac/bypassMac/*.cc castalia/src/node/communication/mac/mac802154/*.cc castalia/src/node/communication/mac/tMac/*.cc castalia/src/node/communication/mac/tunableMac/*.cc castalia/src/node/communication/radio/*.cc castalia/src/node/communication/routing/*.cc castalia/src/node/communication/routing/bypassRouting/*.cc castalia/src/node/communication/routing/multipathRingsRouting/*.cc castalia/src/node/mobilityManager/*.cc castalia/src/node/mobilityManager/lineMobilityManager/*.cc castalia/src/node/mobilityManager/noMobilityManager/*.cc castalia/src/node/resourceManager/*.cc castalia/src/physicalProcess/*.cc castalia/src/physicalProcess/carsPhysicalProcess/*.cc castalia/src/physicalProcess/customizablePhysicalProcess/*.cc castalia/src/wirelessChannel/*.cc doc/*.cc doc/html/*.cc doc/html/search/*.cc doc/manual/*.cc doc/manual/figures/*.cc doc/pdfs/*.cc models/*.cc models/COM/*.cc models/CPU/*.cc models/SEN/*.cc utils/*.cc videos/*.cc videos/Crowd_PETS09/*.cc videos/Crowd_PETS09/S2/*.cc videos/Crowd_PETS09/S2/L1/*.cc videos/Crowd_PETS09/S2/L1/Groundtruth/*.cc videos/HDA_Dataset_V1.3/*.cc videos/HDA_Dataset_V1.3/hda_annotations/*.cc videos/HDA_Dataset_V1.3/hda_detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/FPClass/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera17/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera17/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera18/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera18/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera19/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera19/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera40/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera40/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera50/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera50/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera53/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera53/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera54/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera54/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera56/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera56/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera57/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera57/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera58/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera58/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera59/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera59/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera60/*.cc videos/HDA_Dataset_V1.3/hda_detections/AcfInria/camera60/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera17/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera17/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera18/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera18/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera19/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera19/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera40/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera40/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera50/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera50/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera53/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera53/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera54/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera54/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera56/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera56/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera57/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera57/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera58/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera58/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera59/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera59/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera60/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsAll/camera60/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera17/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera17/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera18/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera18/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera19/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera19/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera40/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera40/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera50/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera50/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera53/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera53/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera54/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera54/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera56/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera56/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera57/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera57/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera58/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera58/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera59/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera59/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera60/*.cc videos/HDA_Dataset_V1.3/hda_detections/GtAnnotationsClean/camera60/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/Toy3/*.cc videos/HDA_Dataset_V1.3/hda_detections/Toy3/camera60/*.cc videos/HDA_Dataset_V1.3/hda_detections/Toy3/camera60/Detections/*.cc videos/HDA_Dataset_V1.3/hda_detections/Toy8/*.cc videos/HDA_Dataset_V1.3/hda_detections/Toy8/camera60/*.cc videos/HDA_Dataset_V1.3/hda_detections/Toy8/camera60/Detections/*.cc videos/HDA_Dataset_V1.3/hda_docs/*.cc videos/HDA_Dataset_V1.3/hda_homographies/*.cc videos/HDA_Dataset_V1.3/hda_image_sequences_matlab/*.cc videos/HDA_Dataset_V1.3/hda_sample_train_data/*.cc videos/HDA_Dataset_V1.3/hda_sample_train_data_toy3/*.cc videos/HDA_Dataset_V1.3/hda_sample_train_data_toy8/*.cc videos/ICGLab6/*.cc videos/ICGLab6/calibration/*.cc videos/ICGLab6/chap/*.cc videos/ICGLab6/chap/Groundtruth/*.cc videos/vot2017/*.cc videos/vot2017/ants1/*.cc videos/vot2017/ants3/*.cc videos/vot2017/bag/*.cc videos/vot2017/ball1/*.cc videos/vot2017/ball2/*.cc videos/vot2017/basketball/*.cc videos/vot2017/birds1/*.cc videos/vot2017/blanket/*.cc videos/vot2017/bmx/*.cc videos/vot2017/bolt1/*.cc videos/vot2017/bolt2/*.cc videos/vot2017/book/*.cc videos/vot2017/butterfly/*.cc videos/vot2017/car1/*.cc videos/vot2017/conduction1/*.cc videos/vot2017/crabs1/*.cc videos/vot2017/crossing/*.cc videos/vot2017/dinosaur/*.cc videos/vot2017/drone1/*.cc videos/vot2017/drone_across/*.cc videos/vot2017/drone_flip/*.cc videos/vot2017/fernando/*.cc videos/vot2017/fish1/*.cc videos/vot2017/fish2/*.cc videos/vot2017/fish3/*.cc videos/vot2017/flamingo1/*.cc videos/vot2017/frisbee/*.cc videos/vot2017/girl/*.cc videos/vot2017/glove/*.cc videos/vot2017/godfather/*.cc videos/vot2017/graduate/*.cc videos/vot2017/gymnastics1/*.cc videos/vot2017/gymnastics2/*.cc videos/vot2017/gymnastics3/*.cc videos/vot2017/hand/*.cc videos/vot2017/handball1/*.cc videos/vot2017/handball2/*.cc videos/vot2017/helicopter/*.cc videos/vot2017/iceskater1/*.cc videos/vot2017/iceskater2/*.cc videos/vot2017/leaves/*.cc videos/vot2017/matrix/*.cc videos/vot2017/motocross1/*.cc videos/vot2017/motocross2/*.cc videos/vot2017/nature/*.cc videos/vot2017/pedestrian1/*.cc videos/vot2017/rabbit/*.cc videos/vot2017/racing/*.cc videos/vot2017/road/*.cc videos/vot2017/shaking/*.cc videos/vot2017/sheep/*.cc videos/vot2017/singer2/*.cc videos/vot2017/singer3/*.cc videos/vot2017/soccer1/*.cc videos/vot2017/soccer2/*.cc videos/vot2017/soldier/*.cc videos/vot2017/tiger/*.cc videos/vot2017/traffic/*.cc videos/vot2017/wiper/*.cc videos/vot2017/zebrafish1/*.cc wise/*.cc wise/simulations/*.cc wise/simulations/Tutorial_ICIP17/*.cc wise/simulations/wiseMultiCameraPeriodicApp_DPF/*.cc wise/simulations/wiseMultiCameraPeriodicApp_DPF/res/*.cc wise/simulations/wiseMultiCameraPeriodicApp_ICF/*.cc wise/simulations/wiseMultiCameraPeriodicApp_ICF/res/*.cc wise/simulations/wiseMultiCameraPeriodicApp_ICF/scripts/*.cc wise/simulations/wiseMultiCameraPeriodicApp_KCF/*.cc wise/simulations/wiseMultiCameraPeriodicApp_KCF/res/*.cc wise/simulations/wiseMultiCameraPeriodicApp_KCF/scripts/*.cc wise/simulations/wiseMultiCameraPeriodicApp_MTIC/*.cc wise/simulations/wiseTest/*.cc wise/simulations/wiseTest/res/*.cc wise/src/*.cc wise/src/node/*.cc wise/src/node/application/*.cc wise/src/node/application/wiseBaseApp/*.cc wise/src/node/application/wiseBaseAppTest/*.cc wise/src/node/application/wiseCameraApp/*.cc wise/src/node/application/wiseCameraAppTest/*.cc wise/src/node/application/wiseCameraPeriodicApp/*.cc wise/src/node/application/wiseCameraPeriodicAppDet/*.cc wise/src/node/application/wiseCameraPeriodicAppTest/*.cc wise/src/node/application/wiseCameraPeriodicAppTracker/*.cc wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/*.cc wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/*.cc wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/*.cc wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/*.cc wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/*.cc wise/src/node/resourceManager/*.cc wise/src/node/sensorManager/*.cc wise/src/node/sensorManager/sensorManager/*.cc wise/src/node/sensorManager/wiseCameraManager/*.cc wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/*.cc wise/src/node/sensorManager/wiseEmptySensorManager/*.cc wise/src/utils/*.cc wise/src/utils/gmm/*.cc wise/src/utils/gmm/c-gmm/*.cc wise/src/utils/libMvtnorm/*.cc wise/src/utils/libMvtnorm/libMvtnorm/*.cc wise/src/utils/pft/*.cc wise/src/wirelessChannel/*.cc wise/src/world/*.cc wise/src/world/gui/*.cc wise/src/world/gui/opencv/*.cc wise/src/world/physicalProcess/*.cc wise/src/world/physicalProcess/wiseMovingTarget/*.cc wise/src/world/physicalProcess/wiseVideoFile/*.cc wise/src/world/terrain/*.cc wise/src/world/terrain/wiseTerrainCalibrated/*.cc wise/src/world/terrain/wiseTerrainEmpty/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/castalia/src/helpStructures/CastaliaModule.o: castalia/src/helpStructures/CastaliaModule.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/helpStructures/DebugInfoWriter.o: castalia/src/helpStructures/DebugInfoWriter.cc \
	castalia/src/helpStructures/DebugInfoWriter.h
$O/castalia/src/helpStructures/OmnetCompatibility.o: castalia/src/helpStructures/OmnetCompatibility.cc \
	castalia/src/helpStructures/OmnetCompatibility.h
$O/castalia/src/helpStructures/TimerService.o: castalia/src/helpStructures/TimerService.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/helpStructures/TimerServiceMessage_m.o: castalia/src/helpStructures/TimerServiceMessage_m.cc \
	castalia/src/helpStructures/TimerServiceMessage_m.h
$O/castalia/src/node/application/ApplicationPacket_m.o: castalia/src/node/application/ApplicationPacket_m.cc \
	castalia/src/node/application/ApplicationPacket_m.h
$O/castalia/src/node/application/VirtualApplication.o: castalia/src/node/application/VirtualApplication.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h
$O/castalia/src/node/application/bridgeTest/BridgeTest.o: castalia/src/node/application/bridgeTest/BridgeTest.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/application/bridgeTest/BridgeTest.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h
$O/castalia/src/node/application/connectivityMap/ConnectivityMap.o: castalia/src/node/application/connectivityMap/ConnectivityMap.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/application/connectivityMap/ConnectivityMap.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h
$O/castalia/src/node/application/simpleAggregation/SimpleAggregation.o: castalia/src/node/application/simpleAggregation/SimpleAggregation.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/application/simpleAggregation/SimpleAggregation.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h
$O/castalia/src/node/application/throughputTest/ThroughputTest.o: castalia/src/node/application/throughputTest/ThroughputTest.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/application/throughputTest/ThroughputTest.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h
$O/castalia/src/node/application/valuePropagation/ValuePropagation.o: castalia/src/node/application/valuePropagation/ValuePropagation.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/application/valuePropagation/ValuePropagation.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h
$O/castalia/src/node/application/valueReporting/ValueReporting.o: castalia/src/node/application/valueReporting/ValueReporting.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/application/valueReporting/ValueReporting.h \
	castalia/src/node/application/valueReporting/ValueReportingPacket_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h
$O/castalia/src/node/application/valueReporting/ValueReportingPacket_m.o: castalia/src/node/application/valueReporting/ValueReportingPacket_m.cc \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/valueReporting/ValueReportingPacket_m.h
$O/castalia/src/node/communication/mac/MacPacket_m.o: castalia/src/node/communication/mac/MacPacket_m.cc \
	castalia/src/node/communication/mac/MacPacket_m.h
$O/castalia/src/node/communication/mac/VirtualMac.o: castalia/src/node/communication/mac/VirtualMac.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/VirtualMac.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/communication/routing/RoutingPacket_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/node/communication/mac/baselineBanMac/BaselineBANMac.o: castalia/src/node/communication/mac/baselineBanMac/BaselineBANMac.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/VirtualMac.h \
	castalia/src/node/communication/mac/baselineBanMac/BaselineBANMac.h \
	castalia/src/node/communication/mac/baselineBanMac/BaselineMacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/communication/routing/RoutingPacket_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/node/communication/mac/baselineBanMac/BaselineMacPacket_m.o: castalia/src/node/communication/mac/baselineBanMac/BaselineMacPacket_m.cc \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/baselineBanMac/BaselineMacPacket_m.h
$O/castalia/src/node/communication/mac/bypassMac/BypassMAC.o: castalia/src/node/communication/mac/bypassMac/BypassMAC.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/VirtualMac.h \
	castalia/src/node/communication/mac/bypassMac/BypassMAC.h \
	castalia/src/node/communication/mac/bypassMac/BypassMacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/communication/routing/RoutingPacket_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/node/communication/mac/bypassMac/BypassMacPacket_m.o: castalia/src/node/communication/mac/bypassMac/BypassMacPacket_m.cc \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/bypassMac/BypassMacPacket_m.h
$O/castalia/src/node/communication/mac/mac802154/Mac802154.o: castalia/src/node/communication/mac/mac802154/Mac802154.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/VirtualMac.h \
	castalia/src/node/communication/mac/mac802154/Mac802154.h \
	castalia/src/node/communication/mac/mac802154/Mac802154Packet_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/communication/routing/RoutingPacket_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/node/communication/mac/mac802154/Mac802154Packet_m.o: castalia/src/node/communication/mac/mac802154/Mac802154Packet_m.cc \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/mac802154/Mac802154Packet_m.h
$O/castalia/src/node/communication/mac/tMac/TMAC.o: castalia/src/node/communication/mac/tMac/TMAC.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/VirtualMac.h \
	castalia/src/node/communication/mac/tMac/TMAC.h \
	castalia/src/node/communication/mac/tMac/TMacControlMessage_m.h \
	castalia/src/node/communication/mac/tMac/TMacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/communication/routing/RoutingPacket_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/node/communication/mac/tMac/TMacControlMessage_m.o: castalia/src/node/communication/mac/tMac/TMacControlMessage_m.cc \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/tMac/TMacControlMessage_m.h \
	castalia/src/node/communication/mac/tMac/TMacPacket_m.h
$O/castalia/src/node/communication/mac/tMac/TMacPacket_m.o: castalia/src/node/communication/mac/tMac/TMacPacket_m.cc \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/tMac/TMacPacket_m.h
$O/castalia/src/node/communication/mac/tunableMac/TunableMAC.o: castalia/src/node/communication/mac/tunableMac/TunableMAC.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/VirtualMac.h \
	castalia/src/node/communication/mac/tunableMac/TunableMAC.h \
	castalia/src/node/communication/mac/tunableMac/TunableMacControl_m.h \
	castalia/src/node/communication/mac/tunableMac/TunableMacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/communication/routing/RoutingPacket_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/node/communication/mac/tunableMac/TunableMacControl_m.o: castalia/src/node/communication/mac/tunableMac/TunableMacControl_m.cc \
	castalia/src/node/communication/mac/tunableMac/TunableMacControl_m.h
$O/castalia/src/node/communication/mac/tunableMac/TunableMacPacket_m.o: castalia/src/node/communication/mac/tunableMac/TunableMacPacket_m.cc \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/tunableMac/TunableMacPacket_m.h
$O/castalia/src/node/communication/radio/Radio.o: castalia/src/node/communication/radio/Radio.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/node/communication/radio/RadioControlMessage_m.o: castalia/src/node/communication/radio/RadioControlMessage_m.cc \
	castalia/src/node/communication/radio/RadioControlMessage_m.h
$O/castalia/src/node/communication/radio/RadioSupportFunctions.o: castalia/src/node/communication/radio/RadioSupportFunctions.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/node/communication/routing/RoutingPacket_m.o: castalia/src/node/communication/routing/RoutingPacket_m.cc \
	castalia/src/node/communication/routing/RoutingPacket_m.h
$O/castalia/src/node/communication/routing/VirtualRouting.o: castalia/src/node/communication/routing/VirtualRouting.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/communication/routing/RoutingPacket_m.h \
	castalia/src/node/communication/routing/VirtualRouting.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/node/communication/routing/bypassRouting/BypassRouting.o: castalia/src/node/communication/routing/bypassRouting/BypassRouting.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/communication/routing/RoutingPacket_m.h \
	castalia/src/node/communication/routing/VirtualRouting.h \
	castalia/src/node/communication/routing/bypassRouting/BypassRouting.h \
	castalia/src/node/communication/routing/bypassRouting/BypassRoutingPacket_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/node/communication/routing/bypassRouting/BypassRoutingPacket_m.o: castalia/src/node/communication/routing/bypassRouting/BypassRoutingPacket_m.cc \
	castalia/src/node/communication/routing/RoutingPacket_m.h \
	castalia/src/node/communication/routing/bypassRouting/BypassRoutingPacket_m.h
$O/castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRouting.o: castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRouting.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/communication/routing/RoutingPacket_m.h \
	castalia/src/node/communication/routing/VirtualRouting.h \
	castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRouting.h \
	castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingControl_m.h \
	castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingPacket_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingControl_m.o: castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingControl_m.cc \
	castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingControl_m.h
$O/castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingPacket_m.o: castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingPacket_m.cc \
	castalia/src/node/communication/routing/RoutingPacket_m.h \
	castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingPacket_m.h
$O/castalia/src/node/mobilityManager/MobilityManagerMessage_m.o: castalia/src/node/mobilityManager/MobilityManagerMessage_m.cc \
	castalia/src/node/mobilityManager/MobilityManagerMessage_m.h
$O/castalia/src/node/mobilityManager/VirtualMobilityManager.o: castalia/src/node/mobilityManager/VirtualMobilityManager.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/node/mobilityManager/lineMobilityManager/LineMobilityManager.o: castalia/src/node/mobilityManager/lineMobilityManager/LineMobilityManager.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/mobilityManager/MobilityManagerMessage_m.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/node/mobilityManager/lineMobilityManager/LineMobilityManager.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/node/mobilityManager/noMobilityManager/NoMobilityManager.o: castalia/src/node/mobilityManager/noMobilityManager/NoMobilityManager.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/node/mobilityManager/noMobilityManager/NoMobilityManager.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/node/resourceManager/ResourceManager.o: castalia/src/node/resourceManager/ResourceManager.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/node/resourceManager/ResourceManager.h \
	castalia/src/node/resourceManager/ResourceManagerMessage_m.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseApp.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/castalia/src/node/resourceManager/ResourceManagerMessage_m.o: castalia/src/node/resourceManager/ResourceManagerMessage_m.cc \
	castalia/src/node/resourceManager/ResourceManagerMessage_m.h
$O/castalia/src/physicalProcess/PhysicalProcessMessage_m.o: castalia/src/physicalProcess/PhysicalProcessMessage_m.cc \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h
$O/castalia/src/physicalProcess/carsPhysicalProcess/CarsPhysicalProcess.o: castalia/src/physicalProcess/carsPhysicalProcess/CarsPhysicalProcess.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/physicalProcess/carsPhysicalProcess/CarsPhysicalProcess.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/physicalProcess/customizablePhysicalProcess/CustomizablePhysicalProcess.o: castalia/src/physicalProcess/customizablePhysicalProcess/CustomizablePhysicalProcess.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/physicalProcess/customizablePhysicalProcess/CustomizablePhysicalProcess.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/wirelessChannel/WirelessChannel.o: castalia/src/wirelessChannel/WirelessChannel.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/wirelessChannel/WirelessChannel.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	castalia/src/wirelessChannel/WirelessChannelTemporal.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/castalia/src/wirelessChannel/WirelessChannelMessages_m.o: castalia/src/wirelessChannel/WirelessChannelMessages_m.cc \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h
$O/castalia/src/wirelessChannel/WirelessChannelTemporal.o: castalia/src/wirelessChannel/WirelessChannelTemporal.cc \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/wirelessChannel/WirelessChannelTemporal.h
$O/wise/src/node/application/wiseBaseApp/WiseBaseApp.o: wise/src/node/application/wiseBaseApp/WiseBaseApp.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/tMac/TMacControlMessage_m.h \
	castalia/src/node/communication/mac/tMac/TMacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannel.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	castalia/src/wirelessChannel/WirelessChannelTemporal.h \
	wise/src/node/application/wiseBaseApp/WiseBaseApp.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.o: wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseBaseAppTest/WiseBaseAppTest.o: wise/src/node/application/wiseBaseAppTest/WiseBaseAppTest.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseApp.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseBaseAppTest/WiseBaseAppTest.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorMessage_m.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraApp/WiseCameraApp.o: wise/src/node/application/wiseCameraApp/WiseCameraApp.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseApp.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraApp.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraAppTest/WiseCameraAppTest.o: wise/src/node/application/wiseCameraAppTest/WiseCameraAppTest.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseApp.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraApp.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/application/wiseCameraAppTest/WiseCameraAppTest.h \
	wise/src/node/application/wiseCameraAppTest/WiseCameraAppTestPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraAppTest/WiseCameraAppTestPacket_m.o: wise/src/node/application/wiseCameraAppTest/WiseCameraAppTestPacket_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraAppTest/WiseCameraAppTestPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicApp.o: wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicApp.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseApp.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraApp.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicApp.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppTypes.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseGTreader.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.o: wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseCameraPeriodicAppDet/WiseCameraPeriodicAppDet.o: wise/src/node/application/wiseCameraPeriodicAppDet/WiseCameraPeriodicAppDet.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseApp.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraApp.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicApp.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppTypes.h \
	wise/src/node/application/wiseCameraPeriodicAppDet/WiseCameraPeriodicAppDet.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseGTreader.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraPeriodicAppTest/WiseCameraPeriodicAppTest.o: wise/src/node/application/wiseCameraPeriodicAppTest/WiseCameraPeriodicAppTest.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseApp.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraApp.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicApp.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppTypes.h \
	wise/src/node/application/wiseCameraPeriodicAppTest/WiseCameraPeriodicAppTest.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseGTreader.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraPeriodicAppTracker/WiseCameraPeriodicAppTracker.o: wise/src/node/application/wiseCameraPeriodicAppTracker/WiseCameraPeriodicAppTracker.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseApp.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraApp.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicApp.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppTypes.h \
	wise/src/node/application/wiseCameraPeriodicAppTracker/WiseCameraPeriodicAppTracker.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseGTreader.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/WiseMultiCameraPeriodicApp_DPF.o: wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/WiseMultiCameraPeriodicApp_DPF.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseApp.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraApp.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicApp.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppTypes.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/WiseMultiCameraPeriodicApp_DPF.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/WiseMultiCameraPeriodicApp_DPFPacket_custom.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/WiseMultiCameraPeriodicApp_DPFPacket_m.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/pft.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/pft_exception.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseException.h \
	wise/src/utils/WiseGTreader.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/utils/gmm/c-gmm/clust_defs.h \
	wise/src/utils/gmm/wise_utils_gmm.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/WiseMultiCameraPeriodicApp_DPFPacket_m.o: wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/WiseMultiCameraPeriodicApp_DPFPacket_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_DPF/WiseMultiCameraPeriodicApp_DPFPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/gmm/c-gmm/clust_defs.h \
	wise/src/utils/gmm/wise_utils_gmm.h
$O/wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICF.o: wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICF.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseApp.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraApp.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicApp.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppTypes.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICF.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICFPacket_m.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICF_utils.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseGTreader.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/gui/opencv/WiseGuiWorldOpencv.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICFPacket_m.o: wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICFPacket_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICFPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICF_utils.o: wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICF_utils.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICFPacket_m.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_ICF/WiseMultiCameraPeriodicApp_ICF_utils.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseUtils.h
$O/wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/WiseMultiCameraPeriodicApp_KCF.o: wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/WiseMultiCameraPeriodicApp_KCF.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseApp.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraApp.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicApp.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppTypes.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/WiseMultiCameraPeriodicApp_KCF.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/WiseMultiCameraPeriodicApp_KCFPacket_m.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/WiseMultiCameraPeriodicApp_KCF_utils.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseGTreader.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/WiseMultiCameraPeriodicApp_KCFPacket_m.o: wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/WiseMultiCameraPeriodicApp_KCFPacket_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_KCF/WiseMultiCameraPeriodicApp_KCFPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTIC.o: wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTIC.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseApp.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraApp.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicApp.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppTypes.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTIC.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTICPacket_m.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTIC_utils.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseGTreader.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/utils/libMvtnorm/libMvtnorm/mvtnorm.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/gui/opencv/WiseGuiWorldOpencv.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTICPacket_m.o: wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTICPacket_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTICPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTIC_utils.o: wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTIC_utils.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTICPacket_m.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_MTIC/WiseMultiCameraPeriodicApp_MTIC_utils.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseUtils.h
$O/wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/WiseMultiCameraPeriodicApp_ReID.o: wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/WiseMultiCameraPeriodicApp_ReID.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseApp.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraApp.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicApp.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppTypes.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/WiseMultiCameraPeriodicApp_ReID.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/WiseMultiCameraPeriodicApp_ReIDPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseGTreader.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/WiseMultiCameraPeriodicApp_ReIDPacket_m.o: wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/WiseMultiCameraPeriodicApp_ReIDPacket_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicApp/WiseCameraPeriodicAppPacket_m.h \
	wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/WiseMultiCameraPeriodicApp_ReIDPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/resourceManager/WiseResourceManager.o: wise/src/node/resourceManager/WiseResourceManager.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/application/VirtualApplication.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseBaseApp/WiseBaseApp.h \
	wise/src/node/application/wiseBaseApp/WiseBaseAppPacket_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/resourceManager/WiseResourceManager_utils.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/PropertyFileReader.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/resourceManager/WiseResourceManagerMessage_m.o: wise/src/node/resourceManager/WiseResourceManagerMessage_m.cc \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/resourceManager/WiseResourceManager_utils.o: wise/src/node/resourceManager/WiseResourceManager_utils.cc \
	wise/src/node/resourceManager/WiseResourceManager_utils.h
$O/wise/src/node/sensorManager/WiseBaseSensorManager.o: wise/src/node/sensorManager/WiseBaseSensorManager.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/sensorManager/WiseSensorManagerMessage_m.o: wise/src/node/sensorManager/WiseSensorManagerMessage_m.cc \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h
$O/wise/src/node/sensorManager/sensorManager/SensorManager.o: wise/src/node/sensorManager/sensorManager/SensorManager.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManager.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h
$O/wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.o: wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.cc \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/sensorManager/SensorManagerMessage_m.h
$O/wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.o: wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.o: wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.cc \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h
$O/wise/src/node/sensorManager/wiseCameraManager/cameraModel.o: wise/src/node/sensorManager/wiseCameraManager/cameraModel.cc \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseUtils.h
$O/wise/src/node/sensorManager/wiseCameraManager/xmlUtil.o: wise/src/node/sensorManager/wiseCameraManager/xmlUtil.cc \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h
$O/wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetections.o: wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetections.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetections.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.o: wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.cc \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h
$O/wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.o: wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseException.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideo.o: wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideo.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideo.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/physicalProcess/wiseVideoFile/WiseVideoFileMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.o: wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.cc \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.h
$O/wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorManager.o: wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorManager.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorManager.h \
	wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorMessage_m.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorMessage_m.o: wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorMessage_m.cc \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorMessage_m.h
$O/wise/src/utils/PropertyFileReader.o: wise/src/utils/PropertyFileReader.cc \
	wise/src/utils/PropertyFileReader.h
$O/wise/src/utils/WiseDebug.o: wise/src/utils/WiseDebug.cc \
	wise/src/utils/WiseDebug.h
$O/wise/src/utils/WiseGTreader.o: wise/src/utils/WiseGTreader.cc \
	wise/src/utils/WiseGTreader.h
$O/wise/src/utils/WiseUtils.o: wise/src/utils/WiseUtils.cc \
	wise/src/utils/WiseUtils.h
$O/wise/src/utils/gmm/wise_utils_gmm.o: wise/src/utils/gmm/wise_utils_gmm.cc \
	wise/src/utils/WiseException.h \
	wise/src/utils/gmm/c-gmm/alloc_util.h \
	wise/src/utils/gmm/c-gmm/clust_defs.h \
	wise/src/utils/gmm/c-gmm/clust_util.h \
	wise/src/utils/gmm/c-gmm/subcluster.h \
	wise/src/utils/gmm/wise_utils_gmm.h
$O/wise/src/wirelessChannel/WiseDummyWirelessChannel.o: wise/src/wirelessChannel/WiseDummyWirelessChannel.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseDebug.h \
	wise/src/wirelessChannel/WiseDummyWirelessChannel.h
$O/wise/src/world/gui/WiseGuiWorld.o: wise/src/world/gui/WiseGuiWorld.cc \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/utils/WiseException.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h
$O/wise/src/world/gui/opencv/WiseGuiWorldOpencv.o: wise/src/world/gui/opencv/WiseGuiWorldOpencv.cc \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/gui/opencv/WiseGuiWorldOpencv.h
$O/wise/src/world/physicalProcess/WiseBasePhysicalProcess.o: wise/src/world/physicalProcess/WiseBasePhysicalProcess.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WiseBasePhysicalProcess.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.o: wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.cc \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h
$O/wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTarget.o: wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTarget.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WiseBasePhysicalProcess.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTarget.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.o: wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.cc \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h
$O/wise/src/world/physicalProcess/wiseVideoFile/WiseVideoFile.o: wise/src/world/physicalProcess/wiseVideoFile/WiseVideoFile.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/physicalProcess/WiseBasePhysicalProcess.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseVideoFile/WiseVideoFile.h \
	wise/src/world/physicalProcess/wiseVideoFile/WiseVideoFileMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/world/physicalProcess/wiseVideoFile/WiseVideoFileMessage_m.o: wise/src/world/physicalProcess/wiseVideoFile/WiseVideoFileMessage_m.cc \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseVideoFile/WiseVideoFileMessage_m.h
$O/wise/src/world/terrain/WiseBaseTerrain.o: wise/src/world/terrain/WiseBaseTerrain.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/world/terrain/wiseTerrainCalibrated/WiseTerrainCalibrated.o: wise/src/world/terrain/wiseTerrainCalibrated/WiseTerrainCalibrated.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/terrain/WiseBaseTerrain.h \
	wise/src/world/terrain/wiseTerrainCalibrated/WiseTerrainCalibrated.h
$O/wise/src/world/terrain/wiseTerrainEmpty/WiseTerrainEmpty.o: wise/src/world/terrain/wiseTerrainEmpty/WiseTerrainEmpty.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	wise/src/node/application/wiseCameraApp/WiseCameraInfo.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/gui/WiseGuiWorld.h \
	wise/src/world/terrain/WiseBaseTerrain.h \
	wise/src/world/terrain/wiseTerrainEmpty/WiseTerrainEmpty.h

