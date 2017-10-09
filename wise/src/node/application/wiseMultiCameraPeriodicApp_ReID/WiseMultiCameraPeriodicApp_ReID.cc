// *****************************************************************************************
// Copyright (C) 2017 Juan C. SanMiguel and Andrea Cavallaro
// You may use, distribute and modify this code under the terms of the ACADEMIC PUBLIC
// license (see the attached LICENSE_WISE file).
//
// This file is part of the WiseMnet simulator
//
// Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// Please cite the following reference when publishing results obtained with WiseMnet:
//   J. SanMiguel & A. Cavallaro,
//   "Networked Computer Vision: the importance of a holistic simulator",
//   IEEE Computer, 50(7):35-43, Jul 2017, http://ieeexplore.ieee.org/document/7971873/
// *****************************************************************************************

/**
 * \file WiseMultiCameraPeriodicApp_ReID.cc
 * \author Juan C. SanMiguel (2017)
 * \brief Source file for the WiseMultiCameraPeriodicApp_ReID class
 * \version 1.4
 */
#include <wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/WiseMultiCameraPeriodicApp_ReID.h>
#include <wise/src/node/application/wiseMultiCameraPeriodicApp_ReID/WiseMultiCameraPeriodicApp_ReIDPacket_m.h>//packet format
#include <wise/src/utils/WiseDebug.h> //for logs/debug (constant WISE_DEBUG_LEVEL must be defined first)
#include <wise/src/utils/WiseUtils.h>
using namespace std;

//register module in simulator
Define_Module(WiseMultiCameraPeriodicApp_ReID);

/*! Class initialization and getting of user-defined variables in omnetpp.ini*/
void WiseMultiCameraPeriodicApp_ReID::at_startup()
{
    // Called upon simulation start-up
    WISE_DEBUG_32("WiseCamPerAppREID::startup()");

	// Access related-module parameters (read number of targets)
	//cModule *network = getParentModule()->getParentModule();

	//read module parameters
	_dataTypeTX = par("dataTypeTX"); //type of data to send
	_sinkNode = par("sinkNode"); //indicates the node in the network being "sink"
	_extractGabor = par("extractGabor"); //enable Gabor features
	_extractRGB = par("extractRGB");     //enable RGB   features
	_use_gt_detections = par("use_gt_detections"); //use GT detections instead of HOG

	_show_internals = par("show_internals");
	_show_sink = par("show_sink");

	determineSinkNode();
	initFeatureExtractorGabor();
}

void WiseMultiCameraPeriodicApp_ReID::determineSinkNode()
{
    WISE_DEBUG_32("WiseCamPerAppREID::startup()");
    //NOTE: currently we assume that the "sink" is known to all cameras and introduced in *.ini files

    //determine the sink node via direct connection
    //_sinkNode = self;
    //for (int i = 0; i < n_nodes; i++) {
    //        if (i == self)
    //            continue;
    //        cModule *m = getParentModule()->getParentModule(); // m=SN
    //        m = m->getSubmodule("node", i)->getSubmodule("Application");
    //
    //        WiseMultiCameraPeriodicApp_ReID *c = check_and_cast<WiseMultiCameraPeriodicApp_ReID*>(m);
    //        if (c->isSink == true)
    //            _sinkNode = i;
    //}
    if (_sinkNode == self)
        isSink = true;
    else
        isSink = false;
}

/*!
 * ...
 */
