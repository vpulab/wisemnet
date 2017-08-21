clear all
close all
clc

load figs/TrackErrIP_cmp_sensing.mat
load figs/TrackErrIP_cmp_processing.mat
load figs/Coalition_sensing_consumption.mat
load figs/Coalition_processing_consumption.mat

PRO.clk = [0.25 0.5 0.75 1 1.25 1.5];
PROene.clk = [0.25 0.5 0.75 1 1.25 1.5];

f1a=figure('Position',[100 100 500 300]);
T = bplot(SEN.Xgp,'points'); legend(T,'location','northeast');
set(gca,'XTick',1:numel(SEN.fps), 'XTickLabel',SEN.fps);
axis([0.5 numel(SENene.fps)+0.5 1 4.1]);% axis([0 numel(SENene.fps)+1 0 max(max(SENene.data))]);
xlabel('Sensing framerate (fps)');   ylabel('Coalition tracking error (m)');

f1e=figure('Position',[300 300 500 300]);
bar(SENene.data');
plot(SENene.data','-*'); hold on; 
axis([0.5 numel(SENene.fps)+0.5 0 1000]);% axis([0 numel(SENene.fps)+1 0 max(max(SENene.data))]);
legend('Sensing', 'Processing', 'Comms','Location','NorthWest');
set(gca,'XTick',1:numel(SENene.fps), 'XTickLabel',strread(num2str(SENene.fps),'%s'));
xlabel('Sensing framerate (fps)');ylabel('Coalition consumption (mJ/sec)');box off

% saveas(f1a, 'plots/CoalitionTrack_pro_errGP.eps','epsc'); 
% saveas(f1e, 'plots/CoalitionTrack_pro_ene.eps','epsc'); 


f2a=figure('Position',[100 100 500 300]);
T = bplot(PRO.Xgp','points'); legend(T,'location','northeast');
set(gca,'XTick',1:numel(PRO.clk), 'XTickLabel',PRO.clk);
axis([0.5 numel(PRO.clk)+0.5 1 4.1]);% axis([0 numel(SENene.fps)+1 0 max(max(SENene.data))]);
xlabel('Processor clock (Ghz)');   ylabel('Coalition tracking error (m)');

f2e=figure('Position',[300 300 500 300]);
% bar(PROene.data'); hold on; 
plot(PROene.data','-*'); hold on; 
axis([0.5 numel(PRO.clk)+0.5 0 1000]);% axis([0 numel(SENene.fps)+1 0 max(max(SENene.data))]);
legend('Sensing', 'Processing', 'Comms','Location','NorthWest');
set(gca,'XTick',1:numel(PROene.clk), 'XTickLabel',strread(num2str(PROene.clk),'%s'));
xlabel('Processor clock (Ghz)');ylabel('Coalition consumption (mJ/sec)');box off