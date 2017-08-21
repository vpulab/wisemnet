clc; clear all; close all;
addpath('./utils');

dataDir = '../res/test3';
% dataDir = './test3';

%load data
res=load_data(dataDir);

%get the CPU frequencies
PROclk=[]; SENclk = []; SENfps_rea = []; SENfps_req = [];
for i=1:numel(res)
    PROclk = [PROclk res(i).PRO.clockfreq];
    SENclk = [SENclk res(i).SEN.clockfreq];
    SENfps_rea = [SENfps_rea res(i).SEN.FPSrea];
    SENfps_req = [SENfps_req res(i).SEN.FPSreq];
end

simTime = max (res(1).t_sim);
PROclk = sort(unique(PROclk), 'descend');
SENclk = sort(unique(SENclk), 'ascend');
SENfps_req = sort(unique(SENfps_req), 'ascend');

energy.COMtot = zeros(numel(SENfps_req),numel(PROclk),numel(SENclk));
energy.PROtot = zeros(numel(SENfps_req),numel(PROclk),numel(SENclk));
energy.PROact = zeros(numel(SENfps_req),numel(PROclk),numel(SENclk));
energy.PROidl = zeros(numel(SENfps_req),numel(PROclk),numel(SENclk));
energy.SENtot = zeros(numel(SENfps_req),numel(PROclk),numel(SENclk));
energy.SENact = zeros(numel(SENfps_req),numel(PROclk),numel(SENclk));
energy.SENidl = zeros(numel(SENfps_req),numel(PROclk),numel(SENclk));

frProcess.PROtot = zeros(numel(SENfps_req),numel(PROclk),numel(SENclk));
frProcess.SENtot = zeros(numel(SENfps_req),numel(PROclk),numel(SENclk));
frProcess.SENtot_fps = zeros(numel(SENfps_req),numel(PROclk),numel(SENclk));

count = zeros(numel(SENfps_req),numel(PROclk),numel(SENclk));
tottime = zeros(numel(SENfps_req),numel(PROclk),numel(SENclk));
for i=1:numel(res)
        
    indF = find(res(i).SEN.FPSreq==SENfps_req);
    indP = find(res(i).PRO.clockfreq==PROclk);
    indS = find(res(i).SEN.clockfreq==SENclk);
    count(indF,indP,indS) = count(indF,indP,indS) + 1;
        
    ind = find(res(i).PRO.eTot > 0);   
    frProcess.PROtot(indF,indP,indS) = frProcess.PROtot(indF,indP,indS) + numel(ind);
    energy.PROtot(indF,indP,indS) = energy.PROtot(indF,indP,indS) + sum(res(i).PRO.eTot(ind));
    energy.PROact(indF,indP,indS) = energy.PROact(indF,indP,indS) + sum(res(i).PRO.eAct(ind));
    energy.PROidl(indF,indP,indS) = energy.PROidl(indF,indP,indS) + sum(res(i).PRO.eIdl(ind));   
    tottime(indF,indP,indS) = res(i).t_sim(end) - res(i).t_sim(ind(1));  
    
    energy.COMtot(indF,indP,indS) = energy.COMtot(indF,indP,indS) + sum(res(i).COM.eTot(ind));
    
    ind_ = find(res(i).t_sim <= 2);
    ind = find(res(i).SEN.eTot > 0);   
    frProcess.SENtot(indF,indP,indS) = frProcess.SENtot(indF,indP,indS) + numel(ind) - numel(ind_)+1;     
    frProcess.SENtot_fps(indF,indP,indS) = frProcess.SENtot_fps(indF,indP,indS) + res(i).SEN.FPSrea;
    
    energy.SENtot(indF,indP,indS) = energy.SENtot(indF,indP,indS) + sum(res(i).SEN.eTot(ind));
    energy.SENact(indF,indP,indS) = energy.SENact(indF,indP,indS) + sum(res(i).SEN.eAct(ind));
    energy.SENidl(indF,indP,indS) = energy.SENidl(indF,indP,indS) + sum(res(i).SEN.eIdl(ind));
