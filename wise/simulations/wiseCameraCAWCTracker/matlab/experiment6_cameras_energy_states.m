% This script shows the energy consumption for the active and idle states of
% a selected camera (sensing, processing & comms). 
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

%% settings
load_plot_config;

root_dir='/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/';
scenario='pets2009_S2_L1';
data_dir='res_scalable_C6_7fps_t09_25s_r50_o2';

%% load data
if exist(['./data/' data_dir '_EnergyCams.mat'], 'file') == 2
    load(['./data/' data_dir '_EnergyCams.mat']);
else
    res_cams = CAWC_compute_energy_cams(root_dir,data_dir); %compute energy statistics
end

FPSreq = floor(res_cams.fps);
Pclk = res_cams.Pclk;

%% plot data - energy consumption
figsize = [100, 100, 800, 500];
figPos = [.13 .15 .86 .76];
c=1;

[N,M]=meshgrid(FPSreq,Pclk);
zlab = 'Consumption (mJ/s)';  

f1a=figure('Name',sprintf('Overview consumption for camera %03d - sensing - active',c),'Position', figsize);
data=reshape(res_cams.cam.sen.eAct(c,:,:)./res_cams.cam.simTime(c,:,:), [numel(Pclk) numel(FPSreq) ]);
mesh(N,M,data);
[ly,lx,lz]=plot_labels_axis('Sensing - Active state',zlab,Pclk,FPSreq);
ly.Position = [1.2 1.15e+09 -max(max(data))/3];
lx.Position = [numel(FPSreq)/2 -0 -max(max(data))/10];
lz.Position = [0.25 1.5865e+09 max(max(data))/1.5];
set(gcf,'Units','normal')
set(gca,'Position',figPos)
axis([FPSreq(1) FPSreq(end)+0.5 Pclk(1) Pclk(end)+0.05e9 0 max(max(data))]);

f2a=figure('Name',sprintf('Overview consumption for camera %03d - processing - active',c),'Position', figsize);
data=reshape(res_cams.cam.pro.eAct(c,:,:)./res_cams.cam.simTime(c,:,:), [numel(Pclk) numel(FPSreq) ]);
mesh(N,M,data); 
[ly,lx,lz]=plot_labels_axis('Processing - Active state',zlab,Pclk,FPSreq);
ly.Position = [1.2 1.15e+09 -max(max(data))/3];
lx.Position = [numel(FPSreq)/2 0 -max(max(data))/10];
lz.Position = [0.05 1.6e+09 max(max(data))/1.5];

set(gcf,'Units','normal')
set(gca,'Position',figPos)
axis([FPSreq(1) FPSreq(end)+0.5 Pclk(1) Pclk(end)+0.05e9 0 max(max(data))]);

f3a=figure('Name',sprintf('Overview consumption for camera %03d - comm - active',c),'Position', figsize);
data=reshape(res_cams.cam.com.eAct(c,:,:)./res_cams.cam.simTime(c,:,:), [numel(Pclk) numel(FPSreq) ]);
mesh(N,M,data); 
[ly,lx,lz]=plot_labels_axis('Comms - Active state',zlab,Pclk,FPSreq);
ly.Position = [1.2 1.15e+09 -max(max(data))/3];
lx.Position = [numel(FPSreq)/2 -0 -max(max(data))/10];
lz.Position = [0.25 1.6e+09 max(max(data))/1.5];
set(gcf,'Units','normal')
set(gca,'Position',figPos)
axis([FPSreq(1) FPSreq(end)+0.5 Pclk(1) Pclk(end)+0.05e9 0 max(max(data))]);


%Idle state
f1b=figure('Name',sprintf('Overview consumption for camera %03d - sensing - idle',c),'Position', figsize);
data=reshape(res_cams.cam.sen.eIdl(c,:,:)./res_cams.cam.simTime(c,:,:), [numel(Pclk) numel(FPSreq) ]);
mesh(N,M,data);
[ly,lx,lz]=plot_labels_axis('Sensing - Idle state',zlab,Pclk,FPSreq);
ly.Position = [1.2 1.15e+09 -max(max(data))/3];
lx.Position = [numel(FPSreq)/2 -0 -max(max(data))/10];
lz.Position = [0.25 1.5865e+09 max(max(data))/1.5];
set(gcf,'Units','normal')
set(gca,'Position',figPos)
axis([FPSreq(1) FPSreq(end)+0.5 Pclk(1) Pclk(end)+0.05e9 0 max(max(data))]);

f2b=figure('Name',sprintf('Overview consumption for camera %03d - pro - idle',c),'Position', figsize);
data=reshape(res_cams.cam.pro.eIdl(c,:,:)./res_cams.cam.simTime(c,:,:), [numel(Pclk) numel(FPSreq) ]);
mesh(N,M,data); 
[ly,lx,lz]=plot_labels_axis('Processing - Idle state',zlab,Pclk,FPSreq);
ly.Position = [1.2 1.15e+09 -max(max(data))/3];
lx.Position = [numel(FPSreq)/2 0 -max(max(data))/10];
lz.Position = [0.05 1.6e+09 max(max(data))/1.5];
set(gcf,'Units','normal')
set(gca,'Position',figPos)
axis([FPSreq(1) FPSreq(end)+0.5 Pclk(1) Pclk(end)+0.05e9 0 max(max(data))]);

