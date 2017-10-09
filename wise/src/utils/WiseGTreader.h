#ifndef __WISEGROUNDTRUTH_READER_H__
#define __WISEGROUNDTRUTH_READER_H__

#include <stdio.h>
#include <vector>
#include <map>

#define MAX_LINE 512


struct target_detection_t {
    int target_id;
    double bb_x_tl,bb_y_tl,bb_x_br,bb_y_br; //image plane coordinates (2D bounding box)
    double Xw,Yw,Zw; //world coordinates (3D point)
public:
    target_detection_t() : target_id(0), bb_x_tl(0), bb_y_tl(0), bb_x_br(0), bb_y_br(0), Xw(0), Yw(0), Zw(0) {} ;
    target_detection_t(double tid, double bb_x_tl,double bb_y_tl,double bb_x_br,double bb_y_br,double Xw,double Yw,double Zw) : target_id(tid), bb_x_tl(bb_x_tl), bb_y_tl(bb_y_tl), bb_x_br(bb_x_br), bb_y_br(bb_y_br), Xw(Xw), Yw(Yw), Zw(Zw)  {} ;
};

class WiseGTreader
{
    char _filename[255];
    FILE *_filePtr;

    bool _gt_common_all_cameras;
    char _lineFormat[255];

    //ground-truth format <frame,detections>
    std::map<int,std::vector<target_detection_t>> m;

public:
    WiseGTreader();
    ~WiseGTreader();

    int parsefile(const char *filename,const char * format);
    std::map<int,std::vector<target_detection_t>>* getData(){return &m;};
   /* int getProperty(const char *name, char *valor);
    int getProperty(const char *name, int *valor);
    int getProperty(const char *name, long *valor);
    int getProperty(const char *name, double *valor);
    int getProperty(const char *name, float *value);


    void readLines();

    int setProperty(const char *name, char *valor);
    int setProperty(const char *name, int valor);
    int setProperty(const char *name, long valor);
    int setProperty(const char *name, double value);


    */
};

#endif // __WISEGROUNDTRUTH_READER_H__

