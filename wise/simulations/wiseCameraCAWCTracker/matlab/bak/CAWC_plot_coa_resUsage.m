% function []=CAWC_plot_coa_resUsage()
clc; clear all; close all;
addpath('./utils');

%% LOAD AND PREPROCESS DATA
% dataDir = '/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/res_P_t09_5s_r50_f4';
dataDir = '/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/res_S_t09_5s_r50_f4';

[runs,coa]=load_coa_data(dataDir); %coalition tracking data
[cams.track,ids,cids]=load_cams_data(dataDir);
[cams.usage,ids,cids]=load_cams_consumption(dataDir);
%
[Ncams,Nruns,PROclk,SENclk,optFactor,SENfps_req,SENfps_rea,comparedFrames] = preprocess_data(cams);

%% PLOT SENSING-VS-PROCESSING FOR COALITION CAMERAS
en.SENact = zeros(numel(PROclk), numel(SENfps_req)); en.SENact_c = zeros(numel(PROclk), numel(SENfps_req));
en.SENidl = zeros(numel(PROclk), numel(SENfps_req)); en.SENidl_c = zeros(numel(PROclk), numel(SENfps_req));
en.PROact = zeros(numel(PROclk), numel(SENfps_req)); en.PROact_c = zeros(numel(PROclk), numel(SENfps_req));
en.PROidl = zeros(numel(PROclk), numel(SENfps_req)); en.PROidl_c = zeros(numel(PROclk), numel(SENfps_req));
en.COMact = zeros(numel(PROclk), numel(SENfps_req)); en.COMact_c = zeros(numel(PROclk), numel(SENfps_req));
en.COMidl = zeros(numel(PROclk), numel(SENfps_req)); en.COMidl_c = zeros(numel(PROclk), numel(SENfps_req));
en.steps = zeros(numel(PROclk), numel(SENfps_req)); en.time = zeros(numel(PROclk), numel(SENfps_req));
en.nSize = zeros(numel(PROclk), numel(SENfps_req));
en.time = zeros(numel(PROclk), numel(SENfps_req));
ti.accTime= zeros(numel(PROclk), numel(SENfps_req));

en.nCoa = zeros(numel(PROclk), numel(SENfps_req));
en.SENtot = zeros(numel(PROclk), numel(SENfps_req)); en.SENtot_r = zeros(numel(PROclk), numel(SENfps_req));
en.PROtot = zeros(numel(PROclk), numel(SENfps_req)); en.PROtot_r = zeros(numel(PROclk), numel(SENfps_req));
en.COMtot = zeros(numel(PROclk), numel(SENfps_req)); en.COMtot_r = zeros(numel(PROclk), numel(SENfps_req));
en.COMtot_bits = zeros(numel(PROclk), numel(SENfps_req)); en.COMtot_bits_c = zeros(numel(PROclk), numel(SENfps_req));