void WiseMultiCameraPeriodicApp_ReID::initFeatureExtractorGabor()
{
    WISE_DEBUG_32("WiseCamPerAppREID::startup()");

    //only no-sink nodes do processing and generate result files
    if (isSink == false)
    {
        _hog = new cv::HOGDescriptor();
        _hog->setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());

        if (_extractGabor){
            int ksize = 31;
            double sig[] = {1,2};
            double th[] = {0, 3.14/2};
            double lm[] = {4,8};
            double gm[] = {0.3, 0.4}; //0.02
            double ps = 0;

            cv::Mat kernel1 = cv::getGaborKernel(cv::Size(ksize,ksize), sig[1], th[0], lm[0], gm[1], ps);
            cv::Mat kernel2 = cv::getGaborKernel(cv::Size(ksize,ksize), sig[0], th[0], lm[1], gm[0], ps);
            cv::Mat kernel3 = cv::getGaborKernel(cv::Size(ksize,ksize), sig[0], th[0], lm[0], gm[0], ps);
            cv::Mat kernel4 = cv::getGaborKernel(cv::Size(ksize,ksize), sig[1], th[1], lm[0], gm[0], ps);
            cv::Mat kernel5 = cv::getGaborKernel(cv::Size(ksize,ksize), sig[0], th[1], lm[1], gm[0], ps);
            cv::Mat kernel6 = cv::getGaborKernel(cv::Size(ksize,ksize), sig[1], th[1], lm[1], gm[0], ps);
            cv::Mat kernel7 = cv::getGaborKernel(cv::Size(ksize,ksize), sig[0], th[1], lm[0], gm[1], ps);
            cv::Mat kernel8 = cv::getGaborKernel(cv::Size(ksize,ksize), sig[1], th[1], lm[1], gm[1], ps);
            _GKernelList.push_back(kernel1);
            _GKernelList.push_back(kernel2);
            _GKernelList.push_back(kernel3);
            _GKernelList.push_back(kernel4);
            _GKernelList.push_back(kernel5);
            _GKernelList.push_back(kernel6);
            _GKernelList.push_back(kernel7);
            _GKernelList.push_back(kernel8);
        }
    }
}

/*!
 * Init resources for processing. Declared in base class WiseCameraPeriodicApp.
 */
bool WiseMultiCameraPeriodicApp_ReID::at_init()
{
    WISE_DEBUG_32("WiseCamPerAppREID::startup()");

    if (this->isSink)
    {
        _win_sink << "Network sink id="<< _camID << std::endl;
        return false;
    }

    //create GUI windows
    double cpuf = this->resMgr->getPROInfo().clockfreq;
    double senf = this->resMgr->getSENFrameRate();

    _win_dets << "Camera id=" << _camID << ":detections (sen=" << senf<<"fps cpu="<<cpuf/1e9<<" Ghz)"<<std::endl;
    _win_crop << "Camera id=" << _camID << ":cropped image"<<std::endl;
    _win_desc_RGB << "Camera id=" << _camID << ":descriptor RGB"<<std::endl;
    _win_desc_GAB << "Camera id=" << _camID << ":descriptor GAB"<<std::endl;

    cv::namedWindow(_win_dets.str().c_str());

    if (_show_internals)
    {
       //cv::namedWindow(_win_crop.str().c_str());
       // cv::namedWindow(_win_desc_RGB.str().c_str());
       // cv::namedWindow(_win_desc_GAB.str().c_str());
    }

    if (this->_pause_place_GUI)
    {
        cv::Mat temp = cv::Mat::zeros(480,640,CV_32F);

        //if (_show_internals)
        //{
        //    cv::imshow(_win_crop.str().c_str(),temp);
        //    if (_extractRGB) cv::imshow(_win_desc_RGB.str(),temp);
        //    if (_extractGabor) cv::imshow(_win_desc_GAB.str(),temp);
        //}

        cv::imshow(_win_dets.str(),temp);
        std::cout << "Please place the GUI and press any key..." << std::endl;
        cv::waitKey(0);
    }

    return true;
}


/*!
 * Called when a new sample (image) is ready. For each target, KF processing consist on computing and initial detection/estimation,
 * which is later sent to other neighbors to initiate consensus. Declared in base class WiseCameraPeriodicApp.
 */
