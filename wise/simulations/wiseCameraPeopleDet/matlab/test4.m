% TEST FOR 'Requested framerate' versus 'operating frequency PRO'

clc; clear all; close all;
addpath('./utils');

%% LOAD 
dataDir = '../res/test4';
% dataDir = './test4';

%load data
res=load_data(dataDir);

%% PREPROCESS DATA
rot_angle1 = 15;
rot_angle2 = 25;

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

%% GENERATE VARIABLES TO PLOT
energy.PROtot = zeros(numel(SENfps_req), numel(PROclk));
energy.PROact = zeros(numel(SENfps_req), numel(PROclk));
energy.PROidl = zeros(numel(SENfps_req), numel(PROclk));
energy.COMtot = zeros(numel(SENfps_req), numel(PROclk));
energy.COMact = zeros(numel(SENfps_req), numel(PROclk));
energy.COMidl = zeros(numel(SENfps_req), numel(PROclk));

frProcess.TXraw = zeros(numel(SENfps_req), numel(PROclk));
frProcess.CompRatio = zeros(numel(SENfps_req), numel(PROclk));
frProcess.TXreq = zeros(numel(SENfps_req), numel(PROclk));
frProcess.TXdone = zeros(numel(SENfps_req), numel(PROclk));
frProcess.Tactive = zeros(numel(SENfps_req), numel(PROclk));
frProcess.Tframe = zeros(numel(SENfps_req), numel(PROclk));
frProcess.nByteTXmax = 0;
frProcess.nByteTXmin = Inf;
frProcess.PROtotFrames = zeros(numel(SENfps_req), numel(PROclk));
frProcess.SENtotFrames = zeros(numel(SENfps_req), numel(PROclk));

numFiles = zeros(numel(SENfps_req), numel(PROclk));
tottime = zeros(numel(SENfps_req), numel(PROclk));

datarate = 250000;
for i=1:numel(res)
        
    indF = find(res(i).SEN.FPSreq==SENfps_req);
    indP = find(res(i).PRO.clockfreq==PROclk);    
    
    numFiles(indF,indP) = numFiles(indF,indP) + 1;
    
    ind_ = find(res(i).t_sim <= 2);
    ind = find(res(i).SEN.eTot > 0);   
    frProcess.SENtotFrames(indF,indP) = frProcess.SENtotFrames(indF,indP) + numel(ind) - numel(ind_)+1;
    
    ind = find(res(i).PRO.eTot > 0); 
    frProcess.PROtotFrames(indF,indP) = frProcess.PROtotFrames(indF,indP) + numel(ind);
    energy.PROtot(indF,indP) = energy.PROtot(indF,indP) + sum(res(i).PRO.eTot(ind));
    energy.PROact(indF,indP) = energy.PROact(indF,indP) + sum(res(i).PRO.eAct(ind));
    energy.PROidl(indF,indP) = energy.PROidl(indF,indP) + sum(res(i).PRO.eIdl(ind));   
    
    tottime(indF,indP) = res(i).t_sim(end) - res(i).t_sim(ind(1));    
    
    frProcess.TXraw(indF,indP) = frProcess.TXraw(indF,indP)+ sum(res(i).COM.TXraw(ind));
    frProcess.TXreq(indF,indP) = frProcess.TXreq(indF,indP)+ sum(res(i).COM.TXreq(ind));
    frProcess.TXdone(indF,indP) = frProcess.TXdone(indF,indP)+ sum(res(i).COM.TXdone(ind));
    frProcess.CompRatio(indF,indP) = frProcess.CompRatio(indF,indP)+ sum(res(i).COM.CompRatio(ind));    
    frProcess.nByteTXmax = max(frProcess.nByteTXmax, max(max(res(i).COM.TXdone(ind))));
    frProcess.nByteTXmin = min(frProcess.nByteTXmin, min(min(res(i).COM.TXdone(ind))));
    energy.COMtot(indF,indP) = energy.COMtot(indF,indP) + sum(res(i).COM.eTot(ind));
    energy.COMact(indF,indP) = energy.COMact(indF,indP) + sum(res(i).COM.eActTX(ind));
    energy.COMidl(indF,indP) = energy.COMidl(indF,indP) + sum(res(i).COM.eIdl(ind));   
    
    Tframe = 1/res(i).SEN.FPSrea;
    Tactive = (8*res(i).COM.TXdone(ind))./datarate;
    frProcess.Tactive(indF,indP) = frProcess.Tactive(indF,indP) + sum(Tactive);
    frProcess.Tframe(indF,indP) = Tframe;  
end

%average over multiple runs
energy.PROtot = energy.PROtot./numFiles;
energy.PROact = energy.PROact./numFiles;
energy.PROidl = energy.PROidl./numFiles;
energy.COMtot = energy.COMtot./numFiles;
energy.COMact = energy.COMact./numFiles;
energy.COMidl = energy.COMidl./numFiles;

