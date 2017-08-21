clear all
close all
clc

%% REAL results

load ../wiseCameraICF/icf_results_res_real.mat
load kcf_results_res_real.mat

% plot results
f1=figure('Position',[100 100 650 300]);
errorbar(icf.iterU,icf.AvgErr,icf.stdErr,'rx-');
hold on;
errorbar(kcf.iterU,kcf.AvgErr,kcf.stdErr/3,'go--');

axis([icf.iterU(1)-0.5 icf.iterU(end)+0.5 -inf inf]);
xlabel('# iterations for consensus'); ylabel('Average tracking error (m)');
ll=legend('ICF','KCF');
ll.FontSize=12;
%title('ICF results for single target tracking');
box off;
set(gcf,'Units','normal')
set(gca,'Position',[.1 .15 .9 .85])
set(gca,'fontsize', 12);

f2=figure('Position',[100 100 650 350]);
fac=1e3;
plot(icf.iterU,icf.pro*fac, 'ks-',icf.iterU,icf.com*fac, 'm*-'); 
hold on;
plot(kcf.iterU,kcf.pro*fac, 'bs--',kcf.iterU,kcf.com*fac, 'g*--'); 
axis([icf.iterU(1)-0.5 icf.iterU(end)+0.5 -inf inf]);
xlabel('# iterations for consensus'); ylabel('Energy consumption (uJ/sample)');
ll=legend('ICF-Processing','ICF-Communication','KCF-Processing','KCF-Communication','Location','northwest');
ll.FontSize=12;
box off;
set(gcf,'Units','normal')
set(gca,'Position',[.1 .13 .9 .85])
set(gca,'fontsize', 12);

f3=figure('Position',[100 100 650 350]);
plot(icf.iterU,icf.PacketsTX/max(t_sim), 'ks-',...
     icf.iterU,icf.RxReachedNoInterference/max(t_sim), 'm*-',...
     icf.iterU,icf.RxFailedNoRxState/max(t_sim), 'co-'); 
hold on;
plot(icf.iterU,kcf.PacketsTX/max(t_sim), 'bs--',...
     icf.iterU,kcf.RxReachedNoInterference/max(t_sim), 'g*--',...
     icf.iterU,kcf.RxFailedNoRxState/max(t_sim), 'ro--');  
axis([icf.iterU(1)-0.5 icf.iterU(end)+0.5 -inf inf]);
xlabel('# iterations for consensus'); ylabel('Average packets/second');
ll = legend('ICF-TX','ICF-RX', 'ICF-RX failed','KCF-TX','KCF-RX','KCF-RX failed');
ll.FontSize=12;
box off;
set(gcf,'Units','normal')
set(gca,'Position',[.1 .13 .9 .85])
set(gca,'fontsize', 12);

f4=figure('Position',[100 100 650 300]);
errorbar(icf.iterU,icf.delayT,icf.delayS,'rx-');
hold on;
errorbar(kcf.iterU,kcf.delayT,kcf.delayS,'go--');

axis([icf.iterU(1)-0.5 icf.iterU(end)+0.5 -inf inf]);
xlabel('# iterations for consensus'); ylabel('Average delay (sec/sample)');
ll=legend('ICF','KCF','Location','northwest');
ll.FontSize=12;
%title('ICF results for single target tracking');
box off;
set(gcf,'Units','normal')
set(gca,'Position',[.1 .15 .9 .85])
set(gca,'fontsize', 12);

epsfig = hgexport('factorystyle');
epsfig.Format = 'eps';
hgexport(f1,'FilterComparison_real_accuracy.eps',epsfig,'Format','eps')
hgexport(f2,'FilterComparison_real_energy.eps',epsfig,'Format','eps')
hgexport(f3,'FilterComparison_real_packts.eps',epsfig,'Format','eps')
hgexport(f4,'FilterComparison_real_delay.eps',epsfig,'Format','eps')

%% IDEAL RESULTS
load ../wiseCameraICF/icf_results_res_ideal.mat
load kcf_results_res_ideal.mat

% plot results
f1=figure('Position',[100 100 650 300]);
errorbar(icf.iterU,icf.AvgErr,icf.stdErr,'rx-');
hold on;
errorbar(kcf.iterU,kcf.AvgErr,kcf.stdErr/3,'go--');

axis([icf.iterU(1)-0.5 icf.iterU(end)+0.5 -inf inf]);
xlabel('# iterations for consensus'); ylabel('Average tracking error (m)');
ll=legend('ICF','KCF');
ll.FontSize=12;
%title('ICF results for single target tracking');
box off;
set(gcf,'Units','normal')
set(gca,'Position',[.1 .15 .9 .85])
set(gca,'fontsize', 12);

f2=figure('Position',[100 100 650 350]);
fac=1e3;
plot(icf.iterU,icf.pro*fac, 'ks-',icf.iterU,icf.com*fac, 'm*-'); 
hold on;
plot(kcf.iterU,kcf.pro*fac, 'bs--',kcf.iterU,kcf.com*fac, 'g*--'); 
axis([icf.iterU(1)-0.5 icf.iterU(end)+0.5 -inf inf]);
xlabel('# iterations for consensus'); ylabel('Energy consumption (uJ/sample)');
ll=legend('ICF-Processing','ICF-Communication','KCF-Processing','KCF-Communication','Location','northwest');
ll.FontSize=12;
box off;
set(gcf,'Units','normal')
set(gca,'Position',[.1 .13 .9 .85])
set(gca,'fontsize', 12);

epsfig = hgexport('factorystyle');
epsfig.Format = 'eps';
hgexport(f1,'FilterComparison_ideal_accuracy.eps',epsfig,'Format','eps')
hgexport(f2,'FilterComparison_ideal_energy.eps',epsfig,'Format','eps')
