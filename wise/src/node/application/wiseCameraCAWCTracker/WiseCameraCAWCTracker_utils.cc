// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2015
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//
//  This file is part of the implementation for the cost-aware coalition-based
//  tracking (CAWC) for single targets described in the paper:
//      Juan C. SanMiguel and A. Cavallaro "Cost-aware coalitions for collaborative
//      Tracker tracking", IEEE Sensors Journal, May 2015
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// *****************************************************************************

#define TRACK_EVAL_WINDOW 3 //in seconds, number of frames depends on framerate

#include <Utils/histogram.h>
#include "WiseCameraCAWCTracker_utils.h"
#include <Utils/math_utils.h>

using namespace CAWC;

CamTracker::CamTracker(int id,double framerate)
{
    _id = id;
    _struck = NULL;
    _conf = NULL;

    _started = false;
    _trackers_str = CAWC::create_tracker_str();
    init = false;
    _counterScore = 0;
    _targetLost = false;
    _score = -1;

    _framerate = framerate;
    _frames2updateModel = (int)(TRACK_EVAL_WINDOW * _framerate);
    //_data = cv::Mat::zeros(_counterPrevFrame, 1, CV_64F);
    _ms=-1;
    _ss=-1;
    _th = 0.5;
    done = false;
    _recover_count = 0;
}

CamTracker::~CamTracker()
{
    if (_struck!=NULL){
        delete _struck;
        delete _conf;
    }
}

bool CamTracker::selectTracker(tracker_type_t type)
{
    _selTracker = type;
    //std::cout << "selected tracker "<< _trackers_str[_selTracker] << endl;

    switch (_selTracker) {

            case STRUCK:
                _conf = new Config("../../src/node/application/Trackers/struck/config.txt");
                _struck = new _Tracker(*_conf);
                //cout << *_conf << endl;
                break;
            default:
                return false;
        }
    return true;
}

bool CamTracker::initialize(cv::Mat frame, target_initialization_t iniT)
{
    double resize = iniT.resize;
    cv::Mat tmp;

    switch (_selTracker)
    {
          case STRUCK:
          {
              FloatRect initBB = FloatRect((iniT.Xc-iniT.width/2)*resize, (iniT.Yc-iniT.height/2)*resize, iniT.width*resize, iniT.height*resize);
              _struck->Initialise(frame, initBB);
              _trackWindow = cv::Rect(_struck->GetBB().XMin(),_struck->GetBB().YMin(),_struck->GetBB().Width(),_struck->GetBB().Height());
              break;
          }
      }

   //compute covariance matrix for the initial model
   cv::Mat descriptor = getCovDescriptor(frame, _trackWindow);
   _init_model = MathUtils::computeCovarianceMatrix(descriptor);
   _curr_model = MathUtils::computeCovarianceMatrix(descriptor);

   //update flags
   _started = true;
   _counter = 0;

   return true;
}

bool CamTracker::update(cv::Mat frame)
{
    cv::Mat tmp;
    if (_started == false)
        return false;

    _counter++;
    switch (_selTracker)
    {
       case STRUCK:
           _struck->Track(frame);
           break;
    }
    return true;
}

cv::Rect2d CamTracker::getTrackWindow ()
{
    if (_started == false)
        return cvRect(-1,-1,-1,-1);

    switch (_selTracker)
        {
           case STRUCK:
               _trackWindow = cv::Rect(_struck->GetBB().XMin(),_struck->GetBB().YMin(),_struck->GetBB().Width(),_struck->GetBB().Height());
               break;
        }

    return _trackWindow;
}