bool WiseMultiCameraPeriodicApp_ReID::at_sample()
{
    // DO PROCESSING
    WISE_DEBUG_32("WiseCamPerAppREID::at_sample()");

    if (this->isSink)
        return false;

    // Called when a new sample (image) is ready
    _step_counter++;

    cv::Mat frame = _buf.frame;
    //cv::resize(_buf.frame, frame, cvSize(320,240));

    //vector containing the detected people
    std::vector<cv::Rect> found;

    if(_use_gt_detections==false)
    {
        // run the detector with default parameters. to get a higher hit-rate
        // (and more false alarms, respectively), decrease the hitThreshold and
        // groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
        double hitThreshold = HOG_HIT_THRESHOLD;
        double scale0= HOG_SCALE;
        int groupThreshold=HOG_GROUP_THRESHOLD;
        cv::Size minSize = cv::Size(HOG_MIN_SIZE,HOG_MIN_SIZE);//cv::Size minSize = cv::Size(8,8);
        cv::Size maxSize = cv::Size(HOG_MAX_SIZE,HOG_MAX_SIZE);//cv::Size maxSize = cv::Size(32,32);
        _hog->detectMultiScale(frame, found, hitThreshold, minSize, maxSize, scale0, groupThreshold);

         //t = (double)getTickCount() - t;
         //printf("tdetection time = %gms\n", t*1000./cv::getTickFrequency());
        size_t i, j;
        for( i = 0; i < found.size(); i++ )
        {
            cv::Rect r = found[i];
            for( j = 0; j < found.size(); j++ )
                if( j != i && (r & found[j]) == r)
                    break;

            if( j == found.size() )
            {
                r.x += cvRound(r.width*0.1);
                r.width = cvRound(r.width*0.8);
                r.y += cvRound(r.height*0.07);
                r.height = cvRound(r.height*0.8);
                //found_filtered.push_back(r);
                cv::rectangle(frame, r.tl(), r.br(), cv::Scalar(0,255,0), 3);
            }
        }
    }
    else
    {
        if(_gtreader!=NULL)
        {
            //use the detections provided by the ground-truth
            std::map<int,std::vector<target_detection_t>> *alldets = _gtreader->getData();
            std::vector<target_detection_t> dets = (*alldets)[_buf.curFrame];

            for (int i=0;i<(int)dets.size();i++)
            {
               target_detection_t d = dets[i];
               int width=abs(d.bb_x_tl-d.bb_x_br);
               int height=abs(d.bb_y_tl-d.bb_y_br);
               cv::Rect a(d.bb_x_tl,d.bb_y_tl,width,height);
               found.push_back(a);
               cv::rectangle(frame, a.tl(), a.br(), cv::Scalar(0,255,0), 3);
            }
        }
    }
    _numDet = found.size();
    WISE_DEBUG_32("WiseCamPerAppREID:: NumDet=" << _numDet);

    // PLOT DETECTIONS
    if(!isSink)
    {
        //get the frame number and write it on the current frame
        stringstream ss;
        //cv::rectangle(frame, cv::Point(10, 2), cv::Point(100,20), cv::Scalar(255,255,255), -1);
        ss << _buf.curFrame;
        cv::putText(frame,  ss.str().c_str(), cv::Point(frame.cols-60, 40),cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0,0,255));

        //show the current frame with tracking data
        cv::Mat newFrame;
        cv::resize(frame,newFrame,cv::Size(frame.cols*_displayWinScale,frame.rows*_displayWinScale));
        cv::imshow(_win_dets.str().c_str(),newFrame);
        cv::waitKey(1);
    }

    // SEND DATA TO SINK NODE
    generateDescriptors(_buf.frame, found);
    sendDescriptors();
    return true;
}

