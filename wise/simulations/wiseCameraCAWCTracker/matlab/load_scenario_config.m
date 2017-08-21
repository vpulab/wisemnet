%% CONFIGURATION FILE
% This file provides the required configuration (videofiles, calibration
% and annotation) for multicamera datasets.
%
% Juan C. SanMiguel, July 2014
fprintf('Loading scenario %s...\n',scenario); 

config.verbose = 0;
config.buffer.size = 400; %buffer size to store data (frames)

config.vis.ip = 1;
config.vis.gp = 0; %visualization of ground-plane (only feet)

config.rootDir = '/home/jcs/code/svn/multicamera/videos';
config.rootDir = '/media/jcs/DATA/datasets/multicamera';
% config.rootDir = 'F:/assets/videos';

config.resize = 1; %use original resolution

%% input settings
switch scenario
    case 'pets2009_S2_L1'    
        %area (xmin, xmax, ymin, ymax):[0 100 0 30] meters
        %area (xmin, xmax, ymin, ymax):[0 50 0 30] meters
        %ground-plane: (xmin, xmax, ymin, ymax): (-14069.6, 4981.3, -14274.0, 1733.5) 
        
        config.mpp = [50/(19069.6+4981)  30/(14274.0+1733.5)]; %metters per point in ground-plane
        config.datasetDir = [config.rootDir '/PETS2009_S2_L1/'];
        config.selCams    = [1 3 4 5 6 7 8];     
        config.vidFile = {'PETS2009_S2_L1_view001_7fps.avi' ... %cam1
            ''...                            %cam2
            'PETS2009_S2_L1_view003_7fps.avi' ... %cam3
            'PETS2009_S2_L1_view004_7fps.avi' ... %cam4
            'PETS2009_S2_L1_view005_7fps.avi' ... %cam5
            'PETS2009_S2_L1_view006_7fps.avi' ... %cam6
            'PETS2009_S2_L1_view007_7fps.avi' ... %cam7
            'PETS2009_S2_L1_view008_7fps.avi'};   %cam8
        
        config.caltype = 'tsai';
        config.calFile =  {'PETS2009_S2_L1_view001_calib.xml' ...   %cam1
            ''...   %cam2
            'PETS2009_S2_L1_view003_calib.xml'...   %cam3
            'PETS2009_S2_L1_view004_calib.xml'...   %cam4
            'PETS2009_S2_L1_view005_calib.xml'...   %cam5
            'PETS2009_S2_L1_view006_calib.xml'...   %cam6
            'PETS2009_S2_L1_view007_calib.xml'...   %cam7
            'PETS2009_S2_L1_view008_calib.xml'};    %cam8
        config.gtType    = 'GP';
        config.nTargets  = 19;
        config.Target  = [9];
        config.gtFile    = {'PETS2009_S2_L1_gt/annotations_person_1_gp.txt'... %person1 GT
            'PETS2009_S2_L1_gt/annotations_person_2_gp.txt'... %person2 GT
            'PETS2009_S2_L1_gt/annotations_person_3_gp.txt'... %person3 GT
            'PETS2009_S2_L1_gt/annotations_person_4_gp.txt'... %person4 GT
            'PETS2009_S2_L1_gt/annotations_person_5_gp.txt'... %person5 GT
            'PETS2009_S2_L1_gt/annotations_person_6_gp.txt'... %person6 GT
            'PETS2009_S2_L1_gt/annotations_person_7_gp.txt'... %person7 GT
            'PETS2009_S2_L1_gt/annotations_person_8_gp.txt'... %person8 GT
            'PETS2009_S2_L1_gt/annotations_person_9_gp.txt'... %person9 GT
            'PETS2009_S2_L1_gt/annotations_person_10_gp.txt'... %person10 GT
            'PETS2009_S2_L1_gt/annotations_person_11_gp.txt'... %person11 GT
            'PETS2009_S2_L1_gt/annotations_person_12_gp.txt'... %person12 GT
            'PETS2009_S2_L1_gt/annotations_person_13_gp.txt'... %person13 GT
            'PETS2009_S2_L1_gt/annotations_person_14_gp.txt'... %person14 GT
            'PETS2009_S2_L1_gt/annotations_person_15_gp.txt'... %person15 GT
            'PETS2009_S2_L1_gt/annotations_person_16_gp.txt'... %person16 GT
            'PETS2009_S2_L1_gt/annotations_person_17_gp.txt'... %person17 GT
            'PETS2009_S2_L1_gt/annotations_person_18_gp.txt'... %person18 GT
            'PETS2009_S2_L1_gt/annotations_person_19_gp.txt'};  %person19 GT
        
        config.gtFileInit= {'PETS2009_S2_L1_gt/annotations_person_1_ip_init.txt'... %person0 GT (initialization for image plane)
            'PETS2009_S2_L1_gt/annotations_person_2_ip_init.txt'... %person2 GT (initialization for image plane)
            'PETS2009_S2_L1_gt/annotations_person_3_ip_init.txt'... %person3 GT (initialization for image plane)
            'PETS2009_S2_L1_gt/annotations_person_4_ip_init.txt'... %person4 GT (initialization for image plane)
            'PETS2009_S2_L1_gt/annotations_person_5_ip_init.txt'... %person5 GT (initialization for image plane)
            'PETS2009_S2_L1_gt/annotations_person_6_ip_init.txt'... %person6 GT (initialization for image plane)
            'PETS2009_S2_L1_gt/annotations_person_7_ip_init.txt'... %person7 GT (initialization for image plane)
            'PETS2009_S2_L1_gt/annotations_person_8_ip_init.txt'... %person8 GT (initialization for image plane)
            'PETS2009_S2_L1_gt/annotations_person_9_ip_init.txt'... %person9 GT (initialization for image plane)
            'PETS2009_S2_L1_gt/annotations_person_11_ip_init.txt'... %person10 GT (initialization for image plane)
            'PETS2009_S2_L1_gt/annotations_person_12_ip_init.txt'... %person11 GT (initialization for image plane)
            'PETS2009_S2_L1_gt/annotations_person_13_ip_init.txt'... %person12 GT (initialization for image plane)
            'PETS2009_S2_L1_gt/annotations_person_14_ip_init.txt'... %person13 GT (initialization for image plane)
            'PETS2009_S2_L1_gt/annotations_person_15_ip_init.txt'... %person14 GT (initialization for image plane)
            'PETS2009_S2_L1_gt/annotations_person_16_ip_init.txt'... %person15 GT (initialization for image plane)
            'PETS2009_S2_L1_gt/annotations_person_17_ip_init.txt'... %person16 GT (initialization for image plane)
            'PETS2009_S2_L1_gt/annotations_person_18_ip_init.txt'... %person17 GT (initialization for image plane)
            };
        
         config.nTargetIDs  = [1:18];
        
    case 'epflPOM-4p'
        config.datasetDir = [config.rootDir '/EPFL-POM/'];
        config.selCams    = [1 2 3 4];
        config.vidFile = {'4p-c0.avi' ... %cam1
            '4p-c1.avi'...    %cam2
            '4p-c2.avi' ...   %cam3
            '4p-c3.avi' };    %cam4
        
        config.caltype = 'homography';
        config.calFile =  {'4p-c0_calib.xml' ... %cam1
            '4p-c1_calib.xml'...   %cam2
            '4p-c2_calib.xml'...   %cam3
            '4p-c3_calib.xml'};    %cam4
        
        config.nTargets  = 0;
        config.gtFile    = {'none.xml'... %cam1 GT
            ''...                                     %cam2 GT
            'none.xml'};  %cam3 GT
    case 'epflPOM-6p'
        config.datasetDir = [config.rootDir '/EPFL-POM/'];
        config.selCams    = [1 2 3 4];
        config.vidFile = {'6p-c0.avi' ... %cam1
            '6p-c1.avi'...    %cam2
            '6p-c2.avi' ...   %cam3
            '6p-c3.avi' };    %cam4
        
        config.caltype = 'homography';
        config.calFile =  {'4p-c0_calib.xml' ... %cam1
            '4p-c1_calib.xml'...   %cam2
            '4p-c2_calib.xml'...   %cam3
            '4p-c3_calib.xml'};    %cam4
        
        config.nTargets  = 0;
        config.gtFile    = {'none.xml'... %cam1 GT
            ''...                                     %cam2 GT
            'none.xml'};  %cam3 GT
    case 'ICGLab6_chap'
        config.datasetDir = [config.rootDir '/ICGLab6/chap/'];
        config.selCams    = [1 2 3 4];
        config.vidFile = {'cam131.avi' ... %cam1
            'cam132.avi'...    %cam2
            'cam133.avi' ...   %cam3
            'cam134.avi' };    %cam4
        
        config.caltype = 'homography';
        config.calFile =  {'cam131_calib.xml' ... %cam1
            'cam132_calib.xml'...   %cam2
            'cam133_calib.xml'...   %cam3
            'cam134_calib.xml'};    %cam4
        
        config.gtType    = 'GP';
        config.gtType    = 'IP';
        config.nTargetIDs  = [0,1,2,3,4];
        config.gtFile    = {'chap_gt/annotations_person_0_gp.txt'... %person0 GT
            'chap_gt/annotations_person_1_gp.txt'... %person1 GT
            'chap_gt/annotations_person_2_gp.txt'... %person2 GT
            'chap_gt/annotations_person_3_gp.txt'... %person3 GT
            'chap_gt/annotations_person_4_gp.txt'};  %person4 GT
        %         config.gtFileInit= {'groundtruth/annotations_person_0_ip_init.txt'... %person0 GT (initialization for image plane)
        config.gtFileInit= {'chap_gt/annotations_person_0_ip_init.txt'... %person0 GT (initialization for image plane)
            'chap_gt/annotations_person_1_ip_init.txt'... %person1 GT
            'chap_gt/annotations_person_2_ip_init.txt'... %person2 GT
            'chap_gt/annotations_person_3_ip_init.txt'... %person3 GT
            'chap_gt/annotations_person_4_ip_init.txt'};  %person4 GT
        config.gpo = [600 125]; %[gp_offset_x gp_offset_y]
        config.mpp = [0.00715 0.00715]; %[ m_per_pixel_x m_per_pixel_y]
        config.ARTE.W1 = 10;
        % config.ARTE.t_W1 = [5 10 20 30 40 50];
        config.ARTE.W2 = 10;
        config.ARTE.alpha = 0.7;%0.25;
        config.ARTE.rho4 = 0.90;%threshold for detecting a small decrease of NSU
        
        config.ARTE.rho1_{1} = 30;%threshold for detecting an increase of NSU
        config.ARTE.rho1_{2} = 20;%threshold for detecting an increase of NSU
        config.ARTE.rho1_{3} = 20;%threshold for detecting an increase of NSU
        config.ARTE.rho1_{4} = 20;%threshold for detecting an increase of NSU
        
        config.ARTE.rho2_{1} = -config.ARTE.rho1_{1}/5;%threshold for detecting an increase of NSU
        config.ARTE.rho2_{2} = -config.ARTE.rho1_{2}/5;%threshold for detecting an increase of NSU
        config.ARTE.rho2_{3} = -config.ARTE.rho1_{3}/5;%threshold for detecting an increase of NSU
        config.ARTE.rho2_{4} = -config.ARTE.rho1_{4}/5;%threshold for detecting an increase of NSU
        config.back = 100;
        %config.ARTE.rho2 = -config.ARTE.rho1/2;%threshold for detecting a decrease of NSU
        %config.ARTE.rho3 =  config.ARTE.rho1/5;%threshold for detecting a small decrease of NSU
        
        config.ARTE.stable(1) = 40;
        config.ARTE.stable(2) = 5;
        config.ARTE.stable(3) = 20;
        config.ARTE.stable(4) = 20;
        
    case 'ICGLab6_easy1'
        config.datasetDir = [config.rootDir '/ICGLab6/easy/'];
        config.selCams    = [1 2 3];
        config.vidFile = {'easy_set1_cam1.avi' ... %cam1
            'easy_set1_cam2.avi'...    %cam2
            'easy_set1_cam3.avi' };    %cam3
        
        config.caltype = 'homography';
        config.calFile =  {'cam1_calib.xml' ... %cam1
            'cam2_calib.xml'...   %cam2
            'cam3_calib.xml'};    %cam3
        
        config.gtType    = 'GP';
        config.nTargets  = 0;
        config.gtFile    = {'groundtruth/annotations_person_0_gp.txt'... %person0 GT
            'groundtruth/annotations_person_4_gp.txt'};  %person4 GT
        config.gpo = [600 125]; %[gp_offset_x gp_offset_y]
        config.mpp = [0.00715 0.00715]; %[ m_per_pixel_x m_per_pixel_y]
    case 'ICGLab6_medium1'
        config.datasetDir = [config.rootDir '/ICGLab6/medium/'];
        config.selCams    = [1 2 3];
        config.vidFile = {'medium_set1_cam1.avi' ... %cam1
            'medium_set1_cam2.avi'...    %cam2
            'medium_set1_cam3.avi' };    %cam3
        
        config.caltype = 'homography';
        config.calFile =  {'cam1_calib.xml' ... %cam1
            'cam2_calib.xml'...   %cam2
            'cam3_calib.xml'};    %cam3
        
        config.gtType    = 'GP';
        config.nTargets  = 0;
        config.gtFile    = {'groundtruth/annotations_person_0_gp.txt'... %person0 GT
            'groundtruth/annotations_person_4_gp.txt'};  %person4 GT
        config.gpo = [600 125]; %[gp_offset_x gp_offset_y]
        config.mpp = [0.00715 0.00715]; %[ m_per_pixel_x m_per_pixel_y]
    case 'ICGLab6_hard1'
        config.datasetDir = [config.rootDir '/ICGLab6/hard/'];
        config.selCams    = [1 2 3];
        config.vidFile = {'hard_set1_cam1.avi' ... %cam1
            'hard_set1_cam2.avi'...    %cam2
            'hard_set1_cam3.avi' };    %cam3
        
        config.caltype = 'homography';
        config.calFile =  {'cam1_calib.xml' ... %cam1
            'cam2_calib.xml'...   %cam2
            'cam3_calib.xml'};    %cam3
        
        config.gtType    = 'GP';
        config.nTargets  = 0;
        config.gtFile    = {'groundtruth/annotations_person_0_gp.txt'... %person0 GT
            'groundtruth/annotations_person_4_gp.txt'};  %person4 GT
        
        config.gpo = [600 125]; %[gp_offset_x gp_offset_y]
        config.mpp = [0.00715 0.00715]; %[ m_per_pixel_x m_per_pixel_y]
end

%create color tags for the selected targets
config.colorTgt=hsv(config.nTargets);
config.colorCam=hsv(length(config.selCams));