for tt=1:numel(coa)
    
    %current run
    r = find (runs == coa(tt).run);
    
    %find sen&pro clos
    curPROclk = cams.usage{1,r}.PRO.clockfreq;
    curSENclk = cams.usage{1,r}.SEN.clockfreq;
    curSENfps = cams.usage{1,r}.SEN.FPSrea;
    
    acc.mSENa=[]; acc.mSENi=[]; acc.mPROa=[];acc.mPROi=[];acc.mCOMa=[];acc.mCOMi=[];
    acc.mSEN=[]; acc.mPRO=[];acc.mCOM=[];
    acc.tSEN=[];acc.tPRO=[];acc.tCOM=[];acc.tCOMbits=[];
    
    time = max(cams.usage{1,r}.t_sim);
    steps = size(coa(tt).res,2); %current step
    nCoa=0;
    nSize = [];
    ratio = [];
    for n=2:steps
        
        if (size(coa(tt).res(n),1)*size(coa(tt).res(n),2) > 1)
            error('Error. \nThere should be only one sample to analize')
        end
        
        %Coalition data
        frameID = coa(tt).res(n).frameID;%frame analyzed
        CoaCams = coa(tt).res(n).cam{1}; %coalition cameras
        
        if ~isnan(CoaCams)
            
            %find camera & compute average of coalition cameras
            tmp00=[];tmp01=[];tmp10=[];tmp11=[];tmp20=[];tmp21=[];tmp22=[];tmp23=[];tmp24=[];
            for i=1:numel(CoaCams)
                p = find (ids == CoaCams(i));
                fr = find (cams.usage{p,r}.frID == frameID);
                
                k=0;
                while isempty(fr)
                    k=k+1;
                    fr = find (cams.usage{p,r}.frID+k == frameID);
                end
                
                %due to different processing times, there is desynchronization
                %and therefore, not all cameras provide results for the same
                %frame. Here we take the times for the previous frame analyzed
                while (cams.usage{p,r}.COM.eIdl(fr) < 0)
                    fr = fr - 1;
                end
                tmp00 = [tmp00 cams.usage{p,r}.SEN.eAct(fr)];
                tmp01 = [tmp01 cams.usage{p,r}.SEN.eIdl(fr)];
                tmp10 = [tmp10 cams.usage{p,r}.PRO.eAct(fr)];
                %tmp10 = [tmp10 cams.usage{p,r}.PRO.eCol(fr)];
                tmp11 = [tmp11 cams.usage{p,r}.PRO.eIdl(fr)];
                tmp20 = [tmp20 cams.usage{p,r}.COM.eActTX(fr)];
                tmp21 = [tmp21 cams.usage{p,r}.COM.eActRX(fr)];
                tmp22 = [tmp22 cams.usage{p,r}.COM.eIdl(fr)];
                
                tmp23 = [tmp23 cams.usage{p,r}.COM.TXdone(fr)];
                tmp24 = [tmp24 cams.usage{p,r}.COM.RXdone(fr)];
            end
            %tmp00,tmp01,tmp10,tmp11,tmp20,tmp21,tmp22,
            acc.mSENa = [acc.mSENa mean(tmp00)];
            acc.mSENi = [acc.mSENi mean(tmp01)];
            acc.mPROa = [acc.mPROa mean(tmp10)];
            acc.mPROi = [acc.mPROi mean(tmp11)];
            acc.mCOMa = [acc.mCOMa mean(tmp20(:)+tmp21(:))];
            acc.mCOMi = [acc.mCOMi mean(tmp22)];
            
            acc.tSEN = [acc.tSEN sum(tmp00+tmp01)];
            acc.mSEN = [acc.mSEN mean(tmp00+tmp01)];
            acc.tPRO = [acc.tPRO sum(tmp10+tmp11)];
            acc.mPRO = [acc.mPRO mean(tmp10+tmp11)];
            acc.tCOM = [acc.tCOM sum(tmp20+tmp21+tmp22)];
            acc.mCOM = [acc.mCOM mean(tmp20+tmp21+tmp22)];
            allocBitrate = 250000*1/curSENfps;
            acc.tCOMbits = [acc.tCOMbits sum(tmp23+tmp24)/allocBitrate];
            
            %sum(tmp00+tmp01)/sum(tmp10+tmp11)
            nCoa = nCoa +1;
            nSize = [nSize numel(CoaCams)];
            
            fprintf('tt=%03d s=%03d: NCams=%d sen=%.2f pro=%.2f com=%.2f\n',tt,n,numel(CoaCams),  sum(tmp00+tmp01)/numel(CoaCams), sum(tmp10+tmp11)/numel(CoaCams), sum(tmp20+tmp21+tmp22)/numel(CoaCams));
        else
            fprintf('run=%d step=%d -> Empty coalition\n',tt,n);
        end
    end
    ip = find(PROclk==curPROclk);
    is = find(SENfps_req==curSENfps);
    en.SENact(ip,is) = en.SENact(ip,is) + sum(acc.mSENa); en.SENact_c(ip,is) = en.SENact_c(ip,is)+1;
    en.SENidl(ip,is) = en.SENidl(ip,is) + sum(acc.mSENi); en.SENact_c(ip,is) = en.SENidl_c(ip,is)+1;
    en.PROact(ip,is) = en.PROact(ip,is) + sum(acc.mPROa); en.PROact_c(ip,is) = en.PROact_c(ip,is)+1;
    en.PROidl(ip,is) = en.PROidl(ip,is) + sum(acc.mPROi); en.PROidl_c(ip,is) = en.PROidl_c(ip,is)+1;
    en.COMact(ip,is) = en.COMact(ip,is) + sum(acc.mCOMa); en.COMact_c(ip,is) = en.COMact_c(ip,is)+1;
    en.COMidl(ip,is) = en.COMidl(ip,is) + sum(acc.mCOMi); en.COMidl_c(ip,is) = en.COMidl_c(ip,is)+1;
    
    if isnan(acc.mSENa)
        a=1;
    end
    
    ti.accTime(ip,is)=ti.accTime(ip,is)+time*nCoa/steps;
    en.time(ip,is)=time;
    
    en.SENtot(ip,is) = en.SENtot(ip,is) + sum(acc.tSEN); en.SENtot_r(ip,is) = en.SENtot_r(ip,is)+1;
    en.PROtot(ip,is) = en.PROtot(ip,is) + sum(acc.tPRO); en.PROtot_r(ip,is) = en.PROtot_r(ip,is)+1;
    en.COMtot(ip,is) = en.COMtot(ip,is) + sum(acc.tCOM); en.COMtot_r(ip,is) = en.COMtot_r(ip,is)+1;
    %     en.SENtot(ip,is) = en.SENtot(ip,is) + mean(acc.tSEN); en.SENtot_r(ip,is) = en.SENtot_r(ip,is)+1;
    %     en.PROtot(ip,is) = en.PROtot(ip,is) + mean(acc.tPRO); en.PROtot_r(ip,is) = en.PROtot_r(ip,is)+1;
    %     en.COMtot(ip,is) = en.COMtot(ip,is) + mean(acc.tCOM); en.COMtot_r(ip,is) = en.COMtot_r(ip,is)+1;
    en.COMtot_bits(ip,is) = en.COMtot_bits(ip,is) + mean(acc.tCOMbits); en.COMtot_bits_c(ip,is) = en.COMtot_bits_c(ip,is)+1;
    
    %     ratio = [ratio sum(acc.tSEN)/sum(acc.tPRO)]
    %     nSize
    en.nCoa(ip,is) = en.nCoa(ip,is) + nCoa;
    en.steps(ip,is) = steps;
    en.nSize(ip,is) = en.nSize(ip,is) + mean(nSize);
