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

#pragma GCC diagnostic ignored "-Wunused-function"

#ifndef __WISECAMERACAWCTRACKER_UTILS_H__
#define __WISECAMERACAWCTRACKER_UTILS_H__

#include <iostream>

#include <opencv2/tracking.hpp>

#include "WiseCameraCAWCTrackerPkt_m.h" //application messages
#include "WiseUtils.h"
#include "../Trackers/struck/_Tracker.h" //STRUCK algorithm & configuration

namespace CAWC
{
    //////////////////////////////////////////////////////////////////////
    //
    //  VISUAL TRACKERS (types, class & strings)
    //
    //////////////////////////////////////////////////////////////////////

    /// Defines the implemented trackers to be used by the CamTracker class
    typedef enum {
       STRUCK      = 0, //!< STRUCK tracker
       //...
    } tracker_type_t;

    /// Defines the data required to initialize the tracker in each camera
    struct target_initialization_t  {
        std::string filenameGT; //!< filename with ground-truth data (for multi-camera settings)
        int id;                 //!< id of the target (as described in the ground-truth data)
        int camID;              //!< id of the camera (as described in the ground-truth data)
        int frame;              //!< initialization frame number
        int Xc;                 //!< initialization X
        int Yc;                 //!< initialization Y
        int width;              //!< initialization width
        int height;             //!< initialization height
        double resize;          //!< Resizing factor (to apply for both frame and initialization data)
    };

    //class description
    /**
     * \class CamTracker
     * \brief This class implements a tracker running in the application layer of each node.
     * Currently, the possible trackers to use are defined in the structure tracker_type_t.
     *
     */
    class CamTracker
    {
        private:
            int _counter;               //!< counter for the number of processed frames

            int _id;                    //!< id of the node (camera) running the tracker
            tracker_type_t _selTracker; //!< flag for the selected tracker
            bool _started;              //!< flag to indicate the tracker is running

            cv::Rect2d _trackWindow;    //!< current target state estimation

            int _counterScore;
            int _frames2updateModel;
            bool _targetLost;
            double _framerate;

            bool init;                  //!< flag to compute the descriptor once
            cv::Mat _init_model;         //!< covariance matrix of descriptor at the initialization model
            cv::Mat _curr_model;         //!< covariance matrix of descriptor at the current model (updated each X frames)

            double _score;              //!< Tracker performance estimation without ground-truth

            cv::Ptr<cv::Tracker> _tracker; //!< OpenCV based trackers
            _Tracker* _struck;              //!< STRUCK tracker
            Config* _conf;                 //!< STRUCK configuration

            std::map<int,std::string> _trackers_str;  //!< Strings with each tracker name

            bool done;
            double _ms, _ss,_th;
            cv::Mat _data;
            int _recover_count;

        public:
            CamTracker(int id=0,double framerate=25); //!< Constructor
            ~CamTracker(); //!< Destructor

            bool selectTracker(CAWC::tracker_type_t type = STRUCK);     //!< Selects the tracker to be used
            bool initialize(cv::Mat frame, target_initialization_t);    //!< Initializes the tracker given a bounding box
            bool update(cv::Mat frame);                                 //!< Updates the target state estimation of the tracker
            void computeScore(cv::Mat frame);                           //!< Estimates tracker performance in the range (0,1)

            cv::Rect2d getTrackWindow ();   //!< Returns the current target state estimation
            int getId();                    //!< Returns the ID of the node using the tracker
            bool getStarted () ;            //!< Returns whether the tracker has started or not
            double getScore() ;             //!< Returns the tracker performance score
            void setId(int id);             //!< Sets the ID of the node using the tracker
            void setFramerate(double framerate);//!< Sets the framerate of the node using the tracker
            double getFramerate();              //!< gets the framerate of the node using the tracker

            const char *getTrackerName() {return _trackers_str[_selTracker].c_str();};//!< Returns a string with the tracker name

            void setTrackerUtility(double m, double v,double th);

        private:
            cv::Mat getCovDescriptor(cv::Mat img, cv::Rect roi);    //!< Computes the Covariance descriptor of the estimated target state
    };

