%% MODEL FITTING FOR CORTEX - A9 (Samsung Galaxy II & III)
% This script models the active and idle power of the processor. Moreover,
% it also computes the relation between frequency and voltage.

%% Required variables
close all; clear all; clc;

%conversion units
Mhz2Hz=1e6; %from Mhz to Hz
V2mV=1e3; %from V to mV
W2mW=1e3; %from W to mW

%order of polynomial model fitting
order=[1 2 3 4 5];

%color codes for plotting curves
color={'b-','k-','m-','g-','c-'};

%% Voltage-frequency model
% The model for the relation between Voltage ($V$) and frequency ($f$) is 
% $V=p_1f^n + p_2f^{n-1} + ... + p_nf + p_{n+1}$ 

%frequency-Voltage measurements
f = [25 50 100 200 300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500 1600]*Mhz2Hz; %Hz 
V = [850 875 900 925 950 950 950 975 1000 1025 1075 1125 1175 1225 1250 1275 1325 1350]*1/V2mV; %V 

% model fitting
ws = warning('off','all');  % Turn off warning
for i=1:numel(order)
    [vf_p{i},vf_err{i}] = polyfit(f,V,order(i));
end
warning(ws)  % Turn it back on.

% display results
figure(1); plot(f/Mhz2Hz,V*V2mV,'ro'); hold on;set(0, 'defaultTextInterpreter', 'tex');

cad =' legend (''Measurements''';
for i=1:numel(order)
    pop_fit = polyval(vf_p{i},f,vf_err{i}); plot(f/Mhz2Hz,pop_fit*V2mV,color{i});    
    cad = [cad [',''' sprintf('%d',i) '-order error\pm' sprintf('%.2f (mV)',sqrt(vf_err{i}.normr*V2mV)) '''']];
end
eval ([cad ',''Location'', ''SouthEast'');']);

title('\bf{Model fitting for V-f_{clk} (CORTEX A9)}');
xlabel('f_{clk}^P (Mhz)'); ylabel('Voltage (mV)');

%% Active power model
% The model for the relation between Power active ($P_{act}$) and frequency ($f$) is 
% $P_{act}=gamma * nu * alpha * C_eq * f * V^2$ 
% We fit to a generic $P_{act}=p_1f^n + p_2f^{n-1} + ... + p_nf + p_{n+1}$ 

%model from paper
gamma = 1;
nu_alpha_Ceq = 0.34e-9;
Pact = nu_alpha_Ceq.*f.*V.*V;

% model fitting
ws = warning('off','all');  % Turn off warning
for i=1:numel(order)
    [Pa_p{i},Pa_err{i}] = polyfit(f,Pact,order(i));
end
warning(ws)  % Turn it back on.

% display results
figure(2);plot(f/Mhz2Hz,Pact*W2mW,'ro'); hold on;set(0, 'defaultTextInterpreter', 'tex');

cad =' legend (''Measurements''';
for i=1:numel(order)
    pop_fit = polyval(Pa_p{i},f,Pa_err{i}); plot(f/Mhz2Hz,pop_fit*W2mW,color{i});    
    cad = [cad [',''' sprintf('%d',i) '-order error\pm' sprintf('%.2f (mV)',sqrt(Pa_err{i}.normr*V2mV)) '''']];
end
eval ([cad ',''Location'', ''SouthEast'');']);

title('\bf{Model fitting for ACTIVE power (CORTEX A9)}');
xlabel('f_{clk}^P (Mhz)'); ylabel('P_{act} (mW)');

%% Idle power model
% The model for the relation between idle power ($P_{idle}$) and frequency ($f$) is 
% $P_{idle}=k(f) * P_{act} = K * P_{act}$ 

% P_idle is reported in paper "On Understanding the Energy Consumption of
% ARM-based Multicore Servers" 2013
% P_idle_0 = 0.025; %for f=25Mhz 
% f_P_idle = 200*Mhz2Hz;

% In the thesis "Evaluation of power management strategies on actual
% multiprocessor platforms", P_idle is reported as 30 mW (f=300Mhz), 60 mW
% (f=600Mhz) and 90 mW (f=1000Mhz)
P_idle_0 = 0.030; %for f=300Mhz 
f_P_idle = 300*Mhz2Hz;

ind=find(f==f_P_idle,1);
k = P_idle_0/Pact(ind(1));
Pidle = k.* Pact;

% % model fitting
% ws = warning('off','all');  % Turn off warning
% for i=1:numel(order)
%     [Pi_p{i},Pi_err{i}] = polyfit(f,Pidle,order(i));
% end
% warning(ws)  % Turn it back on.

% display results
figure(3);plot(f/Mhz2Hz,Pidle*W2mW,'k-+'); hold on;set(0, 'defaultTextInterpreter', 'tex');
% 
% cad =' legend (''Measurements''';
% for i=1:numel(order)
%     pop_fit = polyval(Pi_p{i},f,Pi_err{i}); plot(f/Mhz2Hz,pop_fit*1/W2mW,color{i});    
%     cad = [cad [',''1st-order error\pm' sprintf('%.2f (mV)',sqrt(Pi_err{i}.normr*1/W2mW)) '''']];
% end
% eval ([cad ',''Location'', ''SouthEast'');']);

title(['\bf{Model fitting for IDLE power (CORTEX A9) -> k\cdotP_{active}}' sprintf(' with k=%.3f', k)]);
xlabel('f_{clk}^P (Mhz)'); ylabel('P_{idle} (mW)');