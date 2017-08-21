% This script computes the ground-plane tracking error versus energy consumption for each
% camera. The processing clock is fp = 1:5GHz and the sensing framerates are 5; 10; 15; 20 and 25fps
%
%   Author:      Juan Carlos SanMiguel (juancarlos.sanmiguel@uam.es)
%   Affiliation: University Autonoma of Madrid
%   URL:         http://www-vpu.ii.uam.es/~jcs
%   Date:        November 2015
addpath('./cawc','./utils');

clc;
clear all;
close all;

%% settings
load_plot_config;

root_dir='/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/';
scenario='pets2009_S2_L1';
data_dir='res_S_C6_7fps_t09_25s_r50_o2';%selected

%% load data
if exist(['./data/' data_dir '_EnergyCams.mat'], 'file') == 2
    load(['./data/' data_dir '_EnergyCams.mat']);
else
    res_cams = CAWC_compute_energy_cams(root_dir,data_dir); %compute energy statistics
end

if exist(['./data/' data_dir '_TrackingErr.mat'], 'file') == 2
    load(['./data/' data_dir '_TrackingErr.mat']);
else
    err_s=CAWC_compute_accuracy(root_dir,data_dir,scenario,0); %compute accuracy statistics (coalition & cams)
end

%% PLOT SETTINGS
%define labels
labels=strread(num2str(floor(err_s.fps)),'%s');
for ll=1:numel(labels)
    labels{ll} = [labels{ll} ' fps'];
end

%define offset for text of cameras
offsety=[-0.1 -0.1 0.1 -0.1 -0.1 -0.1 0];
offsetx=[ 2 2 2 2 2 2 0];
fntsize = 18;
fntsize2 = 14;

%% PLOT accuracy-consumption of cameras
% fc=figure('Name',sprintf('Camera accuracy-consumption for Cameras d P=%.2fGHz',err_s.Pclk/1e9),'Position',[100 100 400 300] );

for c=1:res_cams.Ncams    
    fc=figure('Name',sprintf('Camera accuracy-consumption for Cameras P=%.2fGHz & t=%.2fs',err_s.Pclk/1e9,max(res_cams.cam.simTime(:))));
    
    dataCam=res_cams.cam.sen.eAct(c,:,:)+res_cams.cam.sen.eIdl(c,:,:)+res_cams.cam.pro.eAct(c,:,:)+res_cams.cam.pro.eIdl(c,:,:)+res_cams.cam.com.eAct(c,:,:)+res_cams.cam.com.eIdl(c,:,:);
    times = res_cams.cam.simTime(c,:,:);
    dataCam=reshape(dataCam(:)./times(:), [numel(dataCam) 1]);
    errCam_m=reshape(err_s.err.camGPm(c,:,:), [numel(dataCam) 1]);
    errCam_v=reshape(err_s.err.camGPv(c,:,:), [numel(dataCam) 1]);
    
    %   subplot(3,3,c);
    errorbar(dataCam,errCam_m,errCam_v,'*-','Color',camColor(c,:));
    box off;
    set(gcf,'Units','normal')
    %set(gca,'Position',[.12 .15 .85 .82]); %fontsize 12-16
    set(gca,'Position',[.15 .17 .80 .80]); %fontsize 18
    
%     axis([min(min(dataCam))-25 max(max(dataCam))+25 min(min(err_s.err.camGPm))-0.15 max(max(err_s.err.camGPm))]);
    axis([225 600 min(min(err_s.err.camGPm))-0.15 max(max(err_s.err.camGPm))]);
    set(gca,'XTick',200:50:600, 'XTickLabel',200:50:600);
    xlabel('Average Consumption (mJ/sec)','FontSize', fntsize);
    ylabel('Average Tracking Error (m)','FontSize', fntsize);    
    set(gca,'FontSize', fntsize);
    
    switch (c)
        case 5
            despx=[offsetx(c) -25 offsetx(c)*ones(1,numel(dataCam)-2)]';
            despy=[+0.1 offsety(c)*ones(1,numel(dataCam)-1)]';
            text(dataCam+despx,errCam_m+despy,labels,'FontSize', fntsize2)
        case 6
            despy=[+0.1 offsety(c) +0.1  offsety(c) 0.1 offsety(c)*ones(1,numel(dataCam)-5)]';
            text(dataCam+offsetx(c),errCam_m+despy,labels,'FontSize', fntsize2);
        otherwise
            text(dataCam+offsetx(c),errCam_m+offsety(c),labels,'FontSize', fntsize2)
    end
        
    epsfig = hgexport('factorystyle');
    epsfig.Format = 'eps';
    hgexport(gcf,sprintf('figs/AccuracyEnergy_sen_cam%d_%s.eps',c,data_dir),epsfig,'Format','eps')
