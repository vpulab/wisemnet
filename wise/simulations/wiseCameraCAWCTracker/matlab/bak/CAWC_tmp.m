

%% PLOT ERRORS
if(numel(PROclk)>1 && numel(FPSreq)>1)
    % 3D plot for simultaneous testing of framerate and processing clock
    hp=figure('Name','Tracking error ground-plane');
    [N,M]=meshgrid(FPSreq,PROclk);    
    for c=1:Ncams
        subplot(2,4,c); mesh(N,M,reshape(err.CAMGPm(c,:,:),[nP nS])); plot_labels_axis(sprintf('Camera %d',c),'Mean tracking error GP (m)',PROclk,FPSreq);
    end
    subplot(2,4,8); mesh(N,M,err.COA_GPm); plot_labels_axis('Coalition','Mean tracking error GP (m)',PROclk,FPSreq);
    
    hp=figure('Name','Tracking error image-plane');
    for c=1:Ncams
        subplot(2,4,c); mesh(N,M,reshape(err.CAMIPm(c,:,:),[nP nS])); plot_labels_axis(sprintf('Camera %d',c),'Mean tracking error IP (pixels)',PROclk,FPSreq);
    end
    subplot(2,4,8); mesh(N,M,err.COA_IPm); plot_labels_axis('Coalition','Mean tracking error GP (m)',PROclk,FPSreq);    
else
    
    % 2D bar plot for independent testing of framerate or processing clock
    if numel(FPSreq)>1 %framerate testing
