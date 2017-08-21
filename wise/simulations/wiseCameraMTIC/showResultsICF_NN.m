clc
close all
clear all

rootdir = 'res/';
% rootdir = 'res_Nt2/';
% rootdir = 'res_Nt1_clutter_level/';

files = dir([rootdir '*.res']);

for i=1:length(files)    
     [t_sim t_step NID TID Zx Zy Inix Iniy ESTx ESTy GTx GTy Err ErrAcc] ...
         = textread([rootdir files(i).name], '%f %f %f %f %f %f %f %f %f %f %f %f %f %f', 'commentstyle', 'shell');
   
    Nc = size(unique(NID),1);
    Nt = size(unique(TID),1);
    ind = find(t_step == t_step(end));
    Terr{i} = ErrAcc(ind);
    Lam(i) = str2double(files(i).name(39:43)); %number of iteration
    iter = str2double(files(i).name(30:31));
    Merr(i) = mean(ErrAcc(ind)/t_step(end));
end

figure;
plot(Merr, '+-');
save ICF_NN_results.mat

% load ../WiseCameraKCF/KCF_results.mat
% hold on;
% plot(Lam,Merr, 'r+-');

set(gca,'XTick',[1:length(files)]);
cad = ['set(gca,''XTickLabel'',{'''];
    
for i=1:length(files)    
   cad = [cad '' sprintf('%.4f', str2double(files(i).name(39:43))/10000) ''','''];
end
cad = [cad(1:end-2) '});'];
eval(cad);    

title(sprintf('ICF-NN results for multiple target tracking k=%d',iter)); xlabel('Clutter level - Lambda factor'); ylabel('Mean error for all targets');
legend('ICF-NN', 'KCF');