void CamTracker::computeScore(cv::Mat frame)
{
    if (_started == false){
        _score = 0;
        return;
    }

    //compute covariance matrix of descriptor for current tracking data
    cv::Mat descriptor = getCovDescriptor(frame, getTrackWindow());
    cv::Mat covar_mat = MathUtils::computeCovarianceMatrix(descriptor);

    if(_targetLost==false) {
        float covar_distance = MathUtils::covarianceDistance(_curr_model, covar_mat);

        if (_ms!=-1)
            _score = exp(-0.5 * (covar_distance-_ms)/_ss *(covar_distance-_ms)/_ss );
        else
            _score = covar_distance;

        if (_counter > 1 && _score<0.12)
            _targetLost = true;

        //update model if needed
       if (_counter % _frames2updateModel == 0) {
           //cv::Mat descriptor = getCovDescriptor(frame, _trackWindow);
           //_curr_model = MathUtils::computeCovarianceMatrix(descriptor);
           covar_mat.copyTo(_curr_model);
       }
    }
    else
    {
        //float covar_distance1 = MathUtils::covarianceDistance(_curr_model, covar_mat);
        float covar_distance2 = MathUtils::covarianceDistance(_init_model, covar_mat);
        //double tmp1 = exp(-0.5 * (covar_distance1-_ms)/_ss *(covar_distance1-_ms)/_ss );
        double tmp2 = exp(-0.5 * (covar_distance2-_ms)/_ss *(covar_distance2-_ms)/_ss );

        if (tmp2 > _th)
            _recover_count++;

        if (_recover_count > 2){
            _targetLost = false;
            _recover_count = 0;
            covar_mat.copyTo(_curr_model);
        }
        _score = -tmp2;
        _score = 0;
    }
}

void CamTracker::setTrackerUtility(double m, double v,double th)
{
    _ms = m;
    _ss = v;
    _th=th;
}

cv::Mat CamTracker::getCovDescriptor(cv::Mat img, cv::Rect roi)
{
    //get subimage
    assert( RECT_IN_MAT(roi, img) );
    cv::Mat subImg(img, roi);
    //cv::imshow("PATH",subImg); cv::waitKey(0);

    //compute descriptor (xpos, ypos, R value, G value, B value)
    //cv::Mat des = cv::Mat::zeros(subImg.rows*subImg.cols, 5, CV_64F);

    //compute descriptor (xpos, ypos, R value, G value, B value, Hue value & 5x5 mean )
    //cv::Mat des = cv::Mat::zeros(subImg.rows*subImg.cols, 7, CV_64F);

    //compute descriptor (xpos, ypos, R value, G value, B value, Hue value )
    cv::Mat des = cv::Mat::zeros(subImg.rows*subImg.cols, 6, CV_64F);

    for (int i=0; i < subImg.rows; i++)
      for (int j=0; j < subImg.cols; j++) {
          //Normalized Pixel location
          des.at<double>(i*subImg.cols + j,1) = double(i)/subImg.rows;
          des.at<double>(i*subImg.cols + j,2) = double(j)/subImg.cols;

          //RGB value
          des.at<double>(i*subImg.cols + j,3) = subImg.at<cv::Vec3b>(i,j)[0];
          des.at<double>(i*subImg.cols + j,4) = subImg.at<cv::Vec3b>(i,j)[1];
          des.at<double>(i*subImg.cols + j,5) = subImg.at<cv::Vec3b>(i,j)[2];

          //Hue
          des.at<double>(i*subImg.cols + j,6) = subImg.at<cv::Vec3b>(i,j)[0];

          //5x5 mean
          //int i_min = ((i-2) < 0 ? 0 : i-2);
          //int i_max = ((i+2) >= subImg.rows? (subImg.rows-1) : (i+2));
          //int j_min = ((j-2) < 0 ? 0 : j-2);
          //int j_max = ((j+2) >= subImg.cols ? subImg.cols : (i+2));

          // Get subimage & compute histogram
          //cv::Mat sub = subImg(cv::Range(i_min,i_max-i_min+1), cv::Range(j_min,j_max-j_min+1));
          //Histogram hist(sub);
          //des.at<double>(i*subImg.cols + j,7) = hist.mean();
      }

    return des;
}

int CamTracker::getId() {return this->_id;};
bool CamTracker::getStarted () {return _started;};
double CamTracker::getScore() {return this->_score;};
void CamTracker::setId(int id) {this->_id = id;};

void CamTracker::setFramerate(double framerate)//!< Sets the framerate of the node using the tracker
{
   _framerate = framerate;
   _frames2updateModel = (int)(TRACK_EVAL_WINDOW * _framerate);
  //std::cout << "_counterPrevFrame=" << _counterPrevFrame << " framerate=" << _framerate << endl;

  if (_frames2updateModel < 1) {
      _frames2updateModel=1;
    //  std::cout << "Adjusted _counterPrevFrame=" << _counterPrevFrame << " framerate=" << _framerate << endl;
  }
}
double CamTracker::getFramerate(){return this->_framerate;};              //!< Sets the framerate of the node using the tracker
