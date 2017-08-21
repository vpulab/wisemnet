% TEST FOR 'Requested frequency' versus 'operating frequency SEN'

clc; clear all; close all;
addpath('./utils');

rot_angle1 = 15;
rot_angle2 = 25;

%% LOAD AND PRESENCESS DATA
dataDir = '../res/test1';
%load data
res=load_data(dataDir);

%get the test variables (frequencies)
SENclk=[]; SENclk = []; SENfps_rea = []; SENfps_req = [];
for i=1:numel(res)
    SENclk = [SENclk res(i).SEN.clockfreq];
    SENclk = [SENclk res(i).SEN.clockfreq];
    SENfps_rea = [SENfps_rea res(i).SEN.FPSrea];
    SENfps_req = [SENfps_req res(i).SEN.FPSreq];
end

simTime = max (res(1).t_sim);
SENclk = sort(unique(SENclk), 'ascend');
SENclk = sort(unique(SENclk), 'ascend');
SENfps_req = sort(unique(SENfps_req), 'ascend');

energy.SENtot = zeros(numel(SENfps_req), numel(SENclk));
energy.SENact = zeros(numel(SENfps_req), numel(SENclk));
energy.SENidl = zeros(numel(SENfps_req), numel(SENclk));

frSENcess.SENtot = zeros(numel(SENfps_req), numel(SENclk));
frSENcess.SENfps = zeros(numel(SENfps_req), numel(SENclk));%achieved fps

%% GENERATE VARIABLES TO PLOT
count = zeros(numel(SENfps_req), numel(SENclk));
for i=1:numel(res)
        
    indF = find(res(i).SEN.FPSreq==SENfps_req);
    indS = find(res(i).SEN.clockfreq==SENclk);
    count(indF, indS) = count(indF, indS) + 1;
   
    ind = find(res(i).SEN.eTot > 0);   
    frSENcess.SENtot(indF,indS) = frSENcess.SENtot(indF,indS) + numel(ind);
    frSENcess.SENfps(indF,indS) = frSENcess.SENfps(indF,indS) + res(i).SEN.FPSrea;
     
    energy.SENtot(indF,indS) = energy.SENtot(indF,indS) + sum(res(i).SEN.eTot(ind));
    energy.SENact(indF,indS) = energy.SENact(indF,indS) + sum(res(i).SEN.eAct(ind));
    energy.SENidl(indF,indS) = energy.SENidl(indF,indS) + sum(res(i).SEN.eIdl(ind));    
end

energy.SENtot = energy.SENtot./count;
energy.SENact = energy.SENact./count;
energy.SENidl = energy.SENidl./count;

frSENcess.SENtot = frSENcess.SENtot./count;   
frSENcess.SENfps = frSENcess.SENfps./count;   

%% plot results - sensed frames
[N,M]=meshgrid(SENclk,SENfps_req);
h1=figure(1);
mesh(N,M,frSENcess.SENfps); axis tight;
set(gca,'XTick',SENclk, 'XTickLabel',SENclk/1e6,'YTick',SENfps_req, 'YTickLabel',SENfps_req)  % This automatically sets the XTickMode to manual.
title('Frames captured for B3 sensor'); zlabel('Achieved framerate (fps)'); xlabel('Sensing Clock (MHz)','Rotation',rot_angle1); ylabel('Requested framerate (fps)','Rotation',-rot_angle2);
saveas(h1, 'figs/REID_SEN_achievedFramerate.fig');
saveas(h1, 'figs/REID_SEN_achievedFramerate.eps', 'epsc');

%% PLOT TEST RESULTS
%% plot results - active/idle consumption (mJ/frame)
h2=figure('Position', [100 100 1200 300],'PaperPositionMode', 'auto');