f3b=figure('Name',sprintf('Overview consumption for camera %03d - comms - idle',c),'Position', figsize);
data=reshape(res_cams.cam.com.eIdl(c,:,:)./res_cams.cam.simTime(c,:,:), [numel(Pclk) numel(FPSreq) ]);
mesh(N,M,data); 
[ly,lx,lz]=plot_labels_axis('Comms - Idle state',zlab,Pclk,FPSreq);
ly.Position = [1.2 1.15e+09 -max(max(data))/3];
lx.Position = [numel(FPSreq)/2 -0 -max(max(data))/10];
lz.Position = [0.25 1.5865e+09 max(max(data))/1.5];
set(gcf,'Units','normal')
set(gca,'Position',figPos)
axis([FPSreq(1) FPSreq(end)+0.5 Pclk(1) Pclk(end)+0.05e9 0 max(max(data))]);

%total

f2c=figure('Name',sprintf('Overview consumption for camera %03d - pro - both',c),'Position', figsize);
data2=reshape((res_cams.cam.pro.eAct(c,:,:)+res_cams.cam.pro.eIdl(c,:,:))./res_cams.cam.simTime(c,:,:), [numel(Pclk) numel(FPSreq) ]);
mesh(N,M,data2); 
[ly,lx,lz]=plot_labels_axis('Processing - both states',zlab,Pclk,FPSreq);
ly.Position = [1.2 1.15e+09 -max(max(data2))/3];
lx.Position = [numel(FPSreq)/2 0 -max(max(data2))/10];
lz.Position = [0.05 1.6e+09 max(max(data2))/1.5];
set(gcf,'Units','normal')
set(gca,'Position',figPos)
axis([FPSreq(1) FPSreq(end)+0.5 Pclk(1) Pclk(end)+0.05e9 0 400]);
set(gca,'ZTick',0:100:400, 'ZTickLabel',0:100:400);


f1c=figure('Name',sprintf('Overview consumption for camera %03d - sensing - both',c),'Position', figsize);
data=reshape((res_cams.cam.sen.eAct(c,:,:)+res_cams.cam.sen.eIdl(c,:,:))./res_cams.cam.simTime(c,:,:), [numel(Pclk) numel(FPSreq) ]);
mesh(N,M,data);
[ly,lx,lz]=plot_labels_axis('Sensing - both states',zlab,Pclk,FPSreq);
ly.Position = [1.2 1.15e+09 -max(max(data2))/3];
lx.Position = [numel(FPSreq)/2 0 -max(max(data2))/10];
lz.Position = [0.05 1.6e+09 max(max(data2))/1.5];
set(gcf,'Units','normal')
set(gca,'Position',figPos)
axis([FPSreq(1) FPSreq(end)+0.5 Pclk(1) Pclk(end)+0.05e9 0 400]);
set(gca,'ZTick',0:100:400, 'ZTickLabel',0:100:400);

f3c=figure('Name',sprintf('Overview consumption for camera %03d - comm - both',c),'Position', figsize);
data=reshape((res_cams.cam.com.eAct(c,:,:)+res_cams.cam.com.eIdl(c,:,:))./res_cams.cam.simTime(c,:,:), [numel(Pclk) numel(FPSreq) ]);
mesh(N,M,data);  
[ly,lx,lz]=plot_labels_axis('Comms - both states',zlab,Pclk,FPSreq);
ly.Position = [1.2 1.15e+09 -max(max(data2))/3];
lx.Position = [numel(FPSreq)/2 0 -max(max(data2))/10];
lz.Position = [0.05 1.6e+09 max(max(data2))/1.5];
set(gcf,'Units','normal')
set(gca,'Position',figPos)
axis([FPSreq(1) FPSreq(end)+0.5 Pclk(1) Pclk(end)+0.05e9 0 400]);
set(gca,'ZTick',0:100:400, 'ZTickLabel',0:100:400);


epsfig = hgexport('factorystyle');
epsfig.Format = 'eps';
hgexport(f1a,sprintf('figs/CamEnergy_sena_C%d_%s.eps',c,data_dir),epsfig,'Format','eps')
hgexport(f2a,sprintf('figs/CamEnergy_proa_C%d_%s.eps',c,data_dir),epsfig,'Format','eps')
hgexport(f3a,sprintf('figs/CamEnergy_coma_C%d_%s.eps',c,data_dir),epsfig,'Format','eps')
hgexport(f1b,sprintf('figs/CamEnergy_seni_C%d_%s.eps',c,data_dir),epsfig,'Format','eps')
hgexport(f2b,sprintf('figs/CamEnergy_proi_C%d_%s.eps',c,data_dir),epsfig,'Format','eps')
hgexport(f3b,sprintf('figs/CamEnergy_comi_C%d_%s.eps',c,data_dir),epsfig,'Format','eps')
hgexport(f1c,sprintf('figs/CamEnergy_sent_C%d_%s.eps',c,data_dir),epsfig,'Format','eps')
hgexport(f2c,sprintf('figs/CamEnergy_prot_C%d_%s.eps',c,data_dir),epsfig,'Format','eps')
hgexport(f3c,sprintf('figs/CamEnergy_comt_C%d_%s.eps',c,data_dir),epsfig,'Format','eps')