/***************************************************************************
 *   cameraModel.cpp   - description
 *
 *   This program is part of the Etiseo project.
 *
 *   See http://www.etiseo.net  http://www.silogic.fr   
 *
 *   (C) Silogic - Etiseo Consortium
 ***************************************************************************/
#include <fstream>

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include <math.h>

#include <libxml/xmlwriter.h>
#include <libxml/xmlreader.h>

#include "cameraModel.h"
#include "WiseUtils.h"
using namespace std;

using namespace Etiseo;

CameraModel::CameraModel(std::string calibType)
{
	isInit = false;
	isInit_w2map = false;
	this->mcalibType = calibType;
}

CameraModel::~CameraModel()
{
}

void CameraModel::internalInit()
{
    if (mcalibType.compare("tsai") == 0)
    {
        double sa;
        double ca;
        double sb;
        double cb;
        double sg;
        double cg;

        // compute matrix ...
        sa = sin(mRx);
        ca = cos(mRx);
        sb = sin(mRy);
        cb = cos(mRy);
        sg = sin(mRz);
        cg = cos(mRz);

        mR11 = cb * cg;
        mR12 = cg * sa * sb - ca * sg;
        mR13 = sa * sg + ca * cg * sb;
        mR21 = cb * sg;
        mR22 = sa * sb * sg + ca * cg;
        mR23 = ca * sb * sg - cg * sa;
        mR31 = -sb;
        mR32 = cb * sa;
        mR33 = ca * cb;

        //compute camera position
        mCposx = -(mTx*mR11 + mTy*mR21 + mTz*mR31);
        mCposy = -(mTx*mR12 + mTy*mR22 + mTz*mR32);
        mCposz = -(mTx*mR13 + mTy*mR23 + mTz*mR33);
    }
    
    if (mcalibType.compare("homography") == 0)
    {
       mH_i2w = cv::Mat::zeros(3,3,CV_32F);
       mH_w2i = cv::Mat::zeros(3,3,CV_32F);
    }
    mH_w2map= cv::Mat::zeros(3,3,CV_32F);

    isInit = true;
}

void CameraModel::setGeometry(int width, int height, double ncx, double nfx, double dx, double dy, double dpx, double dpy)
{
	mImgWidth = width;
	mImgHeight = height;
	mNcx = ncx;
	mNfx = nfx;
	mDx = dx;
	mDy = dy;
	mDpx = dpx;
	mDpy = dpy; 
	
	isInit = false;
}

void CameraModel::setIntrinsic(double focal, double kappa1, double cx, double cy, double sx)
{
	mFocal = focal;
	mKappa1 = kappa1;
	mCx = cx;
	mCy = cy;
	mSx = sx;
	
	isInit = false;
}
	  
void CameraModel::setExtrinsic(double tx, double ty, double tz, double rx, double ry, double rz)
{
	mTx = tx;
	mTy = ty;
	mTz = tz;
	mRx = rx;
	mRy = ry;
	mRz = rz;
	
	isInit = false;
}

