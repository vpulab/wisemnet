%script to show kcf results and the energy consumption
clc
close all
clear all

input_dir = 'res_real/';
% input_dir = 'res_ideal/';

%% read consumption data
[cams.usage,ids,cids]=load_cams_consumption(input_dir);%camera consumption
Ncams = size(cams.usage,1);
Nruns = size(cams.usage,2);

%% read accuracy data
tot=0;
files = dir([input_dir '*.dat']);
%Nruns = numel(files);
for f=1:numel(files)    
    [t_sim t_step NID TID Zx Zy Inix Iniy ESTx ESTy GTx GTy Err ErrAcc delay] ...
        = textread([input_dir files(f).name], '%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f', 'commentstyle', 'shell');

    Ncams = size(unique(NID),1);
    Nt = size(unique(TID),1);
    
    %remove last result as not all cameras may have written results
    ind = find(t_step(end) == t_step);
    t_sim(ind) = [];
    t_step(ind) = [];
    Zx(ind) = [];
    Zy(ind) = [];
    Err(ind) = [];
    ErrAcc(ind) = [];
    delay(ind) = [];
    
    temp = 0;
    Zt = Zx+Zy;
    for n = 1:Ncams
        temp = temp+Zt(n:Ncams:end);
    end
    ind=find(temp==0); %frames without measurements
    
    for i=1:numel(ind)
         ind2 = find(t_step == ind(i));
         t_step(ind2) = 0;
    end
    
    ind = find(t_step > 0);
    kcf.Terr{f} = ErrAcc(ind);
    kcf.iter(f) = str2double(files(f).name(20:21)); %number of iteration
    kcf.run(f) = str2double(files(f).name(6:8)); %number of iteration
    kcf.err.mean(f) = mean(Err(ind));    
    kcf.err.max(f) = max(Err(ind));
    kcf.err.min(f) = min(Err(ind));
    kcf.delay(f) = mean(delay(ind));
    kcf.delay_std(f) = std(delay(ind));
    tot = tot + numel(ind);
     
    temp = 0;
    k=1;
    for n = 1:Ncams:numel(t_step)
        temp(k) = std(Err(n:n+Ncams-1));
        k=k+1;
    end
    kcf.StdErr{f} = temp;    
    kcf.err.std(f) = mean(temp);
   
end

kcf.iterU = sort(unique(kcf.iter), 'ascend');
kcf.com = zeros(numel(kcf.iterU), 1);
kcf.pro = zeros(numel(kcf.iterU), 1);
kcf.citer = zeros(numel(kcf.iterU), 1);
kcf.countP = zeros(numel(kcf.iterU), 1);
kcf.countC = zeros(numel(kcf.iterU), 1);

for r=1:Nruns       
    for c=1:Ncams
        i = find(kcf.iter(r) == kcf.iterU);
        kcf.citer(i)=kcf.citer(i)+1;
        
        ind = find(cams.usage{c,r}.PRO.eAct ~= -1);
        kcf.pro(i) = kcf.pro(i) + sum(cams.usage{c,r}.PRO.eAct(ind)+cams.usage{c,r}.PRO.eCol(ind));
        kcf.countP(i) = kcf.countP(i) + numel(ind);
        
        ind = find(cams.usage{c,r}.COM.eActTX ~= -1);
        kcf.com(i) = kcf.com(i) + sum(cams.usage{c,r}.COM.eActTX(ind)+cams.usage{c,r}.COM.eActRX(ind));
        kcf.countC(i) = kcf.countC(i) + numel(ind);
    end
end
kcf.pro = kcf.pro./(kcf.citer.*kcf.countP);
kcf.com = kcf.com./(kcf.citer.*kcf.countC);

%% compute statistics for error
kcf.AvgErr = zeros(numel(kcf.iterU), 1);
kcf.stdErr = zeros(numel(kcf.iterU), 1);
kcf.MaxErr = zeros(numel(kcf.iterU), 1);
kcf.MinErr = zeros(numel(kcf.iterU), 1);
kcf.countE = zeros(numel(kcf.iterU), 1);
kcf.delayT = zeros(numel(kcf.iterU), 1);
kcf.delayS = zeros(numel(kcf.iterU), 1);

for f=1:numel(files)   
    i = find(kcf.iter(f) == kcf.iterU);
    
    kcf.AvgErr(i)=kcf.AvgErr(i)+kcf.err.mean(f);
    kcf.stdErr(i)=kcf.stdErr(i)+kcf.err.std(f);    
    kcf.MaxErr(i)=kcf.MaxErr(i)+kcf.err.max(f);
    kcf.MinErr(i)=kcf.MinErr(i)+kcf.err.min(f);
    kcf.delayT(i)=kcf.delayT(i)+kcf.delay(f);
    kcf.delayS(i)=kcf.delayS(i)+kcf.delay_std(f);
    kcf.countE(i) = kcf.countE(i) + 1;
end
kcf.AvgErr = kcf.AvgErr./kcf.countE;
kcf.stdErr = kcf.stdErr./kcf.countE;
kcf.MaxErr = kcf.MaxErr./kcf.countE;
kcf.MinErr = kcf.MinErr./kcf.countE;
kcf.delayT = kcf.delayT./kcf.countE;
kcf.delayS = kcf.delayS./kcf.countE;


%% radio data

