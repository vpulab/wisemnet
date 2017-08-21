%% MODEL FITTING FOR CORTEX - SA1100 (old processor widely used, 74-206Mhz)
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

%frequency-Voltage model in paper "Energy-efficient DSPs for wireless
%sensor networks", SPM2002
V = 0.75:0.05:1.44;
f = 239.28.*(V - 0.5);
f = f*Mhz2Hz;

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

title('\bf{Model fitting for V-f_{clk} (CORTEX SA1100)}');
xlabel('f_{clk}^P (Mhz)'); ylabel('Voltage (mV)');

%% Active power model
% The model for the relation between Power active ($P_{act}$) and frequency ($f$) is 
% $P_{act}=C_eq * f * V^2$.
% We fit to a generic $P_{act}=p_1f^n + p_2f^{n-1} + ... + p_nf + p_{n+1}$ 

% Get measurements from paper model
Ceq = 0.67e-9;
Pact = Ceq.*f.*V.*V;

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

title('\bf{Model fitting for ACTIVE power (CORTEX SA1100)}');
xlabel('f_{clk}^P (Mhz)'); ylabel('P_{act} (mW)');

%% Idle power model
% The model for the relation between idle power ($P_{idle}$) and frequency ($f$) is 
% $P_{idle}=k(f) * P_{act} = K * P_{act}$ 

% P_idle is reported in datasheet https://stuff.mit.edu/afs/sipb/contrib/doc/specs/ic/cpu/arm/sa1100-update.pdf
P_idle_0 = 0.065; %for f=190Mhz 
f_P_idle = 190*Mhz2Hz;

ind=find(round(f/(10*Mhz2Hz)) == round(f_P_idle/(10*Mhz2Hz)),1);
k = P_idle_0/Pact(ind(1));
Pidle = k.* Pact;

% display results
figure(3);plot(f/Mhz2Hz,Pidle*W2mW,'k-+'); hold on;set(0, 'defaultTextInterpreter', 'tex');
title(['\bf{Model fitting for IDLE power (CORTEX SA1100) -> k\cdotP_{active}}' sprintf(' with k=%.3f', k)]);
xlabel('f_{clk}^P (Mhz)'); ylabel('P_{idle} (mW)');