bool CameraModel::fromXmlCalib(std::string calibFile)
{

    Etiseo::UtilXml::Init();
    std::ifstream is;
    is.open(calibFile.c_str());

    if (!is.is_open())
    {
        std::cout << "cannot read image2world calibration from file: "<< calibFile << std::endl;
        return false;
    }

    std::string prevLocale = setlocale(LC_NUMERIC, NULL);
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); //use '.' as decimal separator
    //std::setlocale(LC_NUMERIC, "es_ES.UTF-8"); //use ',' as decimal separator

    xmlDocPtr doc = xmlReadIO(UtilXml::ReadCallback,UtilXml::InputCloseCallback, &is,  NULL, NULL, 0);
    xmlNodePtr node = xmlDocGetRootElement(doc);

    if (mcalibType.compare("tsai") == 0)
    {
        if (node) {
                char *temp;
                if (xmlStrcmp(node->name, XML_TAG_CAMERA) == 0) {

                    temp = (char*)xmlGetProp(node, XML_TAG_NAME);
                    if (temp)
                        mName = temp;

                    xmlNodePtr child = node->xmlChildrenNode;
                    while (child != NULL) {
                        if (xmlStrcmp(child->name, XML_TAG_GEOMETRY) == 0) {

                            temp = (char*)xmlGetProp(child, XML_TAG_WIDTH);
                            if (temp) {
                                mImgWidth = atoi(temp);
                                xmlFree(temp);
                            }
                            temp = (char*)xmlGetProp(child, XML_TAG_HEIGHT);
                            if (temp) {
                                mImgHeight = atoi(temp);
                                xmlFree(temp);
                            }
                            temp = (char*)xmlGetProp(child, XML_TAG_NCX);
                            if (temp) {
                                std::string tmp(temp);
                                //tmp.replace(tmp.find("."), 1, ",");
                                mNcx = atof(tmp.c_str());
                                xmlFree(temp);
                            }
                            temp = (char*)xmlGetProp(child, XML_TAG_NFX);
                            if (temp) {
                                std::string tmp(temp);
                                //tmp.replace(tmp.find("."), 1, ",");
                                mNfx = atof(tmp.c_str());
                                xmlFree(temp);
                            }
                            temp = (char*)xmlGetProp(child, XML_TAG_DX);
                            if (temp) {
                                std::string tmp(temp);
                                //tmp.replace(tmp.find("."), 1, ",");
                                mDx = atof(tmp.c_str());
                                xmlFree(temp);
                            }
                            temp = (char*)xmlGetProp(child, XML_TAG_DY);
                            if (temp) {
                                std::string tmp(temp);
                                //tmp.replace(tmp.find("."), 1, ",");
                                mDy = atof(tmp.c_str());
                                xmlFree(temp);
                            }
                            temp = (char*)xmlGetProp(child, XML_TAG_DPX);
                            if (temp) {
                                std::string tmp(temp);
                                //tmp.replace(tmp.find("."), 1, ",");
                                mDpx = atof(tmp.c_str());
                                xmlFree(temp);
                            }
                            temp = (char*)xmlGetProp(child, XML_TAG_DPY);
                            if (temp) {
                                std::string tmp(temp);
                                //tmp.replace(tmp.find("."), 1, ",");
                                mDpy = atof(tmp.c_str());
                                xmlFree(temp);
                            }
                        } else if (xmlStrcmp(child->name, XML_TAG_INTRINSIC) == 0) {

                            temp = (char*)xmlGetProp(child, XML_TAG_FOCAL);
                            if (temp) {
                                std::string tmp(temp);
                                //tmp.replace(tmp.find("."), 1, ",");
                                mFocal = atof(temp);
                                xmlFree(temp);
                            }
                            temp = (char*)xmlGetProp(child, XML_TAG_KAPPA1);
                            if (temp) {
                                std::string tmp(temp);
                                //tmp.replace(tmp.find("."), 1, ",");
                                mKappa1 = atof(tmp.c_str());
                                xmlFree(temp);
                            }
                            temp = (char*)xmlGetProp(child, XML_TAG_CX);
                            if (temp) {
                                std::string tmp(temp);
                                //tmp.replace(tmp.find("."), 1, ",");
                                mCx = atof(tmp.c_str());
                                xmlFree(temp);
                            }
                            temp = (char*)xmlGetProp(child, XML_TAG_CY);
                            if (temp) {
                                std::string tmp(temp);
                                //tmp.replace(tmp.find("."), 1, ",");
                                mCy = atof(tmp.c_str());
                                xmlFree(temp);
                            }
                            temp = (char*)xmlGetProp(child, XML_TAG_SX);
                            if (temp) {
                                std::string tmp(temp);
                               //tmp.replace(tmp.find("."), 1, ",");
                                mSx = atof(tmp.c_str());
                                xmlFree(temp);
                            }
                        } else if (xmlStrcmp(child->name, XML_TAG_EXTRINSIC) == 0) {

                            temp = (char*)xmlGetProp(child, XML_TAG_TX);
                            if (temp) {
                                std::string tmp(temp);
                                //tmp.replace(tmp.find("."), 1, ",");
                                mTx = atof(tmp.c_str());
                                xmlFree(temp);
                            }
                            temp = (char*)xmlGetProp(child, XML_TAG_TY);
                            if (temp) {
                                std::string tmp(temp);
                                //tmp.replace(tmp.find("."), 1, ",");
                                mTy = atof(tmp.c_str());
                                xmlFree(temp);
                            }
                            temp = (char*)xmlGetProp(child, XML_TAG_TZ);
                            if (temp) {
                                std::string tmp(temp);
                                //tmp.replace(tmp.find("."), 1, ",");
                                mTz = atof(tmp.c_str());
                                xmlFree(temp);
                            }
                            temp = (char*)xmlGetProp(child, XML_TAG_RX);
                            if (temp) {
                                std::string tmp(temp);
                                //tmp.replace(tmp.find("."), 1, ",");
                                mRx = atof(tmp.c_str());
                                xmlFree(temp);
                            }
                            temp = (char*)xmlGetProp(child, XML_TAG_RY);
                            if (temp) {
                                std::string tmp(temp);
                                //tmp.replace(tmp.find("."), 1, ",");
                                mRy = atof(tmp.c_str());
                                xmlFree(temp);
                            }
                            temp = (char*)xmlGetProp(child, XML_TAG_RZ);
                            if (temp) {
                                std::string tmp(temp);
                                //tmp.replace(tmp.find("."), 1, ",");
                                mRz = atof(tmp.c_str());
                                xmlFree(temp);
                            }
                        }

                        child = child->next;
                    }

                    internalInit();
                }
        }
    }

    if (mcalibType.compare("homography") == 0)
    {
       internalInit();

       if (node) {
           //char *temp;
           if (xmlStrcmp(node->name, XML_TAG_CALIBRATION) == 0) {

               xmlNodePtr child = node->xmlChildrenNode;
               while (child != NULL) {
                   if (xmlStrcmp(child->name, XML_TAG_HOMOGRAPHY) == 0) {

                       xmlNodePtr child2 = child->xmlChildrenNode;

                       while (child2 != NULL) {
                           if (xmlStrcmp(child2->name, XML_TAG_DATA) == 0) {

                               const vector<string> vals = split((char*)xmlNodeGetContent(child2), " ",true);
                               int i=0;
                               while(atof(vals[i].c_str())==0)
                                   i++;
                               mH_w2i.at<float>(0,0) =  atof(vals[i].c_str());
                               mH_w2i.at<float>(0,1) =  atof(vals[i+1].c_str());
                               mH_w2i.at<float>(0,2) =  atof(vals[i+2].c_str());
                               mH_w2i.at<float>(1,0) =  atof(vals[i+3].c_str());
                               mH_w2i.at<float>(1,1) =  atof(vals[i+4].c_str());
                               mH_w2i.at<float>(1,2) =  atof(vals[i+5].c_str());
                               mH_w2i.at<float>(2,0) =  atof(vals[i+6].c_str());
                               mH_w2i.at<float>(2,1) =  atof(vals[i+7].c_str());
                               mH_w2i.at<float>(2,2) =  atof(vals[i+8].c_str());

                               //std::cout << mH_w2i << endl;
                               mH_i2w = mH_w2i.inv();
                           }
                           child2 = child2->next;
                       }
                   }
                   if (xmlStrcmp(child->name, XML_TAG_CENTERCAM) == 0) {

                      xmlNodePtr child2 = child->xmlChildrenNode;
                      while (child2 != NULL) {
                          if (xmlStrcmp(child2->name, XML_TAG_DATA) == 0) {

                              const vector<string> vals = split((char*)xmlNodeGetContent(child2), " ",true);
                              int i=0;
                              while(atof(vals[i].c_str())==0)
                                  i++;
                              mCposx = atof(vals[i].c_str());
                              mCposy = atof(vals[i+1].c_str());
                              mCposz = atof(vals[i+2].c_str());
                          }
                          child2 = child2->next;
                      }
                   }
                   else if (xmlStrcmp(child->name, XML_TAG_GEOMETRY) == 0) {
                         xmlNodePtr child2 = child->xmlChildrenNode;
                         while (child2 != NULL) {
                             if (xmlStrcmp(child2->name, XML_TAG_WIDTH) == 0) {

                                 const vector<string> vals = split((char*)xmlNodeGetContent(child2), " ",true);
                                 int i=0;
                                 while(atoi(vals[i].c_str())==0)
                                     i++;
                                 mImgWidth = atoi(vals[i].c_str());
                             }
                             else if (xmlStrcmp(child2->name, XML_TAG_HEIGHT) == 0) {

                                  const vector<string> vals = split((char*)xmlNodeGetContent(child2), " ",true);
                                  int i=0;
                                  while(atoi(vals[i].c_str())==0)
                                      i++;
                                  mImgHeight = atoi(vals[i].c_str());
                             }
                             child2 = child2->next;
                         }
                   }
                   child = child->next;
               }
           }
       }
    }

    return isInit;
}