void WiseMultiCameraPeriodicApp_ReID::generateDescriptors(cv::Mat frame, std::vector<cv::Rect> found)
{
    WISE_DEBUG_32("WiseCamPerAppREID::generateDescriptors()");

    //RGB and GABOR descriptors
    cv::Mat allDescRGB,allDescGAB;

    //Parameters for REID descriptors
    int histSize = HIST_SIZE; //number of bins - typical value for people re-id
    float range[] = { 0, 256 } ;     /// Set the ranges ( for B,G,R) ) - step1
    const float* histRange = { range };     /// Set the ranges ( for B,G,R) ) - step2
    bool uniform = true;
    bool accumulate = false;

    for(int i = 0; i < (int)found.size(); i++ )
    {
        cv::Rect roi = found[i];
        if (roi.x < 0 || roi.y < 0 || roi.width < 0 || roi.height < 0 ||
                roi.x + roi.width > frame.cols || roi.y + roi.height > frame.rows){
            //option1
            //_numDet = _numDet -1;
            //continue;

            //option2
            if (roi.x < 0) roi.x = 0;
            if (roi.y < 0) roi.y = 0;
            if (roi.width < 0) roi.width = 0;
            if (roi.height < 0) roi.height = 0;

            if (roi.x + roi.width > frame.cols) roi.width = frame.cols - roi.x;
            if (roi.y + roi.height > frame.rows) roi.height = frame.rows - roi.y;
        }

        cv::Mat mask = cv::Mat::zeros(frame.size(), cv::DataType<uchar>::type);  // type of mask is CV_8U
        mask(roi) = cv::Scalar(255, 255, 255);

        // RGB HISTOGRAM
        if (_extractRGB){
            std::vector<cv::Mat> bgr_planes;
            cv::split(frame, bgr_planes); //split RGB image into planes

            // Compute the RGB histograms:
            cv::Mat b_hist, g_hist, r_hist;
            cv::calcHist( &bgr_planes[0], 1, 0, mask, b_hist, 1, &histSize, &histRange, uniform, accumulate );
            cv::calcHist( &bgr_planes[1], 1, 0, mask, g_hist, 1, &histSize, &histRange, uniform, accumulate );
            cv::calcHist( &bgr_planes[2], 1, 0, mask, r_hist, 1, &histSize, &histRange, uniform, accumulate );

            // Concatenate the RGB histograms
            if ((allDescRGB.cols * allDescRGB.rows) == 0)
                b_hist.copyTo(allDescRGB);
            else
                cv::vconcat(allDescRGB, b_hist, allDescRGB);

            cv::vconcat(allDescRGB, g_hist, allDescRGB);
            cv::vconcat(allDescRGB, r_hist, allDescRGB);

            if(_show_internals)
                displayDescBGR(b_hist, g_hist, r_hist, histSize, _win_desc_RGB.str());
        }

        // GABOR HISTOGRAM
        //Example at https://cvtuts.wordpress.com/2014/04/27/gabor-filters-a-practical-overview/

        if (_extractGabor){

            //Conversion to gray-level image using float type
            cv::Mat greyMatf, greyMat;
            cv::cvtColor(frame, greyMat, cv::COLOR_BGR2GRAY);
            greyMat.convertTo(greyMatf,CV_32F);

            cv::Mat res,res_acc = cv::Mat::zeros(frame.size(), CV_32F); //auxiliary images

            for (int k = 0; k<(int)_GKernelList.size();k++){
                cv::filter2D(greyMatf, res, CV_32F, _GKernelList[k]);
                cv::max(res, res_acc, res_acc);
            }

            // Compute the histogram
            cv::Mat gab_hist;
            cv::calcHist( &res_acc, 1, 0, mask, gab_hist, 1, &histSize, &histRange, uniform, accumulate );

            // Concatenate the histograms
            if ((allDescGAB.cols * allDescGAB.rows) == 0)
                gab_hist.copyTo(allDescGAB);
            else
                cv::vconcat(allDescGAB, gab_hist, allDescGAB);

            if(_show_internals)
                displayDescGABOR(gab_hist, histSize, _win_desc_GAB.str());
        }

        //display data
        if(_show_internals)
        {
            cv::Mat miniMat = frame(roi);
            cv::imshow(_win_crop.str(),miniMat);
            cv::waitKey(0);
        }
    }
    //copy generated descriptors to internal class variables
    allDescRGB.copyTo(_allDescRGB);
    allDescGAB.copyTo(_allDescGAB);
}


