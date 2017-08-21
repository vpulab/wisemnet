% This script computes coalition tracking error and associated energy consumption 
% for dynamic sensing and processing capabilities.
%   - First for various sensing framerates with Pclk = 1.5Ghz 
%   - Second for various processing clocks with 25fps
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
data_dir='res_S_C6_7fps_t09_25s_r50_o2';

%% load data
if exist(['./data/' data_dir '_EnergyCoa.mat'], 'file') == 2
    load(['./data/' data_dir '_EnergyCoa.mat']);
else
    res_coa = CAWC_compute_energy_coalition(root_dir,data_dir); %compute energy statistics
end

if exist(['./data/' data_dir '_TrackingErr.mat'], 'file') == 2
    load(['./data/' data_dir '_TrackingErr.mat']);
else
    err_s=CAWC_compute_accuracy(root_dir,data_dir,scenario,0); %compute accuracy statistics (coalition & cams)
end

%% TRACKING RESULTS
%prepare tracking data
Xgp=[];
for is=1:numel(err_s.fps)
    Xgp = [Xgp; err_s.err.coaGP{1,is}(:)'];
end

%plot tracking data
f1=figure('Position',[100 100 500 300]);
T = bplot(Xgp','points'); legend(T,'location','northeast');
set(gca,'XTick',1:numel(err_s.fps), 'XTickLabel',floor(err_s.fps));
xlabel('Sensing framerate (fps)');ylabel('Coalition tracking error (m)');
axis([0.5 numel(err_s.fps)+0.5 0.6  1.8]); %axis Ylimits match the same experiment for 'processing'

%% ENERGY RESULTS
%prepare energy data
data = [(res_coa.coa.sen.eTot./res_coa.coa.simTime); ...
        (res_coa.coa.pro.eTot./res_coa.coa.simTime); ...
        (res_coa.coa.com.eTot./res_coa.coa.simTime)];

%plot energy data
f2=figure('Position',[100 100 500 300]);
h=plot(data');
set(h,{'LineStyle'},moduleStyle(1:3),{'Color'},moduleColor(1:3),{'Marker'},moduleMark(1:3));%loaded in 'load_plot_config.m'

axis([0.5 numel(err_s.fps)+0.5 0  800]); %axis Ylimits match the same experiment for 'processing'
legend('Sensing', 'Processing', 'Comms','Location','NorthWest');
set(gca,'XTick',1:numel(err_s.fps), 'XTickLabel',strread(num2str(floor(err_s.fps)),'%s'));
set(gca,'YTick',0:100:800, 'YTickLabel',0:100:800);

xlabel('Sensing framerate (fps)');ylabel('Coalition consumption (mJ/sec)');box off

epsfig = hgexport('factorystyle');
epsfig.Format = 'eps';
hgexport(f1,sprintf('figs/AccuracyEnergy_coa_sen_err_%s.eps',data_dir),epsfig,'Format','eps')
hgexport(f2,sprintf('figs/AccuracyEnergy_coa_sen_ene_%s.eps',data_dir),epsfig,'Format','eps')