bool CameraModel::fromXmlMap(std::string calibMapFile)
{
    Etiseo::UtilXml::Init();
    std::ifstream is;
    is.open(calibMapFile.c_str());

    if (!is.is_open())
    {
        std::cout << "cannot read world2map calibration from file: "<< calibMapFile << std::endl;
        isInit_w2map = false;
        return false;
    }

    std::string prevLocale = setlocale(LC_NUMERIC, NULL);
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); //use '.' as decimal separator
    //std::setlocale(LC_NUMERIC, "es_ES.UTF-8"); //use ',' as decimal separator

    xmlDocPtr doc = xmlReadIO(UtilXml::ReadCallback,UtilXml::InputCloseCallback, &is,  NULL, NULL, 0);
    xmlNodePtr node = xmlDocGetRootElement(doc);

   if (node) {
       if (xmlStrcmp(node->name, XML_TAG_CALIBRATION) == 0) {

           xmlNodePtr child = node->xmlChildrenNode;
           while (child != NULL) {
               if (xmlStrcmp(child->name, XML_TAG_HOMOGRAPHY) == 0) {

                   xmlNodePtr child2 = child->xmlChildrenNode;

                   while (child2 != NULL) {
                       if (xmlStrcmp(child2->name, XML_TAG_DATA) == 0) {

                           const vector<string> vals = split((char*)xmlNodeGetContent(child2), " ",true);
                           int i=0;
                           while(atof(vals[i].c_str())==0)
                               i++;
                           mH_w2map.at<float>(0,0) =  atof(vals[i].c_str());
                           mH_w2map.at<float>(0,1) =  atof(vals[i+1].c_str());
                           mH_w2map.at<float>(0,2) =  atof(vals[i+2].c_str());
                           mH_w2map.at<float>(1,0) =  atof(vals[i+3].c_str());
                           mH_w2map.at<float>(1,1) =  atof(vals[i+4].c_str());
                           mH_w2map.at<float>(1,2) =  atof(vals[i+5].c_str());
                           mH_w2map.at<float>(2,0) =  atof(vals[i+6].c_str());
                           mH_w2map.at<float>(2,1) =  atof(vals[i+7].c_str());
                           mH_w2map.at<float>(2,2) =  atof(vals[i+8].c_str());

                           //std::cout << mH_w2map << endl;
                       }
                       child2 = child2->next;
                   }
               }
               child = child->next;
           }
       }
   }

   isInit_w2map = true;
   return isInit_w2map;
}

