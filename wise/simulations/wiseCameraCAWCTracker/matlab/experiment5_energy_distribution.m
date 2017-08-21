% This script computes the distribution of the energy consumption for the 
% camera network (coalition manager and the coalition cameras). 
% The processing clock is fp = 1.5GHz and the sensing framerates is 7fps
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
data_dir='res_fixed_C6_7fps_t09_25s_r50_o2';

%% load data
if exist(['./data/' data_dir '_EnergyCams.mat'], 'file') == 2
    load(['./data/' data_dir '_EnergyCams.mat']);
else
    res_cams = CAWC_compute_energy_cams(root_dir,data_dir); %compute energy statistics
end

if exist(['./data/' data_dir '_EnergyCoa.mat'], 'file') == 2
    load(['./data/' data_dir '_EnergyCoa.mat']);
else
    res_coa = CAWC_compute_energy_coalition(root_dir,data_dir); %compute energy statistics
end

%% get data to plot
labels = {'Sensing', 'Processing-track', 'Processing-coalition','Communication'};
% data1 = [res_coa.coa.sen.eAct_acc+res_coa.coa.sen.eIdl_acc; res_coa.coa.pro.eAct_acc; res_coa.coa.pro.eCol_acc; res_coa.coa.com.eAct_acc];
% data2 = [res_coa.coa.man.sen.eAct_acc+res_coa.coa.man.sen.eIdl_acc; res_coa.coa.man.pro.eAct_acc; res_coa.coa.man.pro.eCol_acc; res_coa.coa.man.com.eAct_acc];

%simulations may have wrongly written the results so data1 & data2 are redefined
res_coa.coa.pro.eCol_acc = res_coa.coa.pro.eCol_acc/3;
res_coa.coa.man.com.eAct_acc = res_coa.coa.man.com.eAct_acc * 3;
data1 = [res_coa.coa.sen.eAct_acc+res_coa.coa.sen.eIdl_acc; res_coa.coa.pro.eAct_acc; res_coa.coa.man.pro.eCol_acc; res_coa.coa.com.eAct_acc];
data1m = [mean(res_coa.coa.sen.eAct_acc+res_coa.coa.sen.eIdl_acc); mean(res_coa.coa.pro.eAct_acc); mean(res_coa.coa.man.pro.eCol_acc); mean(res_coa.coa.com.eAct_acc)];
data2 = [res_coa.coa.man.sen.eAct_acc+res_coa.coa.man.sen.eIdl_acc; res_coa.coa.man.pro.eAct_acc; res_coa.coa.pro.eCol_acc; res_coa.coa.man.com.eAct_acc];
data2m = [mean(res_coa.coa.man.sen.eAct_acc+res_coa.coa.man.sen.eIdl_acc); mean(res_coa.coa.man.pro.eAct_acc); mean(res_coa.coa.pro.eCol_acc); mean(res_coa.coa.man.com.eAct_acc)];

%% plot manager & cameras of coalition consumption (bplot)
fntsize=11.5;
f1=figure('Position',[100 100 650 300]);
T = bplot(data1','nooutliers'); legend(T(1:end-1),'location','northeast');
set(gca,'XTick',1:4, 'XTickLabel',labels,'FontSize', fntsize);
xlabel('Coalition cameras');ylabel('Energy consumption (mJ/frame)');
axis([0.5 4.5 0 71]);%linear scale
% set(gca,'yscale','log');
% axis([0.5 4.5 0 100]);%log scale
set(gcf,'Units','normal')
set(gca,'Position',[.10 .15 .9 .82])


f2=figure('Position',[100 100 650 300]);
T = bplot(data2','nooutliers'); legend(T(1:end-1),'location','northeast');
set(gca,'XTick',1:4, 'XTickLabel',labels,'FontSize', fntsize);
xlabel('Coalition manager');ylabel('Energy consumption (mJ/frame)');
axis([0.5 4.5 0 71]);%linear scale
% set(gca,'yscale','log');
% axis([0.5 4.5 0 100]);%log scale
set(gcf,'Units','normal')
set(gca,'Position',[.10 .15 .9 .82])

%% plot manager & cameras of coalition consumption (pie)
%pale colours for the pie
moduleColor{1,:} = [31, 117, 254]/255; %[0 0 1]
moduleColor{2,:} = [234, 60, 83]/255; %[1 0 0]
moduleColor{3,:} = [.5 1 .5]; %[0 1 0]
moduleColor{4,:} = [.75 .75 .75]; %[1 1 1]


f3=figure('Position',[100 100 675 350]);
subplot 121;
l1=pie(data1m);
l1(1).FaceColor = moduleColor{1,:}; %sensing
l1(3).FaceColor = moduleColor{2,:}; %processing
l1(5).FaceColor = moduleColor{4,:}; %processing-colaborative
l1(6).String='<1%';
l1(6).Position = [0.35 1.1034 0];
l1(7).FaceColor = moduleColor{3,:}; %comms
l1(8).Position = [0.05 1.10970 0];
title('Coalition cameras');
ll=legend(labels,'Location','southoutside','Orientation','horizontal','FontSize', fntsize);
ll.Position = [0.02 0.05 0.9664 0.0632];
ll.Visible = 'off'; %legend is created so the 'pie' graphic is aligned with the following one

subplot 122;
l2=pie(data2m);
l2(1).FaceColor = moduleColor{1,:}; %sensing
l2(3).FaceColor = moduleColor{2,:}; %processing
l2(5).FaceColor = moduleColor{4,:}; %processing-colaborative
l2(7).FaceColor = moduleColor{3,:}; %comms
l2(8).Position = [0.1225 1.1037 0];
title('Coalition manager');
ll=legend(labels,'Location','southoutside','Orientation','horizontal','FontSize', fntsize);
ll.Position = [0.02 0.05 0.96 0.0632];

% set(gcf,'Units','normal')
% set(gca,'Position',[.10 .15 .9 .82])

%save figures
epsfig = hgexport('factorystyle');
epsfig.Format = 'eps';
hgexport(f1,sprintf('figs/EnergyDist_cam_%s.eps',data_dir),epsfig,'Format','eps')
hgexport(f2,sprintf('figs/EnergyDist_coa_%s.eps',data_dir),epsfig,'Format','eps')
hgexport(f3,sprintf('figs/EnergyDist_summary_%s.eps',data_dir),epsfig,'Format','eps')