void WiseMultiCameraPeriodicApp_ReID::sendDescriptors()
{
    WISE_DEBUG_32("WiseCamPerAppREID::sendDescriptors()");

    int histSize = HIST_SIZE; //typical value for people re-id

    cv::Mat allDesc;
    double DescBitsRaw=0, DescBitsCod=0;
    if (_numDet > 0){

        if (_extractGabor && _extractRGB){
            cv::vconcat(_allDescRGB, _allDescGAB, allDesc);
        }
        if (_extractGabor && !_extractRGB)
            _allDescGAB.copyTo(allDesc);

        if (!_extractGabor && _extractRGB)
            _allDescRGB.copyTo(allDesc);

        //Encode descriptors (each histogram value is quantified to 256 values - 8 bits)
        std::stringstream data;
        serialize(allDesc, &data);
        DescBitsRaw = (double)8*(int)data.str().size(); //allDesc.size().height * allDesc.size().width * WISE_BYTES_INT
        DescBitsCod = (double)encode_huffman(data);
    }
    else
    {
        DescBitsRaw=0;
        DescBitsCod=0;
    }

    WiseMultiCameraPeriodicApp_ReIDPacket *pkt = NULL;
    int TotBytes=-1,compresionRatio=-1,BaseSzByte=0;
    switch (_dataTypeTX)
    {
        // SEND FULL FRAME
        case 1:
        {
            pkt = new WiseMultiCameraPeriodicApp_ReIDPacket("TX:frame", APPLICATION_PACKET);
            pkt->setFrame(_buf.frame);
            pkt->setPayloadArraySize(_buf.frame.channels() * _buf.frame.cols * _buf.frame.rows);
            pkt->setNumDetections(0);
            BaseSzByte =  WISE_BYTES_INT + //frame number
                            WISE_BYTES_INT + //camera number
                            WISE_BYTES_UINT8; //number of detected targets
            TotBytes = BaseSzByte + _buf.frame.channels() * _buf.frame.cols * _buf.frame.rows * WISE_BYTES_UINT8; //frame data as uchar
            compresionRatio = 1;
            break;
        }
        // SEND COMPRESSED FRAME
        case 2:
        {
            pkt = new WiseMultiCameraPeriodicApp_ReIDPacket("TX:frame JPEG", APPLICATION_PACKET);

            //conversion to JPEG
            std::vector<uchar> buff;//buffer for coding
            std::vector<int> param(2);
            param[0] = cv::IMWRITE_JPEG_QUALITY;
            param[1] = 60;//default(95) 0-100
            cv::imencode(".jpg", _buf.frame, buff, param);

            pkt->setPayloadArraySize(buff.size());
            for (int i=0;i<(int)buff.size();i++)
                 pkt->setPayload(i,buff[i]);

            pkt->setNumDetections(0);
              BaseSzByte =  WISE_BYTES_INT + //frame number
                            WISE_BYTES_INT + //camera number
                            WISE_BYTES_UINT8; //number of detected targets
            TotBytes = BaseSzByte + buff.size() * WISE_BYTES_UINT8; //frame data as uchar
            compresionRatio = buff.size() / (_buf.frame.channels() * _buf.frame.cols * _buf.frame.rows);
            break;
        }
        //SEND DESCRIPTORS
        case 3:
        {
            pkt = new WiseMultiCameraPeriodicApp_ReIDPacket("TX:desc", APPLICATION_PACKET);

            pkt->setNumDetections(_numDet);
            if (_numDet >0)        {
                //pkt->setDescriptorData(data);
                pkt->setDescriptorData(allDesc);
                pkt->setHistSize(histSize);
            }
            pkt->setPayloadArraySize(DescBitsRaw/8+_numDet*4);

            BaseSzByte = WISE_BYTES_INT + //frame number
                             WISE_BYTES_INT + //camera number
                             WISE_BYTES_INT * 5 + //time stamp (day, month, hour, min, sec, )
                             WISE_BYTES_INT; //number of detected targets
            TotBytes = BaseSzByte + DescBitsRaw/8 + _numDet * 4 * WISE_BYTES_INT;
            compresionRatio=1;
            break;
        }
        //SEND COMPRESSED DESCRIPTORS
        case 4:
        {
            pkt = new WiseMultiCameraPeriodicApp_ReIDPacket("TX:desc comp", APPLICATION_PACKET);

            pkt->setNumDetections(_numDet);
            if (_numDet >0)        {
                //pkt->setDescriptorData(data);
                pkt->setDescriptorData(allDesc);
                pkt->setHistSize(histSize);
            }
            pkt->setPayloadArraySize(DescBitsCod/8+_numDet*4);

            BaseSzByte = WISE_BYTES_INT + //frame number
                             WISE_BYTES_INT + //camera number
                             WISE_BYTES_INT * 5 + //time stamp (day, month, hour, min, sec, )
                             WISE_BYTES_INT; //number of detected targets
            TotBytes =  BaseSzByte + DescBitsCod/8 + _numDet * 4 * WISE_BYTES_INT;
            compresionRatio=DescBitsCod/DescBitsRaw;
            break;
        }
    }
     pkt->setByteLength(TotBytes);
     pkt->setSubType(WISE_APP_NORMAL); //normal APP for the network

     //pkt->setTypeNeighbour(WISE_NEIGHBOUR_COM);
     std::ostringstream dst;
     dst << _sinkNode;
     send_message(pkt, dst.str().c_str());// send pkt to sink
     resMgr->_com.data.compresionRatio[resMgr->_com.cost.count-1] = compresionRatio; //set compression ratio
     resMgr->_com.data.numDet[resMgr->_com.cost.count-1] = _numDet; //set number of detections
     resMgr->_com.data.TXbit_raw[resMgr->_com.cost.count-1] = 8* (BaseSzByte +  DescBitsRaw/8); //set bitrate

     //std::cout << "cam " << self << ": numDet=" << _numDet << " " << (BaseSzByte +  DescSzByteRaw) << " Bytes (compressed "<< BaseSzByte +  DescSzByteCod << " Bytes)" << std::endl;
     delete pkt;
}