void CameraModel::toXml(std::ostream& os) const
{
	XmlOutputHandler	out(os);
	
	xmlTextWriterPtr  writer = xmlNewTextWriter(out.xmlOutputBuffer());
	
	xmlTextWriterSetIndent (writer, 1);	
	xmlTextWriterStartDocument(writer, NULL, "UTF-8", NULL);

	xmlTextWriterStartElement(writer, XML_TAG_CAMERA);
	xmlTextWriterWriteFormatAttribute(writer, XML_TAG_NAME,   "%s", mName.c_str());
		
		xmlTextWriterStartElement(writer, XML_TAG_GEOMETRY);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_WIDTH, "%d",	mImgWidth);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_HEIGHT,"%d",	mImgHeight);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_NCX,	 "%lf",	mNcx);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_NFX,   "%lf",	mNfx);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_DX,    "%lf",	mDx);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_DY,	 "%lf",	mDy);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_DPX,   "%lf",	mDpx);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_DPY,   "%lf",	mDpy);
		xmlTextWriterEndElement(writer); // XML_TAG_GEOMETRY

		
		xmlTextWriterStartElement(writer, XML_TAG_INTRINSIC);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_FOCAL, "%lf",	mFocal);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_KAPPA1,"%lf",	mKappa1);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_CX,	 "%lf",	mCx);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_CY,    "%lf",	mCy);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_SX,    "%lf",	mSx);
		xmlTextWriterEndElement(writer); // XML_TAG_INTRINSIC
	
		xmlTextWriterStartElement(writer, XML_TAG_EXTRINSIC);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_TX, "%lf",	mTx);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_TY, "%lf",	mTy);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_TZ, "%lf",	mTz);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_RX, "%lf",	mRx);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_RY, "%lf",	mRy);
			xmlTextWriterWriteFormatAttribute(writer, XML_TAG_RZ, "%lf",	mRz);
		xmlTextWriterEndElement(writer); // XML_TAG_EXTRINSIC
	
	xmlTextWriterEndElement(writer); // XML_TAG_CAMERA
	
	xmlTextWriterEndDocument(writer);
	xmlFreeTextWriter(writer);

}

