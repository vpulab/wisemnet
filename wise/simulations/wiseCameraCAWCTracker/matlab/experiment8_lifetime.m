% This script shows the predicted lifetime for the camera network and the 
% prediction error by comparing active/idle models for sensing, processing & comms
% The processing clock is fp = 0.25-1.5GHz and the sensing framerates is 1-7fps
%%
%   Author:      Juan Carlos SanMiguel (juancarlos.sanmiguel@uam.es)
%   Affiliation: University Autonoma of Madrid
%   URL:         http://www-vpu.ii.uam.es/~jcs
%   Date:        November 2015
addpath('./cawc','./utils');

clc;
clear all;
close all;

%% input data
load_plot_config;

root_dir='/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/';
scenario='pets2009_S2_L1';
data_dir='res_lifetime_C6_7fps_t09_25s_r50';

%% load data
if exist(['./data/' data_dir '_EnergyCams.mat'], 'file') == 2
    load(['./data/' data_dir '_EnergyCams.mat']);
else
    res_cams = CAWC_compute_energy_cams(root_dir,data_dir); %compute energy statistics
end

FPSreq = floor(res_cams.fps);
Pclk = res_cams.Pclk;
OptFactor = res_cams.optF;
Ncams = res_cams.Ncams;

%% battery model
battery=2300*3.940;%2300mAh*3940mV (Watt-h) %NEXUS 5
%battery=9000*3.940;%2300mAh*3940mV (Watt-h) %NEXUS 10
battery = battery * 3600; %(Watt-sec or Joules)

%% get Active/Idle times for each optFactor
time =  mean(reshape(res_cams.cam.simTime,[Ncams numel(OptFactor)]),1);
en.SENactm = mean(res_cams.cam.sen.eAct,1);         
en.SENidlm = mean(res_cams.cam.sen.eIdl,1);        
en.PROactm = mean(res_cams.cam.pro.eAct,1);        
en.PROidlm = mean(res_cams.cam.pro.eIdl,1);        
en.COMactm = mean(res_cams.cam.com.eAct,1);        
en.COMidlm = mean(res_cams.cam.com.eIdl,1);
        
en.SENtot=en.SENactm+en.SENidlm;
en.PROtot=en.PROactm+en.PROidlm;
en.COMtot=en.COMactm+en.COMidlm;

PRO = (en.SENtot+en.PROtot+en.COMtot)./time;
soa_SEN = (en.SENactm+en.PROtot+en.COMtot)./time;
soa_PRO = (en.SENtot+en.PROactm+en.COMtot)./time;
soa_COM = (en.SENtot+en.PROtot+en.COMactm)./time;
soa_ALL = (en.SENactm+en.PROactm+en.COMactm)./time;

%% predicted lifetime
f1=figure('Position',[100 100 500 275]);              
plot(flip(1/3600*battery./soa_SEN),'bd-'); hold on;
plot(flip(1/3600*battery./soa_PRO),'ro-');
plot(flip(1/3600*battery./soa_COM),'cs-');
plot(flip(1/3600*battery./soa_ALL),'k*-');
plot(flip(1/3600*battery./PRO),'g+-');hold on;   box off;      
legend('Utilization-based sensing','Utilization-based processing','Utilization-based comms','Utilization-based all', 'Proposed', 'Location','NorthEast');
set(gca,'XTick',1:numel(OptFactor), 'XTickLabel',strread(num2str(round(flip(mean(res_cams.cam.pro.tAct,1)./time*100))),'%s'));
xlabel('Utilization processing (%)');ylabel('Predicted lifetime (hours)');
set(gcf,'Units','normal')
set(gca,'Position',[.10 .15 .87 .80])

f2=figure('Position',[100 100 500 275]);
plot(100*flip(1 - soa_SEN./PRO),'bd-'); hold on;
plot(100*flip(1 - soa_PRO./PRO),'ro-');
plot(100*flip(1 - soa_COM./PRO),'cs-');
plot(100*flip(1 - soa_ALL./PRO),'k*-');
box off;          
legend('Utilization-based sensing','Utilization-based processing','Utilization-based comms','Utilization-based all');
set(gca,'XTick',1:numel(OptFactor), 'XTickLabel',strread(num2str(round(flip(mean(res_cams.cam.pro.tAct,1)./time*100))),'%s'));
xlabel('Utilization processing (%)');ylabel('Average prediction error (%)');
set(gcf,'Units','normal')
set(gca,'Position',[.10 .15 .87 .80])
% axis()

epsfig = hgexport('factorystyle');
epsfig.Format = 'eps';
hgexport(f1,sprintf('figs/Lifetime_pre_%s.eps',data_dir),epsfig,'Format','eps')
hgexport(f2,sprintf('figs/Lifetime_err_%s.eps',data_dir),epsfig,'Format','eps')