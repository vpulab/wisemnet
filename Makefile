#
# OMNeT++/OMNEST Makefile for wisemnet-master
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/include/eigen3 -I/usr/include/libxml2 -lxml2 -lopencv_tracking -lopencv_videoio -lopencv_objdetect -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -lopencv_video -lopencv_core -lopencv_features2d -- wise/src/utils/gmm/c-gmm/c-gmm-64bit.a
#

# Name of target to be created (-o option)
TARGET = wisemnet-master$(EXE_SUFFIX)

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
    -Ivideos/AVSS07 \
    -Ivideos/Crowd_PETS09 \
    -Ivideos/Crowd_PETS09/S2 \
    -Ivideos/Crowd_PETS09/S2/L1 \
    -Ivideos/Crowd_PETS09/S2/L1/Groundtruth \
    -Ivideos/Crowd_PETS09/S2/L1/Time_12-34 \
    -Ivideos/Crowd_PETS09/S2/L1/Time_12-34/View_001 \
    -Ivideos/Crowd_PETS09/S2/L1/Time_12-34/View_003 \
    -Ivideos/Crowd_PETS09/S2/L1/Time_12-34/View_004 \
    -Ivideos/Crowd_PETS09/S2/L1/Time_12-34/View_005 \
    -Ivideos/Crowd_PETS09/S2/L1/Time_12-34/View_006 \
    -Ivideos/Crowd_PETS09/S2/L1/Time_12-34/View_007 \
    -Ivideos/Crowd_PETS09/S2/L1/Time_12-34/View_008 \
    -Ivideos/ICGLab6 \
    -Ivideos/ICGLab6/calibration \
    -Ivideos/ICGLab6/chap \
    -Ivideos/ICGLab6/chap/Groundtruth \
    -Ivideos/ICGLab6/leaf1 \
    -Ivideos/ICGLab6/leaf1/Groundtruth \
    -Ivideos/ICGLab6/leaf2 \
    -Ivideos/ICGLab6/leaf2/Groundtruth \
    -Ivideos/ICGLab6/much \
    -Ivideos/ICGLab6/much/Groundtruth \
    -Ivideos/ICGLab6/pose \
    -Ivideos/ICGLab6/pose/Groundtruth \
    -Ivideos/ICGLab6/table \
    -Ivideos/ICGLab6/table/Groundtruth \
    -Iwise \
    -Iwise/simulations \
    -Iwise/simulations/python_scripts \
    -Iwise/simulations/python_scripts/results \
    -Iwise/simulations/wiseCameraCAWCTracker \
    -Iwise/simulations/wiseCameraCAWCTracker/matlab \
    -Iwise/simulations/wiseCameraCAWCTracker/matlab/bak \
    -Iwise/simulations/wiseCameraCAWCTracker/matlab/utils \
    -Iwise/simulations/wiseCameraDPF_example1 \
    -Iwise/simulations/wiseCameraDPF_example2 \
    -Iwise/simulations/wiseCameraDPF_example3 \
    -Iwise/simulations/wiseCameraICF \
    -Iwise/simulations/wiseCameraICF/matlab \
    -Iwise/simulations/wiseCameraICF_NN \
    -Iwise/simulations/wiseCameraICF_NN/matlab \
    -Iwise/simulations/wiseCameraKCF \
    -Iwise/simulations/wiseCameraKCF/matlab \
    -Iwise/simulations/wiseCameraMTIC \
    -Iwise/simulations/wiseCameraMultiVideo \
    -Iwise/simulations/wiseCameraPeopleDet \
    -Iwise/simulations/wiseCameraPeopleDet/matlab \
    -Iwise/simulations/wiseCameraPeopleDet/matlab/utils \
    -Iwise/simulations/wiseCamera_test_dFOV \
    -Iwise/simulations/wiseCamera_test_sFOV \
    -Iwise/simulations/wiseSimpleApp_test \
    -Iwise/simulations/wiseTracker_test \
    -Iwise/src \
    -Iwise/src/gui \
    -Iwise/src/gui/opencv \
    -Iwise/src/node \
    -Iwise/src/node/application \
    -Iwise/src/node/application/Trackers \
    -Iwise/src/node/application/Trackers/struck \
    -Iwise/src/node/application/Trackers/struck/GraphUtils \
    -Iwise/src/node/application/Trackers/struck/Utils \
    -Iwise/src/node/application/wiseAppTest \
    -Iwise/src/node/application/wiseCameraAppTest \
    -Iwise/src/node/application/wiseCameraApplication \
    -Iwise/src/node/application/wiseCameraCAWCTracker \
    -Iwise/src/node/application/wiseCameraClusterICF \
    -Iwise/src/node/application/wiseCameraDPF \
    -Iwise/src/node/application/wiseCameraICF \
    -Iwise/src/node/application/wiseCameraICF_NN \
    -Iwise/src/node/application/wiseCameraKCF \
    -Iwise/src/node/application/wiseCameraMTIC \
    -Iwise/src/node/application/wiseCameraMultiVideo \
    -Iwise/src/node/application/wiseCameraPeopleDet \
    -Iwise/src/node/application/wiseCameraPeriodicAlgo \
    -Iwise/src/node/application/wiseCameraSimplePeriodicTracker \
    -Iwise/src/node/application/wiseCameraTrackerTest \
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
    -Iwise/src/world/physicalProcess \
    -Iwise/src/world/physicalProcess/wiseMovingTarget \
    -Iwise/src/world/physicalProcess/wiseVideoFile \
    -Iwise/src/world/terrain \
    -Iwise/src/world/terrain/wiseEmptyTerrain

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
    $O/wise/src/gui/WiseGuiWorld.o \
    $O/wise/src/gui/opencv/WiseGuiWorldOpencv.o \
    $O/wise/src/node/application/WiseBaseApplication.o \
    $O/wise/src/node/application/Trackers/struck/HistogramFeatures.o \
    $O/wise/src/node/application/Trackers/struck/Sampler.o \
    $O/wise/src/node/application/Trackers/struck/MultiFeatures.o \
    $O/wise/src/node/application/Trackers/struck/ImageRep.o \
    $O/wise/src/node/application/Trackers/struck/main.o \
    $O/wise/src/node/application/Trackers/struck/HaarFeature.o \
    $O/wise/src/node/application/Trackers/struck/Features.o \
    $O/wise/src/node/application/Trackers/struck/RawFeatures.o \
    $O/wise/src/node/application/Trackers/struck/LaRank.o \
    $O/wise/src/node/application/Trackers/struck/HaarFeatures.o \
    $O/wise/src/node/application/Trackers/struck/_Tracker.o \
    $O/wise/src/node/application/Trackers/struck/Config.o \
    $O/wise/src/node/application/Trackers/struck/GraphUtils/GraphUtils.o \
    $O/wise/src/node/application/Trackers/struck/Utils/string_utils.o \
    $O/wise/src/node/application/Trackers/struck/Utils/time_utils.o \
    $O/wise/src/node/application/Trackers/struck/Utils/shell_utils.o \
    $O/wise/src/node/application/Trackers/struck/Utils/log.o \
    $O/wise/src/node/application/Trackers/struck/Utils/histogram.o \
    $O/wise/src/node/application/Trackers/struck/Utils/math_utils.o \
    $O/wise/src/node/application/wiseAppTest/WiseAppTest.o \
    $O/wise/src/node/application/wiseCameraAppTest/WiseCameraAppTest.o \
    $O/wise/src/node/application/wiseCameraApplication/WiseCameraApplication.o \
    $O/wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTracker_utils.o \
    $O/wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTracker.o \
    $O/wise/src/node/application/wiseCameraClusterICF/WiseCameraClusterICF.o \
    $O/wise/src/node/application/wiseCameraDPF/WiseCameraDPF.o \
    $O/wise/src/node/application/wiseCameraICF/WiseCameraICF.o \
    $O/wise/src/node/application/wiseCameraICF/WiseCameraICF_utils.o \
    $O/wise/src/node/application/wiseCameraICF_NN/hungarian.o \
    $O/wise/src/node/application/wiseCameraICF_NN/WiseCameraICF_NN.o \
    $O/wise/src/node/application/wiseCameraKCF/WiseCameraKCF.o \
    $O/wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC_utils.o \
    $O/wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC.o \
    $O/wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideo.o \
    $O/wise/src/node/application/wiseCameraPeopleDet/WiseCameraPeopleDet.o \
    $O/wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgo.o \
    $O/wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker.o \
    $O/wise/src/node/application/wiseCameraTrackerTest/WiseCameraTrackerTest.o \
    $O/wise/src/node/resourceManager/PropertyFileReader.o \
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
    $O/wise/src/utils/WiseDebug.o \
    $O/wise/src/utils/WiseUtils.o \
    $O/wise/src/utils/gmm/wise_utils_gmm.o \
    $O/wise/src/wirelessChannel/WiseDummyWirelessChannel.o \
    $O/wise/src/world/physicalProcess/WiseBasePhysicalProcess.o \
    $O/wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTarget.o \
    $O/wise/src/world/physicalProcess/wiseVideoFile/WiseVideoFile.o \
    $O/wise/src/world/terrain/WiseBaseTerrain.o \
    $O/wise/src/world/terrain/wiseEmptyTerrain/WiseEmptyTerrain.o \
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
    $O/wise/src/node/application/WiseApplicationPacket_m.o \
    $O/wise/src/node/application/wiseCameraAppTest/WiseCameraAppTestPacket_m.o \
    $O/wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTrackerPkt_m.o \
    $O/wise/src/node/application/wiseCameraClusterICF/WiseCameraClusterICFMsg_m.o \
    $O/wise/src/node/application/wiseCameraDPF/WiseCameraDPFMessage_m.o \
    $O/wise/src/node/application/wiseCameraICF/WiseCameraICFMsg_m.o \
    $O/wise/src/node/application/wiseCameraKCF/WiseCameraKCFMsg_m.o \
    $O/wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC_Msg_m.o \
    $O/wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideoPacketFull_m.o \
    $O/wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideoPacket_m.o \
    $O/wise/src/node/application/wiseCameraPeopleDet/WiseCameraPeopleDetPacket_m.o \
    $O/wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgoPacket_m.o \
    $O/wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker_m.o \
    $O/wise/src/node/application/wiseCameraTrackerTest/WiseCameraTrackerTestMessage_m.o \
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
    wise/src/node/application/WiseApplicationPacket.msg \
    wise/src/node/application/wiseCameraAppTest/WiseCameraAppTestPacket.msg \
    wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTrackerPkt.msg \
    wise/src/node/application/wiseCameraClusterICF/WiseCameraClusterICFMsg.msg \
    wise/src/node/application/wiseCameraDPF/WiseCameraDPFMessage.msg \
    wise/src/node/application/wiseCameraICF/WiseCameraICFMsg.msg \
    wise/src/node/application/wiseCameraKCF/WiseCameraKCFMsg.msg \
    wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC_Msg.msg \
    wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideoPacketFull.msg \
    wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideoPacket.msg \
    wise/src/node/application/wiseCameraPeopleDet/WiseCameraPeopleDetPacket.msg \
    wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgoPacket.msg \
    wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker.msg \
    wise/src/node/application/wiseCameraTrackerTest/WiseCameraTrackerTestMessage.msg \
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
	$(Q)-rm -f wisemnet-master wisemnet-master.exe libwisemnet-master.so libwisemnet-master.a libwisemnet-master.dll libwisemnet-master.dylib
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
	$(Q)-rm -f videos/AVSS07/*_m.cc videos/AVSS07/*_m.h videos/AVSS07/*_sm.cc videos/AVSS07/*_sm.h
	$(Q)-rm -f videos/Crowd_PETS09/*_m.cc videos/Crowd_PETS09/*_m.h videos/Crowd_PETS09/*_sm.cc videos/Crowd_PETS09/*_sm.h
	$(Q)-rm -f videos/Crowd_PETS09/S2/*_m.cc videos/Crowd_PETS09/S2/*_m.h videos/Crowd_PETS09/S2/*_sm.cc videos/Crowd_PETS09/S2/*_sm.h
	$(Q)-rm -f videos/Crowd_PETS09/S2/L1/*_m.cc videos/Crowd_PETS09/S2/L1/*_m.h videos/Crowd_PETS09/S2/L1/*_sm.cc videos/Crowd_PETS09/S2/L1/*_sm.h
	$(Q)-rm -f videos/Crowd_PETS09/S2/L1/Groundtruth/*_m.cc videos/Crowd_PETS09/S2/L1/Groundtruth/*_m.h videos/Crowd_PETS09/S2/L1/Groundtruth/*_sm.cc videos/Crowd_PETS09/S2/L1/Groundtruth/*_sm.h
	$(Q)-rm -f videos/Crowd_PETS09/S2/L1/Time_12-34/*_m.cc videos/Crowd_PETS09/S2/L1/Time_12-34/*_m.h videos/Crowd_PETS09/S2/L1/Time_12-34/*_sm.cc videos/Crowd_PETS09/S2/L1/Time_12-34/*_sm.h
	$(Q)-rm -f videos/Crowd_PETS09/S2/L1/Time_12-34/View_001/*_m.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_001/*_m.h videos/Crowd_PETS09/S2/L1/Time_12-34/View_001/*_sm.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_001/*_sm.h
	$(Q)-rm -f videos/Crowd_PETS09/S2/L1/Time_12-34/View_003/*_m.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_003/*_m.h videos/Crowd_PETS09/S2/L1/Time_12-34/View_003/*_sm.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_003/*_sm.h
	$(Q)-rm -f videos/Crowd_PETS09/S2/L1/Time_12-34/View_004/*_m.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_004/*_m.h videos/Crowd_PETS09/S2/L1/Time_12-34/View_004/*_sm.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_004/*_sm.h
	$(Q)-rm -f videos/Crowd_PETS09/S2/L1/Time_12-34/View_005/*_m.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_005/*_m.h videos/Crowd_PETS09/S2/L1/Time_12-34/View_005/*_sm.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_005/*_sm.h
	$(Q)-rm -f videos/Crowd_PETS09/S2/L1/Time_12-34/View_006/*_m.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_006/*_m.h videos/Crowd_PETS09/S2/L1/Time_12-34/View_006/*_sm.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_006/*_sm.h
	$(Q)-rm -f videos/Crowd_PETS09/S2/L1/Time_12-34/View_007/*_m.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_007/*_m.h videos/Crowd_PETS09/S2/L1/Time_12-34/View_007/*_sm.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_007/*_sm.h
	$(Q)-rm -f videos/Crowd_PETS09/S2/L1/Time_12-34/View_008/*_m.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_008/*_m.h videos/Crowd_PETS09/S2/L1/Time_12-34/View_008/*_sm.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_008/*_sm.h
	$(Q)-rm -f videos/ICGLab6/*_m.cc videos/ICGLab6/*_m.h videos/ICGLab6/*_sm.cc videos/ICGLab6/*_sm.h
	$(Q)-rm -f videos/ICGLab6/calibration/*_m.cc videos/ICGLab6/calibration/*_m.h videos/ICGLab6/calibration/*_sm.cc videos/ICGLab6/calibration/*_sm.h
	$(Q)-rm -f videos/ICGLab6/chap/*_m.cc videos/ICGLab6/chap/*_m.h videos/ICGLab6/chap/*_sm.cc videos/ICGLab6/chap/*_sm.h
	$(Q)-rm -f videos/ICGLab6/chap/Groundtruth/*_m.cc videos/ICGLab6/chap/Groundtruth/*_m.h videos/ICGLab6/chap/Groundtruth/*_sm.cc videos/ICGLab6/chap/Groundtruth/*_sm.h
	$(Q)-rm -f videos/ICGLab6/leaf1/*_m.cc videos/ICGLab6/leaf1/*_m.h videos/ICGLab6/leaf1/*_sm.cc videos/ICGLab6/leaf1/*_sm.h
	$(Q)-rm -f videos/ICGLab6/leaf1/Groundtruth/*_m.cc videos/ICGLab6/leaf1/Groundtruth/*_m.h videos/ICGLab6/leaf1/Groundtruth/*_sm.cc videos/ICGLab6/leaf1/Groundtruth/*_sm.h
	$(Q)-rm -f videos/ICGLab6/leaf2/*_m.cc videos/ICGLab6/leaf2/*_m.h videos/ICGLab6/leaf2/*_sm.cc videos/ICGLab6/leaf2/*_sm.h
	$(Q)-rm -f videos/ICGLab6/leaf2/Groundtruth/*_m.cc videos/ICGLab6/leaf2/Groundtruth/*_m.h videos/ICGLab6/leaf2/Groundtruth/*_sm.cc videos/ICGLab6/leaf2/Groundtruth/*_sm.h
	$(Q)-rm -f videos/ICGLab6/much/*_m.cc videos/ICGLab6/much/*_m.h videos/ICGLab6/much/*_sm.cc videos/ICGLab6/much/*_sm.h
	$(Q)-rm -f videos/ICGLab6/much/Groundtruth/*_m.cc videos/ICGLab6/much/Groundtruth/*_m.h videos/ICGLab6/much/Groundtruth/*_sm.cc videos/ICGLab6/much/Groundtruth/*_sm.h
	$(Q)-rm -f videos/ICGLab6/pose/*_m.cc videos/ICGLab6/pose/*_m.h videos/ICGLab6/pose/*_sm.cc videos/ICGLab6/pose/*_sm.h
	$(Q)-rm -f videos/ICGLab6/pose/Groundtruth/*_m.cc videos/ICGLab6/pose/Groundtruth/*_m.h videos/ICGLab6/pose/Groundtruth/*_sm.cc videos/ICGLab6/pose/Groundtruth/*_sm.h
	$(Q)-rm -f videos/ICGLab6/table/*_m.cc videos/ICGLab6/table/*_m.h videos/ICGLab6/table/*_sm.cc videos/ICGLab6/table/*_sm.h
	$(Q)-rm -f videos/ICGLab6/table/Groundtruth/*_m.cc videos/ICGLab6/table/Groundtruth/*_m.h videos/ICGLab6/table/Groundtruth/*_sm.cc videos/ICGLab6/table/Groundtruth/*_sm.h
	$(Q)-rm -f wise/*_m.cc wise/*_m.h wise/*_sm.cc wise/*_sm.h
	$(Q)-rm -f wise/simulations/*_m.cc wise/simulations/*_m.h wise/simulations/*_sm.cc wise/simulations/*_sm.h
	$(Q)-rm -f wise/simulations/python_scripts/*_m.cc wise/simulations/python_scripts/*_m.h wise/simulations/python_scripts/*_sm.cc wise/simulations/python_scripts/*_sm.h
	$(Q)-rm -f wise/simulations/python_scripts/results/*_m.cc wise/simulations/python_scripts/results/*_m.h wise/simulations/python_scripts/results/*_sm.cc wise/simulations/python_scripts/results/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraCAWCTracker/*_m.cc wise/simulations/wiseCameraCAWCTracker/*_m.h wise/simulations/wiseCameraCAWCTracker/*_sm.cc wise/simulations/wiseCameraCAWCTracker/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraCAWCTracker/matlab/*_m.cc wise/simulations/wiseCameraCAWCTracker/matlab/*_m.h wise/simulations/wiseCameraCAWCTracker/matlab/*_sm.cc wise/simulations/wiseCameraCAWCTracker/matlab/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraCAWCTracker/matlab/bak/*_m.cc wise/simulations/wiseCameraCAWCTracker/matlab/bak/*_m.h wise/simulations/wiseCameraCAWCTracker/matlab/bak/*_sm.cc wise/simulations/wiseCameraCAWCTracker/matlab/bak/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraCAWCTracker/matlab/utils/*_m.cc wise/simulations/wiseCameraCAWCTracker/matlab/utils/*_m.h wise/simulations/wiseCameraCAWCTracker/matlab/utils/*_sm.cc wise/simulations/wiseCameraCAWCTracker/matlab/utils/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraDPF_example1/*_m.cc wise/simulations/wiseCameraDPF_example1/*_m.h wise/simulations/wiseCameraDPF_example1/*_sm.cc wise/simulations/wiseCameraDPF_example1/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraDPF_example2/*_m.cc wise/simulations/wiseCameraDPF_example2/*_m.h wise/simulations/wiseCameraDPF_example2/*_sm.cc wise/simulations/wiseCameraDPF_example2/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraDPF_example3/*_m.cc wise/simulations/wiseCameraDPF_example3/*_m.h wise/simulations/wiseCameraDPF_example3/*_sm.cc wise/simulations/wiseCameraDPF_example3/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraICF/*_m.cc wise/simulations/wiseCameraICF/*_m.h wise/simulations/wiseCameraICF/*_sm.cc wise/simulations/wiseCameraICF/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraICF/matlab/*_m.cc wise/simulations/wiseCameraICF/matlab/*_m.h wise/simulations/wiseCameraICF/matlab/*_sm.cc wise/simulations/wiseCameraICF/matlab/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraICF_NN/*_m.cc wise/simulations/wiseCameraICF_NN/*_m.h wise/simulations/wiseCameraICF_NN/*_sm.cc wise/simulations/wiseCameraICF_NN/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraICF_NN/matlab/*_m.cc wise/simulations/wiseCameraICF_NN/matlab/*_m.h wise/simulations/wiseCameraICF_NN/matlab/*_sm.cc wise/simulations/wiseCameraICF_NN/matlab/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraKCF/*_m.cc wise/simulations/wiseCameraKCF/*_m.h wise/simulations/wiseCameraKCF/*_sm.cc wise/simulations/wiseCameraKCF/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraKCF/matlab/*_m.cc wise/simulations/wiseCameraKCF/matlab/*_m.h wise/simulations/wiseCameraKCF/matlab/*_sm.cc wise/simulations/wiseCameraKCF/matlab/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraMTIC/*_m.cc wise/simulations/wiseCameraMTIC/*_m.h wise/simulations/wiseCameraMTIC/*_sm.cc wise/simulations/wiseCameraMTIC/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraMultiVideo/*_m.cc wise/simulations/wiseCameraMultiVideo/*_m.h wise/simulations/wiseCameraMultiVideo/*_sm.cc wise/simulations/wiseCameraMultiVideo/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraPeopleDet/*_m.cc wise/simulations/wiseCameraPeopleDet/*_m.h wise/simulations/wiseCameraPeopleDet/*_sm.cc wise/simulations/wiseCameraPeopleDet/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraPeopleDet/matlab/*_m.cc wise/simulations/wiseCameraPeopleDet/matlab/*_m.h wise/simulations/wiseCameraPeopleDet/matlab/*_sm.cc wise/simulations/wiseCameraPeopleDet/matlab/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCameraPeopleDet/matlab/utils/*_m.cc wise/simulations/wiseCameraPeopleDet/matlab/utils/*_m.h wise/simulations/wiseCameraPeopleDet/matlab/utils/*_sm.cc wise/simulations/wiseCameraPeopleDet/matlab/utils/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCamera_test_dFOV/*_m.cc wise/simulations/wiseCamera_test_dFOV/*_m.h wise/simulations/wiseCamera_test_dFOV/*_sm.cc wise/simulations/wiseCamera_test_dFOV/*_sm.h
	$(Q)-rm -f wise/simulations/wiseCamera_test_sFOV/*_m.cc wise/simulations/wiseCamera_test_sFOV/*_m.h wise/simulations/wiseCamera_test_sFOV/*_sm.cc wise/simulations/wiseCamera_test_sFOV/*_sm.h
	$(Q)-rm -f wise/simulations/wiseSimpleApp_test/*_m.cc wise/simulations/wiseSimpleApp_test/*_m.h wise/simulations/wiseSimpleApp_test/*_sm.cc wise/simulations/wiseSimpleApp_test/*_sm.h
	$(Q)-rm -f wise/simulations/wiseTracker_test/*_m.cc wise/simulations/wiseTracker_test/*_m.h wise/simulations/wiseTracker_test/*_sm.cc wise/simulations/wiseTracker_test/*_sm.h
	$(Q)-rm -f wise/src/*_m.cc wise/src/*_m.h wise/src/*_sm.cc wise/src/*_sm.h
	$(Q)-rm -f wise/src/gui/*_m.cc wise/src/gui/*_m.h wise/src/gui/*_sm.cc wise/src/gui/*_sm.h
	$(Q)-rm -f wise/src/gui/opencv/*_m.cc wise/src/gui/opencv/*_m.h wise/src/gui/opencv/*_sm.cc wise/src/gui/opencv/*_sm.h
	$(Q)-rm -f wise/src/node/*_m.cc wise/src/node/*_m.h wise/src/node/*_sm.cc wise/src/node/*_sm.h
	$(Q)-rm -f wise/src/node/application/*_m.cc wise/src/node/application/*_m.h wise/src/node/application/*_sm.cc wise/src/node/application/*_sm.h
	$(Q)-rm -f wise/src/node/application/Trackers/*_m.cc wise/src/node/application/Trackers/*_m.h wise/src/node/application/Trackers/*_sm.cc wise/src/node/application/Trackers/*_sm.h
	$(Q)-rm -f wise/src/node/application/Trackers/struck/*_m.cc wise/src/node/application/Trackers/struck/*_m.h wise/src/node/application/Trackers/struck/*_sm.cc wise/src/node/application/Trackers/struck/*_sm.h
	$(Q)-rm -f wise/src/node/application/Trackers/struck/GraphUtils/*_m.cc wise/src/node/application/Trackers/struck/GraphUtils/*_m.h wise/src/node/application/Trackers/struck/GraphUtils/*_sm.cc wise/src/node/application/Trackers/struck/GraphUtils/*_sm.h
	$(Q)-rm -f wise/src/node/application/Trackers/struck/Utils/*_m.cc wise/src/node/application/Trackers/struck/Utils/*_m.h wise/src/node/application/Trackers/struck/Utils/*_sm.cc wise/src/node/application/Trackers/struck/Utils/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseAppTest/*_m.cc wise/src/node/application/wiseAppTest/*_m.h wise/src/node/application/wiseAppTest/*_sm.cc wise/src/node/application/wiseAppTest/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraAppTest/*_m.cc wise/src/node/application/wiseCameraAppTest/*_m.h wise/src/node/application/wiseCameraAppTest/*_sm.cc wise/src/node/application/wiseCameraAppTest/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraApplication/*_m.cc wise/src/node/application/wiseCameraApplication/*_m.h wise/src/node/application/wiseCameraApplication/*_sm.cc wise/src/node/application/wiseCameraApplication/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraCAWCTracker/*_m.cc wise/src/node/application/wiseCameraCAWCTracker/*_m.h wise/src/node/application/wiseCameraCAWCTracker/*_sm.cc wise/src/node/application/wiseCameraCAWCTracker/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraClusterICF/*_m.cc wise/src/node/application/wiseCameraClusterICF/*_m.h wise/src/node/application/wiseCameraClusterICF/*_sm.cc wise/src/node/application/wiseCameraClusterICF/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraDPF/*_m.cc wise/src/node/application/wiseCameraDPF/*_m.h wise/src/node/application/wiseCameraDPF/*_sm.cc wise/src/node/application/wiseCameraDPF/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraICF/*_m.cc wise/src/node/application/wiseCameraICF/*_m.h wise/src/node/application/wiseCameraICF/*_sm.cc wise/src/node/application/wiseCameraICF/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraICF_NN/*_m.cc wise/src/node/application/wiseCameraICF_NN/*_m.h wise/src/node/application/wiseCameraICF_NN/*_sm.cc wise/src/node/application/wiseCameraICF_NN/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraKCF/*_m.cc wise/src/node/application/wiseCameraKCF/*_m.h wise/src/node/application/wiseCameraKCF/*_sm.cc wise/src/node/application/wiseCameraKCF/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraMTIC/*_m.cc wise/src/node/application/wiseCameraMTIC/*_m.h wise/src/node/application/wiseCameraMTIC/*_sm.cc wise/src/node/application/wiseCameraMTIC/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraMultiVideo/*_m.cc wise/src/node/application/wiseCameraMultiVideo/*_m.h wise/src/node/application/wiseCameraMultiVideo/*_sm.cc wise/src/node/application/wiseCameraMultiVideo/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraPeopleDet/*_m.cc wise/src/node/application/wiseCameraPeopleDet/*_m.h wise/src/node/application/wiseCameraPeopleDet/*_sm.cc wise/src/node/application/wiseCameraPeopleDet/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraPeriodicAlgo/*_m.cc wise/src/node/application/wiseCameraPeriodicAlgo/*_m.h wise/src/node/application/wiseCameraPeriodicAlgo/*_sm.cc wise/src/node/application/wiseCameraPeriodicAlgo/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraSimplePeriodicTracker/*_m.cc wise/src/node/application/wiseCameraSimplePeriodicTracker/*_m.h wise/src/node/application/wiseCameraSimplePeriodicTracker/*_sm.cc wise/src/node/application/wiseCameraSimplePeriodicTracker/*_sm.h
	$(Q)-rm -f wise/src/node/application/wiseCameraTrackerTest/*_m.cc wise/src/node/application/wiseCameraTrackerTest/*_m.h wise/src/node/application/wiseCameraTrackerTest/*_sm.cc wise/src/node/application/wiseCameraTrackerTest/*_sm.h
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
	$(Q)-rm -f wise/src/world/physicalProcess/*_m.cc wise/src/world/physicalProcess/*_m.h wise/src/world/physicalProcess/*_sm.cc wise/src/world/physicalProcess/*_sm.h
	$(Q)-rm -f wise/src/world/physicalProcess/wiseMovingTarget/*_m.cc wise/src/world/physicalProcess/wiseMovingTarget/*_m.h wise/src/world/physicalProcess/wiseMovingTarget/*_sm.cc wise/src/world/physicalProcess/wiseMovingTarget/*_sm.h
	$(Q)-rm -f wise/src/world/physicalProcess/wiseVideoFile/*_m.cc wise/src/world/physicalProcess/wiseVideoFile/*_m.h wise/src/world/physicalProcess/wiseVideoFile/*_sm.cc wise/src/world/physicalProcess/wiseVideoFile/*_sm.h
	$(Q)-rm -f wise/src/world/terrain/*_m.cc wise/src/world/terrain/*_m.h wise/src/world/terrain/*_sm.cc wise/src/world/terrain/*_sm.h
	$(Q)-rm -f wise/src/world/terrain/wiseEmptyTerrain/*_m.cc wise/src/world/terrain/wiseEmptyTerrain/*_m.h wise/src/world/terrain/wiseEmptyTerrain/*_sm.cc wise/src/world/terrain/wiseEmptyTerrain/*_sm.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES) $(SM_CC_FILES)  ./*.cc castalia/*.cc castalia/Simulations/*.cc castalia/Simulations/BANtest/*.cc castalia/Simulations/BridgeTest/*.cc castalia/Simulations/Parameters/*.cc castalia/Simulations/Parameters/MAC/*.cc castalia/Simulations/Parameters/Radio/*.cc castalia/Simulations/Parameters/SensorDevice/*.cc castalia/Simulations/Parameters/WirelessChannel/*.cc castalia/Simulations/Parameters/WirelessChannel/BANmodels/*.cc castalia/Simulations/connectivityMap/*.cc castalia/Simulations/radioTest/*.cc castalia/Simulations/simpleAggregation/*.cc castalia/Simulations/valuePropagation/*.cc castalia/Simulations/valueReporting/*.cc castalia/scripts/*.cc castalia/src/*.cc castalia/src/helpStructures/*.cc castalia/src/node/*.cc castalia/src/node/application/*.cc castalia/src/node/application/bridgeTest/*.cc castalia/src/node/application/connectivityMap/*.cc castalia/src/node/application/simpleAggregation/*.cc castalia/src/node/application/throughputTest/*.cc castalia/src/node/application/valuePropagation/*.cc castalia/src/node/application/valueReporting/*.cc castalia/src/node/communication/*.cc castalia/src/node/communication/mac/*.cc castalia/src/node/communication/mac/baselineBanMac/*.cc castalia/src/node/communication/mac/bypassMac/*.cc castalia/src/node/communication/mac/mac802154/*.cc castalia/src/node/communication/mac/tMac/*.cc castalia/src/node/communication/mac/tunableMac/*.cc castalia/src/node/communication/radio/*.cc castalia/src/node/communication/routing/*.cc castalia/src/node/communication/routing/bypassRouting/*.cc castalia/src/node/communication/routing/multipathRingsRouting/*.cc castalia/src/node/mobilityManager/*.cc castalia/src/node/mobilityManager/lineMobilityManager/*.cc castalia/src/node/mobilityManager/noMobilityManager/*.cc castalia/src/node/resourceManager/*.cc castalia/src/physicalProcess/*.cc castalia/src/physicalProcess/carsPhysicalProcess/*.cc castalia/src/physicalProcess/customizablePhysicalProcess/*.cc castalia/src/wirelessChannel/*.cc doc/*.cc doc/html/*.cc doc/html/search/*.cc doc/manual/*.cc doc/manual/figures/*.cc doc/pdfs/*.cc models/*.cc models/COM/*.cc models/CPU/*.cc models/SEN/*.cc utils/*.cc videos/*.cc videos/AVSS07/*.cc videos/Crowd_PETS09/*.cc videos/Crowd_PETS09/S2/*.cc videos/Crowd_PETS09/S2/L1/*.cc videos/Crowd_PETS09/S2/L1/Groundtruth/*.cc videos/Crowd_PETS09/S2/L1/Time_12-34/*.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_001/*.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_003/*.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_004/*.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_005/*.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_006/*.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_007/*.cc videos/Crowd_PETS09/S2/L1/Time_12-34/View_008/*.cc videos/ICGLab6/*.cc videos/ICGLab6/calibration/*.cc videos/ICGLab6/chap/*.cc videos/ICGLab6/chap/Groundtruth/*.cc videos/ICGLab6/leaf1/*.cc videos/ICGLab6/leaf1/Groundtruth/*.cc videos/ICGLab6/leaf2/*.cc videos/ICGLab6/leaf2/Groundtruth/*.cc videos/ICGLab6/much/*.cc videos/ICGLab6/much/Groundtruth/*.cc videos/ICGLab6/pose/*.cc videos/ICGLab6/pose/Groundtruth/*.cc videos/ICGLab6/table/*.cc videos/ICGLab6/table/Groundtruth/*.cc wise/*.cc wise/simulations/*.cc wise/simulations/python_scripts/*.cc wise/simulations/python_scripts/results/*.cc wise/simulations/wiseCameraCAWCTracker/*.cc wise/simulations/wiseCameraCAWCTracker/matlab/*.cc wise/simulations/wiseCameraCAWCTracker/matlab/bak/*.cc wise/simulations/wiseCameraCAWCTracker/matlab/utils/*.cc wise/simulations/wiseCameraDPF_example1/*.cc wise/simulations/wiseCameraDPF_example2/*.cc wise/simulations/wiseCameraDPF_example3/*.cc wise/simulations/wiseCameraICF/*.cc wise/simulations/wiseCameraICF/matlab/*.cc wise/simulations/wiseCameraICF_NN/*.cc wise/simulations/wiseCameraICF_NN/matlab/*.cc wise/simulations/wiseCameraKCF/*.cc wise/simulations/wiseCameraKCF/matlab/*.cc wise/simulations/wiseCameraMTIC/*.cc wise/simulations/wiseCameraMultiVideo/*.cc wise/simulations/wiseCameraPeopleDet/*.cc wise/simulations/wiseCameraPeopleDet/matlab/*.cc wise/simulations/wiseCameraPeopleDet/matlab/utils/*.cc wise/simulations/wiseCamera_test_dFOV/*.cc wise/simulations/wiseCamera_test_sFOV/*.cc wise/simulations/wiseSimpleApp_test/*.cc wise/simulations/wiseTracker_test/*.cc wise/src/*.cc wise/src/gui/*.cc wise/src/gui/opencv/*.cc wise/src/node/*.cc wise/src/node/application/*.cc wise/src/node/application/Trackers/*.cc wise/src/node/application/Trackers/struck/*.cc wise/src/node/application/Trackers/struck/GraphUtils/*.cc wise/src/node/application/Trackers/struck/Utils/*.cc wise/src/node/application/wiseAppTest/*.cc wise/src/node/application/wiseCameraAppTest/*.cc wise/src/node/application/wiseCameraApplication/*.cc wise/src/node/application/wiseCameraCAWCTracker/*.cc wise/src/node/application/wiseCameraClusterICF/*.cc wise/src/node/application/wiseCameraDPF/*.cc wise/src/node/application/wiseCameraICF/*.cc wise/src/node/application/wiseCameraICF_NN/*.cc wise/src/node/application/wiseCameraKCF/*.cc wise/src/node/application/wiseCameraMTIC/*.cc wise/src/node/application/wiseCameraMultiVideo/*.cc wise/src/node/application/wiseCameraPeopleDet/*.cc wise/src/node/application/wiseCameraPeriodicAlgo/*.cc wise/src/node/application/wiseCameraSimplePeriodicTracker/*.cc wise/src/node/application/wiseCameraTrackerTest/*.cc wise/src/node/resourceManager/*.cc wise/src/node/sensorManager/*.cc wise/src/node/sensorManager/sensorManager/*.cc wise/src/node/sensorManager/wiseCameraManager/*.cc wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/*.cc wise/src/node/sensorManager/wiseEmptySensorManager/*.cc wise/src/utils/*.cc wise/src/utils/gmm/*.cc wise/src/utils/gmm/c-gmm/*.cc wise/src/utils/libMvtnorm/*.cc wise/src/utils/libMvtnorm/libMvtnorm/*.cc wise/src/utils/pft/*.cc wise/src/wirelessChannel/*.cc wise/src/world/*.cc wise/src/world/physicalProcess/*.cc wise/src/world/physicalProcess/wiseMovingTarget/*.cc wise/src/world/physicalProcess/wiseVideoFile/*.cc wise/src/world/terrain/*.cc wise/src/world/terrain/wiseEmptyTerrain/*.cc

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
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/node/resourceManager/ResourceManager.h \
	castalia/src/node/resourceManager/ResourceManagerMessage_m.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
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
$O/wise/src/gui/WiseGuiWorld.o: wise/src/gui/WiseGuiWorld.cc \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseException.h \
	wise/src/utils/WiseTargetInfo.h
$O/wise/src/gui/opencv/WiseGuiWorldOpencv.o: wise/src/gui/opencv/WiseGuiWorldOpencv.cc \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/gui/opencv/WiseGuiWorldOpencv.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h
$O/wise/src/node/application/WiseApplicationPacket_m.o: wise/src/node/application/WiseApplicationPacket_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/WiseBaseApplication.o: wise/src/node/application/WiseBaseApplication.cc \
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
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannel.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	castalia/src/wirelessChannel/WirelessChannelTemporal.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/Trackers/struck/Config.o: wise/src/node/application/Trackers/struck/Config.cc \
	wise/src/node/application/Trackers/struck/Config.h
$O/wise/src/node/application/Trackers/struck/Features.o: wise/src/node/application/Trackers/struck/Features.cc \
	wise/src/node/application/Trackers/struck/Features.h \
	wise/src/node/application/Trackers/struck/ImageRep.h \
	wise/src/node/application/Trackers/struck/Sample.h \
	wise/src/node/application/Trackers/struck/_Rect.h
$O/wise/src/node/application/Trackers/struck/HaarFeature.o: wise/src/node/application/Trackers/struck/HaarFeature.cc \
	wise/src/node/application/Trackers/struck/HaarFeature.h \
	wise/src/node/application/Trackers/struck/ImageRep.h \
	wise/src/node/application/Trackers/struck/Sample.h \
	wise/src/node/application/Trackers/struck/_Rect.h
$O/wise/src/node/application/Trackers/struck/HaarFeatures.o: wise/src/node/application/Trackers/struck/HaarFeatures.cc \
	wise/src/node/application/Trackers/struck/Config.h \
	wise/src/node/application/Trackers/struck/Features.h \
	wise/src/node/application/Trackers/struck/HaarFeature.h \
	wise/src/node/application/Trackers/struck/HaarFeatures.h \
	wise/src/node/application/Trackers/struck/ImageRep.h \
	wise/src/node/application/Trackers/struck/Sample.h \
	wise/src/node/application/Trackers/struck/_Rect.h
$O/wise/src/node/application/Trackers/struck/HistogramFeatures.o: wise/src/node/application/Trackers/struck/HistogramFeatures.cc \
	wise/src/node/application/Trackers/struck/Config.h \
	wise/src/node/application/Trackers/struck/Features.h \
	wise/src/node/application/Trackers/struck/HistogramFeatures.h \
	wise/src/node/application/Trackers/struck/ImageRep.h \
	wise/src/node/application/Trackers/struck/Sample.h \
	wise/src/node/application/Trackers/struck/_Rect.h
$O/wise/src/node/application/Trackers/struck/ImageRep.o: wise/src/node/application/Trackers/struck/ImageRep.cc \
	wise/src/node/application/Trackers/struck/ImageRep.h \
	wise/src/node/application/Trackers/struck/_Rect.h
$O/wise/src/node/application/Trackers/struck/LaRank.o: wise/src/node/application/Trackers/struck/LaRank.cc \
	wise/src/node/application/Trackers/struck/Config.h \
	wise/src/node/application/Trackers/struck/Features.h \
	wise/src/node/application/Trackers/struck/GraphUtils/GraphUtils.h \
	wise/src/node/application/Trackers/struck/ImageRep.h \
	wise/src/node/application/Trackers/struck/Kernels.h \
	wise/src/node/application/Trackers/struck/LaRank.h \
	wise/src/node/application/Trackers/struck/Sample.h \
	wise/src/node/application/Trackers/struck/_Rect.h
$O/wise/src/node/application/Trackers/struck/MultiFeatures.o: wise/src/node/application/Trackers/struck/MultiFeatures.cc \
	wise/src/node/application/Trackers/struck/Features.h \
	wise/src/node/application/Trackers/struck/ImageRep.h \
	wise/src/node/application/Trackers/struck/MultiFeatures.h \
	wise/src/node/application/Trackers/struck/Sample.h \
	wise/src/node/application/Trackers/struck/_Rect.h
$O/wise/src/node/application/Trackers/struck/RawFeatures.o: wise/src/node/application/Trackers/struck/RawFeatures.cc \
	wise/src/node/application/Trackers/struck/Config.h \
	wise/src/node/application/Trackers/struck/Features.h \
	wise/src/node/application/Trackers/struck/ImageRep.h \
	wise/src/node/application/Trackers/struck/RawFeatures.h \
	wise/src/node/application/Trackers/struck/Sample.h \
	wise/src/node/application/Trackers/struck/_Rect.h
$O/wise/src/node/application/Trackers/struck/Sampler.o: wise/src/node/application/Trackers/struck/Sampler.cc \
	wise/src/node/application/Trackers/struck/Config.h \
	wise/src/node/application/Trackers/struck/Sampler.h \
	wise/src/node/application/Trackers/struck/_Rect.h
$O/wise/src/node/application/Trackers/struck/_Tracker.o: wise/src/node/application/Trackers/struck/_Tracker.cc \
	wise/src/node/application/Trackers/struck/Config.h \
	wise/src/node/application/Trackers/struck/Features.h \
	wise/src/node/application/Trackers/struck/GraphUtils/GraphUtils.h \
	wise/src/node/application/Trackers/struck/HaarFeature.h \
	wise/src/node/application/Trackers/struck/HaarFeatures.h \
	wise/src/node/application/Trackers/struck/HistogramFeatures.h \
	wise/src/node/application/Trackers/struck/ImageRep.h \
	wise/src/node/application/Trackers/struck/Kernels.h \
	wise/src/node/application/Trackers/struck/LaRank.h \
	wise/src/node/application/Trackers/struck/MultiFeatures.h \
	wise/src/node/application/Trackers/struck/RawFeatures.h \
	wise/src/node/application/Trackers/struck/Sample.h \
	wise/src/node/application/Trackers/struck/Sampler.h \
	wise/src/node/application/Trackers/struck/_Rect.h \
	wise/src/node/application/Trackers/struck/_Tracker.h
$O/wise/src/node/application/Trackers/struck/main.o: wise/src/node/application/Trackers/struck/main.cc \
	wise/src/node/application/Trackers/struck/Config.h \
	wise/src/node/application/Trackers/struck/_Rect.h \
	wise/src/node/application/Trackers/struck/_Tracker.h
$O/wise/src/node/application/Trackers/struck/GraphUtils/GraphUtils.o: wise/src/node/application/Trackers/struck/GraphUtils/GraphUtils.cc \
	wise/src/node/application/Trackers/struck/GraphUtils/GraphUtils.h
$O/wise/src/node/application/Trackers/struck/Utils/histogram.o: wise/src/node/application/Trackers/struck/Utils/histogram.cc \
	wise/src/node/application/Trackers/struck/Utils/histogram.h \
	wise/src/node/application/Trackers/struck/Utils/my_exception.h \
	wise/src/node/application/Trackers/struck/Utils/shell_utils.h
$O/wise/src/node/application/Trackers/struck/Utils/log.o: wise/src/node/application/Trackers/struck/Utils/log.cc \
	wise/src/node/application/Trackers/struck/Utils/log.h
$O/wise/src/node/application/Trackers/struck/Utils/math_utils.o: wise/src/node/application/Trackers/struck/Utils/math_utils.cc \
	wise/src/node/application/Trackers/struck/Utils/eigen_unsym.h \
	wise/src/node/application/Trackers/struck/Utils/log.h \
	wise/src/node/application/Trackers/struck/Utils/math_utils.h \
	wise/src/node/application/Trackers/struck/Utils/my_exception.h \
	wise/src/node/application/Trackers/struck/Utils/shell_utils.h
$O/wise/src/node/application/Trackers/struck/Utils/shell_utils.o: wise/src/node/application/Trackers/struck/Utils/shell_utils.cc \
	wise/src/node/application/Trackers/struck/Utils/shell_utils.h
$O/wise/src/node/application/Trackers/struck/Utils/string_utils.o: wise/src/node/application/Trackers/struck/Utils/string_utils.cc \
	wise/src/node/application/Trackers/struck/Utils/my_exception.h \
	wise/src/node/application/Trackers/struck/Utils/string_utils.h
$O/wise/src/node/application/Trackers/struck/Utils/time_utils.o: wise/src/node/application/Trackers/struck/Utils/time_utils.cc \
	wise/src/node/application/Trackers/struck/Utils/time_utils.h
$O/wise/src/node/application/wiseAppTest/WiseAppTest.o: wise/src/node/application/wiseAppTest/WiseAppTest.cc \
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
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/application/wiseAppTest/WiseAppTest.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorMessage_m.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
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
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/application/wiseCameraAppTest/WiseCameraAppTest.h \
	wise/src/node/application/wiseCameraAppTest/WiseCameraAppTestPacket_m.h \
	wise/src/node/application/wiseCameraApplication/WiseCameraApplication.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraAppTest/WiseCameraAppTestPacket_m.o: wise/src/node/application/wiseCameraAppTest/WiseCameraAppTestPacket_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/wiseCameraAppTest/WiseCameraAppTestPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseCameraApplication/WiseCameraApplication.o: wise/src/node/application/wiseCameraApplication/WiseCameraApplication.cc \
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
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/application/wiseCameraApplication/WiseCameraApplication.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTracker.o: wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTracker.cc \
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
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/Trackers/struck/Config.h \
	wise/src/node/application/Trackers/struck/_Rect.h \
	wise/src/node/application/Trackers/struck/_Tracker.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/application/wiseCameraApplication/WiseCameraApplication.h \
	wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTracker.h \
	wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTrackerPkt_m.h \
	wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTracker_utils.h \
	wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgo.h \
	wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgoPacket_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTrackerPkt_m.o: wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTrackerPkt_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTrackerPkt_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTracker_utils.o: wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTracker_utils.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/Trackers/struck/Config.h \
	wise/src/node/application/Trackers/struck/Utils/histogram.h \
	wise/src/node/application/Trackers/struck/Utils/math_utils.h \
	wise/src/node/application/Trackers/struck/Utils/my_exception.h \
	wise/src/node/application/Trackers/struck/_Rect.h \
	wise/src/node/application/Trackers/struck/_Tracker.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTrackerPkt_m.h \
	wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTracker_utils.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseUtils.h
$O/wise/src/node/application/wiseCameraClusterICF/WiseCameraClusterICF.o: wise/src/node/application/wiseCameraClusterICF/WiseCameraClusterICF.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/tMac/TMacControlMessage_m.h \
	castalia/src/node/communication/mac/tMac/TMacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/application/wiseCameraApplication/WiseCameraApplication.h \
	wise/src/node/application/wiseCameraClusterICF/WiseCameraClusterICF.h \
	wise/src/node/application/wiseCameraClusterICF/WiseCameraClusterICFMsg_m.h \
	wise/src/node/application/wiseCameraClusterICF/WiseCameraClusterICF_utils.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraClusterICF/WiseCameraClusterICFMsg_m.o: wise/src/node/application/wiseCameraClusterICF/WiseCameraClusterICFMsg_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/wiseCameraClusterICF/WiseCameraClusterICFMsg_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseCameraDPF/WiseCameraDPF.o: wise/src/node/application/wiseCameraDPF/WiseCameraDPF.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/tMac/TMacControlMessage_m.h \
	castalia/src/node/communication/mac/tMac/TMacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/application/wiseCameraApplication/WiseCameraApplication.h \
	wise/src/node/application/wiseCameraDPF/WiseCameraDPF.h \
	wise/src/node/application/wiseCameraDPF/WiseCameraDPFMessage_custom.h \
	wise/src/node/application/wiseCameraDPF/WiseCameraDPFMessage_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseException.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/utils/gmm/c-gmm/clust_defs.h \
	wise/src/utils/gmm/wise_utils_gmm.h \
	wise/src/utils/pft/pft.h \
	wise/src/utils/pft/pft_exception.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraDPF/WiseCameraDPFMessage_m.o: wise/src/node/application/wiseCameraDPF/WiseCameraDPFMessage_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/wiseCameraDPF/WiseCameraDPFMessage_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/gmm/c-gmm/clust_defs.h \
	wise/src/utils/gmm/wise_utils_gmm.h
$O/wise/src/node/application/wiseCameraICF/WiseCameraICF.o: wise/src/node/application/wiseCameraICF/WiseCameraICF.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/tMac/TMacControlMessage_m.h \
	castalia/src/node/communication/mac/tMac/TMacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/application/wiseCameraApplication/WiseCameraApplication.h \
	wise/src/node/application/wiseCameraICF/WiseCameraICF.h \
	wise/src/node/application/wiseCameraICF/WiseCameraICFMsg_m.h \
	wise/src/node/application/wiseCameraICF/WiseCameraICF_utils.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraICF/WiseCameraICFMsg_m.o: wise/src/node/application/wiseCameraICF/WiseCameraICFMsg_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/wiseCameraICF/WiseCameraICFMsg_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseCameraICF/WiseCameraICF_utils.o: wise/src/node/application/wiseCameraICF/WiseCameraICF_utils.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/wiseCameraICF/WiseCameraICFMsg_m.h \
	wise/src/node/application/wiseCameraICF/WiseCameraICF_utils.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseUtils.h
$O/wise/src/node/application/wiseCameraICF_NN/WiseCameraICF_NN.o: wise/src/node/application/wiseCameraICF_NN/WiseCameraICF_NN.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/tMac/TMacControlMessage_m.h \
	castalia/src/node/communication/mac/tMac/TMacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/application/wiseCameraApplication/WiseCameraApplication.h \
	wise/src/node/application/wiseCameraICF/WiseCameraICFMsg_m.h \
	wise/src/node/application/wiseCameraICF/WiseCameraICF_utils.h \
	wise/src/node/application/wiseCameraICF_NN/WiseCameraICF_NN.h \
	wise/src/node/application/wiseCameraICF_NN/hungarian.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraICF_NN/hungarian.o: wise/src/node/application/wiseCameraICF_NN/hungarian.cc \
	wise/src/node/application/wiseCameraICF_NN/hungarian.h
$O/wise/src/node/application/wiseCameraKCF/WiseCameraKCF.o: wise/src/node/application/wiseCameraKCF/WiseCameraKCF.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/tMac/TMacControlMessage_m.h \
	castalia/src/node/communication/mac/tMac/TMacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/application/wiseCameraApplication/WiseCameraApplication.h \
	wise/src/node/application/wiseCameraKCF/WiseCameraKCF.h \
	wise/src/node/application/wiseCameraKCF/WiseCameraKCFMsg_m.h \
	wise/src/node/application/wiseCameraKCF/WiseCameraKCF_utils.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraKCF/WiseCameraKCFMsg_m.o: wise/src/node/application/wiseCameraKCF/WiseCameraKCFMsg_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/wiseCameraKCF/WiseCameraKCFMsg_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC.o: wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/tMac/TMacControlMessage_m.h \
	castalia/src/node/communication/mac/tMac/TMacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/application/wiseCameraApplication/WiseCameraApplication.h \
	wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC.h \
	wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC_Msg_m.h \
	wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC_utils.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/utils/libMvtnorm/libMvtnorm/mvtnorm.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC_Msg_m.o: wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC_Msg_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC_Msg_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC_utils.o: wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC_utils.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC_Msg_m.h \
	wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC_utils.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseUtils.h
$O/wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideo.o: wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideo.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/tMac/TMacControlMessage_m.h \
	castalia/src/node/communication/mac/tMac/TMacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/application/wiseCameraApplication/WiseCameraApplication.h \
	wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideo.h \
	wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideoPacketFull_m.h \
	wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideoPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgo.h \
	wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgoPacket_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideoPacketFull_m.o: wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideoPacketFull_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideoPacketFull_m.h \
	wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideoPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideoPacket_m.o: wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideoPacket_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/wiseCameraMultiVideo/WiseCameraMultiVideoPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseCameraPeopleDet/WiseCameraPeopleDet.o: wise/src/node/application/wiseCameraPeopleDet/WiseCameraPeopleDet.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/tMac/TMacControlMessage_m.h \
	castalia/src/node/communication/mac/tMac/TMacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/application/wiseCameraApplication/WiseCameraApplication.h \
	wise/src/node/application/wiseCameraPeopleDet/WiseCameraPeopleDet.h \
	wise/src/node/application/wiseCameraPeopleDet/WiseCameraPeopleDetPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgo.h \
	wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgoPacket_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraPeopleDet/WiseCameraPeopleDetPacket_m.o: wise/src/node/application/wiseCameraPeopleDet/WiseCameraPeopleDetPacket_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/wiseCameraPeopleDet/WiseCameraPeopleDetPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgo.o: wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgo.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/tMac/TMacControlMessage_m.h \
	castalia/src/node/communication/mac/tMac/TMacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/application/wiseCameraApplication/WiseCameraApplication.h \
	wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgo.h \
	wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgoPacket_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraVideoMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/utils/WiseUtils.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgoPacket_m.o: wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgoPacket_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgoPacket_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker.o: wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/helpStructures/TimerService.h \
	castalia/src/helpStructures/TimerServiceMessage_m.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	castalia/src/node/communication/mac/MacPacket_m.h \
	castalia/src/node/communication/mac/tMac/TMacControlMessage_m.h \
	castalia/src/node/communication/mac/tMac/TMacPacket_m.h \
	castalia/src/node/communication/radio/Radio.h \
	castalia/src/node/communication/radio/RadioControlMessage_m.h \
	castalia/src/node/communication/radio/RadioSupportFunctions.h \
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/application/wiseCameraApplication/WiseCameraApplication.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker_m.o: wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/application/wiseCameraTrackerTest/WiseCameraTrackerTest.o: wise/src/node/application/wiseCameraTrackerTest/WiseCameraTrackerTest.cc \
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
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/application/wiseCameraApplication/WiseCameraApplication.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseCameraSimplePeriodicTracker_m.h \
	wise/src/node/application/wiseCameraSimplePeriodicTracker/WiseDefinitionsTracking.h \
	wise/src/node/application/wiseCameraTrackerTest/WiseCameraTrackerTest.h \
	wise/src/node/application/wiseCameraTrackerTest/WiseCameraTrackerTestMessage_m.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/application/wiseCameraTrackerTest/WiseCameraTrackerTestMessage_m.o: wise/src/node/application/wiseCameraTrackerTest/WiseCameraTrackerTestMessage_m.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/node/application/ApplicationPacket_m.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/wiseCameraTrackerTest/WiseCameraTrackerTestMessage_m.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h
$O/wise/src/node/resourceManager/PropertyFileReader.o: wise/src/node/resourceManager/PropertyFileReader.cc \
	wise/src/node/resourceManager/PropertyFileReader.h
$O/wise/src/node/resourceManager/WiseResourceManager.o: wise/src/node/resourceManager/WiseResourceManager.cc \
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
	castalia/src/node/mobilityManager/VirtualMobilityManager.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	castalia/src/wirelessChannel/WirelessChannelMessages_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/application/WiseApplicationPacket_m.h \
	wise/src/node/application/WiseBaseApplication.h \
	wise/src/node/resourceManager/PropertyFileReader.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/resourceManager/WiseResourceManager_utils.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
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
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
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
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
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
	wise/src/gui/WiseGuiWorld.h \
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
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
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
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraManager.h \
	wise/src/node/sensorManager/wiseCameraManager/WiseCameraMessage_m.h \
	wise/src/node/sensorManager/wiseCameraManager/cameraModel.h \
	wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraHandler.h \
	wise/src/node/sensorManager/wiseCameraManager/xmlUtil.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseException.h \
	wise/src/utils/WiseTargetInfo.h \
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
	wise/src/gui/WiseGuiWorld.h \
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
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
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
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/node/sensorManager/WiseBaseSensorManager.h \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorManager.h \
	wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorMessage_m.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/physicalProcess/WisePhysicalProcessMessage_m.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorMessage_m.o: wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorMessage_m.cc \
	wise/src/node/sensorManager/WiseSensorManagerMessage_m.h \
	wise/src/node/sensorManager/wiseEmptySensorManager/WiseEmptySensorMessage_m.h
$O/wise/src/utils/WiseDebug.o: wise/src/utils/WiseDebug.cc \
	wise/src/utils/WiseDebug.h
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
$O/wise/src/world/physicalProcess/WiseBasePhysicalProcess.o: wise/src/world/physicalProcess/WiseBasePhysicalProcess.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	castalia/src/physicalProcess/PhysicalProcessMessage_m.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
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
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
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
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/resourceManager/WiseResourceManager.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
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
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseDebug.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/terrain/WiseBaseTerrain.h
$O/wise/src/world/terrain/wiseEmptyTerrain/WiseEmptyTerrain.o: wise/src/world/terrain/wiseEmptyTerrain/WiseEmptyTerrain.cc \
	castalia/src/CastaliaMessages.h \
	castalia/src/helpStructures/CastaliaModule.h \
	castalia/src/helpStructures/DebugInfoWriter.h \
	castalia/src/helpStructures/OmnetCompatibility.h \
	wise/src/gui/WiseGuiWorld.h \
	wise/src/node/resourceManager/WiseResourceManagerMessage_m.h \
	wise/src/utils/WiseCameraInfo.h \
	wise/src/utils/WiseTargetInfo.h \
	wise/src/world/terrain/WiseBaseTerrain.h \
	wise/src/world/terrain/wiseEmptyTerrain/WiseEmptyTerrain.h