void WiseMultiCameraPeriodicApp_ReID::displayDescBGR(cv::Mat b_hist, cv::Mat g_hist, cv::Mat r_hist, int histSize, const string& winname)
{
    WISE_DEBUG_32("WiseCamPerAppREID::displayDescBGR()");

    // Draw the histograms for B, G and R
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );

    /// Normalize the result to [ 0, histImage.rows ]
    cv::normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
    cv::normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
    cv::normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );

    /// Draw for each channel
    for( int i = 1; i < histSize; i++ )
    {
      cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
              cv::Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
              cv::Scalar( 255, 0, 0), 2, 8, 0  );
      cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
              cv::Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
              cv::Scalar( 0, 255, 0), 2, 8, 0  );
      cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
              cv::Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
              cv::Scalar( 0, 0, 255), 2, 8, 0  );
    }

    /// Display
    if (winname.length() < 0)
    {
      cv::namedWindow("calcHist Demo", cv::WINDOW_AUTOSIZE );
      cv::imshow("calcHist Demo", histImage );
    }
    else
    {
      cv::namedWindow(winname, cv::WINDOW_AUTOSIZE );
      cv::imshow(winname, histImage );
    }

    //cv::waitKey(0);
    //cv::imshow("Mask", mask );
}

void WiseMultiCameraPeriodicApp_ReID::displayDescGABOR(cv::Mat g_hist, int histSize, const string& winname)
{
    WISE_DEBUG_32("WiseCamPerAppREID::displayDescGABOR()");

    // Draw the histograms for B, G and R
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );

    /// Normalize the result to [ 0, histImage.rows ]
    cv::normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );

    /// Draw for each channel
    for( int i = 1; i < histSize; i++ )
    {
      cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
              cv::Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
              cv::Scalar( 255, 0, 0), 2, 8, 0  );
    }

    /// Display
    if (winname.length() < 0)
    {
      cv::namedWindow("calcHist Demo", cv::WINDOW_AUTOSIZE );
      cv::imshow("calcHist Demo", histImage );
    }
    else
    {
      cv::namedWindow(winname, cv::WINDOW_AUTOSIZE );
      cv::imshow(winname, histImage );
    }
}
/*!
 * Called when a new sample is no longer valid. Declared in base class "WiseCameraPeriodicApp".
 */
