% function []=CAWC_plot_coa_resUsage()
clc; clear all; close all;
addpath('./utils');

%% LOAD AND PREPROCESS DATA
dataDir = '/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/res_O_t09_5s_r10';
dataDir = '/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/res';

% [runs,coa]=load_coa_data(dataDir); %coalition tracking data
[cams.track,ids,cids]=load_cams_data(dataDir); %camera tracking data
[cams.usage,ids,cids]=load_cams_consumption(dataDir);%camera consumption
%
[Ncams, Nruns, PROclk, SENclk, OptFactor, SENfps_req, SENfps_rea,comparedFrames] = preprocess_data(cams);

%% COMPUTE ENERGY STATISTICS
en.SENact = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));
en.SENidl = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));
en.SEN_r = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));
en.PROact = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));
en.PROidl = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));
en.PRO_r = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));
en.COMact = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));
en.COMidl = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));
en.COM_r = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));
en.SEN.steps = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));
en.PRO.steps = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));
en.time = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));

ti.SENact = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));
ti.PROact = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));
ti.PROmis = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));
ti.COMact = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));
ti.COMactMax = zeros(Ncams, numel(PROclk), numel(SENfps_req),numel(OptFactor));

%selected camera to plot results
for c=1:Ncams
    for r=1:size(cams.usage,2)
        
        %find sen&pro clos
        curPROclk = cams.usage{c,r}.PRO.clockfreq;
        curSENclk = cams.usage{c,r}.SEN.clockfreq;
        curSENfps = cams.usage{c,r}.SEN.FPSrea;
        ind =find (cams.usage{c,r}.PRO.TimeS > 0);
        curOpt = round(median(cams.usage{c,r}.PRO.TimeS(ind)./cams.usage{c,r}.PRO.TimeO(ind)),1);
        
        ip = find(PROclk==curPROclk);
        is = find(SENfps_req==curSENfps);
        io = find(OptFactor==round(curOpt,1));
        
        ind = find(cams.usage{c,r}.SEN.eAct > 0);
        en.SENact(c,ip,is,io) = en.SENact(c,ip,is,io) + sum(cams.usage{c,r}.SEN.eAct(ind));
        en.SENidl(c,ip,is,io) = en.SENidl(c,ip,is,io) + sum(cams.usage{c,r}.SEN.eIdl(ind));        
        en.SEN.steps(c,ip,is,io) = en.SEN.steps(c,ip,is,io) + numel(ind);        
        ti.SENact(c,ip,is,io) = ti.SENact(c,ip,is,io) + sum(size(cams.usage{c,r}.SEN.eAct,1)*cams.usage{c,r}.SEN.Tact);
        en.SEN_r(c,ip,is,io) = en.SEN_r(c,ip,is,io)+1;
        
        ind = find(cams.usage{c,r}.PRO.eAct > 0);
        en.PROact(c,ip,is,io) = en.PROact(c,ip,is,io) + sum(cams.usage{c,r}.PRO.eAct(ind));
        en.PROidl(c,ip,is,io) = en.PROidl(c,ip,is,io) + sum(cams.usage{c,r}.PRO.eIdl(ind));        
        en.PRO.steps(c,ip,is,io) = en.PRO.steps(c,ip,is,io)+numel(ind);        
        ti.PROact(c,ip,is,io) = ti.PROact(c,ip,is,io) + sum(cams.usage{c,r}.PRO.TimeO(ind)*1e-3);
        en.PRO_r(c,ip,is,io) = en.PRO_r(c,ip,is,io)+1;
        
        cams.usage{c,r}.COM.eAct = cams.usage{c,r}.COM.eActTX + cams.usage{c,r}.COM.eActRX;
        ind = find(cams.usage{c,r}.COM.eAct > 0);
        en.COMact(c,ip,is,io) = en.COMact(c,ip,is,io) + sum(cams.usage{c,r}.COM.eAct(ind));
        en.COMidl(c,ip,is,io) = en.COMidl(c,ip,is,io) + sum(cams.usage{c,r}.COM.eIdl(ind));
        en.COM_r(c,ip,is,io) = en.COM_r(c,ip,is,io)+1;
        
        en.COM.steps(c,ip,is,io) = numel(ind);
        en.time(c,ip,is,io) = en.time(c,ip,is,io) + max(cams.usage{c,r}.t_sim);
        
        allocBitrate = 250000*1/8*1/curSENfps;%bitrate in bytes/sec
        tmp = (cams.usage{c,r}.COM.TXdone(ind)+cams.usage{c,r}.COM.RXdone(ind)-128)/allocBitrate;
        ti.COMactMax(c,ip,is,io) = ti.COMactMax(c,ip,is,io) + mean(tmp);
        ti.COMact(c,ip,is,io) = ti.COMact(c,ip,is,io) + sum(tmp);
    end
