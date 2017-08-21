clc; clear all; close all;
addpath('./utils');
rot_angle1 = 15;
rot_angle2 = 25;

%% load data
dataDir = '../res/test2';
res=load_data(dataDir);

%% Preprocess data
%get the CPU frequencies
PROclk=[]; SENclk = []; SENfps_rea = []; SENfps_req = [];
for i=1:numel(res)
    PROclk = [PROclk res(i).PRO.clockfreq];
    SENclk = [SENclk res(i).SEN.clockfreq];
    SENfps_rea = [SENfps_rea res(i).SEN.FPSrea];
    SENfps_req = [SENfps_req res(i).SEN.FPSreq];
end

simTime = max (res(1).t_sim);
PROclk = sort(unique(PROclk), 'ascend');
SENclk = sort(unique(SENclk), 'ascend');
SENfps_req = sort(unique(SENfps_req), 'ascend');

energy.PROtot = zeros(numel(SENfps_req), numel(PROclk));
energy.PROact = zeros(numel(SENfps_req), numel(PROclk));
energy.PROidl = zeros(numel(SENfps_req), numel(PROclk));

frProcess.PROtot = zeros(numel(SENfps_req), numel(PROclk));
frProcess.SENtot = zeros(numel(SENfps_req), numel(PROclk));

numFrSEN = 0;
numFrPRO = 0;
numFrCOM = 0;
count = zeros(numel(SENfps_req), numel(PROclk));
tottime = zeros(numel(SENfps_req), numel(PROclk));
for i=1:numel(res)
        
    indF = find(res(i).SEN.FPSreq==SENfps_req);
    indP = find(res(i).PRO.clockfreq==PROclk);
    count(indF, indP) = count(indF, indP) + 1;
    
    ind_ = find(res(i).t_sim <= 2);
    ind = find(res(i).SEN.eTot > 0);   
    frProcess.SENtot(indF,indP) = frProcess.SENtot(indF,indP) + numel(ind) - numel(ind_)+1;
    
    ind = find(res(i).PRO.eTot > 0);   
    frProcess.PROtot(indF,indP) = frProcess.PROtot(indF,indP) + numel(ind);
    energy.PROtot(indF,indP) = energy.PROtot(indF,indP) + sum(res(i).PRO.eTot(ind));
    energy.PROact(indF,indP) = energy.PROact(indF,indP) + sum(res(i).PRO.eAct(ind));
    energy.PROidl(indF,indP) = energy.PROidl(indF,indP) + sum(res(i).PRO.eIdl(ind));   
    tottime(indF,indP) = res(i).t_sim(end) - res(i).t_sim(ind(1));    
end

%average over multiple runs
energy.PROtot = energy.PROtot./count;
energy.PROact = energy.PROact./count;
energy.PROidl = energy.PROidl./count;
frProcess.PROtot = frProcess.PROtot./count;   
frProcess.SENtot = frProcess.SENtot./count;   

%% plot results - processed frames
[N,M]=meshgrid(PROclk,SENfps_req);
h1=figure(1);
mesh(N,M,100*frProcess.PROtot./frProcess.SENtot); axis tight;
set(gca,'XTick',PROclk, 'XTickLabel',PROclk/1e9,'YTick',SENfps_req, 'YTickLabel',SENfps_req)  % This automatically sets the XTickMode to manual.
title('Frames processed for ARM Cortex A9'); zlabel('Percentage (%)'); xlabel('Processor Clock (GHz)','Rotation',rot_angle1); ylabel('Requested framerate (fps)','Rotation',-rot_angle2);
saveas(h1, 'figs/REID_PRO_processedFrames.fig');
saveas(h1, 'figs/REID_PRO_processedFrames.eps', 'epsc');

%% plot results - active/idle consumption (mJ/frame)
h2=figure('Position', [100 100 1200 300],'PaperPositionMode', 'auto');

subaxis(1,3,1, 'Spacing', 0.1,'Padding', 0, 'MarginLeft', 0.04,'MarginRight', 0);
mesh(N,M,energy.PROtot./frProcess.PROtot); axis tight;
set(gca,'XTick',PROclk, 'XTickLabel',PROclk/1e9,'YTick',SENfps_req, 'YTickLabel',SENfps_req)  % This automatically sets the XTickMode to manual.
title('Active+idle states'); zlabel('Average energy (mJ/frame)'); xlabel('Processor Clock (GHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);

subaxis(1,3,2, 'Spacing', 0.1, 'Padding', 0, 'MarginLeft', 0,'MarginRight', 0); 
mesh(N,M,energy.PROact./frProcess.PROtot); axis tight;
set(gca,'XTick',PROclk, 'XTickLabel',PROclk/1e9,'YTick',SENfps_req, 'YTickLabel',SENfps_req)  % This automatically sets the XTickMode to manual.
title('Active state'); zlabel('Average energy (mJ/frame)'); xlabel('Processor Clock (GHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);

subaxis(1,3,3, 'Spacing', 0.1, 'Padding', 0, 'MarginLeft', 0,'MarginRight', 0.02); 
mesh(N,M,energy.PROidl./frProcess.PROtot); axis tight;
set(gca,'XTick',PROclk, 'XTickLabel',PROclk/1e9,'YTick',SENfps_req, 'YTickLabel',SENfps_req)  % This automatically sets the XTickMode to manual.
title('Idle state'); zlabel('Average energy (mJ/frame)'); xlabel('Processor Clock (GHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);

saveas(h2, 'figs/REID_PRO_consumptionFrame.fig');
saveas(h2, 'figs/REID_PRO_consumptionFrame.eps', 'epsc');

%% plot results - active/idle consumption (mJ/second)
h3=figure('Position', [100 100 1200 300],'PaperPositionMode', 'auto');

subaxis(1,3,1, 'Spacing', 0.1,'Padding', 0, 'MarginLeft', 0.04,'MarginRight', 0);
mesh(N,M,energy.PROtot./tottime); axis tight;
set(gca,'XTick',PROclk, 'XTickLabel',PROclk/1e9,'YTick',SENfps_req, 'YTickLabel',SENfps_req)  % This automatically sets the XTickMode to manual.
title('Active+idle state'); zlabel('Average energy (mJ/s)'); xlabel('Processor Clock (GHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);

subaxis(1,3,2, 'Spacing', 0.1, 'Padding', 0, 'MarginLeft', 0,'MarginRight', 0); 
mesh(N,M,energy.PROact./tottime); axis tight;
set(gca,'XTick',PROclk, 'XTickLabel',PROclk/1e9,'YTick',SENfps_req, 'YTickLabel',SENfps_req)  % This automatically sets the XTickMode to manual.
title('Active state'); zlabel('Average energy (mJ/s)'); xlabel('Processor Clock (GHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);

subaxis(1,3,3, 'Spacing', 0.1, 'Padding', 0, 'MarginLeft', 0,'MarginRight', 0.02); 
mesh(N,M,energy.PROidl./tottime); axis tight;
set(gca,'XTick',PROclk, 'XTickLabel',PROclk/1e9,'YTick',SENfps_req, 'YTickLabel',SENfps_req)  % This automatically sets the XTickMode to manual.
title('Idle state'); zlabel('Average energy (mJ/s)'); xlabel('Processor Clock (GHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);

saveas(h3, 'figs/REID_PRO_consumptionSec.fig');
saveas(h3, 'figs/REID_PRO_consumptionSec.eps', 'epsc');