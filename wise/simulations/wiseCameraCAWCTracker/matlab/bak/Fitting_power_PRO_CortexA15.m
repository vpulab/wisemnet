%% MODEL FITTING FOR CORTEX - A15 (Google Nexus 10)
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

%% Voltage-frequency fitting
% The model for the relation between Voltage ($V$) and frequency ($f$) is 
% $V=p_1f^n + p_2f^{n-1} + ... + p_nf + p_{n+1}$ 

%frequency-Voltage measurements 
% Obtained from "The Energy/Frequency Convexity Rule for a Program’s Energy Consumption: Modeling, Thermosensitivity and Applications"(Pag 48, Table 3.6)
f = [800 900 1000 1100 1200 1300 1400 1500 1600]*Mhz2Hz; %Hz 
V = [900 925 962 1000 1025 1062 1100 1137 1162]*1/V2mV; %V 

% model fitting
ws = warning('off','all');  % Turn off warning
for i=1:numel(order)
    [vf_p{i},vf_err{i}] = polyfit(f,V,order(i));
end
warning (ws);  % Turn on warning

% display results
figure(1); plot(f/Mhz2Hz,V*V2mV,'ro'); hold on;set(0, 'defaultTextInterpreter', 'tex');

cad =' legend (''Measurements''';
for i=1:numel(order)
    pop_fit = polyval(vf_p{i},f,vf_err{i}); plot(f/Mhz2Hz,pop_fit*V2mV,color{i});    
    cad = [cad [',''' sprintf('%d',i) '-order error\pm' sprintf('%.2f (mV)',sqrt(vf_err{i}.normr*V2mV)) '''']];
end
eval ([cad ',''Location'', ''SouthEast'');']);

title('\bf{Model fitting for V-f_{clk} (CORTEX A15)}');
xlabel('f_{clk}^P (Mhz)'); ylabel('Voltage (mV)');

%% Active power model
% The model for the relation between Power active ($P_{act}$) and frequency ($f$) is 
% $P_{act}=p_1f^n + p_2f^{n-1} + ... + p_nf + p_{n+1}$ 

f = [800 900 1000 1100 1200 1300 1400 1500 1600]*1e6; %Mhz (1e6)
f = f*1e-9;

%generate measurements from model in thesis
p = [0.569 -0.426 0.276]; %model params from paper
Pact = p(1).*f.*f + p(2).*f + p(3); %Pact = Pact.* 1e-5 .* rand(1, numel(Pact));
scaling_factor = [1 2];
f=f*1e9;

% model fitting
ws = warning('off','all');  % Turn off warning
for i=1:numel(order)
    [Pa_p{i},Pa_err{i}] = polyfit(f,Pact,order(i));
end
warning (ws);  % Turn on warning

% display results
figure(2);plot(f,Pact*W2mW,'k-+'); hold on;set(0, 'defaultTextInterpreter', 'tex');

cad =' legend (''Measurements''';
for i=1:numel(order)
    pop_fit = polyval(Pa_p{i},f,Pa_err{i}); plot(f,pop_fit*W2mW,color{i});    
    cad = [cad [',''' sprintf('%d',i) '-order error\pm' sprintf('%.2f (mV)',sqrt(Pa_err{i}.normr*V2mV)) '''']];
end
eval ([cad ',''Location'', ''SouthEast'');']);

xlabel('f_{clk}^P (Ghz)'); ylabel('P_{act} (mW)');
title('\bf{Model fitting for ACTIVE power - frequency relation (CORTEX A15)}');

%% Idle power model
% The model for the relation between idle power ($P_{idle}$) and frequency ($f$) is 
% $P_{idle}=k(f) * P_{act} = K * P_{act}$ 

%data from thesis
k = 0.111;
Pidle = k.* Pact;

% display results
figure(3);plot(f,Pidle*W2mW,'k-+'); hold on;set(0, 'defaultTextInterpreter', 'tex');
title(['\bf{Model fitting for IDLE power (CORTEX A15) -> k\cdotP_{active}}' sprintf(' with k=%.3f', k)]);
xlabel('f_{clk}^P (Ghz)'); ylabel('P_{idle} (mW)');