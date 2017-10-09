% *****************************************************************************************
% Copyright (C) 2017 Juan C. SanMiguel and Andrea Cavallaro
% You may use, distribute and modify this code under the terms of the ACADEMIC PUBLIC
% license (see the attached LICENSE_WISE file).
%
% This file is part of the WiseMnet simulator
%
% Updated contact information:
%  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
%  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
%
% Please cite the following reference when publishing results obtained with WiseMnet:
%   J. SanMiguel & A. Cavallaro,
%   "Networked Computer Vision: the importance of a holistic simulator",
%   IEEE Computer, 50(7):35-43, Jul 2017, http://ieeexplore.ieee.org/document/7971873/
% *****************************************************************************************

%script to show icf results and the energy consumption
clc
close all
clear all

input_dir = '.../res/';
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
    icf.Terr{f} = ErrAcc(ind);
    icf.iter(f) = str2double(files(f).name(20:21)); %number of iteration
    icf.run(f) = str2double(files(f).name(6:8)); %number of iteration
    icf.err.mean(f) = mean(Err(ind));    
    icf.err.max(f) = max(Err(ind));
    icf.err.min(f) = min(Err(ind));
    icf.delay(f) = mean(delay(ind));
    icf.delay_std(f) = std(delay(ind));
    tot = tot + numel(ind);
     
    temp = 0;
    k=1;
    for n = 1:Ncams:numel(t_step)
        temp(k) = std(Err(n:n+Ncams-1));
        k=k+1;
    end
    icf.StdErr{f} = temp;    
    icf.err.std(f) = mean(temp);
   
end

icf.iterU = sort(unique(icf.iter), 'ascend');
icf.com = zeros(numel(icf.iterU), 1);
icf.pro = zeros(numel(icf.iterU), 1);
icf.citer = zeros(numel(icf.iterU), 1);
icf.countP = zeros(numel(icf.iterU), 1);
icf.countC = zeros(numel(icf.iterU), 1);

for r=1:Nruns       
    for c=1:Ncams
        i = find(icf.iter(r) == icf.iterU);
        icf.citer(i)=icf.citer(i)+1;
        
        ind = find(cams.usage{c,r}.PRO.eAct ~= -1);
        icf.pro(i) = icf.pro(i) + sum(cams.usage{c,r}.PRO.eAct(ind)+cams.usage{c,r}.PRO.eCol(ind));
        icf.countP(i) = icf.countP(i) + numel(ind);
        
        ind = find(cams.usage{c,r}.COM.eActTX ~= -1);
        icf.com(i) = icf.com(i) + sum(cams.usage{c,r}.COM.eActTX(ind)+cams.usage{c,r}.COM.eActRX(ind));
        icf.countC(i) = icf.countC(i) + numel(ind);
    end
end
icf.pro = icf.pro./(icf.citer.*icf.countP);
icf.com = icf.com./(icf.citer.*icf.countC);

%% compute statistics for error
icf.AvgErr = zeros(numel(icf.iterU), 1);
icf.stdErr = zeros(numel(icf.iterU), 1);
icf.MaxErr = zeros(numel(icf.iterU), 1);
icf.MinErr = zeros(numel(icf.iterU), 1);
icf.countE = zeros(numel(icf.iterU), 1);
icf.delayT = zeros(numel(icf.iterU), 1);
icf.delayS = zeros(numel(icf.iterU), 1);

for f=1:numel(files)   
    i = find(icf.iter(f) == icf.iterU);
    
    icf.AvgErr(i)=icf.AvgErr(i)+icf.err.mean(f);
    icf.stdErr(i)=icf.stdErr(i)+icf.err.std(f);    
    icf.MaxErr(i)=icf.MaxErr(i)+icf.err.max(f);
    icf.MinErr(i)=icf.MinErr(i)+icf.err.min(f);
    icf.delayT(i)=icf.delayT(i)+icf.delay(f);
    icf.delayS(i)=icf.delayS(i)+icf.delay_std(f);
    icf.countE(i) = icf.countE(i) + 1;
end
icf.AvgErr = icf.AvgErr./icf.countE;
icf.stdErr = icf.stdErr./icf.countE;
icf.MaxErr = icf.MaxErr./icf.countE;
icf.MinErr = icf.MinErr./icf.countE;
icf.delayT = icf.delayT./icf.countE;
icf.delayS = icf.delayS./icf.countE;


%% radio data

icf.PacketsTX = zeros(numel(icf.iterU), 1);
icf.RxReachedNoInterference = zeros(numel(icf.iterU), 1);
icf.RxReachedInterference = zeros(numel(icf.iterU), 1);
icf.RxFailedNoInterference = zeros(numel(icf.iterU), 1);
icf.RxFailedInterference = zeros(numel(icf.iterU), 1);
icf.RxFailedSensitivity = zeros(numel(icf.iterU), 1);
icf.RxFailedModulation = zeros(numel(icf.iterU), 1);
icf.RxFailedNoRxState = zeros(numel(icf.iterU), 1);
icf.BufferOverflow = zeros(numel(icf.iterU), 1);
icf.countRad = zeros(numel(icf.iterU), 1);