%         fip1=figure('Name',sprintf('Tracking IP error for P=%.2fGHz',PROclk(1)/1e9));
%         tmp_m = err.CAMIPm; tmp_m(end+1,:,:) = err.COA_IPm; tmp_m=reshape(tmp_m, [Ncams+1 max(size(err.COA_IP))]);
%         tmp_v = err.CAMIPv; tmp_v(end+1,:,:) = err.COA_IPv; tmp_v=reshape(tmp_v, [Ncams+1 max(size(err.COA_IP))]);
%         bar(tmp_m); hold on; legend(strread(num2str(SENfps_req),'%s')');        
%         set(gca,'XTick',1:Ncams+1, 'XTickLabel',[strread(num2str(1:Ncams),'%s');{'Coalition'}]); xlabel('camera');ylabel('IP tracking error (pixels)');
%         title(sprintf('Tracking IP error for P=%.2fGHz and different framerates',PROclk(1)/1e9));
        
        fgp1=figure('Name',sprintf('Tracking GP error for P=%.2fGHz',PROclk(1)/1e9),'Position', [100, 100, 700, 300]);
        tmp_m = err.CAMGPm; %tmp_m(end+1,:,:) = err.COA_GPm; tmp_m=reshape(tmp_m, [Ncams+1 max(size(err.COA_IP))]);
        tmp_m=reshape(tmp_m, [Ncams max(size(err.COA_IP))]);
        %tmp_v = err.CAMGPv; tmp_v(end+1,:,:) = err.COA_GPv; tmp_v=reshape(tmp_v, [Ncams+1 max(size(err.COA_IP))]);
        labels=strread(num2str(FPSreq),'%s');
        for ll=1:numel(labels)
            labels{ll} = [labels{ll} ' fps'];
        end
        b=bar(tmp_m); hold on; leg=legend(labels','Orientation','Horizontal','Location','Northoutside');        
        
        labels=strread(num2str(cids),'%s');
        for ll=1:numel(labels)
            labels{ll} = ['Camera ' labels{ll} ];
        end
%         title(sprintf('Tracking GP error for P=%.2fGHz and different framerates',PROclk(1)/1e9));
        %set(gca,'XTick',1:Ncams+1, 'XTickLabel',[labels;{'Coalition'}]); 
        set(gca,'XTick',1:Ncams, 'XTickLabel',labels); 
        ylabel('Average tracking error (m)');%xlabel('camera');
        box off;  
        axis([0.5 numel(cids)+0.5 0 3.25])
%         axis tight;

        
        Xgp=[];Xip=[];
        for is=1:nS
            Xgp = [Xgp; err.COA_GP{1,is}(:)'];
            Xip = [Xip; err.COA_IP{1,is}(:)'];
        end
        Xgp = Xgp';
        Xip = Xip';
        
%         fip2=figure('Name',sprintf('Coalition tracking IP error for P=%.2fGHz',PROclk(1)/1e9));
%         T = bplot(Xip,'points'); legend(T,'location','northeast');
%         set(gca,'XTick',1:numel(SENfps_req), 'XTickLabel',SENfps_req);
%         xlabel('Sensing framerate (fps)');   ylabel('Average tracking error (pixels)');
%         title(sprintf('Coalition error in Image-Plane for P=%.2fGHz',PROclk(1)/1e9));
        
        fgp2=figure('Name',sprintf('Coalition tracking GP error for P=%.2fGHz',PROclk(1)/1e9));
        T = bplot(Xgp,'points'); legend(T,'location','northeast');
        set(gca,'XTick',1:nS, 'XTickLabel',FPSreq);
        xlabel('Sensing framerate (fps)');   ylabel('Coalition tracking error (m)');
        %title(sprintf('Coalition error in Ground-Plane for P=%.2fGHz',PROclk(1)/1e9));
        
%         saveas(fip1, 'figs/TrackErrIP_cmp_sensing.eps','epsc'); saveas(fip1, 'figs/TrackErrIP_cam_sensing.fig');
        saveas(fgp1, 'figs/TrackErrGP_cmp_sensing.eps','epsc'); saveas(fgp1, 'figs/TrackErrGP_cam_sensing.fig');
%         saveas(fip2, 'figs/TrackErrGP_coa_sensing.eps','epsc'); saveas(fip2, 'figs/TrackErrIP_coa_sensing.fig');
        saveas(fgp2, 'figs/TrackErrGP_coa_sensing.eps','epsc'); saveas(fgp2, 'figs/TrackErrGP_coa_sensing.fig');         
    end
    
    if  nP>1 %processing clock testing
%         fip1=figure('Name',sprintf('Tracking IP error for fps=%.2f',SENfps_req(1)));
%         tmp_m = err.CAMIPm; tmp_m(end+1,:,:) = err.COA_IPm; tmp_m=reshape(tmp_m, [Ncams+1 max(size(err.COA_IP))]);
%         tmp_v = err.CAMIPv; tmp_v(end+1,:,:) = err.COA_IPv; tmp_v=reshape(tmp_v, [Ncams+1 max(size(err.COA_IP))]);
%         bar(tmp_m); hold on; legend(strread(num2str(PROclk/1e9),'%s')');
%         set(gca,'XTick',1:Ncams+1, 'XTickLabel',[strread(num2str(1:Ncams),'%s');{'Coalition'}]); xlabel('camera');ylabel('IP tracking error (pixels)');
%         title(sprintf('Tracking IP error for fps=%.2f and different processing clocks',SENfps_req(1)));
        
        fgp1=figure('Name',sprintf('Tracking GP error for fps=%.2f',FPSreq(1)));
        tmp_m = err.CAMGPm; tmp_m(end+1,:,:) = err.COA_GPm; tmp_m=reshape(tmp_m, [Ncams+1 max(size(err.COA_IP))]);
        tmp_v = err.CAMGPv; tmp_v(end+1,:,:) = err.COA_GPv; tmp_v=reshape(tmp_v, [Ncams+1 max(size(err.COA_IP))]);
        labels=strread(num2str(PROclk/1e9),'%s');
        for ll=1:numel(labels)
            labels{ll} = [labels{ll} ' GHz'];
        end
        bar(tmp_m); hold on; legend(labels');
        title(sprintf('Tracking GP error for fps=%.2f and different processing clocks',FPSreq(1)));
        set(gca,'XTick',1:Ncams+1, 'XTickLabel',[strread(num2str(1:Ncams),'%s');{'Coalition'}]); xlabel('camera');ylabel('GP tracking error (m)');
        
        Xgp=[];Xip=[];
        for ip=1:nP
            Xgp = [Xgp; err.COA_GP{ip,1}(:)'];
            Xip = [Xip; err.COA_IP{ip,1}(:)'];
        end
        
        fgp2=figure('Name',sprintf('Coalition tracking GP error for P=%.2fGHz',PROclk(1)/1e9));
        T = bplot(Xgp','points');
        legend(T,'location','northeast');
        set(gca,'XTick',1:nP, 'XTickLabel',PROclk/1e9);
         xlabel('Processor clock (Ghz)');   ylabel('Coalition tracking error (m)');
        %title(sprintf('Coalition error in Ground-Plane for P=%.2fGHz',PROclk(1)/1e9));
%         
%         fip2=figure('Name',sprintf('Coalition tracking IP error for P=%.2fGHz',PROclk(1)/1e9));
%         T = bplot(Xip','points');
%         legend(T,'location','northeast');
%         set(gca,'XTick',1:nP, 'XTickLabel',PROclk/1e9);
%          xlabel('Processor clock (Ghz)');    ylabel('Average tracking error (pixels)');
%         title(sprintf('Coalition error in Image-Plane for fps=%.2fGHz',SENfps_req(1)));
%         
%         fip_=figure('Name',sprintf('Coalition Tracking IP error for fps=%.2f',SENfps_req(1)));
%         errorbar(err.COA_IPm,sqrt(err.COA_IPv),'rx','MarkerSize',12 );
%         set(gca,'XTick',1:nP, 'XTickLabel',PROclk/1e9);
%         xlabel('Processor clock (Ghz)');   ylabel('Average tracking error (pixels)');
%         title(sprintf('Coalition error in Image Plane for fps=%.2f',SENfps_req(1)));
        
%         saveas(fip1, 'figs/TrackErrIP_cmp_pro.eps','epsc'); saveas(fip1, 'figs/TrackErrIP_cam_pro.fig');
        saveas(fgp1, 'figs/TrackErrGP_cmp_pro.eps','epsc'); saveas(fgp1, 'figs/TrackErrGP_cam_pro.fig');
%         saveas(fip2, 'figs/TrackErrGP_coa_pro.eps','epsc'); saveas(fip2, 'figs/TrackErrIP_coa_pro.fig');
        saveas(fgp2, 'figs/TrackErrGP_coa_pro.eps','epsc'); saveas(fgp2, 'figs/TrackErrGP_coa_pro.fig');        
    end
end