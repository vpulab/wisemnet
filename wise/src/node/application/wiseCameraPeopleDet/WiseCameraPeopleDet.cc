// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2015
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  This file is part of the implementation for the people-detect-transmit demo:
//      J. SanMiguel & A. Cavallaro,
//      "Networked Computer Vision: the importance of a holistic simulator",
//      IEEE COMPUTER 2017, http://ieeexplore.ieee.org/document/XXXX/
//      Preprint available at http://www.eecs.qmul.ac.uk/~andrea/wise-mnet.html
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// *****************************************************************************
#include "TMacControlMessage_m.h"
#include "WiseCameraPeopleDet.h"
#include "WiseUtils.h"
#include "WiseCameraPeopleDetPacket_m.h"

Define_Module(WiseCameraPeopleDet);

#define LOGGER logger << "[" << simTime() << "] @ " << self << " : "
#define BASE_TRACE trace() << "WISEREID: "

ofstream WiseCameraPeopleDet::logger;

/*! Class destructor */
WiseCameraPeopleDet::~WiseCameraPeopleDet()
{

}

/*! Class initialization and getting of user-defined variables in omnetpp.ini*/
void WiseCameraPeopleDet::at_startup()
{
    // Called upon simulation start-up
    BASE_TRACE << "START-UP";

	if (!logger.is_open())
		logger.open("myLog.txt");

	// Access related-module parameters (read number of targets)
	//cModule *network = getParentModule()->getParentModule();
	_mode = par("mode");
	_isSink = par("isSink");

	if (isSink == true)
	    _sampling_time = TIMER_MAX_SIZE;//the sink never captures data

    LOGGER << " mode=" << _mode << endl;

    //determine the sink node via direct connection
    _sinkNode = self;
    for (int i = 0; i < n_nodes; i++) {
            if (i == self)
                continue;
            cModule *m = getParentModule()->getParentModule(); // m=SN
            m = m->getSubmodule("node", i)->getSubmodule("Application");

            WiseCameraPeopleDet *c = check_and_cast<WiseCameraPeopleDet*>(m);
            if (c->isSink == true)
                _sinkNode = i;
    }

    //only no-sink nodes do processing and generate result files
    _extractGabor = par("extractGabor");
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

        //initialize log file
        _testName = par("testName").stringValue();
        std::ostringstream os;
        os << "res/Node" << self << "_" << _testName << "_n" << std::setfill('0') << std::setw(3) << self;
        os << "_CPU" << std::setfill('0') << std::setw(5) << resMgr->getPROClk()/1e5;
        os << "_SEN" << std::setfill('0') << std::setw(5) << resMgr->getSENClk()/1e5;
        //os << "_FR" << std::setfill('0') << std::setw(2) << resMgr->getSENFrameRate(); //real framerate achieved by the sensing module
        os << "_FR" << std::setfill('0') << std::setw(2) << resMgr->getSENFrameRate_user(); //user-defined framerate

        os << "_";
        resMgr->initLogger(get_time_filename(os.str().c_str(), ".res").c_str(), self, -1);
    }

    //_show_results = par(_show_results);
}

/*!
 * From the WiseBaseApplication class.
 *
 * @param[in] c Message received
 */
void WiseCameraPeopleDet::handleMacControlMessage(cMessage *c)
{
    TMacControlMessage *m;
    try {
        m = check_and_cast<TMacControlMessage*>(c);
    } catch (exception& e) {
        // Ignore the control message if it is not from TMac
        return;
    }
    if (m->getType() == TMAC_TX_SUCCESS)
        BASE_TRACE << "packet SENT with T-MAC: retries = " << m->getTxRetries() << "  (max " << m->getMaxTxRetries() << ")";
    else
        if (m->getType() == TMAC_TX_FAILURE)
            BASE_TRACE << "packet NOT SENT with T-MAC: max retries reached (" << m->getMaxTxRetries() << ")";
}

/*!
 * This function receives detections from SensorManager (ie, targets within camera's FOV) and organizes
 *  them in an ordered list as measurements (detections+noise) which is later processed by KFs.
 *
 * @param[in] dt List of WiseTargetDetections (using vector template)
 */
void WiseCameraPeopleDet::make_measurements(const vector<WiseTargetDetection>&dt)
{

}

/*!
 * Init resources for KF processing. Declared in base class WiseCameraPeriodicAlgo.
 */
bool WiseCameraPeopleDet::at_init()
{
    return true;
}

/*!
 * KF processing for first sample. Called when the first sample (image) is ready.Currently first sample is
 * treated as the others. Declared in base class WiseCameraPeriodicAlgo.
 */
