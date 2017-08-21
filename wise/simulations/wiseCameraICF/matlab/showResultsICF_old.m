clc
close all
clear all

files = dir('res/*.res');

for i=1:length(files)    
    [t_sim t_step NID TID Zx Zy Inix Iniy ESTx ESTy GTx GTy Err ErrAcc] ...
        = textread(['res/' files(i).name], '%f %f %f %f %f %f %f %f %f %f %f %f %f %f', 'commentstyle', 'shell');
   
    Nc = size(unique(NID),1);
    Nt = size(unique(TID),1);
    ind = find(t_step == t_step(end));
    Terr{i} = ErrAcc(ind);
    Niter(i) = str2double(files(i).name(28:29)); %number of iteration
    Merr(i) = mean(ErrAcc(ind)/t_step(end));
end

figure;
plot(Niter,Merr, '+-');
save ICF_results.mat

load ../WiseCameraKCF/KCF_results.mat
hold on;
plot(Niter,Merr, 'r+-');

title('ICF results for single target tracking'); xlabel('# iterations for consensus'); ylabel('mean error');
legend('ICF', 'KCF');