kcf.PacketsTX = zeros(numel(kcf.iterU), 1);
kcf.RxReachedNoInterference = zeros(numel(kcf.iterU), 1);
kcf.RxReachedInterference = zeros(numel(kcf.iterU), 1);
kcf.RxFailedNoInterference = zeros(numel(kcf.iterU), 1);
kcf.RxFailedInterference = zeros(numel(kcf.iterU), 1);
kcf.RxFailedSensitivity = zeros(numel(kcf.iterU), 1);
kcf.RxFailedModulation = zeros(numel(kcf.iterU), 1);
kcf.RxFailedNoRxState = zeros(numel(kcf.iterU), 1);
kcf.BufferOverflow = zeros(numel(kcf.iterU), 1);
kcf.countRad = zeros(numel(kcf.iterU), 1);

files = dir([input_dir '*.rad']);
%Nruns = numel(files);
for f=1:numel(files)    
    [node Ptx RxRNI RxRI RxFNI RxFI RxFS RxFM RxNRx bufO] ...
        = textread([input_dir files(f).name], '%f %f %f %f %f %f %f %f %f %f', 'commentstyle', 'shell');

    kcf.rad.iter(f) = str2double(files(f).name(20:21)); %number of iteration
    kcf.rad.run(f) = str2double(files(f).name(6:8)); %number of iteration
    
    i = find(kcf.rad.iter(f) == kcf.iterU);
    
    kcf.PacketsTX(i) = kcf.PacketsTX(i) + mean(Ptx);
    kcf.RxReachedNoInterference(i) = kcf.RxReachedNoInterference(i)+mean(RxRNI); 
    kcf.RxReachedInterference(i) = kcf.RxReachedInterference(i)+mean(RxRI);
    kcf.RxFailedNoInterference(i) = kcf.RxFailedNoInterference(i)+mean(RxFNI);
    kcf.RxFailedInterference(i) = kcf.RxFailedInterference(i)+mean(RxFI);
    kcf.RxFailedSensitivity(i) = kcf.RxFailedSensitivity(i)+mean(RxFS);
    kcf.RxFailedModulation(i) = kcf.RxFailedModulation(i)+mean(RxFM);
    kcf.RxFailedNoRxState(i) = kcf.RxFailedNoRxState(i)+mean(RxNRx);
    kcf.BufferOverflow(i) = kcf.BufferOverflow(i)+mean(bufO);
   
    kcf.countRad(i) = kcf.countRad(i) + 1;
end
kcf.PacketsTX = kcf.PacketsTX./kcf.countRad;
kcf.RxReachedNoInterference = kcf.RxReachedNoInterference./kcf.countRad;
kcf.RxReachedInterference = kcf.RxReachedInterference./kcf.countRad;
kcf.RxFailedNoInterference = kcf.RxFailedNoInterference./kcf.countRad;
kcf.RxFailedInterference = kcf.RxFailedInterference./kcf.countRad;
kcf.RxFailedSensitivity = kcf.RxFailedSensitivity./kcf.countRad;
kcf.RxFailedModulation = kcf.RxFailedModulation./kcf.countRad;
kcf.RxFailedNoRxState = kcf.RxFailedNoRxState./kcf.countRad;
kcf.BufferOverflow = kcf.BufferOverflow./kcf.countRad;

%% plot results
figure;
subplot 311; 
% plot(kcf.iterU,kcf.AvgErr,'rx-'); hold on;
% plot(kcf.iterU,kcf.MaxErr, 'g--',kcf.iterU,kcf.MinErr, 'b--'); 
% legend('Average','Maximum','Minimum')
errorbar(kcf.iterU,kcf.AvgErr,kcf.stdErr,'rx-');
axis([kcf.iterU(1)-0.5 kcf.iterU(end)+0.5 -inf inf]);
xlabel('# iterations for consensus'); ylabel('Average tracking error (m)');
title('kcf results for single target tracking');
box off;

subplot 312; plot(kcf.iterU,kcf.pro*1e-3, 'ks-',kcf.iterU,kcf.com*1e-3, 'm*-'); 
axis([kcf.iterU(1)-0.5 kcf.iterU(end)+0.5 -inf inf]);

xlabel('# iterations for consensus'); ylabel('Energy consumption (J/sample)');
legend('Processing','Communication','Location','northwest');
box off;

subplot 313;
errorbar(kcf.iterU,kcf.delayT,kcf.delayS,'rx-');
axis([kcf.iterU(1)-0.5 kcf.iterU(end)+0.5 -inf inf]);

xlabel('# iterations for consensus'); ylabel('Average delay (s)');
box off;

figure;
plot(kcf.iterU, kcf.PacketsTX/max(t_sim),'rx-'); hold on;
plot(kcf.iterU, kcf.RxReachedNoInterference/max(t_sim),'gx-');
plot(kcf.iterU, kcf.RxReachedInterference/max(t_sim),'bx-');
plot(kcf.iterU, kcf.RxFailedNoInterference/max(t_sim),'cs-');
plot(kcf.iterU, kcf.RxFailedInterference/max(t_sim),'m+-');
plot(kcf.iterU, kcf.RxFailedSensitivity/max(t_sim),'kx-');
plot(kcf.iterU, kcf.RxFailedModulation/max(t_sim),'yx-');
plot(kcf.iterU, kcf.RxFailedNoRxState/max(t_sim),'bx-');
%plot(kcf.iterU, kcf.BufferOverflow,'rx-');
xlabel('# iterations for consensus'); ylabel('Total packets/second');
legend('PacketsTX','RxReachedNoInterference','RxReachedInterference','RxFailedNoInterference',...
    'RxFailedInterference','RxFailedSensitivity','RxFailedModulation','RxFailedNoRxState');

eval(sprintf('save kcf_results_%s.mat',input_dir(1:end-1)));