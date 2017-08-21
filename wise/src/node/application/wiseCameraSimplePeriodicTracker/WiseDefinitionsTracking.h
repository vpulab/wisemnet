// *****************************************************************************
//  Original copyright (C): Christian Nastasi, 2011
//  Updated copyright (C): Juan C. SanMiguel, 2013
//  Author(s): Christian Nastasi, Juan C. SanMiguel
//
//  Developed at the:
//  - Retis LAB, TeCIP Institute, Scuola Superiore Sant'Anna (Pisa, Italy)
//  - School of Elec Eng and Computer Science, Queen Mary University of London (London, UK)
//  - VPULab, Universidad Autonoma of Madrid (Madrid, Spain)
//
//  This file is distributed under the terms in the attached LICENSE_2 file.
//
//  This file describes a template to implement tracking algorithms. Currently only used by WiseCameraDPF
//  TODO: remove this template in future releases of WiseMnet++
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
// *****************************************************************************
#ifndef __WISEDEFINITIONSTRACKING_H__
#define __WISEDEFINITIONSTRACKING_H__

#include <fstream>
#include <opencv.hpp>

//! Generic structures for periodic Target Tracking
//namespace WiseDefinitionsTracking {

    //! Dimension of the 4D state vector
    static const int DIM_STATE_T_4D = 4;

    //! Dimension of the 2D state vector
    static const int DIM_STATE_T_2D = 2;

    //! Dimension of the 2D measurement vector
    static const int DIM_MEASUREMENT_T_2D = 2;

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

    /*! \struct state_t_2D
     *  \brief 2D State vector of target (posx, posy)
     */
    struct state_t_2D
    {
        unsigned int tid;   //!< Target ID
        double x;           //!< Target x-position
        double y;           //!< Target y-position

        /*!
         * To print target data as string following the format "(posx, posy)"
         * @return The string to be printed
         */
        inline std::string str() const
        {
            std::ostringstream os;
            os << "(" << x << ", " << y << ")";
            return os.str();
        }
    };

    /*! \struct measurement_t_2D
     *  \brief 2D Measurement vector of target (posx and posy)
     */
    struct measurement_t_2D
    {
        unsigned int tid;   //!< Target ID
        double x;           //!< x-position
        double y;           //!< y-position

        /*!
         * To print target data as string following the format "(observationx, observationy)"
         * @return The string to be printed
         */
        inline std::string str() const
        {
            std::ostringstream os;
            os << "(" << x << ", " << y << ")";
            return os.str();
        }
    };
//}//end WiseDefinitionsTracking

#endif // __WISEDEFINITIONSTRACKING_H__
