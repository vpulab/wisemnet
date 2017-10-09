#include <opencv.hpp>
#include <WiseGTreader.h>

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

WiseGTreader::WiseGTreader()
{
    strcpy(_filename, "");
    _filePtr = NULL;

    //initialize the map
    target_detection_t det(-1,-1,-1,-1,-1,-1,-1,-1);
    std::vector<target_detection_t> dets;
    dets.push_back(det);
    m.insert(std::make_pair(-1, dets));
}

WiseGTreader::~WiseGTreader()
{
    if (_filePtr != NULL)
        fclose(_filePtr);
}

int WiseGTreader::parsefile(const char * filename,const char * format)
{
    sprintf(_filename, "%s", filename);
    _filePtr = fopen(_filename,"r");
    if ((_filePtr == NULL) || (_filename == NULL))
    {
       printf("ERROR the file '%s' cannot be opened\n", _filename);
       return -1;
    }

    char txtline[MAX_LINE];
    fseek(_filePtr, 0, SEEK_SET);

    float frID,tID,tlX,tlY,width,height,conf=-1,Xw=-1,Yw=-1,Zw=-1,camID=-1;
    std::vector<target_detection_t> dets;
    double last_frameID=1;

    int framecount=1,Xmax=-1,Ymax=1,Xmin=-1,Ymin=-1;
    while (fgets(txtline, MAX_LINE, _filePtr) != NULL)
    {
        // skip comments
        if (strncmp(txtline, "//", 2) == 0)
            continue;

        // skip empty lines
        if (strcmp(txtline, "\n") == 0)
            continue;

        // read descriptions
        switch (str2int(format))
        {
            //MOT-format --> frameID,targetID,topleft_x,topleft_y,width,height,confidence, 3DposX_world,3DposY_world,3DposZ_world

            case str2int("MOT"):
                sscanf(txtline,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",&frID,&tID,&tlX,&tlY,&width,&height,&conf,&Xw,&Yw,&Zw);
                break;

            //ICGLab-format --> frameID,targetID,center_x,center_y,width,height,confidence, 3DposX_world,3DposY_world,3DposZ_world
            case str2int("ICGLab"):
                sscanf(txtline,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",&frID,&tID,&tlX,&tlY,&width,&height,&conf,&Xw,&Yw,&Zw);
                tlX = tlX - width/2; //convert center_x to topleft_x
                tlY = tlY- height/2; //convert center_y to topleft_y
                break;

             //VOT-format --> X1,Y1,X2,Y2,X3,Y3,X4,Y4
             // see http://www.votchallenge.net/vot2015/dataset.html
            case str2int("VOT"):
                float X1,Y1,X2,Y2,X3,Y3,X4,Y4;
                sscanf(txtline,"%f,%f,%f,%f,%f,%f,%f,%f\n",&X1,&Y1,&X2,&Y2,&X3,&Y3,&X4,&Y4);
                frID = framecount;
                tID = 0;//we only have one target
                tlX = X1;
                tlY = Y1;
                Xmax=std::max(std::max(std::max(X1,X2),X3),X4);
                Xmin=std::min(std::min(std::min(X1,X2),X3),X4);
                width= Xmax-Xmin;
                Ymax=std::max(std::max(std::max(Y1,Y2),Y3),Y4);
                Ymin=std::min(std::min(std::min(Y1,Y2),Y3),Y4);
                height= Ymax-Ymin;
                tlX = Xmin;
                tlY = Ymin;
                break;
            case str2int("HDA"):
                sscanf(txtline,"%f,%f,%f,%f,%f,%f,%f\n",&camID,&frID,&tlX,&tlY,&width,&height,&conf);
                //tlX = tlX - width/2; //convert center_x to topleft_x
                //tlY = tlY- height/2; //convert center_y to topleft_y
                break;

            default:
                perror("Unknown ground-truth format");
        }

        // create detection
        //std::cout <<"data->"<<frID<<","<<tID<<","<<tlX<<","<<tlY<<","<<width<<","<<height<<","<<conf<<","<<Xw<<","<<Yw<<","<<Zw<<std::endl;
        target_detection_t det(tID,tlX,tlY,tlX+width,tlY+height,Xw,Yw,Zw);

        //save accumulated detections when changing to new frames
        if (last_frameID != frID)
        {
            //save detections via map
            m.insert(std::make_pair(last_frameID, dets));
            dets.clear();//clear the vector list
            last_frameID = frID; //update counter for last frame
        }
        //accumulate detections
        dets.push_back(det);

        framecount++;
    }
    //insert the remaining detections after finishing the ground-truth file
    m.insert(std::make_pair(last_frameID, dets));
    dets.clear();//clear the vector list
    return 1;
}

//WiseGTreader::parsefile()
//{
//
//}