bool CameraModel::fromDat(std::istream& is, int width, int height)
{
	is >> mNcx;
	is >> mNfx;
	is >> mDx;
	is >> mDy;
	is >> mDpx;
	is >> mDpy;
	is >> mCx;
	is >> mCy;
	is >> mSx;
	is >> mFocal;
	is >> mKappa1;
	is >> mTx;
	is >> mTy;
	is >> mTz;
	is >> mRx;
	is >> mRy;
	is >> mRz;
	
	mImgWidth = width;
	mImgHeight = height;
	
	internalInit();
	
	return isInit;    
    
}

bool CameraModel::imageToWorld(double Xi, double Yi, double Zw, double& Xw, double& Yw)
{
	bool done;
	double Xd;
	double Yd;
	double Xu;
	double Yu;
	double common_denominator;
	
	if (isInit)
	{
	    if (mcalibType.compare("tsai") == 0)
	    {
		/* convert from image to distorted sensor coordinates */
		Xd = mDpx * (Xi - mCx) / mSx;
		Yd = mDpy * (Yi - mCy);
		
		/* convert from distorted sensor to undistorted sensor plane coordinates */
		distortedToUndistortedSensorCoord (Xd, Yd, Xu, Yu);
		
		/* calculate the corresponding xw and yw world coordinates	 */
		/* (these equations were derived by simply inverting	 */
		/* the perspective projection equations using Macsyma)	 */
		common_denominator = ((mR11 * mR32 - mR12 * mR31) * Yu +
				(mR22 * mR31 - mR21 * mR32) * Xu -
				mFocal * mR11 * mR22 + mFocal * mR12 * mR21);
	
		Xw = (((mR12 * mR33 - mR13 * mR32) * Yu +
			(mR23 * mR32 - mR22 * mR33) * Xu -
			mFocal * mR12 * mR23 + mFocal * mR13 * mR22) * Zw +
			(mR12 * mTz - mR32 * mTx) * Yu +
			(mR32 * mTy - mR22 * mTz) * Xu -
			mFocal * mR12 * mTy + mFocal * mR22 * mTx) / common_denominator;
	
		Yw = -(((mR11 * mR33 - mR13 * mR31) * Yu +
			(mR23 * mR31 - mR21 * mR33) * Xu -
			mFocal * mR11 * mR23 + mFocal * mR13 * mR21) * Zw +
			(mR11 * mTz - mR31 * mTx) * Yu +
			(mR31 * mTy - mR21 * mTz) * Xu -
			mFocal * mR11 * mTy + mFocal * mR21 * mTx) / common_denominator;
	    }

	    if (mcalibType.compare("homography") == 0)
	    {
	        cv::Mat coord = (cv::Mat_<float>(3, 1) << Xi, Yi, 1);
	        cv::Mat prj = mH_i2w * coord;

	        Xw = prj.at<float>(0,0)/ prj.at<float>(2,0);
	        Yw = prj.at<float>(1,0)/ prj.at<float>(2,0);
	    }
		done = true;
	}
	return done;
}

void CameraModel::distortedToUndistortedSensorCoord (double Xd, double Yd, double& Xu, double& Yu)
{
	double    distortion_factor;
	
	/* convert from distorted to undistorted sensor plane coordinates */
	distortion_factor = 1 + mKappa1 * (Xd*Xd + Yd*Yd);
	Xu = Xd * distortion_factor;
	Yu = Yd * distortion_factor;
}