    /**
      * This function creates text strings corresponding to the available trackers. It should be used for printing purposes.
      * A std::map class indexes each string using the values of tracker_type_t (treated as integers).
      * @return The std::map with the strings
      */
    static std::map<int,std::string> create_tracker_str() {

        std::map<int,std::string> m;
        m.insert(std::make_pair(STRUCK, "STRUCK"));
        //add pairs here for new trackers...
        return m;
    }

    //////////////////////////////////////////////////////////////////////////////////
    //
    //  CAMERA COALITION - (data types, structures & strings)
    //  The following set of functionalities implements the cost-aware coalition-based
    //  tracking (CAWC) for single targets described in the paper:
    //   Juan C. SanMiguel and A. Cavallaro "Cost-aware coalitions for collaborative
    //   Tracker tracking", IEEE Sensors Journal, May 2015
    //
    /////////////////////////////////////////////////////////////////////////////////

    /// Information filter employed by the coalition manager to track the target state (position) in the ground-plane.
    struct IF_filter_t  {
        unsigned int dimS; //!< Dimension of the state vector
        unsigned int dimM; //!< Dimension of the measurement vector

        cv::Mat x;      //!< posterior estimate
        cv::Mat x_;     //!< prior estimate

        cv::Mat J;      //!< posterior information matrix (inverse of covariance)
        cv::Mat J_;     //!< prior information matrix (inverse of covariance)
        cv::Mat P;      //!< priori error estimate covariance matrix P'(k)): P'(k)=A*P(k-1)*At + Q)
        cv::Mat P_;      //!< priori error estimate covariance matrix P'(k)): P'(k)=A*P(k-1)*At + Q)
        cv::Mat Pinv;

        cv::Mat u;      //!< Information vector
        cv::Mat U;      //!< Information matrix

        cv::Mat v;      //!< Accumulated Information vector
        cv::Mat V;      //!< Accumulated Information matrix

        cv::Mat A;      //!< transition matrix
        cv::Mat At;     //!< transition matrix (transpose)
        cv::Mat H;      //!< measurement matrix
        cv::Mat Ht;     //!< measurement matrix (transpose)

        cv::Mat Q;      //!< process covariance matrix (for transition)
        cv::Mat Rinv;   //!< measurement covariance matrix (for measurement)
        cv::Mat eyeS;   //!< diagonal matrix IF.dimS-by-IF.dimS

        cv::Mat z;      //!< Measurement
    };

  /**
    * This function initializes the struct IF_filter_t with default values
    * @return The IF filter
    */
    static IF_filter_t create_IF() {
         IF_filter_t IF;

         IF.dimS = 4; //target state size (x, y, velx, vely)
         IF.dimM = 2; //measurement size (x, y)
         double measNoiseCov = 10; //Covariance noise of the measurement
         double procNoiseCov = 10; //Covariance noise of the process

         IF.eyeS = cv::Mat::eye(IF.dimS, IF.dimS, CV_64F);

         //prior, posterior and covariance of the state
         IF.x_ = cv::Mat::zeros(IF.dimS, 1, CV_64F); //prior state
         IF.x  = cv::Mat::zeros(IF.dimS, 1, CV_64F); //posterior state
         IF.P_ = (cv::Mat_<double>(IF.dimS, IF.dimS) << 5,0,0,0, 0,5,0,0, 0,0,2,0, 0,0,0,2); //prior state covariance
         IF.P  = cv::Mat::zeros(IF.dimS, IF.dimS, CV_64F); //posterior state
         IF.Pinv  = cv::Mat::zeros(IF.dimS, IF.dimS, CV_64F);
         IF.Pinv  = IF.P.inv(cv::DECOMP_SVD); //prior state covariance

         //transition matrix
         IF.A  = (cv::Mat_<double>(IF.dimS, IF.dimS) << 1,0,1,0, 0,1,0,1, 0,0,1,0, 0,0,0,1);
         IF.At = cv::Mat::zeros(IF.dimS, IF.dimS, CV_64F);
         cv::transpose(IF.A, IF.At);

         //measurement matrix
         IF.H    = (cv::Mat_<double>(IF.dimM, IF.dimS) << 1,0,0,0, 0,1,0,0);
         IF.Ht = cv::Mat::zeros(IF.dimS, IF.dimM, CV_64F);
         cv::transpose(IF.H, IF.Ht);

         //measurement covariance
         IF.Rinv = measNoiseCov * cv::Mat::eye(IF.dimM, IF.dimM, CV_64F);
         IF.Rinv = 1.0 * IF.Rinv.inv(cv::DECOMP_SVD);

         //process covariance
         IF.Q  = procNoiseCov * (cv::Mat_<double>(IF.dimS, IF.dimS) << 1,0,0.1,0, 0,1,0,0.1, 0,0,0.1,0, 0,0,0,0.1);

         //information-based variables
         IF.J_ = cv::Mat::zeros(IF.dimS, IF.dimS, CV_64F); //prior information matrix
         IF.J_ = IF.eyeS/IF.P;
         IF.J  = cv::Mat::zeros(IF.dimS, IF.dimS, CV_64F); //posterior information matrix
         IF.v  = cv::Mat::zeros(IF.dimS, 1, CV_64F); //accumulated information vector
         IF.V  = cv::Mat::zeros(IF.dimS, IF.dimS, CV_64F); //accumulated information matrix
         IF.u  = cv::Mat::zeros(IF.dimS, 1, CV_64F);    //information vector
         IF.U  = cv::Mat::zeros(IF.dimS, IF.dimS, CV_64F); //information matrix

         IF.z  = cv::Mat::zeros(IF.dimM, 1, CV_64F);
         //LOGGER << "ICF CONFIG" << endl << "A=" << endl << IF.A << endl << "H=" << endl << IF.H
         //        << endl << "P=" << endl << IF.P << endl << "Pinv=" << endl << IF.Pinv << endl
         //        << endl << "Rinv=" << endl << IF.Rinv << endl << "Q=" << endl << IF.Q << endl;
         return IF;
    }

