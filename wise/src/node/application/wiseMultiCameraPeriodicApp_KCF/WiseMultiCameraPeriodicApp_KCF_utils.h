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
 * \file WiseMultiCameraPeriodicApp_KCF_utils.h
 * \author Juan C. SanMiguel (2017)
 * \brief Utilities and structures for the WiseMultiCameraPeriodicApp_KCF class (header file)
 * \version 1.4
 */
#ifndef __WISECAMERAKCF_UTILS_H__
#define __WISECAMERAKCF_UTILS_H__

#include <WiseUtils.h>

//  Utilities for the KCF tracker
//  This file is part of the implementation for the Kalman-consensus tracker for single targets:
//         R. Olfati-Saber, "Kalman-consensus filter: Optimality stability and performance",
//         Proc. IEEE Conf. Decision and Control, pp. 7036-7042, 2009-Dec.
//         http://ieeexplore.ieee.org/document/4118472
namespace kcf
{
    /*! \struct state_t_4D
     *  \brief 4D State vector of target (posx, posy, velx and vely)
     */
    struct state_t_4D
    {
        unsigned int tid;   //!< Target ID
        double x;           //!< Target x-position
        double Vx;          //!< Target x-velocity
        double y;           //!< Target y-position
        double Vy;          //!< Target y-velocity

        /*!
         * To print target data as string following the format "(posx, posy, Velx, Vely)"
         * @return The string to be printed
         */
        inline std::string str() const
        {
            std::ostringstream os;
            os << "(" << x << ", " << y << ", " << Vx << ", " << Vy << ")";
            return os.str();
        }
    };

    /*! \struct KalmanFilter_t
    *  \brief Variables required for implementing the Kalman Filter using the IF (Information Filter) form
    */
   struct KalmanFilter_t
   {
       unsigned int dimS; //!< Dimension of the state vector
       unsigned int dimM; //!< Dimension of the measurement vector

       cv::Mat x_;     //!< prior estimate  state (x'(k)): x(k)=A*x(k-1)
       cv::Mat x;      //!< posterior or corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))

       cv::Mat A;      //!< state transition matrix (A)
       cv::Mat Ainv;   //!< Inverse state transition matrix (A)^-1
       cv::Mat H;      //!< measurement matrix (H)
       cv::Mat Ht;     //!< Transpose measurement matrix (H)^t

       cv::Mat Q;      //!< process noise covariance matrix (Q)
       cv::Mat R;      //!< measurement noise covariance matrix (R)
       cv::Mat Rinv;   //!< Inverse measurement noise covariance matrix (R^-1)

       cv::Mat eyeS;   //!< Identity matrix for the state (dimS x dimS)

       cv::Mat P;      //!< priori error estimate covariance matrix P'(k)): P'(k)=A*P(k-1)*At + Q)
       cv::Mat M;      //!< posterior error estimate covariance matrix (P(k)): P(k)=(I-K(k)*H)*P'(k)
       //cv::Mat gain; //!< Kalman gain matrix (K(k)): K(k)=P'(k)*Ht*inv(H*P'(k)*Ht+R)

       cv::Mat y;      //!< variable for sum of the information vector of neighbor nodes (dimS x 1)
       cv::Mat S;      //!< variable for sum of the information matrix of neighbor nodes (dimS x dimS)

       cv::Mat u;      //!< information vector of node (dimS x 1)
       cv::Mat U;      //!< information matrix of node (dimS x dimS)
   };

   /**
        * This function initializes the structure KalmanFilter_t with default values
        * @return The KF data
        */
       static KalmanFilter_t init_KalmanFilter(int dimS, int dimM, double procNoiseCov, double measNoiseCov) {

                  KalmanFilter_t KF;

                  int type = cv::DataType<double>::type;//CV_64F

                  KF.x_ = cv::Mat::zeros(dimS, 1, type);
                  KF.x  = cv::Mat::zeros(dimS, 1, type);
                  KF.P  = (cv::Mat_<double>(dimS, dimS) << 5,0,0,0, 0,5,0,0, 0,0,2,0, 0,0,0,2);

                  //transition matrix
                  KF.A    = (cv::Mat_<double>(dimS, dimS) << 1,0,1,0, 0,1,0,1, 0,0,1,0, 0,0,0,1);
                  KF.Ainv = KF.A.inv(cv::DECOMP_SVD);

                  //measurement matrix
                  KF.H    = (cv::Mat_<double>(dimM, dimS) << 1,0,0,0, 0,1,0,0);
                  KF.Ht   = cv::Mat::zeros(dimS,dimM, CV_64F);
                  cv::transpose(KF.H, KF.Ht);

                  //measurement covariance
                  KF.Rinv = measNoiseCov * cv::Mat::eye(dimM, dimM,CV_64F);
                  KF.Rinv = KF.Rinv.inv(cv::DECOMP_SVD);
                  KF.eyeS = cv::Mat::eye(dimS, dimS,CV_64F);

                  //process covariance
                  KF.Q  = procNoiseCov * (cv::Mat_<double>(dimS, dimS) << 1,0,0.1,0, 0,1,0,0.1, 0,0,0.1,0, 0,0,0,0.1);

                  KF.M = cv::Mat::zeros(dimS, dimS, type); //posterior covariance

                  KF.y = cv::Mat::zeros(dimS, 1, type);    //sum of the information vector of neighbor nodes
                  KF.S = cv::Mat::zeros(dimS, dimS, type); //sum of the information matrix of neighbor nodes
                  KF.u = cv::Mat::zeros(dimS, 1, type);    //information vector of node
                  KF.U = cv::Mat::zeros(dimS, dimS, type); //information matrix of node
                  return KF;
        }