subaxis(1,3,1, 'Spacing', 0.1,'Padding', 0, 'MarginLeft', 0.04,'MarginRight', 0);
mesh(N,M,energy.SENtot./frSENcess.SENtot); axis tight;
set(gca,'XTick',SENclk, 'XTickLabel',SENclk/1e6,'YTick',SENfps_req, 'YTickLabel',SENfps_req)  % This automatically sets the XTickMode to manual.
title('Active+idle states'); zlabel('Average energy (mJ/frame)'); xlabel('Sensing Clock (MHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);

subaxis(1,3,2, 'Spacing', 0.1, 'Padding', 0, 'MarginLeft', 0,'MarginRight', 0); 
mesh(N,M,energy.SENact./frSENcess.SENtot); axis tight;
set(gca,'XTick',SENclk, 'XTickLabel',SENclk/1e6,'YTick',SENfps_req, 'YTickLabel',SENfps_req)  % This automatically sets the XTickMode to manual.
title('Active state'); zlabel('Average energy (mJ/frame)'); xlabel('Sensing Clock (MHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);

subaxis(1,3,3, 'Spacing', 0.1, 'Padding', 0, 'MarginLeft', 0,'MarginRight', 0.02); 
mesh(N,M,energy.SENidl./frSENcess.SENtot); axis tight;
set(gca,'XTick',SENclk, 'XTickLabel',SENclk/1e6,'YTick',SENfps_req, 'YTickLabel',SENfps_req)  % This automatically sets the XTickMode to manual.
title('Idle state'); zlabel('Average energy (mJ/frame)'); xlabel('Sensing Clock (MHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);

saveas(h2, 'figs/REID_SEN_consumptionFrame.fig');
saveas(h2, 'figs/REID_SEN_consumptionFrame.eps', 'epsc');

%% plot results - active/idle consumption (mJ/second)
h3=figure('Position', [100 100 1200 300],'PaperPositionMode', 'auto');
subaxis(1,3,1, 'Spacing', 0.1,'Padding', 0, 'MarginLeft', 0.04,'MarginRight', 0);
mesh(N,M,energy.SENtot./simTime); axis tight;
set(gca,'XTick',SENclk, 'XTickLabel',SENclk/1e6,'YTick',SENfps_req, 'YTickLabel',SENfps_req)  % This automatically sets the XTickMode to manual.
title('Active+idle state'); zlabel('Average energy (mJ/s)'); xlabel('Sensing Clock (MHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);

subaxis(1,3,2, 'Spacing', 0.1, 'Padding', 0, 'MarginLeft', 0,'MarginRight', 0); 
mesh(N,M,energy.SENact./simTime); axis tight;
set(gca,'XTick',SENclk, 'XTickLabel',SENclk/1e6,'YTick',SENfps_req, 'YTickLabel',SENfps_req)  % This automatically sets the XTickMode to manual.
title('Active state'); zlabel('Average energy (mJ/s)'); xlabel('Sensing Clock (MHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);

subaxis(1,3,3, 'Spacing', 0.1, 'Padding', 0, 'MarginLeft', 0,'MarginRight', 0.02); 
mesh(N,M,energy.SENidl./simTime); axis tight;
set(gca,'XTick',SENclk, 'XTickLabel',SENclk/1e6,'YTick',SENfps_req, 'YTickLabel',SENfps_req)  % This automatically sets the XTickMode to manual.
title('Idle state'); zlabel('Average energy (mJ/s)'); xlabel('Sensing Clock (MHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);

saveas(h3, 'figs/REID_SEN_consumptionSec.fig');
saveas(h3, 'figs/REID_SEN_consumptionSec.eps', 'epsc');


% 
% h1=figure('Position', [100 100 900 600]);
% display3D(2,2,1,N,M,frSENcess.SENfps,SENclk,SENfps_req, 1e6, 1, ...
%     'ACHIEVED FRAMERATE','Achieved framerate (fps)','f_{clk}^s SENSING (MHz)','Desired framerate (fps)');
% 
% display3D(2,2,2,N,M,energy.SENtot./frSENcess.SENtot,SENclk,SENfps_req, 1e6, 1, ...
%     'ENERGY CONSUMPTION (active+idle)','Energy (mJ/frame)','f_{clk}^{s} (MHz)','Desired framerate (fps)');
% 
% display3D(2,2,3,N,M,energy.SENact./frSENcess.SENtot,SENclk,SENfps_req, 1e6, 1, ...
%     'ENERGY CONSUMPTION (active)','Energy (mJ/frame)','f_{clk}^s SENSING (MHz)','Desired framerate (fps)');
% 
% display3D(2,2,4,N,M,energy.SENidl./frSENcess.SENtot,SENclk,SENfps_req, 1e6, 1, ...
%     'ENERGY CONSUMPTION (idle)','Energy (mJ/frame)','f_{clk}^s SENSING (MHz)','Desired framerate (fps)');
% 
% saveas(h1, 'figs/REID_SEN_consumptionFrames.fig');
% saveas(h1, 'figs/REID_SEN_consumptionFrames.eps', 'epsc');
% 
% h2=figure('Position', [100 100 900 600]);
% display3D(2,2,1,N,M,frSENcess.SENfps,SENclk,SENfps_req, 1e6, 1, ...
%     'Achieved framerate','Achieved framerate (fps)','f_{clk}^s clock (MHz)','Desired framerate (fps)');
% 
% display3D(2,2,2,N,M,energy.SENtot./simTime,SENclk,SENfps_req, 1e6, 1, ...
%     'Active+Idle states','Energy (mJ/s)','f_{clk}^{s} clock (MHz)','Desired framerate (fps)');
% 
% display3D(2,2,3,N,M,energy.SENact./simTime,SENclk,SENfps_req, 1e6, 1, ...
%     'Active state','Energy (mJ/s)','f_{clk}^{s} clock (MHz)','Desired framerate (fps)');
% 
% display3D(2,2,4,N,M,energy.SENidl./simTime,SENclk,SENfps_req, 1e6, 1, ...
%     'Idle state','Energy (mJ/s)','f_{clk}^{s} clock (MHz)','Desired framerate (fps)');
% 
% saveas(h2, 'figs/REID_SEN_consumptionSec.fig');
% saveas(h2, 'figs/REID_SEN_consumptionSec.eps', 'epsc');