end
clear tmp*;
en.SENtot = en.SENtot./en.SENtot_r;
en.PROtot = en.PROtot./en.PROtot_r;
en.COMtot = en.COMtot./en.COMtot_r;
en.SENact = en.SENact./en.SENtot_r;
en.PROact = en.PROact./en.PROtot_r;
en.COMact = en.COMact./en.COMtot_r;
en.SENidl = en.SENidl./en.SENtot_r;
en.PROidl = en.PROidl./en.PROtot_r;
en.COMidl = en.COMidl./en.COMtot_r;
ti.accTime = ti.accTime./en.SENtot_r;

en.nSize = en.nSize./en.SENtot_r;

%% PLOT DATA - mJ/s & mJ/framerot_angle1 = 0; rot_angle2 = 0;
[N,M]=meshgrid(SENfps_req,PROclk);
if(numel(SENfps_req)>2 && numel(PROclk) > 2)
    for i=1:2
        h(i)=figure('Name','Total energy of the coalition');
        
        switch i
            case 1
                variable = en.time;
                zlab = 'Consumption (mJ/s)';
            case 2
                variable = en.steps;
                zlab = 'Consumption (mJ/frame)';
        end
        
        subplot(i,3,1); mesh(N,M,en.SENtot./variable); plot_labels_axis('Sensing - Coalition',zlab,PROclk,SENfps_req);
        subplot(i,3,2); mesh(N,M,en.PROtot./variable); plot_labels_axis('Processing - Coalition',zlab,PROclk,SENfps_req);
        subplot(i,3,3); mesh(N,M,en.COMtot./variable); plot_labels_axis('Comms - Coalition',zlab,PROclk,SENfps_req);
    end
    
    hp=figure('Name','Communication performance');
    mesh(N,M,100*en.COMtot_bits); plot_labels_axis('Comms - coalition','Bandwidth usage (%)',PROclk,SENfps_req);
    
