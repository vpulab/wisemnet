% function []=CAWC_plot_cam_resUsage()
clc; clear all; close all;
addpath('./utils');

% LOAD AND PREPROCESS DATA
dataDir = '/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/res';
dataDir = '/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/res_SP_t09_5s_r50';
% dataDir = '/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/res_S_t09_5s_r50';
dataDir = '/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/res_S_t09_5s_r50_f4';


%load data
[cams.track,ids,cids]=load_cams_data(dataDir);
[cams.usage,ids,cids]=load_cams_consumption(dataDir);

[Ncams,Nruns,PROclk,SENclk,optFactor,SENfps_req,SENfps_rea,comparedFrames] = preprocess_data(cams);

%% COMPUTE SENSING-VS-PROCESSING FOR COALITION CAMERAS
ti.SENact = zeros(Ncams, numel(PROclk), numel(SENfps_req)); 
ti.PROact = zeros(Ncams, numel(PROclk), numel(SENfps_req)); 
ti.PROmis = zeros(Ncams, numel(PROclk), numel(SENfps_req)); 
ti.COMact = zeros(Ncams, numel(PROclk), numel(SENfps_req));
ti.COMactMax = zeros(Ncams, numel(PROclk), numel(SENfps_req));

en.SENact = zeros(Ncams, numel(PROclk), numel(SENfps_req)); 
en.SENidl = zeros(Ncams, numel(PROclk), numel(SENfps_req)); 
ti.SEN_r = zeros(Ncams,numel(PROclk), numel(SENfps_req));
en.PROact = zeros(Ncams,numel(PROclk), numel(SENfps_req)); 
en.PROidl = zeros(Ncams,numel(PROclk), numel(SENfps_req)); 
ti.PRO_r = zeros(Ncams,numel(PROclk), numel(SENfps_req));
en.COMact = zeros(Ncams,numel(PROclk), numel(SENfps_req)); 
en.COMidl = zeros(Ncams,numel(PROclk), numel(SENfps_req)); 
ti.COMmax_r = zeros(Ncams,numel(PROclk), numel(SENfps_req));
ti.COM_r = zeros(Ncams,numel(PROclk), numel(SENfps_req));

en.steps = zeros(Ncams,numel(PROclk), numel(SENfps_req)); 
en.time = zeros(Ncams,numel(PROclk), numel(SENfps_req));
en.SEN.steps = zeros(Ncams, numel(PROclk), numel(SENfps_req)); 
en.PRO.steps = zeros(Ncams, numel(PROclk), numel(SENfps_req)); 
en.time = zeros(Ncams, numel(PROclk), numel(SENfps_req));

%selected camera to plot results
for c=1:Ncams
    a=1;
    for r=1:Nruns

        %find sen&pro clos
        curPROclk = cams.usage{c,r}.PRO.clockfreq;
        curSENclk = cams.usage{c,r}.SEN.clockfreq;
        curSENfps = cams.usage{c,r}.SEN.FPSrea;

        ip = find(PROclk==curPROclk);
        is = find(SENfps_req==curSENfps);
        
        ind1 = find(cams.usage{c,r}.SEN.eAct > 0);
        en.SEN.steps(c,ip,is) =en.SEN.steps(c,ip,is)+ numel(ind1);
        ti.SENact(c,ip,is) = ti.SENact(c,ip,is) + sum(size(cams.usage{c,r}.SEN.eAct,1)*cams.usage{c,r}.SEN.Tact); 
        ti.SEN_r(c,ip,is) = ti.SEN_r(c,ip,is)+1;
        
        ind = find(cams.usage{c,r}.PRO.eAct > 0);
        en.PRO.steps(c,ip,is) = en.PRO.steps(c,ip,is) + numel(ind);
        ti.PROact(c,ip,is) = ti.PROact(c,ip,is) + sum(cams.usage{c,r}.PRO.TimeO(ind)*1e-3); 
        ti.PRO_r(c,ip,is) = ti.PRO_r(c,ip,is)+1;
        ti.PROmis(c,ip,is) = ti.PROmis(c,ip,is) + abs(numel(ind)-numel(ind1));

        allocBitrate = 250000*1/8*1/curSENfps;%bitrate in bytes/sec
        tmp = (cams.usage{c,r}.COM.TXdone(ind)+cams.usage{c,r}.COM.RXdone(ind)-128)/allocBitrate;       
        ti.COMactMax(c,ip,is) = ti.COMactMax(c,ip,is) + mean(tmp);         
        ti.COMmax_r(c,ip,is) = ti.COMmax_r(c,ip,is)+1;
        ti.COMact(c,ip,is) = ti.COMact(c,ip,is) + sum(tmp); 
