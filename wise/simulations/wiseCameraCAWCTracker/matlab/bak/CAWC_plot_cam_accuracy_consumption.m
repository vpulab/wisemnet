clear all
close all
clc
addpath 'utils/'

load figs/TrackErrIP_cmp_sensing.mat
load figs/CameraEnergy.mat

figsize= [100, 100, 700, 300];
PROclk = 1.5e9;

%%
f1=figure('Name',sprintf('Tracking GP error for P=%.2fGHz',PROclk(1)/1e9),'Position', figsize);
tmp_m = SEN.err.CAMGPm; %tmp_m(end+1,:,:) = err.COA_GPm; tmp_m=reshape(tmp_m, [Ncams+1 max(size(err.COA_IP))]);
tmp_m=reshape(tmp_m, [SEN.Ncams max(size(SEN.err.COA_IP))]);
%tmp_v = err.CAMGPv; tmp_v(end+1,:,:) = err.COA_GPv; tmp_v=reshape(tmp_v, [Ncams+1 max(size(err.COA_IP))]);
labels=strread(num2str(SEN.fps),'%s');
for ll=1:numel(labels)
    labels{ll} = [labels{ll} ' fps'];
end
b=bar(tmp_m); hold on; 
leg=legend(labels','Orientation','Horizontal','Location','Northoutside');        

labcams=strread(num2str(SEN.cids),'%s');
for ll=1:numel(labcams)
    labcams{ll} = ['Camera ' labcams{ll} ];
end
%         title(sprintf('Tracking GP error for P=%.2fGHz and different framerates',PROclk(1)/1e9));
%set(gca,'XTick',1:Ncams+1, 'XTickLabel',[labels;{'Coalition'}]); 
set(gca,'XTick',1:SEN.Ncams, 'XTickLabel',labcams); 
ylabel('Average tracking error (m)');%xlabel('camera');
box off;  
axis([0.5 numel(SEN.cids)+0.5 0 3.25])
set(gcf,'Units','normal')
set(gca,'Position',[.1 .1 .9 .75])

%%
f2=figure('Name',sprintf('Energy consumption for P=%.2fGHz',PROclk(1)/1e9),'Position', figsize);
data=ENE.dataSEN+ENE.dataPRO+ENE.dataCOM;
data=reshape(data,[ENE.Ncams numel(ENE.fps)]);
bar(data);
set(gca,'XTick',1:SEN.Ncams, 'XTickLabel',labcams); 
ylabel('Average consumption (mJ/sec)');%xlabel('camera');
box off;  
axis([0.5 numel(SEN.cids)+0.5 0 max(max(data))])
set(gcf,'Units','normal')
set(gca,'Position',[.1 .1 .9 .9])

saveas(f1, 'plots/CameraTrack_sen_errGP.eps','epsc'); 
saveas(f2, 'plots/CameraTrack_sen_ene.eps','epsc'); 
 
%%
f3=figure('Name',sprintf('Camera accuracy-consumption for P=%.2fGHz',PROclk(1)/1e9),'Position', [100 100 1300 1000]);
ml = 0.05;
pd = 0.00;
sp = 0.05;

labels=strread(num2str(SEN.fps),'%s');
for ll=1:numel(labels)
    labels{ll} = [labels{ll} 'fps'];
end

offsety=[-0.2 -0.2 -0.2 -0.2 -0.2 -0.1];
offsetx=[ 2 2 2 2 2 -35];
for c=1:ENE.Ncams
    
  dataCam=ENE.dataSEN(c,1,:)+ENE.dataPRO(c,1,:)+ENE.dataCOM(c,1,:);
  dataCam=reshape(dataCam, [numel(dataCam) 1]);
  errCam=SEN.err.CAMGP(c,1,:);  
  errCam_m=SEN.err.CAMGPm(c,1,:); 
  errCam_m=reshape(errCam_m, [numel(dataCam) 1]);
  
  for is=1:numel(SEN.fps)
    errCam_v(is)=std(errCam{1,1,is}); 
  end
  
  %subplot(3,2,c)
  subaxis(3,2,c, 'Spacing', sp, 'PaddingBottom', pd, 'MarginLeft', 1*ml,'MarginRight', 0.5*ml); 
  %plot(dataCam,errCam_m,'+-');
  errorbar(dataCam,errCam_m,errCam_v,'*-','Color',labelcol(c,:));
  box off;
  
%   Xgp=[];Xip=[];
%   for is=1:numel(SEN.fps)
%         Xgp = [Xgp; errCam{1,1,is}];        
%   end         
%   T = bplot(Xgp',dataCam,'points'); legend(T,'location','northeast');

  axis([min(min(data))-25 max(max(data))+25 min(min(SEN.err.CAMGPm)) max(max(SEN.err.CAMGPm))]);
    axis([min(min(data))-25 max(max(data))+25 0.75 max(max(SEN.err.CAMGPm))+.5]);

  xlabel('Average Consumption (mJ/sec)');
  ylabel('Average Tracking Error (m)');  
  tb=text(dataCam+offsetx(c),errCam_m+offsety(c),labels,'FontSize',8);
%   set(gca,'YTick',1.25:0.25:3.25, 'YTickLabel',1.25:0.25:3.25);
%   title(sprintf('Camera %d',SEN.cids(c)));
  
  if c==ENE.Ncams
      tb(5).Position = tb(5).Position - [-40 0 0];
  end
end

%%

offsety=[-0.2 -0.2 -0.2 -0.2 -0.2 -0.1];
offsetx=[ 2 2 2 2 2 -35];
for c=1:ENE.Ncams
    
  dataCam=ENE.dataSEN(c,1,:)+ENE.dataPRO(c,1,:)+ENE.dataCOM(c,1,:);
  dataCam=reshape(dataCam, [numel(dataCam) 1]);
  errCam=SEN.err.CAMGP(c,1,:);  
  errCam_m=SEN.err.CAMGPm(c,1,:); 
  errCam_m=reshape(errCam_m, [numel(dataCam) 1]);
  
  for is=1:numel(SEN.fps)
    errCam_v(is)=std(errCam{1,1,is}); 
  end
  
  fc=figure('Name',sprintf('Camera accuracy-consumption for Camera%d P=%.2fGHz',c, PROclk(1)/1e9),'Position',[100 100 400 300] );  errorbar(dataCam,errCam_m,errCam_v,'*-','Color',labelcol(c,:));
  box off;
  set(gcf,'Units','normal')
  set(gca,'Position',[.12 .15 .89 .9])
%   axis tight;

  axis([min(min(data))-25 max(max(data))+25 min(min(SEN.err.CAMGPm)) max(max(SEN.err.CAMGPm))]);
  axis([min(min(data))-25 max(max(data))+25 0.75 max(max(SEN.err.CAMGPm))+.5]);

  xlabel('Average Consumption (mJ/sec)');
  ylabel('Average Tracking Error (m)');  
  tb=text(dataCam+offsetx(c),errCam_m+offsety(c),labels,'FontSize',8);
%   set(gca,'YTick',1.25:0.25:3.25, 'YTickLabel',1.25:0.25:3.25);
%   title(sprintf('Camera %d',SEN.cids(c)));
  
  if c==ENE.Ncams
      tb(5).Position = tb(5).Position - [-40 0 0];
  end
  
  if c==2
      tb(5).Position = tb(5).Position - [35 0 0];
  end
  
  
  epsfig = hgexport('factorystyle');
  epsfig.Format = 'eps';
  hgexport(gcf,sprintf('plots/CameraTrack_sen_errGP_cam%d.eps',c),epsfig,'Format','eps')
    
  %saveas(fc, sprintf('plots/CameraTrack_sen_errGP_cam%d.eps',c),'epsc'); 
end

%%
f4=figure('Name',sprintf('Camera accuracy-consumption for P=%.2fGHz',PROclk(1)/1e9));
hold on;
%offsety=[-0.1 -0.1 0.05 0.05 0.05 0.05];
%offsetx=[-10 0 0 0 0 0];
labelcol(1,:) = [0 1 1];%cyan
labelcol(2,:) = [1 0.5 0];%orange
labelcol(3,:) = [0 1 0];%green
labelcol(4,:) = [1 0 0];%red
labelcol(5,:) = [1 1 0];%yellow
labelcol(6,:) = [75/255,0,130/255];%purple

for c=1:ENE.Ncams
    
  dataCam=ENE.dataSEN(c,1,:)+ENE.dataPRO(c,1,:)+ENE.dataCOM(c,1,:);
  dataCam=reshape(dataCam, [numel(dataCam) 1]);
  errCam=SEN.err.CAMGP(c,1,:);  
  errCam_m=SEN.err.CAMGPm(c,1,:); 
  errCam_m=reshape(errCam_m, [numel(dataCam) 1]);
  
  for is=1:numel(SEN.fps)
    errCam_v(is)=std(errCam{1,1,is}); 
  end
    
  plot(dataCam,errCam_m,'*-','MarkerFaceColor',labelcol(c,:));
  %errorbar(dataCam,errCam_m,errCam_v,'*','MarkerFaceColor',labelcol(c,:));
  
%   Xgp=[];Xip=[];
%   for is=1:numel(SEN.fps)
%         Xgp = [Xgp; errCam{1,1,is}];        
%   end         
%   T = bplot(Xgp',dataCam,'points'); legend(T,'location','northeast');

  axis([min(min(data))-25 max(max(data))+25 min(min(SEN.err.CAMGPm)) max(max(SEN.err.CAMGPm))]);
  xlabel('Average Consumption (mJ/sec)');
  ylabel('Average Tracking Error (m)');  
  text(dataCam+offsetx(c),errCam_m+offsety(c),labels)
%   set(gca,'YTick',1.25:0.25:3.25, 'YTickLabel',1.25:0.25:3.25);
  title(sprintf('Camera %d',SEN.cids(c)));
  
end

%load figs/TrackErrIP_cmp_processing.mat
%load figs/Coalition_sensing_consumption.mat
%load figs/Coalition_processing_consumption.mat
% 
% PRO.clk = [0.25 0.5 0.75 1 1.25 1.5];
% PROene.clk = [0.25 0.5 0.75 1 1.25 1.5];
% 
% f1a=figure('Position',[100 100 500 300]);
% T = bplot(SEN.Xgp,'points'); legend(T,'location','northeast');
% set(gca,'XTick',1:numel(SEN.fps), 'XTickLabel',SEN.fps);
% axis([0.5 numel(SENene.fps)+0.5 1 4.1]);% axis([0 numel(SENene.fps)+1 0 max(max(SENene.data))]);
% xlabel('Sensing framerate (fps)');   ylabel('Coalition tracking error (m)');
% 
% f1e=figure('Position',[300 300 500 300]);
% bar(SENene.data');
% plot(SENene.data','-*'); hold on; 
% axis([0.5 numel(SENene.fps)+0.5 0 1000]);% axis([0 numel(SENene.fps)+1 0 max(max(SENene.data))]);
% legend('Sensing', 'Processing', 'Comms','Location','NorthWest');
% set(gca,'XTick',1:numel(SENene.fps), 'XTickLabel',strread(num2str(SENene.fps),'%s'));
% xlabel('Sensing framerate (fps)');ylabel('Coalition consumption (mJ/sec)');box off
% 
% % saveas(f1a, 'plots/CoalitionTrack_pro_errGP.eps','epsc'); 
% % saveas(f1e, 'plots/CoalitionTrack_pro_ene.eps','epsc'); 
% 
% 
% f2a=figure('Position',[100 100 500 300]);
% T = bplot(PRO.Xgp','points'); legend(T,'location','northeast');
% set(gca,'XTick',1:numel(PRO.clk), 'XTickLabel',PRO.clk);
% axis([0.5 numel(PRO.clk)+0.5 1 4.1]);% axis([0 numel(SENene.fps)+1 0 max(max(SENene.data))]);
% xlabel('Processor clock (Ghz)');   ylabel('Coalition tracking error (m)');
% 
% f2e=figure('Position',[300 300 500 300]);
% % bar(PROene.data'); hold on; 
% plot(PROene.data','-*'); hold on; 
% axis([0.5 numel(PRO.clk)+0.5 0 1000]);% axis([0 numel(SENene.fps)+1 0 max(max(SENene.data))]);
% legend('Sensing', 'Processing', 'Comms','Location','NorthWest');
% set(gca,'XTick',1:numel(PROene.clk), 'XTickLabel',strread(num2str(PROene.clk),'%s'));
% xlabel('Processor clock (Ghz)');ylabel('Coalition consumption (mJ/sec)');box off