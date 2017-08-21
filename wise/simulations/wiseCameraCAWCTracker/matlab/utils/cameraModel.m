%% Camera model
% This class provides an interface to compute the mapping between image and
% ground-planes.
% It can use two types of inputs: tsai parameters or image-ground plane
% homographies.
%
% Use the following function to compute the image-to-ground conversion for
% coordinates:
% [Xw,Yw,Zw]=imageToWorld(cam,Xi,Yi)
%
% Use the following function to compute the ground-to-image conversion for
% coordinates:
% [Xi,Yi]=worldToImage(cam,Xw,Yw,Zw)
% NOTE: Zw is usually computed at feet level (Zw=0). However, matlab
% indexes of vectors start at 1 so please use Zw = 1
%
% Juan C. SanMiguel, July 2014

classdef cameraModel < handle
    properties
        pos;%camera position
        
        mode;%mode 'tsai' or 'homography'
        
        H_w2i;%world2image plane homography
        H_i2w;%image2word plane homography
        p;%tsai parameters
        r;%rotation angles (rx, ry & rz)
        mR;%rotation matrix
        mT;%traslation matrix
        mDpx;
        mDpy;
        mCx;
        mCy;
        mSx;
        mFocal;%focal distance
        mKappa1;%distortion correction parameter
    end
    
    methods
        
        %% constructor
        function cam = cameraModel(file, config)
            if (nargin > 0)
                cam = cameraModel;
                cam.mode = config.caltype;
                
                % create an structure to read data
                [ s ] = xml2struct( file );
                
                switch cam.mode
                    
                    case 'tsai'
                        %Read calibration data in tsai format
                        cam.p.intrinsic = s.Camera.Intrinsic.Attributes;
                        cam.p.extrinsic = s.Camera.Extrinsic.Attributes;
                        cam.p.geometry = s.Camera.Geometry.Attributes;
                        cam.internalInit; %compute rotation & traslation matrix
                    case 'homography'
                        %Read calibration data in homography format
                        data = str2num(s.calibration.H.data.Text);
                        cols = str2double(s.calibration.H.cols.Text);
                        rows = str2double(s.calibration.H.rows.Text);
                        
                        switch s.calibration.H.Attributes.type_id
                            case 'homography_image2world'
                                cam.H_i2w = reshape(data, [cols rows])';
                                cam.H_w2i = inv(cam.H_i2w);
                            case 'homography_world2image'
                                cam.H_w2i = reshape(data, [cols rows])';
                                cam.H_i2w = inv(cam.H_w2i);
                            otherwise
                                cam.H_w2i = reshape(data, [cols rows])';
                                cam.H_i2w = inv(cam.H_w2i);
                        end
                        
                        % %Alternative method via the xml read object
                        % xmldoc=xmlread(file);
                        % %read homography data
                        % pnode = xmldoc.getElementsByTagName('H').item(0);
                        % rows = str2double(pnode.getElementsByTagName('rows').item(0).getTextContent);
                        % cols = str2double(pnode.getElementsByTagName('cols').item(0).getTextContent);
                        % data = str2num(pnode.getElementsByTagName('data').item(0).getTextContent);
                        % cam.H_w2i = reshape(data, [cols rows])';
                end
            end
        end %end constructor
        
        %% internalInit
        % computes the rotation and traslation matrix
        function internalInit(cam)
            if strcmp('tsai',cam.mode) == 1
                
                %rotation angles
                mRx = str2double(cam.p.extrinsic.rx);
                mRy = str2double(cam.p.extrinsic.ry);
                mRz = str2double(cam.p.extrinsic.rz);
                cam.r=[mRx mRy mRz];
                
                %traslation
                mTx = str2double(cam.p.extrinsic.tx);
                mTy = str2double(cam.p.extrinsic.ty);
                mTz = str2double(cam.p.extrinsic.tz);
                cam.mT=[mTx mTy mTz];
                
                % compute matrix ...
                sa = sin(mRx);
                ca = cos(mRx);
                sb = sin(mRy);
                cb = cos(mRy);
                sg = sin(mRz);
                cg = cos(mRz);
                
                cam.mR(1,1) = cb * cg;
                cam.mR(1,2) = cg * sa * sb - ca * sg;
                cam.mR(1,3) = sa * sg + ca * cg * sb;
                cam.mR(2,1) = cb * sg;
                cam.mR(2,2) = sa * sb * sg + ca * cg;
                cam.mR(2,3) = ca * sb * sg - cg * sa;
                cam.mR(3,1) = -sb;
                cam.mR(3,2) = cb * sa;
                cam.mR(3,3) = ca * cb;
                
                %compute camera position
                cam.pos(1) = -(mTx*cam.mR(1,1) + mTy*cam.mR(2,1) + mTz*cam.mR(3,1));
                cam.pos(2) = -(mTx*cam.mR(1,2) + mTy*cam.mR(2,2) + mTz*cam.mR(3,2));
                cam.pos(3) = -(mTx*cam.mR(1,3) + mTy*cam.mR(2,3) + mTz*cam.mR(3,3));
                
                cam.mDpx = str2double(cam.p.geometry.dpx);
                cam.mDpy = str2double(cam.p.geometry.dpy);
                cam.mCx = str2double(cam.p.intrinsic.cx);
                cam.mCy = str2double(cam.p.intrinsic.cy);
                cam.mSx = str2double(cam.p.intrinsic.sx);
                cam.mFocal = str2double(cam.p.intrinsic.focal);
                cam.mKappa1 = str2double(cam.p.intrinsic.kappa1);
                
            end
        end
        
        %% imageToWorld
        % converts image coordinates to global (ground-plane) coordinates
        function [Xw,Yw,Zw]=imageToWorld(cam,Xi,Yi)
            
            switch cam.mode
                case 'tsai'
                    
                    Zw = 0;
                    
                    %convert from image to distorted sensor coordinates
                    Xd = cam.mDpx * (Xi - cam.mCx) / cam.mSx;
                    Yd = cam.mDpy * (Yi - cam.mCy);
                    
                    % convert from distorted sensor to undistorted sensor plane coordinates
                    [Xu,Yu] = cam.distortedToUndistortedSensorCoord (Xd,Yd);
                    
                    % calculate the corresponding xw and yw world coordinates
                    % (these equations were derived by simply inverting
                    % the perspective projection equations using Macsyma)
                    common_denominator = ((cam.mR(1,1) * cam.mR(3,2) - cam.mR(1,2) * cam.mR(3,1)) * Yu +...
                        (cam.mR(2,2) * cam.mR(3,1) - cam.mR(2,1) * cam.mR(3,2)) * Xu -...
                        cam.mFocal * cam.mR(1,1) * cam.mR(2,2) + cam.mFocal * cam.mR(1,2) * cam.mR(2,1));
                    %
                    Xw = (((cam.mR(1,2) * cam.mR(3,3)- cam.mR(1,3) * cam.mR(3,2)) * Yu +...
                        (cam.mR(2,3) * cam.mR(3,2) - cam.mR(2,2) * cam.mR(3,3)) * Xu -...
                        cam.mFocal * cam.mR(1,2) * cam.mR(2,3) + cam.mFocal * cam.mR(1,3) * cam.mR(2,2)) * Zw +...
                        (cam.mR(1,2) * cam.mT(3) - cam.mR(3,2) * cam.mT(1)) * Yu +...
                        (cam.mR(3,2) * cam.mT(2) - cam.mR(2,2) * cam.mT(3)) * Xu -...
                        cam.mFocal * cam.mR(1,2) * cam.mT(2) + cam.mFocal * cam.mR(2,2) * cam.mT(1)) / common_denominator;
                    
                    Yw = -(((cam.mR(1,1) * cam.mR(3,3) - cam.mR(1,3) * cam.mR(3,1)) * Yu +...
                        (cam.mR(2,3) * cam.mR(3,1) - cam.mR(2,1) * cam.mR(3,3)) * Xu -...
                        cam.mFocal * cam.mR(1,1) * cam.mR(2,3) + cam.mFocal * cam.mR(1,3) * cam.mR(2,1)) * Zw +...
                        (cam.mR(1,1) * cam.mT(3) - cam.mR(3,1) * cam.mT(1)) * Yu +...
                        (cam.mR(3,1) * cam.mT(2) - cam.mR(2,1) * cam.mT(3)) * Xu -...
                        cam.mFocal * cam.mR(1,1) * cam.mT(2) + cam.mFocal * cam.mR(2,1) * cam.mT(1)) / common_denominator;
                    
                case 'homography'
                    prj = cam.H_i2w * [Xi Yi 1]';                    
                    Xw = prj(1,:) ./ prj(3,:);
                    Yw = prj(2,:) ./ prj(3,:);
                    Zw = 0;
            end
        end
        
        %% worldToImage
        % converts global (ground-plane) coordinates to image coordinates
        function [Xi,Yi]=worldToImage(cam,Xw,Yw,Zw)
            switch cam.mode
                case 'tsai'
                    % convert from world coordinates to camera coordinates */
                    prj = cam.mR * [Xw Yw Zw]' + cam.mT';
                    
                    %                     xc = cam.mR11 * Xw + cam.mR(1,2) * Yw + cam.mR13 * Zw + cam.mT(1);
                    %                     yc = cam.mR21 * Xw + cam.mR22 * Yw + cam.mR23 * Zw + cam.mT(2);
                    %                     zc = cam.mR31 * Xw + cam.mR32 * Yw + cam.mR33 * Zw + cam.mT(3);
                    
                    % convert from camera coordinates to undistorted sensor plane coordinates */
                    %                     Xu = cam.mFocal * xc / zc;
                    %                     Yu = cam.mFocal * yc / zc;
                    Xu = cam.mFocal * prj(1,:) ./ prj(3,:);
                    Yu = cam.mFocal * prj(2,:) ./ prj(3,:);
                    
                    % convert from undistorted to distorted sensor plane coordinates */
                    [Xd,Yd]= cam.undistortedToDistortedSensorCoord (Xu, Yu);
                    
                    % convert from distorted sensor plane coordinates to image coordinates */
                    Xi = Xd * cam.mSx / cam.mDpx + cam.mCx;
                    Yi = Yd / cam.mDpy + cam.mCy;
                case 'homography'
                    prj = cam.H_w2i * [Xw Yw 1]';                    
                    Xi = prj(1,:) ./ prj(3,:);
                    Yi = prj(2,:) ./ prj(3,:);
            end
        end        
    end %methods
    
    methods (Access = private)
        % NOTE these two methods correct the distortion of the lenses
        % happening in the image plane. Both have been copied from the
        % material available in the PETS2009 dataset
        
        % Correction of distorted coordinates in the image plane
        function [Xu,Yu]=distortedToUndistortedSensorCoord(cam,Xd,Yd)
            
            % convert from distorted to undistorted sensor plane coordinates
            distortion_factor = 1 + cam.mKappa1 * (Xd*Xd + Yd*Yd);
            Xu = Xd * distortion_factor;
            Yu = Yd * distortion_factor;
        end
        
        % Revert the distortion correction
        function [Xd,Yd]=undistortedToDistortedSensorCoord (cam,Xu,Yu)
            
            if (((Xu == 0) && (Yu == 0)) || (cam.mKappa1 == 0))
                Xd = Xu;
                Yd = Yu;
            else
                Ru = sqrt(Xu*Xu + Yu*Yu);
                
                c = 1.0 / cam.mKappa1;
                d = -c * Ru;
                
                Q = c / 3;
                R = -d / 2;
                D = Q*Q*Q + R*R;
                
                if (D >= 0)
                    %% one real root
                    D = sqrt(D);
                    if (R + D > 0)
                        S = (R + D)^(1.0/3.0);
                    else
                        S = -(-R - D)^(1.0/3.0);
                    end
                    
                    if (R - D > 0)
                        T = (R - D)^(1.0/3.0);
                    else
                        T = -(D - R)^(1.0/3.0);
                    end
                    
                    Rd = S + T;
                    
                    if (Rd < 0)
                        Rd = sqrt(-1.0 / (3 * cam.mKappa1));
                        %fprintf (stderr, "\nWarning: undistorted image point to distorted image point mapping limited by\n");
                        %fprintf ('        maximum barrel distortion radius of %lf\n', Rd);
                        %fprintf ('         (Xu = %lf, Yu = %lf) -> (Xd = %lf, Yd = %lf)\n\n', Xu, Yu, Xu * Rd / Ru, Yu * Rd / Ru);
                    end
                else
                    %three real roots
                    D = sqrt(-D);
                    S = (sqrt(R*R + D*D))^(1.0/3.0);
                    T = atan2(D, R) / 3;
                    sinT = sin(T);
                    cosT = cos(T);
                    
                    % the larger positive root is    2*S*cos(T)                   */
                    % the smaller positive root is   -S*cos(T) + SQRT(3)*S*sin(T) */
                    % the negative root is           -S*cos(T) - SQRT(3)*S*sin(T) */
                    
                    Rd = -S * cosT + sqrt(3.0) * S * sinT;	% use the smaller positive root */
                end
                
                lambda = Rd / Ru;
                
                Xd = Xu * lambda;
                Yd = Yu * lambda;
            end
        end
    end
end