bool WiseCameraPeopleDet::at_first_sample()
{
	// Called when the first sample (image) is ready
	BASE_TRACE << "FIRST SAMPLE";
	
	// We can:
	// 1- either put here any first-sample specific code
	// 2- or simply treat the first sample as the others 
	return at_sample(); // option 2
}

/*!
 * KF processing for first sample end of lifetime. Called when the first sample (image) is no longer valid. Currently
 * first sample is treated as the others. Declared in base class WiseCameraPeriodicAlgo.
 */
bool WiseCameraPeopleDet::at_end_first_sample()
{
	// Called when the first sample (image) is no longer valid
	BASE_TRACE << "END FIRST SAMPLE";

	// We can:
	// 1- either put here any first-sample specific code
	// 2- or simply treat the first sample as the others 
	return at_end_sample(); // option 2
}

/*!
 * Called when a new sample (image) is ready. For each target, KF processing consist on computing and initial detection/estimation,
 * which is later sent to other neighbors to initiate consensus. Declared in base class WiseCameraPeriodicAlgo.
 */
bool WiseCameraPeopleDet::at_sample()
{
    BASE_TRACE << "PROCESSING!!!!!";

    if (this->isSink)
        return false;

    // Called when a new sample (image) is ready
    _step_counter++;

    // run the detector with default parameters. to get a higher hit-rate
    // (and more false alarms, respectively), decrease the hitThreshold and
    // groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
    std::vector<cv::Rect> found;//, found_filtered;

    cv::Mat frame;
    cv::resize(_frame, frame, cvSize(320,240));

    double hitThreshold = -2;
    double scale0=1.05;
    int groupThreshold=2;
    cv::Size minSize = cv::Size(4,4);//cv::Size minSize = cv::Size(8,8);
    cv::Size maxSize = cv::Size(8,8);//cv::Size maxSize = cv::Size(32,32);
    _hog->detectMultiScale(frame, found, hitThreshold, minSize, maxSize, scale0, groupThreshold);/**/

     //t = (double)getTickCount() - t;
     //printf("tdetection time = %gms\n", t*1000./cv::getTickFrequency());
    _numDet = found.size();
    size_t i, j;
    for( i = 0; i < _numDet; i++ )
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

   if(_show_results){
        std::ostringstream os,os1;
        os << "CAM " << self << ": Sensing @" << 1/_sampling_time << "fps (Source @" << _frameRateSRC << "fps)";
        os1 << _curFrame; // os1 << _step_counter;

        cv::putText(frame, os1.str(), cv::Point(15,15),cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0,0,255), 1); //BGR
        cv::imshow(os.str(), frame);
        cv::waitKey(10);
    }

    // SINK NODE
    BASE_TRACE << "SEND MESSAGE";

    //Conversion to gray-level image using float type
    cv::Mat greyMatf, greyMat;
    cv::cvtColor(_frame, greyMat, cv::COLOR_BGR2GRAY);
    greyMat.convertTo(greyMatf,CV_32F);

    //GENERATE DESCRIPTOR FOR EACH PERSON
    std::vector<std::vector<cv::Mat> > descList;
    /// Establish the number of bins
    int histSize = 16; //typical value for people re-id

    /// Set the ranges ( for B,G,R) )
    float range[] = { 0, 256 } ;
    const float* histRange = { range };

    bool uniform = true; bool accumulate = false;

    cv::Mat allDescRGB,allDescTEX,res,res_acc = cv::Mat::zeros(greyMat.size(), CV_32F);

    for( i = 0; i < found.size(); i++ )
    {
        cv::Rect roi = found[i];
        if (roi.x < 0 || roi.y < 0 || roi.width < 0 || roi.height < 0 ||
                roi.x + roi.width > _frame.cols || roi.y + roi.height > _frame.rows){
            //option1
            //_numDet = _numDet -1;
            //continue;

            //option2
            if (roi.x < 0) roi.x = 0;
            if (roi.y < 0) roi.y = 0;
            if (roi.width < 0) roi.width = 0;
            if (roi.height < 0) roi.height = 0;

            if (roi.x + roi.width > _frame.cols) roi.width = _frame.cols - roi.x;
            if (roi.y + roi.height > _frame.rows) roi.height = _frame.rows - roi.y;
        }

        cv::Mat mask = cv::Mat::zeros(_frame.size(), cv::DataType<uchar>::type);  // type of mask is CV_8U
        mask(roi) = cv::Scalar(255, 255, 255);

        // RGB HISTOGRAM

        //std::vector<cv::Mat> descBGR;
        std::vector<cv::Mat> bgr_planes;
        cv::split(_frame, bgr_planes );

        // Compute the histograms:
        cv::Mat b_hist, g_hist, r_hist;
        cv::calcHist( &bgr_planes[0], 1, 0, mask, b_hist, 1, &histSize, &histRange, uniform, accumulate );
        cv::calcHist( &bgr_planes[1], 1, 0, mask, g_hist, 1, &histSize, &histRange, uniform, accumulate );
        cv::calcHist( &bgr_planes[2], 1, 0, mask, r_hist, 1, &histSize, &histRange, uniform, accumulate );

        // Concatenate the histograms
        if ((allDescRGB.cols * allDescRGB.rows) == 0)
            b_hist.copyTo(allDescRGB);
        else
            cv::vconcat(allDescRGB, b_hist, allDescRGB);

        cv::vconcat(allDescRGB, g_hist, allDescRGB);
        cv::vconcat(allDescRGB, r_hist, allDescRGB);

        //descBGR.push_back(b_hist);
        //descBGR.push_back(g_hist);
        //descBGR.push_back(r_hist);
        //descList.push_back(descBGR);
        //std::ostringstream os; os << "Descriptor BGR for target " << i;
        //displayDescBGR(b_hist, g_hist, r_hist, histSize, os.str());

        // GABOR HISTOGRAM
        //Example at https://cvtuts.wordpress.com/2014/04/27/gabor-filters-a-practical-overview/

        if (_extractGabor){
            for (int k = 0; k<(int)_GKernelList.size();k++){
                cv::filter2D(greyMatf, res, CV_32F, _GKernelList[k]);
                cv::max(res, res_acc, res_acc);
            }

            // Compute the histogram
            cv::Mat gab_hist;
            cv::calcHist( &res_acc, 1, 0, mask, gab_hist, 1, &histSize, &histRange, uniform, accumulate );

            // Concatenate the histograms
            if ((allDescTEX.cols * allDescTEX.rows) == 0)
                gab_hist.copyTo(allDescTEX);
            else
                cv::vconcat(allDescTEX, gab_hist, allDescTEX);
        }
    }

    double DescBitsRaw=0, DescBitsCod=0;
    if (_numDet > 0){

        if (_extractGabor){
            // we append both descriptors in allDescRGB
            cv::vconcat(allDescRGB, allDescTEX, allDescRGB);
        }

        //Encode descriptors (each histogram value is quantified to 256 values - 8 bits)
        std::stringstream data;
        serialize(allDescRGB, &data);
        DescBitsRaw = (double)8*(int)data.str().size(); //allDesc.size().height * allDesc.size().width * WISE_BYTES_INT
        DescBitsCod = (double)encode_huffman(data);

        BASE_TRACE << "PROCESSING!!!!!" << " NumDet=" << (int)found.size();
    }

    WiseCameraPeopleDetPacket *pkt = NULL;
    // SEND FULL FRAME
    if (_mode == 1){
       pkt = new WiseCameraPeopleDetPacket("TX:frame", APPLICATION_PACKET);
       pkt->setFrame(_frame);
       pkt->setNumTargets(0);
       int TotBytes =  WISE_BYTES_INT + //frame number
                       WISE_BYTES_INT + //camera number
                       WISE_BYTES_UINT8 + //number of detected targets
                       found.size() * _frame.channels() * _frame.cols * _frame.rows * WISE_BYTES_UINT8; //frame data as uchar
       pkt->setByteLength(TotBytes);
    }

    int BaseSzByte,DescSzByteRaw,DescSzByteCod;

    BaseSzByte = WISE_BYTES_INT + //frame number
            WISE_BYTES_INT + //camera number
            WISE_BYTES_DOUBLE * 5 + //time stamp (day, month, hour, min, sec, )
            WISE_BYTES_INT; //number of detected targets

    if (found.size() >0){
        //Descriptor size + bounding boxes (each one with four integers)
        DescSzByteRaw = DescBitsRaw/8 + found.size() * 4 * WISE_BYTES_INT;
        DescSzByteCod = DescBitsCod/8 + found.size() * 4 * WISE_BYTES_INT;
    }
    else{
        DescSzByteRaw = 0;
        DescSzByteCod = 0;
    }

    // SEND PEOPLE DESCRIPTION (UNCOMPRESSED)
    if (_mode == 2){
        pkt = new WiseCameraPeopleDetPacket("TX:descRaw", APPLICATION_PACKET);

        pkt->setNumTargets(found.size());
        if (found.size() >0)        {
            pkt->setDescBGR(descList);
            pkt->setHistSize(histSize);
        }
        //NOTE: we assume that the destination and source are in the packet overhead
        pkt->setBitLength(8*(BaseSzByte +  DescSzByteRaw));
    }

    // SEND PEOPLE DESCRIPTION (COMPRESSED)
    if (_mode == 3){
        pkt = new WiseCameraPeopleDetPacket("TX:descCod", APPLICATION_PACKET);

        pkt->setNumTargets(found.size());
        if (found.size() >0)        {
            pkt->setDescBGR(descList);
            pkt->setHistSize(histSize);
        }
        pkt->setBitLength(8*(BaseSzByte +  DescSzByteCod));
    }

    pkt->setType(WISE_APP_NORMAL); //normal APP for the network
    //pkt->setTypeNeighbour(WISE_NEIGHBOUR_COM);
    std::ostringstream dst;
    dst << _sinkNode;
    send_message(pkt, dst.str().c_str());// send pkt to sink
    resMgr->_com.data.compresionRatio[resMgr->_com.cost.count-1] = (double)(BaseSzByte +  DescSzByteCod)/(double)(BaseSzByte +  DescSzByteRaw); //set compression ratio
    resMgr->_com.data.numDet[resMgr->_com.cost.count-1] = _numDet; //set number of detections
    resMgr->_com.data.TXbit_raw[resMgr->_com.cost.count-1] = 8* (BaseSzByte +  DescSzByteRaw); //set compression ratio

    delete pkt;
    //std::ostringstream os2; os2 << "REPEATED Descriptor BGR for target " << 0;
    //std::vector<cv::Mat> descRGB = descriptors[0];
    //displayDescBGR(descRGB[0], descRGB[1], descRGB[2], histSize, os2.str());

    return true;
}