    ///  Structure to define the data kept by each node from its neighbors (received via network messages)
    struct neigbor_data_t {
        int step_counter;       //!< processing step corresponding to the stored data

        double utility;         //!< camera utility
        double battery_level;   //!< battery level in absolute values (mJ) or relative to the maximum capacity (current/max_battery)
        double load_level;      //!< load level (e.g. number of
        double priority;        //!< camera priority

        int camID;              //!< ID camera. This id relates to the ground-truth data, which may be different from the node ID assigned by the simulator
        int nodeID;             //!< ID node

        cv::Mat z;              //!< Measurement
        cv::Mat Rinv;           //!< Inverse of the measurement covariance matrix
        cv::Mat Ht;             //!< Transpose of the measurement matrix
        cv::Mat H;              //!< Measurement matrix

        //state_t_4D state;       //!< target state estimation
        bool    rcv_state;          //!< FLAG to indicate that target state has been received
        bool    rcv_data_utility;   //!< FLAG to indicate that utility has been received
        bool    rcv_ack_manager;    //!< FLAG to indicate that ACK has been sent to the manager
    };

    /**
     * This function initializes the structure neigbor_data_t with default values
     * @return The neighbor data
     */
    static neigbor_data_t init_neigb_data(int _nodeID, int _camID, int _step_counter, double _utility,
                                           double _battery_level, double _load_level, double _priority) {
       neigbor_data_t nb;
       nb.step_counter = _step_counter;
       nb.nodeID = _nodeID;
       nb.camID = _camID;
       nb.utility= _utility;
       nb.battery_level = _battery_level;
       nb.load_level = _load_level;
       nb.priority = _priority;

       nb.rcv_data_utility = false;
       nb.rcv_state = false;
       nb.rcv_ack_manager = false;

       return nb;
    }

    ///  Defines the current state of the coalition
    typedef enum {
        INACTIVE             =-1,  //!< Not running
        UTILITY_SHARING      = 0,  //!< Cameras are sharing their utilities
        MANAGER_SELECTION    = 1,  //!< Coalition manager is being selected
        NEGOTIATION          = 2,  //!< Manager is negotiating with cameras to join the coalition
        COLLABORATION        = 3,  //!< Manager is collaborating with selected cameras
    } coalition_state_t;