end
%normalization by the number of runs
en.SENact = en.SENact./en.SEN_r;
en.SENidl = en.SENidl./en.SEN_r;
en.SEN.steps = en.SEN.steps./en.SEN_r;
en.PROact = en.PROact./en.PRO_r;
en.PROidl = en.PROidl./en.PRO_r;
en.PRO.steps = en.PRO.steps./en.PRO_r;
en.COMact = en.COMact./en.COM_r;
en.COMidl = en.COMidl./en.COM_r;
en.time = en.time./en.SEN_r;

ti.SENact = 1./en.time .* (ti.SENact./en.SEN_r);
ti.PROact = 1./en.time .* (ti.PROact./en.PRO_r);
ti.COMact = 1./en.time .* (ti.COMact./en.COM_r);

%% PLOT DATA - mJ/s & mJ/framerot_angle1 = 0; rot_angle2 = 0;
% [N,M]=meshgrid(SENfps_req,PROclk);
% if(numel(SENfps_req)>2 && numel(PROclk) > 2)
%     for i=1:2
%         h(i)=figure('Name','Total energy of the coalition');
%         
%         switch i
%             case 1
%                 variable = en.time;
%                 zlab = 'Consumption (mJ/s)';
%             case 2
%                 variable = en.steps;
%                 zlab = 'Consumption (mJ/frame)';
%         end
%         
%         subplot(i,3,1); mesh(N,M,en.SENtot./variable); plot_labels_axis('Sensing - Coalition',zlab,PROclk,SENfps_req);
%         subplot(i,3,2); mesh(N,M,en.PROtot./variable); plot_labels_axis('Processing - Coalition',zlab,PROclk,SENfps_req);
%         subplot(i,3,3); mesh(N,M,en.COMtot./variable); plot_labels_axis('Comms - Coalition',zlab,PROclk,SENfps_req);
%     end
%     
%     hp=figure('Name','Communication performance');
%     mesh(N,M,100*en.COMtot_bits); plot_labels_axis('Comms - coalition','Bandwidth usage (%)',PROclk,SENfps_req);
%     
% else
    
    if numel(SENfps_req)>1
        variable = en.time;
