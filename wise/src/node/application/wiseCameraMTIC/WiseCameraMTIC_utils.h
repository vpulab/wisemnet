// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2015
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  This file is part of the implementation for the MTIC-consensus tracker for multiple targets:
//         Kamal et al, "Distributed Multi-Target Tracking and Data Association in Vision Networks",
//         IEEE TPAMI 2016.
//         http://ieeexplore.ieee.org/document/7286852/
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// *****************************************************************************

#ifndef __WISECAMERAMTIC_UTILS_H__
#define __WISECAMERAMTIC_UTILS_H__

#include <WiseUtils.h>
#include "WiseCameraMTIC_Msg_m.h"

namespace mtic
{

    const int MAX_SIZE_BUFFER = 20;

    typedef enum {
           INACTIVE             =-1,  //!< Not running
           COLLABORATION        = 3,  //!< camera are sending and receiving data
       } mtic_state_t;

       static std::map<int,int> create_pkt_size_bytes_mtic() {
           std::map<int,int> m;

           //packet type (char) + consensus-round (char) + frame number (int) + covariance matrix (16 float, only upper part 6 values) + state (4 float)
           m.insert(std::make_pair(MTIC_COLLABORATION_DATA1, 2*WISE_BYTES_UINT8 + WISE_BYTES_INT + 6*WISE_BYTES_FLOAT + 4*WISE_BYTES_FLOAT));

           //packet type(int) + frame number(int)
           m.insert(std::make_pair(MTIC_COLLABORATION_END, 2*WISE_BYTES_INT)); //8bytes
           return m;
       }
       static std::map<int,int> ICFpkt_size_mtic = mtic::create_pkt_size_bytes_mtic(); //size for each packet type

    class node_ctrl_mtic_t
    {
        public:
            /*! \struct neigbourg_data_t
                 *  \brief Variables to store data received from one neighbor node. It uses ICF-based form of Kalman
                 *          Filter so it stores the received information vector & matrix as well as the target state.
                 */
                struct neigbourg_data_mtic_t
                {
                    int tid;
                    int nodeID;
                    cv::Mat v;      //!< ??
                    cv::Mat V;      //!< ??
                    cv::Mat W;      //!< ??
                    bool rcv_data;      //!< status of the data received by other nodes: received(true) or not received(false)
                    bool end_collaboration;
                };

                /*! \struct neigbourg_data_t_buf
                    *  \brief Buffer for storing neigbourg_data_t of different iterations of the algorithm. Allows to receive unsync
                    *  data at different iterations with a maximum of MAX_SIZE_BUFFER iterations simultaneously
                    */
                   struct neigbourg_data_mtic_t_buf
                   {
                       int tam_buf;                            //!< Size of the buffer
                       std::vector<neigbourg_data_mtic_t> nb_data;  //!< List of neigbours's data (states and status)
                       int iter_buffer;                     //!< Index with the current iterations
                   };

        public:
            int tid;
            bool initialized;                      //!< Flag to indicate tracker initialized (=true) or not (=false)
            bool detection_miss;                   //!< To detect the miss (ie, no-detection) situation (eg., target moves outside FOV)
            //consensus data
            unsigned long iter_counter;           //!< Counter for the iterations done in the consensus for each tracking step (k)
            int n_neighbourgs;                     //!< Number of node's neighbors
            std::vector<neigbourg_data_mtic_t_buf> nb_data_buffer; //!< Buffer for neighbor's data at different iterations (size MAX_SIZE_BUFFER);
            double start_time; //!< Initial time when the consensus was started
            double first_start_time; //!< Initial time when the camera has become active

            node_ctrl_mtic_t();
            node_ctrl_mtic_t(int tid,int n_nodes,int buffersize,int dimS);
            int init_node_ctrl(int tid, int n_nodes,int buffersize,int dimS);
            int findIndexInBuffer(int iter_index);
            int storeDataInBuffer(int iter, int nodeID, WiseCameraMTIC_Msg *m);
    };

    /*! \class MTIC_t
         *  \brief Class that implements the MTIC Information Consensus Filter
         */
        class MTIC_t
        {
            public:

            unsigned int dimS; //!< Dimension of the state vector
            unsigned int dimM; //!< Dimension of the measurement vector
            int n_nodes;
            double procNoiseCov;
            double measNoiseCov;

            double beta0;
            double Pg;
            double lamda;
            double lamdaf;

            cv::Mat x;      //!< posterior estimate
            cv::Mat x_;     //!< prior estimate
            cv::Mat J;      //!< posterior information matrix (inverse of covariance)
            cv::Mat J_;     //!< prior information matrix (inverse of covariance)
            cv::Mat P;      //!< priori error estimate covariance matrix P'(k)): P'(k)=A*P(k-1)*At + Q)
            cv::Mat Pinv;

            cv::Mat u, U, G;      //!< Information vector & Matrix (own)
            cv::Mat v, V, W;      //!< Information vector & Matrix (accumulated)

            cv::Mat R,Rinv;   //!< measurement covariance matrix (for measurement)
            cv::Mat Q;        //!< process covariance matrix (for transition)
            cv::Mat eyeS;     //!< diagonal matrix dimS-by-dimS/**/

            cv::Mat A,At;  //!< transition matrix
            cv::Mat H,Ht;  //!< measurement matrix

            cv::Mat z;        //!< Measurements obtained at each tracking step   (z_l)
            cv::Mat xgt;      //!< Ground-truth positions of target states (gt_l)
            double err;    //!< Error of the target estimation
            double errAcc; //!< Error of the target estimation (accumulated)

            MTIC_t();
            MTIC_t(int dimS, int dimM, double procNoiseCov, double measNoiseCov,double lamda,int n_nodes);

            ~MTIC_t();

            int init_MTIC_t(int dimS, int dimM, double procNoiseCov, double measNoiseCov,double lamda,int n_nodes);
            int initICFstate(cv::Mat xgt, bool debug=false);

            void prepData(bool detection_miss);

            void update_state();
            void update_state_neighbors(std::vector<mtic::node_ctrl_mtic_t::neigbourg_data_mtic_t> &data, double alpha, int n_neighbourgs, int max_neigb_network);
            void estimate_state();
            void predict_state();
            void estimate_and_predict_state();

            double compute_error();

        };
}

#endif // __WISECAMERAMTIC_UTILS_H__