    ///  Structure to define the data kept by the coalition manager (received via network messages)
    struct coalition_data_t {
        bool initialized;
        coalition_state_t state;    //!< current state of the coalition
        IF_filter_t IF;             //!< IF filter for target tracking in the ground-plane

        bool initManager;           //!< FLAG to indicate if the first manager has been selected
        int manID;                  //!< ID of current manager
        bool rcv_state_manager;     //!< FLAG to indicate that coalition managers have exchanged the target state estimation

        std::vector<int> cams;      //!< set of cameras participating in the coalition
        std::vector<int> nego;      //!< set of cameras negotiating to join the coalition
        double u;                   //!< current coalition utility
        double mcost;               //!< marginal cost of adding a camera to the coalition
        double beta;                //!< parameter for manager selection

        double est_energy2operate;  //!< energy required for the operations to do within the coalition

        //!< Function to define the 'copy' operation between structures of type coalition_data_t
        coalition_data_t& operator =(const coalition_data_t& m) {
            state = m.state;
            initialized = m.initialized;
            initManager = m.initManager;
            manID = m.manID;
            nego = m.nego;
            cams = m.cams;
            u = m.u;
            mcost = m.mcost;
            beta = m.beta;
            IF = m.IF;
            est_energy2operate = m.est_energy2operate;
            return *this;
        }
    };

    /**
     * This function initializes the structure coalition_data_t with default values
     * @return The coalition data
     */
    static coalition_data_t init_coalition_data(int manID, double utility, double marginal_cost) {

         coalition_data_t coa;
         coa.initialized = false;
         coa.manID = manID;
         coa.initManager = false;
         coa.state = INACTIVE;
         coa.rcv_state_manager = false;

         coa.cams.clear();
         coa.u = utility;
         coa.mcost = marginal_cost;

         coa.IF = create_IF();
         coa.beta = 0.5;
         coa.est_energy2operate = 10;

         return coa;
     }

    ///  Structure to log the data generated by the coalition, created as a global variable.
    struct coalition_log_t {
        std::vector<int> step_count, manager,frameID;
        std::vector<double> ucoa;
        std::vector< std::vector<int> > cams, nego;
        std::vector<cv::Mat> u,b,l,x,P,rx,tx;
        cv::Mat rxdata;
        cv::Mat txdata;
        double beta;
    };

    ///  Structure to log the data generated by each camera.
    struct camera_data_t {
        int camid;
        std::vector<double> time;
        std::vector<int> step_count, manager, frameID;
        std::vector<double> u,b,l;
        std::vector<double> Xw,Yw;
        std::vector<double> Xi,Yi,Hi,Wi;
        std::vector< std::vector<int> > cams, nego;
        std::vector<cv::Mat> x,P;
    };

    /**
     * This function initializes the structure camera_data_t with default values
     * @return The camera data
     */
    static camera_data_t init_camera_data(int camID) {

        camera_data_t cam;
        cam.camid = camID;
        return cam;
     }

    //////////////////////////////////////////////////////////////////////////////////
    //
    //  CAMERA COALITION - PACKETS (data types, structures & strings)
    //  The following set of functionalities implements the structures to create packets
    //  determine their size for the approach cost-aware coalition-based tracking (CAWC)
    //  for single targets described in the paper:
    //   Juan C. SanMiguel and A. Cavallaro "Cost-aware coalitions for collaborative
    //   Tracker tracking", IEEE Sensors Journal, May 2015
    //
    /////////////////////////////////////////////////////////////////////////////////
    /**
    * This function creates text strings corresponding to the CAWC messages (defined in file WiseCameraCAWCTrackerPkt.msg).
    * It should be used for printing purposes. A std::map class indexes each string using the values of WiseCAWCPacketType (treated as integers).
    * @return The std::map with the strings
    */
    static std::map<int,std::string> create_pkt_str() {
        std::map<int,std::string> m;
        m.insert(std::make_pair(CAWC_UTILITY, "CAWC_UTILITY"));
        m.insert(std::make_pair(CAWC_NEWMANAGER, "CAWC_NEWMANAGER"));
        m.insert(std::make_pair(CAWC_NEWMANAGER_ACK, "CAWC_NEWMANAGER_ACK"));
        m.insert(std::make_pair(CAWC_NEWMANAGER_ACK_SEND, "CAWC_NEWMANAGER_ACK_SEND"));
        m.insert(std::make_pair(CAWC_NEWMANAGER_SEND, "CAWC_NEWMANAGER_SEND"));
        m.insert(std::make_pair(CAWC_NEGOTIATION_JOIN, "CAWC_NEGOTIATION_JOIN"));
        m.insert(std::make_pair(CAWC_NEGOTIATION_REPLY, "CAWC_NEGOTIATION_REPLY"));
        m.insert(std::make_pair(CAWC_COLLABORATION_REQUEST, "CAWC_COLLABORATION_REQUEST"));
        m.insert(std::make_pair(CAWC_COLLABORATION_DATA, "CAWC_COLLABORATION_DATA"));
        m.insert(std::make_pair(CAWC_COLLABORATION_END, "CAWC_COLLABORATION_END"));
        return m;
    }
    static std::map<int,std::string> CAWCpkt_str  = CAWC::create_pkt_str(); //strings for each packet type