void WiseCameraPeopleDet::displayDescBGR(cv::Mat b_hist, cv::Mat g_hist, cv::Mat r_hist, int histSize, const string& winname)
{
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

      cv::waitKey(0);
      //cv::imshow("Mask", mask );
}

/*!
 * Called when a new sample is no longer valid. Declared in base class "WiseCameraPeriodicAlgo".
 */
bool WiseCameraPeopleDet::at_end_sample()
{
	// Called when a new sample (image) is no longer valid
	BASE_TRACE << "END NEW SAMPLE";
	if (this->_isSink == true)
	    return false;

    return true;
}

/*!
 * Called when a packet is received from the network using standard or dummy protocols. In this function, a node
 * receives data from its neigbours, stores the pkt content and when all the data is available (from all neigbourgs),
 * it performs consensus and sents back the averaged result to the neigbourgs using the network.
 *
 * @param[in] pkt Received packet (should be casted to a WiseCameraPeopleDetMessage type)
 */
bool WiseCameraPeopleDet::process_network_message(WiseApplicationPacket *pkt)
{
    BASE_TRACE << "PROCESS NETWORK MESSAGE";
    LOGGER << "PROCESS NETWORK MESSAGE";

    const WiseCameraPeopleDetPacket *m = check_and_cast<const WiseCameraPeopleDetPacket*>(pkt);
    ApplicationInteractionControl_type ctl = m->getApplicationInteractionControl();

    int histSize = m->getHistSize();
    const std::vector<std::vector<cv::Mat> > descriptors = m->getDescBGR();

    for(unsigned int i=0;i<m->getNumTargets();i++)
    {
        cv::Mat b_hist, g_hist, r_hist;
        std::vector<cv::Mat> descBGR = descriptors[i];

        std::ostringstream os;
        os << "CAM" << self << " Received data from cam" << ctl.source << "- DescBGR " << i;

        displayDescBGR(descBGR[0], descBGR[1], descBGR[2], histSize, os.str());
        cv::waitKey(0);
    }

    //std::ostringstream os;
    //os << "CAM" << self << " Received data from cam " << ctl.source;
    //cv::imshow(os.str(), m->getFrame());
    //cv::waitKey(1);
    return true;
}

/*!
 * Processing of the received network messages through direct connection (so no
 *  communication protocol is applied). This communication is faster than using network
 *  protocols allowing direct communication.
 *
* @param[in] pkt Received packet (should be a WiseApplicationPacket type)
 */
void WiseCameraPeopleDet::handleDirectApplicationMessage(WiseApplicationPacket *pkt)
{
    // Called when a DirectApplication Message is received
    BASE_TRACE << "HANDLE DIRECT APPLICATION MESSAGE";

    // In this case we treat the message received through DirectApplication as a normal
    // network message. However, the two mechanisms could be used independently.
    process_network_message(pkt);
}
