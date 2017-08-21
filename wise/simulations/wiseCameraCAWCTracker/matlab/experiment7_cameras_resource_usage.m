% This script shows the maximum resource usage for all cameras in terms of load
% and missed data for sensing, processing & communications
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
data_dir='res_scalable_C6_7fps_t09_25s_r50_o2';

%% load data
if exist(['./data/' data_dir '_EnergyCams.mat'], 'file') == 2
    load(['./data/' data_dir '_EnergyCams.mat']);
else
    res_cams = CAWC_compute_energy_cams(root_dir,data_dir); %compute energy statistics
end

FPSreq = floor(res_cams.fps);
Pclk = res_cams.Pclk;

%% plot data - resource usage
[N,M]=meshgrid(FPSreq,Pclk);
zlab = 'Consumption (mJ/s)';
figPos = [.13 .15 .86 .80];

figsize = [100, 100, 800, 500];
h1=figure('Name','Resource usage for all cameras (sensing)','Position', figsize);
data=reshape(res_cams.cam.sen.tAct./res_cams.cam.simTime, [res_cams.Ncams numel(Pclk) numel(FPSreq) ]);
mesh(N,M,100*reshape(max(data,[],1), [numel(Pclk) numel(FPSreq)])); 
[ly,lx,lz]=plot_labels_axis([],'Max sensing load (%)',Pclk,FPSreq);
ly.Position = [1.2 1.15e+09 -15];
lx.Position = [numel(FPSreq)/2 -0 -5];
lz.Position = [0.0 1.5865e+09 40];
set(gcf,'Units','normal')
set(gca,'Position',figPos)
axis([FPSreq(1) FPSreq(end)+0.5 Pclk(1) Pclk(end)+0.05e9 0 50]);
set(gca,'ZTick',0:10:50, 'ZTickLabel',0:10:50);

h2=figure('Name','Resource usage for all cameras (process)','Position', figsize);
data=reshape(res_cams.cam.pro.tAct./res_cams.cam.simTime, [res_cams.Ncams numel(Pclk) numel(FPSreq) ]);
mesh(N,M,100*reshape(max(data,[],1), [numel(Pclk) numel(FPSreq)])); 
[ly,lx,lz]=plot_labels_axis([],'Max processing load (%)',Pclk,FPSreq);
ly.Position = [1.2 1.15e+09 -30];
lx.Position = [numel(FPSreq)/2 -0 -10];
lz.Position = [0.0 1.5865e+09 75];
axis([FPSreq(1) FPSreq(end)+0.5 Pclk(1) Pclk(end)+0.05e9 0 100]);
set(gca,'ZTick',0:25:100, 'ZTickLabel',0:25:100);
set(gcf,'Units','normal')
set(gca,'Position',figPos)

h3=figure('Name','Resource usage for all cameras (process)','Position', figsize);
data=reshape(res_cams.cam.pro.misFR./res_cams.cam.sen.totFR, [res_cams.Ncams numel(Pclk) numel(FPSreq) ]);
mesh(N,M,100*reshape(max(data,[],1), [numel(Pclk) numel(FPSreq)])); 
[ly,lx,lz]=plot_labels_axis([],'Max missed frames (%)',Pclk,FPSreq);
ly.Position = [1.2 1.15e+09 -30];
lx.Position = [numel(FPSreq)/2 -0 -10];
lz.Position = [0.0 1.5865e+09 75];
axis([FPSreq(1) FPSreq(end)+0.5 Pclk(1) Pclk(end)+0.05e9 0 100]);
set(gca,'ZTick',0:25:100, 'ZTickLabel',0:25:100);
set(gcf,'Units','normal')
set(gca,'Position',figPos)

h4=figure('Name','Resource usage for all cameras (comms)','Position', figsize);
data=reshape(res_cams.cam.com.tAct./res_cams.cam.simTime, [res_cams.Ncams numel(Pclk) numel(FPSreq) ]);
mesh(N,M,100*reshape(max(data,[],1), [numel(Pclk) numel(FPSreq)])); 
[ly,lx,lz]=plot_labels_axis([],'Max comms usage (%)',Pclk,FPSreq);
ly.Position = [1.2 1.15e+09 -30];
lx.Position = [numel(FPSreq)/2 -0 -10];
lz.Position = [0.0 1.5865e+09 75];
axis([FPSreq(1) FPSreq(end)+0.5 Pclk(1) Pclk(end)+0.05e9 0 100]);
set(gca,'ZTick',0:25:100, 'ZTickLabel',0:25:100);
set(gcf,'Units','normal')
set(gca,'Position',figPos)

h5=figure('Name','Resource usage for all cameras (comms)','Position', figsize);
mTime = reshape(mean(res_cams.cam.simTime,1), [numel(Pclk) numel(FPSreq)]); 
BWuse = 0.95*reshape(sum(res_cams.cam.com.tAct,1), [numel(Pclk) numel(FPSreq)]); 
mesh(N,M,100 * BWuse./mTime); 
[ly,lx,lz]=plot_labels_axis([],'Channel bandwidth use (%)',Pclk,FPSreq);
ly.Position = [1.2 1.15e+09 -30];
lx.Position = [numel(FPSreq)/2 -0 -10];
lz.Position = [0.0 1.5865e+09 68];
lz.FontSize=20;
axis([FPSreq(1) FPSreq(end)+0.5 Pclk(1) Pclk(end)+0.05e9 0 100]);
set(gca,'ZTick',0:25:100, 'ZTickLabel',0:25:100);
set(gcf,'Units','normal')
set(gca,'Position',figPos)

epsfig = hgexport('factorystyle');
epsfig.Format = 'eps';
hgexport(h1,sprintf('figs/ResourceUsage_sen_load_%s.eps',data_dir),epsfig,'Format','eps')
hgexport(h2,sprintf('figs/ResourceUsage_pro_load_%s.eps',data_dir),epsfig,'Format','eps')
hgexport(h3,sprintf('figs/ResourceUsage_pro_misF_%s.eps',data_dir),epsfig,'Format','eps')
hgexport(h4,sprintf('figs/ResourceUsage_com_load_%s.eps',data_dir),epsfig,'Format','eps')
hgexport(h5,sprintf('figs/ResourceUsage_com_bwacc_%s.eps',data_dir),epsfig,'Format','eps')