bool CameraModel::worldToImage(double Xw, double Yw, double Zw, double& Xi, double& Yi)
{
	bool done = false;
	double xc;
	double yc;
	double zc;
	double Xu;
	double Yu;
	double Xd;
	double Yd;
	
	if (isInit)
	{
	    if (mcalibType.compare("tsai") == 0)
	    {
            /* convert from world coordinates to camera coordinates */
            xc = mR11 * Xw + mR12 * Yw + mR13 * Zw + mTx;
            yc = mR21 * Xw + mR22 * Yw + mR23 * Zw + mTy;
            zc = mR31 * Xw + mR32 * Yw + mR33 * Zw + mTz;

            /* convert from camera coordinates to undistorted sensor plane coordinates */
            Xu = mFocal * xc / zc;
            Yu = mFocal * yc / zc;

            /* convert from undistorted to distorted sensor plane coordinates */
            undistortedToDistortedSensorCoord (Xu, Yu, Xd, Yd);

            /* convert from distorted sensor plane coordinates to image coordinates */
            Xi = Xd * mSx / mDpx + mCx;
            Yi = Yd / mDpy + mCy;
	    }

        if (mcalibType.compare("homography") == 0)
        {
            cv::Mat coord = (cv::Mat_<float>(3, 1) << Xw, Yw, 1);
            cv::Mat prj = mH_w2i * coord;

            Xi = prj.at<float>(0,0)/ prj.at<float>(2,0);
            Yi = prj.at<float>(1,0)/ prj.at<float>(2,0);
        }
		done = true;
	}
	return done;
}

void CameraModel::undistortedToDistortedSensorCoord (double Xu, double Yu, double& Xd, double& Yd)
{
	double Ru;
	double Rd;
	double lambda;
	double c;
	double d;
	double Q;
	double R;
	double D;
	double S;
	double T;
	double sinT;
	double cosT;
	
	if (((Xu == 0) && (Yu == 0)) || (mKappa1 == 0))
	{
		Xd = Xu;
		Yd = Yu;
	}
	else
	{
		Ru = sqrt(Xu*Xu + Yu*Yu);
		
		c = 1.0 / mKappa1;
		d = -c * Ru;
		
		Q = c / 3;
		R = -d / 2;
		D = Q*Q*Q + R*R;
		
		if (D >= 0) 
		{
			/* one real root */
			D = sqrt(D);
			if (R + D > 0)
			{
				S = pow(R + D, 1.0/3.0);
			}
			else
			{
				S = -pow(-R - D, 1.0/3.0);
			}
			
			if (R - D > 0)
			{
				T = pow(R - D, 1.0/3.0);
			}
			else
			{
				T = -pow(D - R, 1.0/3.0);
			}
			
			Rd = S + T;
			
			if (Rd < 0) 
			{
				Rd = sqrt(-1.0 / (3 * mKappa1));
				/*fprintf (stderr, "\nWarning: undistorted image point to distorted image point mapping limited by\n");
				fprintf (stderr, "         maximum barrel distortion radius of %lf\n", Rd);
				fprintf (stderr, "         (Xu = %lf, Yu = %lf) -> (Xd = %lf, Yd = %lf)\n\n", Xu, Yu, Xu * Rd / Ru, Yu * Rd / Ru);*/
			}
		}
		else
		{
			/* three real roots */
			D = sqrt(-D);
			S = pow( sqrt(R*R + D*D) , 1.0/3.0 );
			T = atan2(D, R) / 3;
			sinT = sin(T);
			cosT = cos(T);
			
			/* the larger positive root is    2*S*cos(T)                   */
			/* the smaller positive root is   -S*cos(T) + SQRT(3)*S*sin(T) */
			/* the negative root is           -S*cos(T) - SQRT(3)*S*sin(T) */
			
			Rd = -S * cosT + sqrt(3.0) * S * sinT;	/* use the smaller positive root */
		}
		
		lambda = Rd / Ru;
		
		Xd = Xu * lambda;
		Yd = Yu * lambda;
	}
}

bool CameraModel::undistortedToDistortedImageCoord (double Xfu, double Yfu, double& Xfd, double& Yfd)
{
	bool done = false;
	double Xu;
	double Yu;
	double Xd;
	double Yd;
	
	if (isInit)
	{
		/* convert from image to sensor coordinates */
		Xu = mDpx * (Xfu - mCx) / mSx;
		Yu = mDpy * (Yfu - mCy);
		
		/* convert from undistorted sensor to distorted sensor plane coordinates */
		undistortedToDistortedSensorCoord (Xu, Yu, Xd, Yd);
		
		/* convert from sensor to image coordinates */
		Xfd = Xd * mSx / mDpx + mCx;
		Yfd = Yd / mDpy + mCy;
		
		done = true;
	}
	return done;
}