end

%% ADDITIONAL PLOT
err = err_s.err;
FPSreq = err_s.fps;
Pclk = err_s.Pclk;
Ncams = err_s.Ncams;

%framerate & processing clock testing
if(numel(FPSreq)>2 && numel(Pclk) > 2)
    % 3D plot for simultaneous testing of framerate and processing clock
    [N,M]=meshgrid(FPSreq,Pclk);
    hp=figure('Name','Tracking error ground-plane');
    for c=1:Ncams
        subplot(2,4,c); mesh(N,M,reshape(err.camGPm(c,:,:),[numel(Pclk) numel(FPSreq)])); plot_labels_axis(sprintf('Camera %d',c),'Mean tracking error GP (m)',Pclk,FPSreq);
    end
    subplot(2,4,8); mesh(N,M,err.coaGPm); plot_labels_axis('Coalition','Mean tracking error GP (m)',Pclk,FPSreq);
    
    hp=figure('Name','Tracking error image-plane');
    for c=1:Ncams
        subplot(2,4,c); mesh(N,M,reshape(err.camIPm(c,:,:),[numel(Pclk) numel(FPSreq)])); plot_labels_axis(sprintf('Camera %d',c),'Mean tracking error IP (pixels)',Pclk,FPSreq);
    end
    subplot(2,4,8); mesh(N,M,err.coaIPm); plot_labels_axis('Coalition','Mean tracking error GP (m)',Pclk,FPSreq);
else
    %framerate testing
    if numel(FPSreq)>1
        fgp1=figure('Name',sprintf('Tracking GP error for P=%.2fGHz & t=%.2fs',Pclk(1)/1e9,max(res_cams.cam.simTime(:))),'Position', [100, 100, 700, 300]);
        tmp_m = err.camGPm; tmp_m(end+1,:,:) = err.coaGPm; tmp_m=reshape(tmp_m, [Ncams+1 max(size(err.coaIP))]);
        b=bar(tmp_m); 
        legend(strread(num2str(floor(FPSreq)),'%s'),'Orientation','Horizontal','Location','Northoutside');
        set(gca,'XTick',1:Ncams+1, 'XTickLabel',[strread(num2str(err_s.cids),'%s');{'Coalition'}]); xlabel('camera');ylabel('GP tracking error (m)');
        box off;axis([0.5 Ncams+1.5 0 max(tmp_m(:))])
    end
    %processing clock testing
    if numel(Pclk)>1
        fgp1=figure('Name',sprintf('Tracking GP error for fps=%.2f & t=%.2fs',FPSreq(1),max(res_cams.cam.simTime(:))),'Position', [100, 100, 700, 300]);
        tmp_m = err.camGPm; tmp_m(end+1,:,:) = err.coaGPm; tmp_m=reshape(tmp_m, [Ncams+1 max(size(err.coaIP))]);
        b=bar(tmp_m); 
        legend(strread(num2str(Pclk),'%s'),'Orientation','Horizontal','Location','Northoutside');
        set(gca,'XTick',1:Ncams+1, 'XTickLabel',[strread(num2str(err_s.cids),'%s');{'Coalition'}]); xlabel('camera');ylabel('GP tracking error (m)');
        box off; axis([0.5 Ncams+1.5 0 max(tmp_m(:))])
    end
    epsfig = hgexport('factorystyle');
    epsfig.Format = 'eps';
    hgexport(fgp1,sprintf('figs/AccuracyEnergy_cam_sen_%s_v2.eps',data_dir),epsfig,'Format','eps')
end