%         %         variable = ti.accTime;
%         %         variable = en.steps;
%         %         en.SENtot = en.SENtot.*[1 2 3 4 5];
%         data = [(en.SENtot./variable); (en.PROtot./variable); (en.COMtot./variable)];
%         %data = [(en.SENact./variable); (en.PROact./variable); (en.COMact./variable)];
%         %data = [(en.SENidl./variable); (en.PROidl./variable); (en.COMidl./variable)];
%         fig=figure('Name',sprintf('Coalition consumption for f^p_{clk}=%.2fGHz',PROclk(1)/1e9),'Position', [100, 100, 550, 400]);
%         bar(data'); hold on; axis([0 numel(SENfps_req)+1 0 max(max(data))]);
%         legend('Sensing', 'Processing', 'Comms','Location','NorthWest');
%         %errorbar(repmat(1:Ncams+1, max(size(err.COA_IP)), 1),tmp_m',sqrt(tmp_v)','.');
%         %errorbar_groups(tmp_m',sqrt(tmp_v'), 'bar_names',[strread(num2str(1:Ncams),'%s');{'Coalition'}]);
%         set(gca,'XTick',1:numel(SENfps_req), 'XTickLabel',strread(num2str(SENfps_req),'%s'));
%         xlabel('Framerate (fps)');ylabel('Coalition consumption (mJ/sec)');
%         title(sprintf('Coalition consumption for Processing clock=%.2fGHz',PROclk(1)/1e9));
%         
%         saveas(fig, 'figs/Coalition_sensing_consumption.eps','epsc');
%         saveas(fig, 'figs/Coalition_sensing_consumption.fig');
        
        %predicted lifetime
        battery=2.300*3.940;%2300mAh*3940mV (Watt-h) %NEXUS 5
        battery=9000*3.940;%2300mAh*3940mV (Watt-h) %NEXUS 10
        battery = battery * 3600; %(Watt-sec or Joules)
        variable = en.time;
        PRO = (en.SENtot+en.PROtot+en.COMtot)./variable;
        soa_SEN = (en.SENact+en.PROtot+en.COMtot)./variable;
        soa_PRO = (en.SENtot+en.PROact+en.COMtot)./variable;
        soa_COM = (en.SENtot+en.PROtot+en.COMact)./variable;
        soa_ALL = (en.SENact+en.PROact+en.COMact)./variable;
        
        fig3=figure;
        plot(1/3600*battery./PRO,'r--'); hold on;
        plot(1/3600*battery./soa_SEN,'b+-');
        plot(1/3600*battery./soa_PRO,'go-');
        plot(1/3600*battery./soa_COM,'cs-');
        plot(1/3600*battery./soa_ALL,'m*-');
        legend('Proposed','Utilization-based sensing','Utilization-based processing','Utilization-based comms','Utilization-based all');
        set(gca,'XTick',1:numel(SENfps_req), 'XTickLabel',strread(num2str(SENfps_req),'%s'));
        title('Predicted lifetime'); xlabel('Framerate (fps)');ylabel('Lifetime (hours)');
        saveas(fig3, 'figs/Coalition_sensing_lifetime.eps','epsc');
        saveas(fig3, 'figs/Coalition_sensing_lifetime.fig');
        
        fig4=figure;
        data=[1 - soa_SEN./PRO 1 - soa_PRO./PRO 1 - soa_COM./PRO 1 - soa_ALL./PRO];
        bar(100.*data);
        legend('Utilization-based sensing','Utilization-based processing','Utilization-based comms','Utilization-based all');
        set(gca,'XTick',1:numel(SENfps_req), 'XTickLabel',strread(num2str(SENfps_req),'%s'));
        title('Lifetime prediction error'); xlabel('Framerate (fps)');ylabel('Lifetime (secs)');
        saveas(fig4, 'figs/Coalition_sensing_lifetime_error.eps','epsc');
        saveas(fig4, 'figs/Coalition_sensing_lifetime_error.fig');
    end
    
    if  numel(PROclk)>1
        variable = en.time;
        en.SENactm = mean(en.SENact,1);
        en.SENidlm = mean(en.SENidl,1);
        en.PROactm = mean(en.PROact,1);
        en.PROidlm = mean(en.PROidl,1);
        en.COMactm = mean(en.COMact,1);
        en.COMidlm = mean(en.COMidl,1);
        
        en.SENtot=en.SENactm+en.SENidlm;
        en.PROtot=en.PROactm+en.PROidlm;
        en.COMtot=en.COMactm+en.COMidlm;
        
        %predicted lifetime
        battery=2.300*3.940;%2300mAh*3940mV (Watt-h) %NEXUS 5
        battery=9000*3.940;%2300mAh*3940mV (Watt-h) %NEXUS 10
        battery = battery * 3600; %(Watt-sec or Joules)
        variable = mean(en.time,1);
        %         en.SENtot=en.SENact+en.SENidl;
        %         en.PROtot=en.PROact+en.PROidl;
        %         en.COMtot=en.COMact+en.COMidl;
        PRO = (en.SENtot+en.PROtot+en.COMtot)./variable;
        soa_SEN = (en.SENactm+en.PROtot+en.COMtot)./variable;
        soa_PRO = (en.SENtot+en.PROactm+en.COMtot)./variable;
        soa_COM = (en.SENtot+en.PROtot+en.COMactm)./variable;
        soa_ALL = (en.SENactm+en.PROactm+en.COMactm)./variable;
        
        fig3=figure;
        plot(1/3600*battery./PRO,'r--'); hold on;
        plot(1/3600*battery./soa_SEN,'b+-');
        plot(1/3600*battery./soa_PRO,'go-');
        plot(1/3600*battery./soa_COM,'cs-');
        plot(1/3600*battery./soa_ALL,'m*-');
        legend('Proposed','Utilization-based sensing','Utilization-based processing','Utilization-based comms','Utilization-based all');
        set(gca,'XTick',1:numel(PROclk), 'XTickLabel',strread(num2str(PROclk/1e9),'%s'));
        title('Predicted lifetime'); xlabel('Processing clock (Ghz)');ylabel('Lifetime (hours)');
        saveas(fig3, 'figs/Coalition_processing_lifetime.eps','epsc');
        saveas(fig3, 'figs/Coalition_processing_lifetime.fig');
        
        fig4=figure;
        data=[1 - soa_SEN./PRO; 1 - soa_PRO./PRO; 1 - soa_COM./PRO; 1 - soa_ALL./PRO];
        bar(100*data');
        legend('Utilization-based sensing','Utilization-based processing','Utilization-based comms','Utilization-based all');
        set(gca,'XTick',1:numel(PROclk), 'XTickLabel',strread(num2str(PROclk/1e9),'%s'));
        title('Lifetime prediction error'); xlabel('Processing clock (Ghz)');ylabel('Error (%)');
        saveas(fig4, 'figs/Coalition_processing_lifetime_error.eps','epsc');
        saveas(fig4, 'figs/Coalition_processing_lifetime_error.fig');
    end
    
    if  numel(OptFactor)>1
        variable =  mean(reshape(en.time,[Ncams numel(OptFactor)]),1);
        en.SENactm = mean(reshape(en.SENact,[Ncams numel(OptFactor)]),1);         
        en.SENidlm = mean(reshape(en.SENidl,[Ncams numel(OptFactor)]),1);        
        en.PROactm = mean(reshape(en.PROact,[Ncams numel(OptFactor)]),1);        
        en.PROidlm = mean(reshape(en.PROidl,[Ncams numel(OptFactor)]),1);        
        en.COMactm = mean(reshape(en.COMact,[Ncams numel(OptFactor)]),1);        
        en.COMidlm = mean(reshape(en.COMidl,[Ncams numel(OptFactor)]),1);
                
        ti.PROactm = mean(reshape(ti.PROact,[Ncams numel(OptFactor)]),1);
        
        en.SENtot=en.SENactm+en.SENidlm;
        en.PROtot=en.PROactm+en.PROidlm;
        en.COMtot=en.COMactm+en.COMidlm;
        
        PRO = (en.SENtot+en.PROtot+en.COMtot)./variable;
        soa_SEN = (en.SENactm+en.PROtot+en.COMtot)./variable;
        soa_PRO = (en.SENtot+en.PROactm+en.COMtot)./variable;
        soa_COM = (en.SENtot+en.PROtot+en.COMactm)./variable;
        soa_ALL = (en.SENactm+en.PROactm+en.COMactm)./variable;
        
        battery=2300*3.940;%2300mAh*3940mV (Watt-h) %NEXUS 5
%         battery=9000*3.940;%2300mAh*3940mV (Watt-h) %NEXUS 10
        battery = battery * 3600; %(Watt-sec or Joules)
        
        fig3=figure('Position',[100 100 500 275]);              
        plot(flip(1/3600*battery./soa_SEN),'bd-'); hold on;
        plot(flip(1/3600*battery./soa_PRO),'ro-');
        plot(flip(1/3600*battery./soa_COM),'cs-');
        plot(flip(1/3600*battery./soa_ALL),'k*-');
        plot(flip(1/3600*battery./PRO),'g+-');hold on;   box off;      
        legend('Utilization-based sensing','Utilization-based processing','Utilization-based comms','Utilization-based all', 'Proposed', 'Location','NorthEast');
        set(gca,'XTick',1:numel(OptFactor), 'XTickLabel',strread(num2str(round(flip(ti.PROactm*100))),'%s'));
        %title('Predicted lifetime'); 
        xlabel('Utilization processing (%)');ylabel('Lifetime (hours)');
        saveas(fig3, 'figs/Coalition_processing_lifetime_ofactor.eps','epsc');
        saveas(fig3, 'figs/Coalition_processing_lifetime_ofactor.fig');
        
        fig4=figure('Position',[100 100 500 275]);
%         data=[flip(1 - soa_SEN./PRO); flip(1 - soa_PRO./PRO); flip(1 - soa_COM./PRO); flip(1 - soa_ALL./PRO)];
%         b=bar(100*data');        
%         b(1).FaceColor='blue';
%         b(2).FaceColor='red';
%         b(3).FaceColor='cyan';
%         b(4).FaceColor='black';       
        plot(100*flip(1 - soa_SEN./PRO),'bd-'); hold on;
        plot(100*flip(1 - soa_PRO./PRO),'ro-');
        plot(100*flip(1 - soa_COM./PRO),'cs-');
        plot(100*flip(1 - soa_ALL./PRO),'k*-');
        box off;          
        legend('Utilization-based sensing','Utilization-based processing','Utilization-based comms','Utilization-based all');
        set(gca,'XTick',1:numel(OptFactor), 'XTickLabel',strread(num2str(round(flip(ti.PROactm*100))),'%s'));
%         title('Lifetime prediction error'); 
        xlabel('Utilization processing (%)');ylabel('Average prediction error (%)'); box off;
        saveas(fig4, 'figs/Coalition_processing_lifetime_error_ofactor.eps','epsc');
        saveas(fig4, 'figs/Coalition_processing_lifetime_error_ofactor.fig');        
    end