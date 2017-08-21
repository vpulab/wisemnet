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
data_dir='res_P_C6_7fps_t09_25s_r50_o2';%selected

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
for ip=1:numel(err_s.Pclk)
    Xgp = [Xgp; err_s.err.coaGP{ip,1}(:)'];
end

%% plot tracking data
f1=figure('Position',[100 100 500 300]);
T = bplot(Xgp','points'); legend(T,'location','northeast');
set(gca,'XTick',1:numel(err_s.Pclk), 'XTickLabel',err_s.Pclk/1e9);
xlabel('Processing clock (Ghz)');ylabel('Coalition tracking error (m)');
axis([0.5 numel(err_s.Pclk)+0.5 0.6  1.8]); %axis Ylimits match the same experiment for 'sensing'

%% ENERGY RESULTS
%prepare energy data
data = [(res_coa.coa.sen.eTot./res_coa.coa.simTime)'; ...
        (res_coa.coa.pro.eTot./res_coa.coa.simTime)'; ...
        (res_coa.coa.com.eTot./res_coa.coa.simTime)'];

%plot energy data
f2=figure('Position',[100 100 500 300]);
h=plot(data');
set(h,{'LineStyle'},moduleStyle(1:3),{'Color'},moduleColor(1:3),{'Marker'},moduleMark(1:3));%loaded in 'load_plot_config.m'

axis([0.5 numel(err_s.Pclk)+0.5 0 800]);%axis Ylimits match the same experiment for 'sensing'
legend('Sensing', 'Processing', 'Comms','Location','NorthWest');
set(gca,'XTick',1:numel(err_s.Pclk), 'XTickLabel',strread(num2str(err_s.Pclk/1e9),'%s'));
set(gca,'YTick',0:100:800, 'YTickLabel',0:100:800);

xlabel('Processing clock (Ghz)');ylabel('Coalition consumption (mJ/sec)');box off

epsfig = hgexport('factorystyle');
epsfig.Format = 'eps';
hgexport(f1,sprintf('figs/AccuracyEnergy_coa_pro_err_%s.eps',data_dir),epsfig,'Format','eps')
hgexport(f2,sprintf('figs/AccuracyEnergy_coa_pro_ene_%s.eps',data_dir),epsfig,'Format','eps')