else
    
    if numel(SENfps_req)>1
        variable = en.time;
        %         variable = ti.accTime;
        %         variable = en.steps;
        %         en.SENtot = en.SENtot.*[1 2 3 4 5];
        data = [(en.SENtot./variable); (en.PROtot./variable); (en.COMtot./variable)];
        %data = [(en.SENact./variable); (en.PROact./variable); (en.COMact./variable)];
        %data = [(en.SENidl./variable); (en.PROidl./variable); (en.COMidl./variable)];
        fig=figure('Name',sprintf('Coalition consumption for f^p_{clk}=%.2fGHz',PROclk(1)/1e9),'Position', [100, 100, 550, 400]);
        bar(data'); hold on; axis([0 numel(SENfps_req)+1 0 max(max(data))]);
        legend('Sensing', 'Processing', 'Comms','Location','NorthWest');
        %errorbar(repmat(1:Ncams+1, max(size(err.COA_IP)), 1),tmp_m',sqrt(tmp_v)','.');
        %errorbar_groups(tmp_m',sqrt(tmp_v'), 'bar_names',[strread(num2str(1:Ncams),'%s');{'Coalition'}]);
        set(gca,'XTick',1:numel(SENfps_req), 'XTickLabel',strread(num2str(SENfps_req),'%s'));
        xlabel('Framerate (fps)');ylabel('Coalition consumption (mJ/sec)');
        title(sprintf('Coalition consumption for Processing clock=%.2fGHz',PROclk(1)/1e9));
        
        saveas(fig, 'figs/Coalition_sensing_consumption.eps','epsc');
        saveas(fig, 'figs/Coalition_sensing_consumption.fig'); 

        SENene.Ncams = Ncams;
        SENene.Nruns = Nruns;
        SENene.data = data;
        SENene.fps = SENfps_req;
        save figs/Coalition_sensing_consumption.mat SENene;
    end
    
    if  numel(PROclk)>1
        variable = en.time;
        
        %en.nSize*cams.usage{1,1}.SEN.eAct(2)+cams.usage{1,1}.SEN.eIdl(2);
        %         variable = en.time.*en.nCoa/max(en.nCoa);
        %         variable = ti.accTime;
        %         data = [(en.SENtot./variable)'; (en.PROtot./variable)'; (en.COMtot./variable)'];
        data = [(en.SENtot./variable)'; (en.PROtot./variable)'; (en.COMtot./variable)'];
        fig=figure('Name',sprintf('Coalition consumption for fps=%.2f',SENfps_req(1)),'Position', [100, 100, 550, 400]);
        bar(data'); hold on; axis([0.5 numel(PROclk)+0.5 0 max(max(data))]);
        legend('Sensing', 'Processing', 'Comms', 'Location', 'northwest');
        set(gca,'XTick',1:numel(PROclk), 'XTickLabel',strread(num2str(PROclk/1e9),'%s'));
        xlabel('Processing clock (Ghz)');ylabel('Coalition consumption (mJ/sec)');
        title(sprintf('Coalition consumption for fps=%.2f',SENfps_req(1)));
        saveas(fig, 'figs/Coalition_processing_consumption.eps','epsc');
        saveas(fig, 'figs/Coalition_processing_consumption.fig');
        
        PROene.Ncams = Ncams;
        PROene.Nruns = Nruns;
        PROene.data = data;
        PROene.fps = PROclk;
        save figs/Coalition_processing_consumption.mat PROene;
    end
end