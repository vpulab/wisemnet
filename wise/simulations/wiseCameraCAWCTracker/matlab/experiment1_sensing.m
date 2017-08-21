% This script computes the energy consumption for image sensor when changing the
% requested framerate (1-25 fps) and the operating frequency (10-24Mhz)
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
cam2show = 1;
root_dir='/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/';
experiment='res_S_B3_1-25fps_10-24clk'; %data for B3 image sensor

%% LOAD SIMULATION DATA
fprintf('Loading simulation data...\n');
% try to load mat file
if exist(['./data/' results_dir '.mat'], 'file') == 2
    load(['./data/' results_dir '.mat']);
else
    [runs,coa]=load_coa_data([root_dir results_dir]); %coalition tracking data
    [cams.track,ids,cids]=load_cams_data([root_dir results_dir]); %camera tracking data
    [cams.usage,ids,cids]=load_cams_consumption([root_dir results_dir]);%camera consumption
    [Ncams,Nruns,Pclk,Sclk,optF,FPSreq,FPSrea,evalFr] = preprocess_data(cams);
    save(['./data/' results_dir '.mat']);
end

%% INIT VARIABLES
cam.runs      = zeros(Ncams,numel(Sclk),numel(FPSreq));
cam.simTime   = zeros(Ncams,numel(Sclk),numel(FPSreq));
cam.sen.eAct  = zeros(Ncams,numel(Sclk),numel(FPSreq)); 
cam.sen.eIdl  = zeros(Ncams,numel(Sclk),numel(FPSreq)); 
cam.sen.tAct  = zeros(Ncams,numel(Sclk),numel(FPSreq)); 
cam.sen.totFR = zeros(Ncams,numel(Sclk),numel(FPSreq));

%% COMPUTE CONSUMPTION OF EACH CAMERA
fprintf('Computing consumption for each camera...\n');
%compute accumulated results of resource consumption
for c=1:Ncams    
    for r=1:Nruns
        %find settings of current experiment
        ic = find(Sclk==cams.usage{c,r}.cam.sen.clockfreq); %index for the processing clock
        is = find(FPSreq==cams.usage{c,r}.cam.sen.FPSreq);  %index for the fps of sensing
        
        cam.runs(c,ip,is) = cam.runs(c,ip,is)+1;
        cam.simTime(c,ip,is) = cam.simTime(c,ip,is) + cams.usage{c,r}.t_sim;  
            
        %SENSING
        indS = find(cams.usage{c,r}.cam.sen.eAct > 0);%indexes for data of 'sensing' module
        cam.sen.totFR(c,ip,is) = cam.sen.totFR(c,ip,is) + numel(indS); %number of frames analized        
        
        en.SENact(c,ip,is) = en.SENact(c,ip,is) + sum(cams.usage{c,r}.cam.sen.eAct(indS)); %sensing energy active
        cam.sen.eIdl(c,ip,is) = cam.sen.eIdl(c,ip,is) + sum(cams.usage{c,r}.cam.sen.eIdl(indS)); %sensing energy idle                
        cam.sen.tAct(c,ip,is) = cam.sen.tAct(c,ip,is) + sum(size(cams.usage{c,r}.cam.sen.eAct,1)*cams.usage{c,r}.cam.sen.Tact); %sensing activation time
    end
end

%% PLOT RESULTS
rot_angle1 = 0; 
rot_angle2 = 0;
c=cam2show;

h=figure('Name',sprintf('Active state/Idle state consumption for camera %03d',c));
[N,M]=meshgrid(FPSreq,SENclk);

nsamples = (cam.runs.*cam.simTime);
subplot 221; mesh(N,M,cam.sen.tAct(c,:,:)./nsamples(c,:,:)); 
plot_labels_axis('Active state','Average energy (mJ/s)',SENclk,FPSreq); %axis(limits);
subplot 222; mesh(N,M,cam.sen.tIdl(c,:,:)./nsamples(c,:,:)); 
plot_labels_axis('Idle state','Average energy (mJ/s)',SENclk,FPSreq);%axis(limits);

nsamples=(cam.runs.*cam.sen.totFR);
subplot 221; mesh(N,M,cam.sen.tAct(c,:,:)./nsamples(c,:,:)); 
plot_labels_axis('Active state','Average energy (mJ/frame)',SENclk,FPSreq); %axis(limits);
subplot 222; mesh(N,M,cam.sen.tIdl(c,:,:)./nsamples(c,:,:)); 
plot_labels_axis('Idle state','Average energy (mJ/frame)',SENclk,FPSreq);%axis(limits);

saveas(h, sprintf('figs/sensing_energy_B3_cam%d.eps',c),'epsc');
saveas(h, sprintf('figs/sensing_energy_B3_cam%d.fig',c),'fig');