%         ti.COMact(c,ip,is) = ti.COMact(c,ip,is) + sum(cams.usage{c,r}.COM.eActTX(ind)+cams.usage{c,r}.COM.eActRX(ind)); 
        ti.COM_r(c,ip,is) = ti.COM_r(c,ip,is) + 1;
%         [cams.usage{c,r}.PRO.clockfreq/1e9 cams.usage{c,r}.SEN.FPSrea sum(tmp)]

        en.SENact(c,ip,is) = en.SENact(c,ip,is) + sum(cams.usage{c,r}.SEN.eAct(ind)); 
        %en.SENact_c(c,ip,is) = en.SENact_c(c,ip,is)+numel(ind);
        en.SENidl(c,ip,is) = en.SENidl(c,ip,is) + sum(cams.usage{c,r}.SEN.eIdl(ind));
        %en.SENact_c(c,ip,is) = en.SENidl_c(c,ip,is)+numel(ind);
        en.PROact(c,ip,is) = en.PROact(c,ip,is) + sum(cams.usage{c,r}.PRO.eAct(ind));
        %en.PROact_c(c,ip,is) = en.PROact_c(c,ip,is)+numel(ind);
        en.PROidl(c,ip,is) = en.PROidl(c,ip,is) + sum(cams.usage{c,r}.PRO.eIdl(ind)); 
        %en.PROidl_c(c,ip,is) = en.PROidl_c(c,ip,is)+numel(ind);

        cams.usage{c,r}.COM.eAct = cams.usage{c,r}.COM.eActTX + cams.usage{c,r}.COM.eActRX;
        en.COMact(c,ip,is) = en.COMact(c,ip,is) + sum(cams.usage{c,r}.COM.eAct(ind));
        %en.COMact_c(c,ip,is) = en.COMact_c(c,ip,is)+numel(ind);
        en.COMidl(c,ip,is) = en.COMidl(c,ip,is) + sum(cams.usage{c,r}.COM.eIdl(ind)); 
        %en.COMidl_c(c,ip,is) = en.COMidl_c(c,ip,is)+numel(ind);
        
        en.frames(c,ip,is) =  numel(cams.usage{c,r}.PRO.TimeO);
        en.time(c,ip,is) = max(cams.usage{c,r}.t_sim);
    end
end
ti.SENact = ti.SENact./ti.SEN_r;
ti.PROact = ti.PROact./ti.PRO_r;
ti.COMact = ti.COMact./ti.COM_r;
ti.COMactMax = ti.COMactMax./ti.COMmax_r;
ti.PROmis = ti.PROmis./ti.PRO_r;

%% PLOT DATA FOR EACH CAMERA - mJ/s
rot_angle1 = 0; rot_angle2 = 0;
[N,M]=meshgrid(SENfps_req,PROclk);
for c=1:Ncams
    h=figure('Name',sprintf('Resource usage for camera %03d',c));
    subplot 141; mesh(N,M,reshape(100*ti.SENact(c,:,:)./en.time(c,:,:),[numel(PROclk) numel(SENfps_req)])); plot_labels_axis('Sensing','Capability usage (%)',PROclk,SENfps_req); %axis(limits);
    subplot 142; mesh(N,M,reshape(100*ti.PROact(c,:,:)./en.time(c,:,:),[numel(PROclk) numel(SENfps_req)])); plot_labels_axis('Processing','Capability usage (%)',PROclk,SENfps_req); %axis(limits);
    subplot 143; mesh(N,M,reshape(100*ti.PROmis(c,:,:)./en.frames(c,:,:),[numel(PROclk) numel(SENfps_req)])); plot_labels_axis('Processing','Missed frames (%)',PROclk,SENfps_req);%axis(limits);
    subplot 144; mesh(N,M,reshape(100*ti.COMact(c,:,:),[numel(PROclk) numel(SENfps_req)])); plot_labels_axis('Comms','Bandwidth Usage (%)',PROclk,SENfps_req); %axis(limits);
end


%% PLOT DATA FOR ALL CAMERAS - mJ/s
ml = 0.05;
pd = 0.05;
sp = 0.05;