files = dir([input_dir '*.rad']);
%Nruns = numel(files);
for f=1:numel(files)    
    [node Ptx RxRNI RxRI RxFNI RxFI RxFS RxFM RxNRx bufO] ...
        = textread([input_dir files(f).name], '%f %f %f %f %f %f %f %f %f %f', 'commentstyle', 'shell');

    icf.rad.iter(f) = str2double(files(f).name(20:21)); %number of iteration
    icf.rad.run(f) = str2double(files(f).name(6:8)); %number of iteration
    
    i = find(icf.rad.iter(f) == icf.iterU);
    
    icf.PacketsTX(i) = icf.PacketsTX(i) + mean(Ptx);
    icf.RxReachedNoInterference(i) = icf.RxReachedNoInterference(i)+mean(RxRNI); 
    icf.RxReachedInterference(i) = icf.RxReachedInterference(i)+mean(RxRI);
    icf.RxFailedNoInterference(i) = icf.RxFailedNoInterference(i)+mean(RxFNI);
    icf.RxFailedInterference(i) = icf.RxFailedInterference(i)+mean(RxFI);
    icf.RxFailedSensitivity(i) = icf.RxFailedSensitivity(i)+mean(RxFS);
    icf.RxFailedModulation(i) = icf.RxFailedModulation(i)+mean(RxFM);
    icf.RxFailedNoRxState(i) = icf.RxFailedNoRxState(i)+mean(RxNRx);
    icf.BufferOverflow(i) = icf.BufferOverflow(i)+mean(bufO);
   
    icf.countRad(i) = icf.countRad(i) + 1;
end
icf.PacketsTX = icf.PacketsTX./icf.countRad;
icf.RxReachedNoInterference = icf.RxReachedNoInterference./icf.countRad;
icf.RxReachedInterference = icf.RxReachedInterference./icf.countRad;
icf.RxFailedNoInterference = icf.RxFailedNoInterference./icf.countRad;
icf.RxFailedInterference = icf.RxFailedInterference./icf.countRad;
icf.RxFailedSensitivity = icf.RxFailedSensitivity./icf.countRad;
icf.RxFailedModulation = icf.RxFailedModulation./icf.countRad;
icf.RxFailedNoRxState = icf.RxFailedNoRxState./icf.countRad;
icf.BufferOverflow = icf.BufferOverflow./icf.countRad;

%% plot results
figure;
subplot 311; 
% plot(icf.iterU,icf.AvgErr,'rx-'); hold on;
% plot(icf.iterU,icf.MaxErr, 'g--',icf.iterU,icf.MinErr, 'b--'); 
% legend('Average','Maximum','Minimum')
errorbar(icf.iterU,icf.AvgErr,icf.stdErr,'rx-');
axis([icf.iterU(1)-0.5 icf.iterU(end)+0.5 -inf inf]);
xlabel('# iterations for consensus'); ylabel('Average tracking error (m)');
title('icf results for single target tracking');
box off;

subplot 312; plot(icf.iterU,icf.pro*1e-3, 'ks-',icf.iterU,icf.com*1e-3, 'm*-'); 
axis([icf.iterU(1)-0.5 icf.iterU(end)+0.5 -inf inf]);

xlabel('# iterations for consensus'); ylabel('Energy consumption (J/sample)');
legend('Processing','Communication','Location','northwest');
box off;

subplot 313;
errorbar(icf.iterU,icf.delayT,icf.delayS,'rx-');
axis([icf.iterU(1)-0.5 icf.iterU(end)+0.5 -inf inf]);

xlabel('# iterations for consensus'); ylabel('Average delay (s)');
box off;

figure;
plot(icf.iterU, icf.PacketsTX/max(t_sim),'rx-'); hold on;
plot(icf.iterU, icf.RxReachedNoInterference/max(t_sim),'gx-');
plot(icf.iterU, icf.RxReachedInterference/max(t_sim),'bx-');
plot(icf.iterU, icf.RxFailedNoInterference/max(t_sim),'cs-');
plot(icf.iterU, icf.RxFailedInterference/max(t_sim),'m+-');
plot(icf.iterU, icf.RxFailedSensitivity/max(t_sim),'kx-');
plot(icf.iterU, icf.RxFailedModulation/max(t_sim),'yx-');
plot(icf.iterU, icf.RxFailedNoRxState/max(t_sim),'bx-');
%plot(icf.iterU, icf.BufferOverflow,'rx-');
xlabel('# iterations for consensus'); ylabel('Total packets/second');
legend('PacketsTX','RxReachedNoInterference','RxReachedInterference','RxFailedNoInterference',...
    'RxFailedInterference','RxFailedSensitivity','RxFailedModulation','RxFailedNoRxState');

eval(sprintf('save icf_results_%s.mat',input_dir(1:end-1)));