bool CameraModel::distortedToUndistortedImageCoord (double Xfd, double Yfd, double& Xfu, double& Yfu)
{
	bool done = false;
	double Xd;
	double Yd;
	double Xu;
	double Yu;
	
	if (isInit)
	{
		/* convert from image to sensor coordinates */
		Xd = mDpx * (Xfd - mCx) / mSx;
		Yd = mDpy * (Yfd - mCy);
		
		/* convert from distorted sensor to undistorted sensor plane coordinates */
		distortedToUndistortedSensorCoord (Xd, Yd, Xu, Yu);
		
		/* convert from sensor to image coordinates */
		Xfu = Xu * mSx / mDpx + mCx;
		Yfu = Yu / mDpy + mCy;
	
		done = true;
	}
	return done;
}

bool CameraModel::worldToCameraCoord (double xw, double yw, double zw, double& xc, double& yc, double& zc)
{
	bool done = false;
	
	if (isInit)
	{
		xc = mR11 * xw + mR12 * yw + mR13 * zw + mTx;
		yc = mR21 * xw + mR22 * yw + mR23 * zw + mTy;
		zc = mR31 * xw + mR32 * yw + mR33 * zw + mTz;
		
		done = true;
	}
	return done;
}

bool CameraModel::cameraToWorldCoord (double xc, double yc, double zc, double& xw, double& yw, double& zw)
{
	bool done = false;
	double common_denominator;
	
	if (isInit)
	{

	    if (mcalibType.compare("tsai") == 0)
	    {
		/* these equations were found by simply inverting the previous routine using Macsyma */
		
		common_denominator = ((mR11 * mR22 - mR12 * mR21) * mR33 +
			(mR13 * mR21 - mR11 * mR23) * mR32 +
			(mR12 * mR23 - mR13 * mR22) * mR31);
			  
		xw = ((mR12 * mR23 -mR13 * mR22) * zc + 
			(mR13 * mR32 - mR12 * mR33) * yc +
			(mR22 * mR33 - mR23 * mR32) * xc +
			(mR13 * mR22 - mR12 * mR23) * mTz +
			(mR12 * mR33 - mR13 * mR32) * mTy +
			(mR23 * mR32 - mR22 * mR33) * mTx) / common_denominator;
			
		yw = -((mR11 * mR23 - mR13 * mR21) * zc +
			(mR13 * mR31 - mR11 * mR33) * yc +
			(mR21 * mR33 - mR23 * mR31) * xc +
			(mR13 * mR21 - mR11 * mR23) * mTz +
			(mR11 * mR33 - mR13 * mR31) * mTy +
			(mR23 * mR31 - mR21 * mR33) * mTx) / common_denominator;
			
		zw = ((mR11 * mR22 - mR12 * mR21) * zc +
			(mR12 * mR31 - mR11 * mR32) * yc +
			(mR21 * mR32 - mR22 * mR31) * xc +
			(mR12 * mR21 - mR11 * mR22) * mTz +
			(mR11 * mR32 - mR12 * mR31) * mTy +
			(mR22 * mR31 - mR21 * mR32) * mTx) / common_denominator;
	    }
	    if (mcalibType.compare("homography") == 0)
	    {

	    }
		done = true;
	}
	return done;
}

//! from world coordinate to ground-plane map coordinate
bool CameraModel::worldToMapCoord (double xw, double yw, double zw, double& xm, double& ym)
{
    bool done = false;

    if(isInit_w2map)
    {
        cv::Mat coord = (cv::Mat_<float>(3, 1) << xw, yw, zw);
        cv::Mat prj = mH_w2map * coord;

        xm = prj.at<float>(0,0); //xm = prj.at<float>(0,0)/ prj.at<float>(2,0);
        ym = prj.at<float>(1,0); //ym = prj.at<float>(1,0)/ prj.at<float>(2,0);
        done = true;
    }
    return done;
}

//! from map coordinate to ground-plane world coordinate
bool CameraModel::mapToWorldCoord (double xm, double ym, double zm, double& xw, double& yw, double& zw)
{
    bool done = false;

    if(isInit_w2map)
    {
        cv::Mat coord = (cv::Mat_<float>(3, 1) << xm, ym, zm);
        cv::Mat prj = mH_w2map.inv() * coord;

        //TODO: check correctness of this conversion
        xw = prj.at<float>(0,0)/ prj.at<float>(2,0);
        yw = prj.at<float>(1,0)/ prj.at<float>(2,0);
        zw = 0;
        done = true;
    }
    return done;
}
