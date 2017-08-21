% function []=CAWC_plot_coa_energy()
clc; clear all; close all;
addpath('./utils');

%% LOAD AND PREPROCESS DATA
dataDir = '/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/res';
dataDir = '/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/res_P_t09_5s_r50';
dataDir = '/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/res_S_t09_5s_r50';

%load data
[runs,coa]=load_coa_data(dataDir);
[cams.track,ids,cids]=load_cams_data(dataDir);
[cams.usage,ids,cids]=load_cams_consumption(dataDir);

%get the test variables (frequencies)
PROclk=[]; SENclk = []; SENfps_rea = []; SENfps_req = [];simTime=0;
for c=1:size(cams.usage,1)
    for r=1:size(cams.usage,2)
        simTime = max([simTime cams.usage{c,r}.t_sim']);
        PROclk = [PROclk cams.usage{c,r}.PRO.clockfreq];
        SENclk = [SENclk cams.usage{c,r}.SEN.clockfreq];
        SENfps_rea = [SENfps_rea cams.usage{c,r}.SEN.FPSrea];
        SENfps_req = [SENfps_req cams.usage{c,r}.SEN.FPSreq];
    end
end

PROclk = sort(unique(PROclk), 'ascend');
SENclk = sort(unique(SENclk), 'ascend');
SENfps_req = sort(unique(SENfps_req), 'ascend');
SENfps_rea = sort(unique(SENfps_rea), 'ascend');

%% PLOT SENSING-VS-PROCESSING FOR COALITION CAMERAS
en.SENact = zeros(numel(PROclk), numel(SENfps_req)); en.SENact_c = zeros(numel(PROclk), numel(SENfps_req));
en.SENidl = zeros(numel(PROclk), numel(SENfps_req)); en.SENidl_c = zeros(numel(PROclk), numel(SENfps_req));
en.PROact = zeros(numel(PROclk), numel(SENfps_req)); en.PROact_c = zeros(numel(PROclk), numel(SENfps_req));
en.PROidl = zeros(numel(PROclk), numel(SENfps_req)); en.PROidl_c = zeros(numel(PROclk), numel(SENfps_req));
en.COMact = zeros(numel(PROclk), numel(SENfps_req)); en.COMact_c = zeros(numel(PROclk), numel(SENfps_req));
en.COMidl = zeros(numel(PROclk), numel(SENfps_req)); en.COMidl_c = zeros(numel(PROclk), numel(SENfps_req));
en.steps = zeros(numel(PROclk), numel(SENfps_req)); en.time = zeros(numel(PROclk), numel(SENfps_req));

for tt=1:numel(coa)
    
    %current run
    r = find (runs == coa(tt).run);
    
    %find sen&pro clos
    curPROclk = cams.usage{1,r}.PRO.clockfreq;
    curSENclk = cams.usage{1,r}.SEN.clockfreq;
    curSENfps = cams.usage{1,r}.SEN.FPSrea;
    
    acc.SENa=[]; acc.SENi=[]; acc.PROa=[];acc.PROi=[];acc.COMa=[];acc.COMi=[];
    
    time = max(cams.usage{1,r}.t_sim);
    steps = size(coa(tt).res,2); %current step
    for n=2:steps
        
        if (size(coa(tt).res(n),1)*size(coa(tt).res(n),2) > 1)
            error('Error. \nThere should be only one sample to analize')
        end
        
        %Coalition data
        frameID = coa(tt).res(n).frameID;%frame analyzed
        CoaCams = coa(tt).res(n).cam{1}; %coalition cameras
        
        if isempty(CoaCams)
            %find camera & compute average of coalition cameras
            tmp00 = [];tmp01 = [];tmp10 = [];tmp11 = [];tmp20 = [];tmp21 = [];tmp22 = [];
            for i=1:numel(CoaCams)
                p = find (ids == CoaCams(i));
                fr = find (cams.usage{p,r}.frID == frameID);

                %due to different processing times, there is desynchronization
                %and therefore, not all cameras provide results for the same
                %frame. Here we take the times for the previous frame analyzed
                while (cams.usage{p,r}.COM.eIdl(fr) < 0)
                    stop_here=1;               
                    idn=find(cams.usage{p,r}.COM.eIdl(fr:-1:fr-5)>0,1);
                    fr = fr - idn + 1;
                end
                tmp00 = [tmp00 cams.usage{p,r}.SEN.eAct(fr)];
                tmp01 = [tmp01 cams.usage{p,r}.SEN.eIdl(fr)];
                tmp10 = [tmp10 cams.usage{p,r}.PRO.eAct(fr)];
                tmp11 = [tmp11 cams.usage{p,r}.PRO.eIdl(fr)];
                tmp20 = [tmp20 cams.usage{p,r}.COM.eActTX(fr)];
                tmp21 = [tmp21 cams.usage{p,r}.COM.eActRX(fr)];
                tmp22 = [tmp22 cams.usage{p,r}.COM.eIdl(fr)];            
            end
            %tmp00,tmp01,tmp10,tmp11,tmp20,tmp21,tmp22,
            acc.SENa = [acc.SENa mean(tmp00)];
            acc.SENi = [acc.SENi mean(tmp01)];
            acc.PROa = [acc.PROa mean(tmp10)];
            acc.PROi = [acc.PROi mean(tmp11)];
            acc.COMa = [acc.COMa mean(tmp20(:)+tmp21(:))];
            acc.COMi = [acc.COMi mean(tmp22)];
        end
    end
    
    ip = find(PROclk==curPROclk);
    is = find(SENfps_req==curSENfps);
    en.SENact(ip,is) = en.SENact(ip,is) + sum(acc.SENa); en.SENact_c(ip,is) = en.SENact_c(ip,is)+1;
    en.SENidl(ip,is) = en.SENidl(ip,is) + sum(acc.SENi); en.SENact_c(ip,is) = en.SENidl_c(ip,is)+1;
    en.PROact(ip,is) = en.PROact(ip,is) + sum(acc.PROa); en.PROact_c(ip,is) = en.PROact_c(ip,is)+1;
    en.PROidl(ip,is) = en.PROidl(ip,is) + sum(acc.PROi); en.PROidl_c(ip,is) = en.PROidl_c(ip,is)+1;
    en.COMact(ip,is) = en.COMact(ip,is) + sum(acc.COMa); en.COMact_c(ip,is) = en.COMact_c(ip,is)+1;
    en.COMidl(ip,is) = en.COMidl(ip,is) + sum(acc.COMi); en.COMidl_c(ip,is) = en.COMidl_c(ip,is)+1;
    
    en.steps(ip,is) = steps;
    en.time(ip,is) = time;
end
clear tmp*;

%% PLOT DATA - mJ/s & mJ/frame
rot_angle1 = 0; rot_angle2 = 0;
[N,M]=meshgrid(SENfps_req,PROclk);
for i=1:2
    h(i)=figure(i);
    
    switch i
        case 1
            variable = en.time;
            zlab = 'Consumption (mJ/s)';
        case 2
            variable = en.steps;
            zlab = 'Consumption (mJ/frame)';
    end
    
    subplot 231; mesh(N,M,en.SENact./variable); plot_labels_axis('Sensing - active',zlab,PROclk,SENfps_req);
    subplot 232; mesh(N,M,en.PROact./variable); plot_labels_axis('Processing - active',zlab,PROclk,SENfps_req);
    subplot 233; mesh(N,M,en.COMact./variable); plot_labels_axis('Comms - active',zlab,PROclk,SENfps_req);
    subplot 234; mesh(N,M,en.SENidl./variable); plot_labels_axis('Sensing - idle',zlab,PROclk,SENfps_req);
    subplot 235; mesh(N,M,en.PROidl./variable); plot_labels_axis('Processing - idle',zlab,PROclk,SENfps_req);
    subplot 236; mesh(N,M,en.COMidl./variable); plot_labels_axis('Comms - idle',zlab,PROclk,SENfps_req);
end