h=figure('Name','Resource usage for all cameras (sensing)','Position', [100, 100, 800, 500]);
mesh(N,M,reshape(max(100*ti.SENact./en.time,[],1),[numel(PROclk) numel(SENfps_req)])); 
plot_labels_axis(' ','Maximum load  (%)',PROclk,SENfps_req); view([-60 30]); %axis(limits); 
saveas(h,'figs/camera_resources_sen.eps','epsc');
saveas(h,'figs/camera_resources_sen.fig');

h=figure('Name','Resource usage for all cameras (processing)','Position', [100, 100, 800, 450]);
subaxis(1,2,1, 'Spacing', sp, 'PaddingBottom', pd, 'MarginLeft', 1.5*ml,'MarginRight', 3*ml); 
mesh(N,M,reshape(max(100*ti.PROact./en.time,[],1),[numel(PROclk) numel(SENfps_req)])); 
view([-60 30]); plot_labels_axis(' ','Average load (%)',PROclk,SENfps_req); %axis(limits);
subaxis(1,2,2, 'Spacing', sp, 'PaddingBottom', pd, 'MarginLeft', 2*ml,'MarginRight',  ml); 
mesh(N,M,reshape(max(100*ti.PROmis./en.frames,[],1),[numel(PROclk) numel(SENfps_req)])); 
view([-60 30]); plot_labels_axis(' ','Maximum missed frames (%)',PROclk,SENfps_req);%axis(limits);
saveas(h,'figs/camera_resources_pro.eps','epsc');
saveas(h,'figs/camera_resources_pro.fig');

h=figure('Name','Resource usage for all cameras (comms)','Position', [100, 100, 800, 450]);
subaxis(1,2,1, 'Spacing', sp, 'PaddingBottom', pd, 'MarginLeft', 1.5*ml,'MarginRight', 3*ml); 
mesh(N,M,reshape(max(ti.COMact./en.time,[],1),[numel(PROclk) numel(SENfps_req)])); 
view([-60 30]); plot_labels_axis(' ','Average load (%)',PROclk,SENfps_req); %axis(limits);
subaxis(1,2,2, 'Spacing', sp, 'PaddingBottom', pd, 'MarginLeft', 2*ml,'MarginRight',  ml); 
mesh(N,M,reshape(max(100*ti.COMactMax,[],1),[numel(PROclk) numel(SENfps_req)])); 
view([-60 30]); plot_labels_axis(' ','Maximum Bandwidth Usage (%)',PROclk,SENfps_req);%axis(limits);
saveas(h,'figs/camera_resources_com.eps','epsc');
saveas(h,'figs/camera_resources_com.fig');

% h=figure('Name','Mean resource usage for all cameras');
% subplot 221; mesh(N,M,reshape(mean(100*ti.SENact./en.time,1),[numel(PROclk) numel(SENfps_req)])); plot_labels_axis('Sensing','Capability usage (%)',PROclk,SENfps_req); %axis(limits);
% subplot 222; mesh(N,M,reshape(mean(100*ti.PROact./en.time,1),[numel(PROclk) numel(SENfps_req)])); plot_labels_axis('Processing','Capability usage (%)',PROclk,SENfps_req); %axis(limits);
% subplot 223; mesh(N,M,reshape(mean(100*ti.PROmis./en.frames,1),[numel(PROclk) numel(SENfps_req)])); plot_labels_axis('Processing','Missed frames (%)',PROclk,SENfps_req);%axis(limits);
% subplot 224; mesh(N,M,reshape(mean(100*ti.COMact,1),[numel(PROclk) numel(SENfps_req)])); plot_labels_axis('Comms','Bandwidth Usage (%)',PROclk,SENfps_req); %axis(limits);
% saveas(h,'camera_resources.eps','epsc');
% saveas(h,'camera_resources.fig');

ENE.Ncams = Ncams;
ENE.Nruns = Nruns;
ENE.dataSEN = (en.SENact+en.SENidl)./(en.time.*ti.SEN_r);
ENE.dataPRO = (en.PROact+en.PROidl)./(en.time.*ti.SEN_r);
ENE.dataCOM = (en.COMact+en.COMidl)./(en.time.*ti.SEN_r);
ENE.fps = SENfps_req;
ENE.clk = PROclk;       
save figs/CameraEnergy.mat ENE;