bool WiseMultiCameraPeriodicApp_ReID::at_end_sample()
{
    // Called when a new sample (image) is no longer valid
    WISE_DEBUG_32("WiseCamPerAppREID::at_end_sample()");

	if(_show_sink & isSink)
	{
	    double tiRound = _time_pkt_processing;
	    if (tiRound<=0) tiRound= _sampling_time;

	    //double rateTX = 1/tiRound * resMgr->getCOMBytesTXreq(); //rateTX_request
	    double rateTX = 1/tiRound * 8* resMgr->getCOMBytesTXdone(); //rateTX_achieve (bps)
	    //double rateRX = 1/tiRound * resMgr->getCOMBytesRXreq(); //rateRX_request
	    double rateRX = 1/tiRound * 8* resMgr->getCOMBytesRXdone(); //rateRX_achieve (bps)

	    cv::Mat img = cv::Mat::zeros(350, 800, CV_8UC3);
	    double scale = 0.8;
	    std::ostringstream ss0a,ss0b,ss0c, ss1,ss2;
        cv::putText(img, "BANDWIDTH AT THE SINK NODE", cv::Point(50,50), cv::FONT_HERSHEY_SIMPLEX, scale, cv::Scalar(255,255,255), 2, CV_AA);

        if (resMgr->getCOMDrop())
            cv::putText(img, "LIMIT EXCEEDED!!!", cv::Point(500,50), cv::FONT_HERSHEY_SIMPLEX, scale, cv::Scalar(0,0,255), 2, CV_AA);

        ss0a << "New frame every "<< _sampling_time*1e3 << " ms (MAX exchanged " << _sampling_time * resMgr->getCOMInfo().bitrateTX * 1/8 <<" KB)";
        cv::putText(img,ss0a.str().c_str(), cv::Point(50,100), cv::FONT_HERSHEY_SIMPLEX, 0.8*scale, cv::Scalar(255,255,255), 2, CV_AA);

        ss0b << this->n_nodes-1 << " connected cameras";
        cv::putText(img,ss0b.str().c_str(), cv::Point(50,150), cv::FONT_HERSHEY_SIMPLEX, 0.8*scale, cv::Scalar(255,255,255), 2, CV_AA);

        switch (_dataTypeTX)
        {
            case 1:
                cv::putText(img,"Receiving uncompressed frames", cv::Point(50,200), cv::FONT_HERSHEY_SIMPLEX, 0.8*scale, cv::Scalar(255,255,255), 2, CV_AA);
                break;
            case 2:
                cv::putText(img,"Receiving frames (JPEG format)", cv::Point(50,200), cv::FONT_HERSHEY_SIMPLEX, 0.8*scale, cv::Scalar(255,255,255), 2, CV_AA);
                break;
            case 3:
                cv::putText(img,"Receiving RGB & GABOR descriptors", cv::Point(50,200), cv::FONT_HERSHEY_SIMPLEX, 0.8*scale, cv::Scalar(255,255,255), 2, CV_AA);
                break;
            case 4:
                cv::putText(img,"Receiving RGB & GABOR descriptors (huffman encoding)", cv::Point(50,200), cv::FONT_HERSHEY_SIMPLEX, 0.8*scale, cv::Scalar(255,255,255), 2, CV_AA);
                break;
        }
        double maxTX = resMgr->getCOMInfo().bitrateTX;//kbps
        double maxRX = resMgr->getCOMInfo().bitrateRX;//kbps

	    ss1 << "TX Rate " <<std::setfill('0')<<std::setw(3)<< rateTX/1e3 << "Kbps, MAX="<< maxTX/1e3 <<"Kbps " <<100*rateTX/maxTX << "%";
	    cv::Scalar col1 = cv::Scalar(0,255,0);
	    if (resMgr->getCOMDrop()) col1 = cv::Scalar(0,0,255);
	    cv::putText(img, ss1.str().c_str(), cv::Point(50,250), cv::FONT_HERSHEY_SIMPLEX, scale,col1, 2, CV_AA);

        ss2 << "RX Rate " <<std::setfill('0')<<std::setw(3)<< rateRX/1e3 << "Kbps, MAX="<< maxRX/1e3 <<"Kbps " <<100*rateRX/maxRX << "%";
        cv::Scalar col2= cv::Scalar(0,255,0);
        if (resMgr->getCOMDrop()) col2 = cv::Scalar(0,0,255);
        cv::putText(img, ss2.str().c_str(), cv::Point(50,300), cv::FONT_HERSHEY_SIMPLEX, scale, col2, 2, CV_AA);

        cv::imshow(_win_sink.str().c_str(),img);
	    //cv::waitKey(0);

	}
    return true;
}