    /**
    * This function defines the size of each CAWC message (with types defined in file WiseCameraCAWCTrackerPkt.msg).
    * A std::map class indexes each string using the values of WiseCAWCPacketType (treated as integers).
    * @return The std::map with the strings
    */
    static std::map<int,int> create_pkt_size_bytes() {
        std::map<int,int> m;

        //CAWC_UTILITY pkt --> message type(int) + frame number(int) + camera ID(int) + utility(double) + battery(double) + load(double) + priority(double)
        m.insert(std::make_pair(CAWC_UTILITY, 4*WISE_BYTES_INT + 4*WISE_BYTES_DOUBLE)); //44 bytes

        //CAWC_NEWMANAGER pkt --> message type(int) + frame number(int) + camera ID(int) + x(4*double) + P(16*double)
        m.insert(std::make_pair(CAWC_NEWMANAGER, 3*WISE_BYTES_INT)); //12 bytes

        //CAWC_NEWMANAGER_ACK pkt --> message type(int) + frame number(int) + ACK(char)
        m.insert(std::make_pair(CAWC_NEWMANAGER_ACK, 2*WISE_BYTES_INT + WISE_BYTES_UINT8)); //9 bytes

        //CAWC_NEWMANAGER_ACK_SEND pkt --> message type(int) + frame number(int) + ACK(char)
        m.insert(std::make_pair(CAWC_NEWMANAGER_ACK_SEND, 2*WISE_BYTES_INT + WISE_BYTES_UINT8)); //9 bytes

        //CAWC_NEWMANAGER_SEND_EST pkt --> message type(int) + frame number(int) + camera ID(int) + x(4*double) + P(16*double)
        m.insert(std::make_pair(CAWC_NEWMANAGER_SEND, 3*WISE_BYTES_INT+20*WISE_BYTES_DOUBLE)); //172 bytes
        //m.insert(std::make_pair(CAWC_NEWMANAGER_SEND, 3*WISE_BYTES_INT+14*WISE_BYTES_DOUBLE)); //108 bytes - only upper diagonal of P is sent

        //CAWC_NEGOTIATION_JOIN pkt --> message type(int) + frame number(int)
        m.insert(std::make_pair(CAWC_NEGOTIATION_JOIN, 2*WISE_BYTES_INT)); //8 bytes

        //CAWC_NEGOTIATION_REPLY pkt --> message type(int) + frame number(int) + data(char)
        m.insert(std::make_pair(CAWC_NEGOTIATION_REPLY, 2*WISE_BYTES_INT + WISE_BYTES_UINT8)); //9 bytes

        //CAWC_COLLABORATION_REQUEST pkt --> message type(int) + frame number(int) + data(char)
        m.insert(std::make_pair(CAWC_COLLABORATION_REQUEST, 2*WISE_BYTES_INT + WISE_BYTES_UINT8));//9 bytes

        //CAWC_COLLABORATION_DATA pkt --> message type(int) + frame number(int) + measurement (2*double) + covariance (4*double) + measurement matrix (8*double)
        m.insert(std::make_pair(CAWC_COLLABORATION_DATA, 2*WISE_BYTES_INT+12*WISE_BYTES_DOUBLE)); //104 bytes
        //m.insert(std::make_pair(CAWC_COLLABORATION_DATA, 2*WISE_BYTES_INT+4*WISE_BYTES_DOUBLE)); //50 bytes - same measurement matrix for all nodes
        //m.insert(std::make_pair(CAWC_COLLABORATION_DATA, 2*WISE_BYTES_INT+4*WISE_BYTES_DOUBLE+8*WISE_BYTES_INT)); //50 bytes - measurement matrix as 8*int

        //CAWC_COLLABORATION_DATA pkt --> message type(int) + frame number(int)
        m.insert(std::make_pair(CAWC_COLLABORATION_END, 2*WISE_BYTES_INT)); //8bytes
        return m;
    }
    static std::map<int,int> CAWCpkt_size = CAWC::create_pkt_size_bytes(); //size for each packet type

