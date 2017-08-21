// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2014
//  Author(s): Juan C. SanMiguel
//  Developed at EECS, Queen Mary University (London)
//  This file is distributed under the terms in the attached LICENSE_2 file.
//  If you do not find this file, copies can be found by writing to:
//  - juan.carlos.sanmiguel@eecs.qmul.ac.uk
//  - andrea.cavallaro@eecs.qmul.ac.uk
// *****************************************************************************

#ifndef __WISECAMERACLUSTERICF_UTILS_H__
#define __WISECAMERACLUSTERICF_UTILS_H__

namespace icfcluster
{
    /*! \struct ICF_t
     *  \brief Variables required for implementing the Information Consensus Filter
     */
    struct ICF_t
    {
        unsigned int dimS; //!< Dimension of the state vector
        unsigned int dimM; //!< Dimension of the measurement vector

        cv::Mat x;      //!< posterior estimate
        cv::Mat x_;     //!< prior estimate

        cv::Mat J;      //!< posterior information matrix (inverse of covariance)
        cv::Mat J_;     //!< prior information matrix (inverse of covariance)
        cv::Mat P;      //!< priori error estimate covariance matrix P'(k)): P'(k)=A*P(k-1)*At + Q)
        cv::Mat Pinv;

        cv::Mat v;      //!< ??
        cv::Mat V;      //!< ??

        cv::Mat A, At;  //!< transition matrix (normal and transpose)
        cv::Mat H, Ht;  //!< measurement matrix (normal and transpose)

        cv::Mat Q;      //!< process covariance matrix (for transition)
        cv::Mat Rinv;   //!< measurement covariance matrix (for measurement)
        cv::Mat eyeS;   //!< diagonal matrix dimS-by-dimS
};

    /*! \struct neigbourg_data_t
     *  \brief Variables to store data received from one neighbor node. It uses ICF-based form of Kalman
     *          Filter so it stores the received information vector & matrix as well as the target state.
     */
    struct neigbourg_data_t
    {
        int tid;
        cv::Mat v;      //!< ??
        cv::Mat V;      //!< ??
        bool    rcv_data;      //!< status of the data received by other nodes: received(true) or not received(false)
    };

    /*! \struct neigbourg_data_t_buf
     *  \brief Buffer for storing neigbourg_data_t of different iterations of the algorithm. Allows to receive unsync
     *  data at different iterations with a maximum of MAX_SIZE_BUFFER iterations simultaneously
     */
    struct neigbourg_data_t_buf
    {
        int tam_buf;                            //!< Size of the buffer
        std::vector<neigbourg_data_t> nb_data;  //!< List of neigbours's data (states and status)
        int iter_buffer;                     //!< Index with the current iterations
    };

    /*! \struct node_ctrl_t
     *  \brief Control behavior of node for each target
     */
    struct node_ctrl_t
    {
        bool initialized;                      //!< Flag to indicate tracker initialized (=true) or not (=false)
        bool detection_miss;                   //!< To detect the miss (ie, no-detection) situation (eg., target moves outside FOV)
        //consensus data
        unsigned long iter_counter;           //!< Counter for the iterations done in the consensus for each tracking step (k)
        int n_neighbourgs;                     //!< Number of node's neighbors
        std::vector<neigbourg_data_t_buf> nb_data_buffer; //!< Buffer for neighbor's data at different iterations (size MAX_SIZE_BUFFER);
    };

}

#endif // __WISECAMERACLUSTERICF_UTILS_H__