frProcess.PROtotFrames = frProcess.PROtotFrames./numFiles;   
frProcess.SENtotFrames = frProcess.SENtotFrames./numFiles; 
frProcess.TXreq = frProcess.TXreq./numFiles;
frProcess.TXdone = frProcess.TXdone./numFiles;
frProcess.TXraw = frProcess.TXdone./numFiles;
frProcess.Tactive = frProcess.Tactive./numFiles;
frProcess.CompRatio = frProcess.CompRatio./numFiles;
%frProcess.Tactive = frProcess.Tactive./frProcess.PROtotFrames;

%% PLOT RESULTS
[N,M]=meshgrid(PROclk,SENfps_req);

h0 = figure('Position', [100 100 900 400],'PaperPositionMode', 'auto');
subaxis(1,2,1, 'Spacing', 0.1,'Padding', 0, 'MarginLeft', 0.1,'MarginRight', 0.05);
mesh(N,M,8e-3*frProcess.TXdone./tottime); axis tight;
set(gca,'XTick',PROclk, 'XTickLabel',PROclk/1e9); 
title('\bf Communication per second (max 250kbps)');
% title('Communication - data TX per second'); % title(sprintf('Communication - data TX per second (min=%.3fKB, max=%.1fKB)',1e-3*frProcess.nByteTXmin,1e-3*frProcess.nByteTXmax)); 
zlabel('Average datarate (Kbps)'); xlabel('Processor Clock (GHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);

subaxis(1,2,2, 'Spacing', 0.1,'Padding', 0, 'MarginLeft', 0.1,'MarginRight', 0.05);
mesh(N,M,8e-3*frProcess.TXdone./frProcess.PROtotFrames); axis([PROclk(1) PROclk(end) SENfps_req(1) SENfps_req(end) 1 10]); %axis tight; 
set(gca,'XTick',PROclk, 'XTickLabel',PROclk/1e9); 
% title(sprintf('Communication - data TX per frame (min=%.3fKB, max=%.1fKB)',1e-3*frProcess.nByteTXmin,1e-3*frProcess.nByteTXmax)); 
title('\bf Communication per frame (max 250kbps/Tframe)');
zlabel('Average datarate (Kb/frame)'); xlabel('Processor Clock (GHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);
saveas(h0, 'figs/REID_COM_TXData.fig');
saveas(h0, 'figs/REID_COM_TXData.eps', 'epsc');

h1 = figure('Position', [100 100 900 400],'PaperPositionMode', 'auto');
subaxis(1,2,1, 'Spacing', 0.1,'Padding', 0, 'MarginLeft', 0.1,'MarginRight', 0.05);
mesh(N,M,energy.COMtot./tottime); axis tight;
set(gca,'XTick',PROclk, 'XTickLabel',PROclk/1e9); 
title('\bf Communication consumption per second');
% title('Communication - data TX per second'); % title(sprintf('Communication - data TX per second (min=%.3fKB, max=%.1fKB)',1e-3*frProcess.nByteTXmin,1e-3*frProcess.nByteTXmax)); 
zlabel('Average energy (mJ/s)'); xlabel('Processor Clock (GHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);

subaxis(1,2,2, 'Spacing', 0.1,'Padding', 0, 'MarginLeft', 0.1,'MarginRight', 0.05);
mesh(N,M,energy.COMtot./frProcess.PROtotFrames); axis([PROclk(1) PROclk(end) SENfps_req(1) SENfps_req(end) 1 8]); %axis tight;
set(gca,'XTick',PROclk, 'XTickLabel',PROclk/1e9); 
% title(sprintf('Communication - data TX per frame (min=%.3fKB, max=%.1fKB)',1e-3*frProcess.nByteTXmin,1e-3*frProcess.nByteTXmax)); 
title('\bf Communication consumption per frame');
zlabel('Average energy (mJ/frame)'); xlabel('Processor Clock (GHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);
saveas(h1, 'figs/REID_COM_Energy.fig');
saveas(h1, 'figs/REID_COM_Energy.eps', 'epsc');

h2=figure;
mesh(N,M,min(100, 100*frProcess.Tactive./tottime)); axis tight;
set(gca,'XTick',PROclk, 'XTickLabel',PROclk/1e9); 
title('\bf Communication - bandwidth performance (max 250kbps)'); zlabel('Bandwidth usage (%)'); xlabel('Processor Clock (GHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);
saveas(h2, 'figs/REID_COM_bwUsage.fig');
saveas(h2, 'figs/REID_COM_bwUsage.eps', 'epsc');

h3=figure;
mesh(N,M,100*(1-frProcess.CompRatio./frProcess.PROtotFrames)); axis tight;
set(gca,'XTick',PROclk, 'XTickLabel',PROclk/1e9); 
title('\bf Communication - Huffman compression'); zlabel('Compression ratio (%)'); xlabel('Processor Clock (GHz)','Rotation',rot_angle1); ylabel('Framerate (fps)','Rotation',-rot_angle2);
saveas(h3, 'figs/REID_COM_compression.fig');
saveas(h3, 'figs/REID_COM_compression.eps', 'epsc');