       /**
              * This function updates the state of the structure KalmanFilter_t with measurements
              * @return The KF structure
              */
             static KalmanFilter_t update(KalmanFilter_t KF, bool debug=false) {

                 KF.M = KF.eyeS / (KF.eyeS / KF.P + KF.S);
                 KF.x = (KF.x_ + KF.M*(KF.y - KF.S*KF.x_));

                 if (debug)
                     std::cout << "KCF   x_=" << mat2vec(KF.x_) <<" x=" << mat2vec(KF.x) << " meas=" << mat2vec( KF.M*(KF.y - KF.S*KF.x_)) << endl;

                 return KF;
             }

             /**
              * This function predicts the state of the structure KalmanFilter_t
              * @return The KF structure
              */
             static KalmanFilter_t predict(KalmanFilter_t KF, bool debug=false) {
                 KF.x_ = KF.A * KF.x;
                 KF.P = KF.A * KF.M * KF.Ainv + KF.Q;

                 if (debug){
                     //TODO
                     //std::cout << "KCF   x_=" << print(KF.x_,4);
                     //std::cout <<" x=" << print(KF.x,4);
                 }
                 return KF;
             }

             static KalmanFilter_t initKFstate(KalmanFilter_t KF, cv::Mat xgt) {

                 KF.x_.at<double>(0) = xgt.at<double>(0);
                 KF.x_.at<double>(1) = xgt.at<double>(1);
                 KF.x_.at<double>(2) = 0;
                 KF.x_.at<double>(3) = 0;
                 return KF;
             }


   /*! \struct neigbourg_data_t
    *  \brief Variables to store data received from one neighbor node. It uses IF-based form of Kalman
    *          Filter so it stores the received information vector & matrix as well as the target state.
    */
   struct neigbourg_data_t
   {
       cv::Mat u;      //!< information vector received from node (dimS x 1)
       cv::Mat U;      //!< information matrix received from node (dimS x dimS)

       state_t_4D rcv_state;   //!< states received from other nodes
       bool    rcv_data;       //!< status of the data received by other nodes: received(true) or not received(false)

       bool end_collaboration;
   };

   /*! \struct neigbourg_data_t_buf
    *  \brief Buffer for storing neigbourg_data_t of different iterations of the algorithm. Allows to receive unsync
    *  data at different iterations with a maximum of MAX_SIZE_BUFFER iterations simultaneously
    */
   struct neigbourg_data_t_buf
   {
       int tam_buf;                            //!< Size of the buffer
       std::vector<neigbourg_data_t> nb_data;  //!< List of neigbours's data (states and status)
       int iter_buffer;                        //!< Index with the current iterations
   };

   /*! \struct node_ctrl_t
    *  \brief Control behavior of node for each target
    */
   struct node_ctrl_t
   {
       bool initialized;                      //!< Flag to indicate tracker initialized (=true) or not (=false)
       double first_start_time;               //!< First simulation time of initialization
       double start_time;   //!< First simulation time when the iterations (of consensus) started
       bool detection_miss;                   //!< To detect the miss (ie, no-detection) situation (eg., target moves outside FOV)

       //consensus data
       unsigned long iter_counter;            //!< Counter for the iterations done in the consensus for each tracking step (k)
       int n_neighbourgs;                     //!< Number of node's neigbours
       std::vector<neigbourg_data_t_buf> nb_data_buffer; //!< Buffer for neighbor's data at different iterations (size MAX_SIZE_BUFFER);
   };

   static node_ctrl_t init_node_ctrl(int n_nodes,int buffersize) {
       node_ctrl_t ctrl;

       ctrl.initialized = false;
       ctrl.first_start_time = -1;
       ctrl.start_time = -1;
       ctrl.detection_miss = true;

       //data for consensus iterations
       ctrl.iter_counter = 0; // iteration of the consensus
       ctrl.n_neighbourgs = -1; //#neigbours of the node - wait until the graphs are completed

       //buffer for neighbor's data of MAX_SIZE_BUFFER iterations
       ctrl.nb_data_buffer.clear();
       ctrl.nb_data_buffer.resize(buffersize);

       for (unsigned int j = 0; j < (unsigned int)buffersize; j++)
       {
           ctrl.nb_data_buffer[j].nb_data.clear();
           ctrl.nb_data_buffer[j].nb_data.resize(n_nodes);
           ctrl.nb_data_buffer[j].iter_buffer=-1;
       }
       return ctrl;
   }


   static std::map<int,int> create_pkt_size_bytes() {
          std::map<int,int> m;

          //packet type (char) + consensus-round(char) + frame number (int) + covariance matrix (16 float, only upper part 6 values)
          m.insert(std::make_pair(KCF_COLLABORATION_DATA1, 2*WISE_BYTES_UINT8 + WISE_BYTES_INT + 6*WISE_BYTES_FLOAT));//30bytes

          //packet type (char) + consensus-round(char) + frame number (int) + state (4 float)
          m.insert(std::make_pair(KCF_COLLABORATION_DATA2, 2*WISE_BYTES_UINT8 + WISE_BYTES_INT + 4*WISE_BYTES_FLOAT));//22 bytes

          //KCF_COLLABORATION_END pkt --> message type(int) + frame number(int)
          m.insert(std::make_pair(KCF_COLLABORATION_END, 2*WISE_BYTES_INT)); //8bytes
          return m;
      }
      static std::map<int,int> KCFpkt_size = kcf::create_pkt_size_bytes(); //size for each packet type

      typedef enum {
              INACTIVE             =-1,  //!< Not running
              COLLABORATION        = 3,  //!< camera are sending and receiving data
          } kcf_state_t;
}

#endif // __WISECAMERAKCF_UTILS_H__