    /**
    * This function creates a utility packet of type CAWC_UTILITY to be shared among neighbor cameras
    * @return The packet
    */
    static WiseCameraCAWCTrackerPkt* create_utility_pkt(int nodeID, int camID,double score,double batlevel,double load,double priority, int currFrame) {
        WiseCameraCAWCTrackerPkt *pkt = new WiseCameraCAWCTrackerPkt("CAWC_UTILITY", APPLICATION_PACKET);
        pkt->setPktType(CAWC_UTILITY);
        pkt->setNodeID(nodeID);
        pkt->setCamID(camID);
        pkt->setUtility(score);
        pkt->setBattery_level(batlevel);
        pkt->setLoad_level(load); //only one target is the current load
        pkt->setPriority(priority); //equal priority
        pkt->setFrameID(currFrame);
        pkt->setByteLength(CAWCpkt_size[CAWC_UTILITY]);
        return pkt;
    }

    /**
    * This function creates a packet of type CAWC_NEWMANAGER to announce the new manager
    * @return The packet
    */
    static WiseCameraCAWCTrackerPkt* create_newMan_pkt(int nodeID, int camID, int newManager, cv::Mat x, cv::Mat P) {
       WiseCameraCAWCTrackerPkt *pkt = new WiseCameraCAWCTrackerPkt("CAWC_NEWMANAGER", APPLICATION_PACKET);
       pkt->setPktType(CAWC_NEWMANAGER);
       pkt->setNodeID(nodeID);
       pkt->setCamID(camID);
       pkt->setNewManager(newManager);
       pkt->setX(x.clone());
       pkt->setP(P.clone());
       pkt->setByteLength(CAWCpkt_size[CAWC_NEWMANAGER]);
       return pkt;
    }

    /**
     * This function creates a packet of type CAWC_COLLABORATION_DATA to send data to the coalition manager
     * @return The packet
     */
    static WiseCameraCAWCTrackerPkt* create_meas_pkt(int nodeID, int camID, cv::Mat z, cv::Mat H, cv::Mat Ht, cv::Mat Rinv) {
       WiseCameraCAWCTrackerPkt *pkt = new WiseCameraCAWCTrackerPkt("CAWC_COLLABORATION_DATA", APPLICATION_PACKET);
       pkt->setPktType(CAWC_COLLABORATION_DATA);
       pkt->setNodeID(nodeID);
       pkt->setCamID(camID);
       pkt->setZ(z.clone());
       pkt->setH(H.clone());
       pkt->setHt(Ht.clone());
       pkt->setRinv(Rinv.clone());
       pkt->setByteLength(CAWCpkt_size[CAWC_COLLABORATION_DATA]);
       return pkt;
    }

    /**
    * This function creates a generic packet of type WiseCAWCPacketType
    * @return The packet
    */
    static WiseCameraCAWCTrackerPkt* create_empty_pkt(WiseCAWCPacketType type,std::string str, int nodeID,int camID) {

        WiseCameraCAWCTrackerPkt *pkt = new WiseCameraCAWCTrackerPkt(str.c_str(), APPLICATION_PACKET);
        pkt->setPktType(type);
        pkt->setNodeID(nodeID);
        pkt->setCamID(camID);
        pkt->setByteLength(CAWCpkt_size[type]);
        return pkt;
    }
}
#endif // __WISECAMERACAWCTRACKER_UTILS_H__