/*!
 * Called when a packet is received from the network using standard or dummy protocols. In this function, a node
 * receives data from its neigbours, stores the pkt content and when all the data is available (from all neigbourgs),
 * it performs consensus and sents back the averaged result to the neigbourgs using the network.
 *
 * @param[in] pkt Received packet (should be casted to a WiseMultiCameraPeriodicApp_ReIDMessage type)
 */
bool WiseMultiCameraPeriodicApp_ReID::process_network_message(WiseBaseAppPacket *pkt)
{
    WISE_DEBUG_32("WiseCamPerAppREID::process_network_message()");

    const WiseMultiCameraPeriodicApp_ReIDPacket *m = check_and_cast<const WiseMultiCameraPeriodicApp_ReIDPacket*>(pkt);
    ApplicationInteractionControl_type ctl = m->getApplicationInteractionControl();

    /*int histSize = m->getHistSize();
    cv::Mat descriptors = m->getDescriptorData();

   for(unsigned int i=0;i<m->getNumDetections();i++)
    {
        cv::Mat b_hist, g_hist, r_hist;
        //std::vector<cv::Mat> descBGR = descriptors[i];

        std::ostringstream os;
        os << "CAM" << self << " Received data from cam" << ctl.source << "- DescBGR " << i;

        //displayDescBGR(descBGR[0], descBGR[1], descBGR[2], histSize, os.str());
        //cv::waitKey(0);
    }/*/

    //std::ostringstream os;
    //os << "CAM" << self << " Received data from cam " << ctl.source;
    //cv::imshow(os.str(), m->getFrame());
    //cv::waitKey(1);
    //std::cout << "CAM " << self << " (sink) Received data from cam " << ctl.source << "(" << m->getByteLength()<<" Bytes if dummy comms)" << std::endl;
    return true;
}

/*!
 * Processing of the received network messages through direct connection (so no
 *  communication protocol is applied). This communication is faster than using network
 *  protocols allowing direct communication.
 *
* @param[in] pkt Received packet (should be a WiseApplicationPacket type)
 */
void WiseMultiCameraPeriodicApp_ReID::handleDirectApplicationMessage(WiseBaseAppPacket *pkt)
{
    // Called when a DirectApplication Message is received
    WISE_DEBUG_32("WiseCamPerAppREID::handleDirectApplicationMessage()");

    // In this case we treat the message received through DirectApplication as a normal
    // network message. However, the two mechanisms could be used independently.
    process_network_message(pkt);
}