end

%average over multiple runs
energy.COMtot = energy.COMtot./count;

energy.PROtot = energy.PROtot./count;
energy.PROact = energy.PROact./count;
energy.PROidl = energy.PROidl./count;

energy.SENtot = energy.SENtot./count;
energy.SENact = energy.SENact./count;
energy.SENidl = energy.SENidl./count;

frProcess.PROtot = frProcess.PROtot./count;   
frProcess.SENtot = frProcess.SENtot./count;   

f1 = figure('Position', [100 100 1200 500],'PaperPositionMode', 'auto');
f2 = figure('Position', [100 100 1200 500],'PaperPositionMode', 'auto');

for i=1:numel(SENfps_req)

    set(0, 'currentfigure', f1);  %# for figures    
    subaxis(numel(SENfps_req),4,(i-1)*4+1, 'Spacing', 0.07,'PaddingBottom', 0.05*(numel(SENfps_req)-i), 'MarginLeft', 0.05,'MarginRight', 0);
    imagesc(reshape(energy.PROtot(i,:,:)./frProcess.PROtot(i,:,:),[numel(PROclk) numel(SENclk)])); colorbar; axis tight;
    set(gca,'YTick',1:numel(PROclk), 'YTickLabel',PROclk/1e9,'XTick',1:numel(SENclk), 'XTickLabel',SENclk/1e6); 
    title('\bf Processing (mJ/frame)'); ylabel('Processor Clock (GHz)'); xlabel('Sensing Clock (MHz)');
    
    subaxis(numel(SENfps_req),4,(i-1)*4+2, 'Spacing', 0.07, 'PaddingBottom', 0.05*(numel(SENfps_req)-i), 'MarginLeft', 0.05,'MarginRight', 0); 
    imagesc(reshape(energy.SENtot(i,:,:)./frProcess.SENtot(i,:,:),[numel(PROclk) numel(SENclk)])); colorbar;axis tight;
    set(gca,'YTick',1:numel(PROclk), 'YTickLabel',PROclk/1e9,'XTick',1:numel(SENclk), 'XTickLabel',SENclk/1e6);  
    %     title(['SENSING (act+idle)' char(10) '(mJ/frame)']);
    title('Sensing (mJ/frame)'); ylabel('Processor Clock (GHz)'); xlabel('Sensing Clock (MHz)');
        
    subaxis(numel(SENfps_req),4,(i-1)*4+3, 'Spacing', 0.07, 'PaddingBottom', 0.05*(numel(SENfps_req)-i), 'MarginLeft', 0.05,'MarginRight', 0); 
    imagesc(reshape(energy.COMtot(i,:,:)./frProcess.PROtot(i,:,:),[numel(PROclk) numel(SENclk)])); colorbar; axis tight;
    set(gca,'YTick',1:numel(PROclk), 'YTickLabel',PROclk/1e9,'XTick',1:numel(SENclk), 'XTickLabel',SENclk/1e6);  
    title(['Comms (mJ/frame)']); ylabel('Processor Clock (GHz)'); xlabel('Sensing Clock (MHz)');
    
    subaxis(numel(SENfps_req),4,(i-1)*4+4, 'Spacing', 0.07, 'PaddingBottom', 0.05*(numel(SENfps_req)-i), 'MarginLeft', 0.05,'MarginRight', 0);     
    energy.TOTtot = energy.SENtot(i,:,:)./frProcess.SENtot(i,:,:)+ energy.PROtot(i,:,:)./frProcess.PROtot(i,:,:) + energy.COMtot(i,:,:)./frProcess.PROtot(i,:,:);
    imagesc(reshape(energy.TOTtot,[numel(PROclk) numel(SENclk)])); colorbar; axis tight;
    set(gca,'YTick',1:numel(PROclk), 'YTickLabel',PROclk/1e9,'XTick',1:numel(SENclk), 'XTickLabel',SENclk/1e6); 
    title(['Accumulated (mJ/frame)']); ylabel('Processor Clock (GHz)'); xlabel('Sensing Clock (MHz)');
    
    
    set(0, 'currentfigure', f2);  %# for figures    
    subaxis(numel(SENfps_req),4,(i-1)*4+1, 'Spacing', 0.07,'PaddingBottom', 0.05*(numel(SENfps_req)-i), 'MarginLeft', 0.05,'MarginRight', 0);
    imagesc(reshape(energy.PROtot(i,:,:)./tottime(i,:,:),[numel(PROclk) numel(SENclk)])); colorbar;
    set(gca,'YTick',1:numel(PROclk), 'YTickLabel',PROclk/1e9,'XTick',1:numel(SENclk), 'XTickLabel',SENclk/1e6);
    title(['Processing (mJ/s)']); ylabel('Processor Clock (GHz)'); xlabel('Sensing Clock (MHz)');
    
    subaxis(numel(SENfps_req),4,(i-1)*4+2, 'Spacing', 0.07, 'PaddingBottom', 0.05*(numel(SENfps_req)-i), 'MarginLeft', 0.05,'MarginRight', 0); 
    imagesc(reshape(energy.SENtot(i,:,:)./tottime(i,:,:),[numel(PROclk) numel(SENclk)])); colorbar;
    set(gca,'YTick',1:numel(PROclk), 'YTickLabel',PROclk/1e9,'XTick',1:numel(SENclk), 'XTickLabel',SENclk/1e6);
    title(['Sensing (mJ/s)']); ylabel('Processor Clock (GHz)'); xlabel('Sensing Clock (MHz)');
    
    subaxis(numel(SENfps_req),4,(i-1)*4+3, 'Spacing', 0.07, 'PaddingBottom', 0.05*(numel(SENfps_req)-i), 'MarginLeft',0.05,'MarginRight', 0); 
    imagesc(reshape(energy.COMtot(i,:,:)./tottime(i,:,:),[numel(PROclk) numel(SENclk)])); colorbar;
    set(gca,'YTick',1:numel(PROclk), 'YTickLabel',PROclk/1e9,'XTick',1:numel(SENclk), 'XTickLabel',SENclk/1e6);
    title(['Comms (mJ/s)']); ylabel('Processor Clock (GHz)'); xlabel('Sensing Clock (MHz)');
    
    subaxis(numel(SENfps_req),4,(i-1)*4+4, 'Spacing', 0.07, 'PaddingBottom', 0.05*(numel(SENfps_req)-i), 'MarginLeft', 0.05,'MarginRight', 0.02);     
    energy.TOTtot = energy.SENtot(i,:,:)./tottime(i,:,:)+ energy.PROtot(i,:,:)./tottime(i,:,:) + energy.COMtot(i,:,:)./tottime(i,:,:);
    imagesc(reshape(energy.TOTtot,[numel(PROclk) numel(SENclk)])); colorbar;
    set(gca,'YTick',1:numel(PROclk), 'YTickLabel',PROclk/1e9,'XTick',1:numel(SENclk), 'XTickLabel',SENclk/1e6);
    title(['Accumulated (mJ/s)']); ylabel('Processor Clock (GHz)'); xlabel('Sensing Clock (MHz)'); 
end
saveas(f1, 'figs/REID_ALL_consumptionFrame.fig');
saveas(f1, 'figs/REID_ALL_consumptionFrame.eps', 'epsc');
saveas(f2, 'figs/REID_ALL_consumptionSec.fig');
saveas(f2, 'figs/REID_ALL_consumptionSec.eps', 'epsc');

% annotation(f1,'textbox',[0.019 0.764 0.0565 0.084],'String',{'5 fps'}, 'EdgeColor','none');
% annotation(f2,'textbox',[0.019 0.764 0.0565 0.084],'String',{'5 fps'}, 'EdgeColor','none');
% annotation(f1,'textbox',[0.025 0.23 0.0565 0.084],'String',{'20 fps'}, 'EdgeColor','none');
% annotation(f2,'textbox',[0.025 0.23 0.0565 0.084],'String',{'20 fps'}, 'EdgeColor','none');