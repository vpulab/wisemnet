close all
clear all
clc
%% SETTINGS
%conversion units
Mhz2Hz=1e6; %from Mhz to Hz
V2mV=1e3; %from V to mV
W2mW=1e3; %from W to mW

%order of polynomial model fitting
order=[1 2 3 4 5];

%color codes for plotting curves
color={'b-','k-','m-','g-','c-'};
figure(1);

%% SA1100 
% Active power model
% The model for the relation between Power active ($P_{act}$) and frequency ($f$) is 
% $P_{act}=C_eq * f * V^2$.
% We fit to a generic $P_{act}=p_1f^n + p_2f^{n-1} + ... + p_nf + p_{n+1}$ 

% Get measurements from paper model
V = 0.75:0.05:1.44;
f = 239.28.*(V - 0.5);
f = f*Mhz2Hz;

Ceq = 0.67e-9;
Pact = Ceq.*f.*V.*V;
Pact = Pact + 0.005*rand(1,numel(Pact));

ws = warning('off','all');  % Turn off warning
for i=1:numel(order)
    [Pa_p{i},Pa_err{i}] = polyfit(f,Pact,order(i));
end
warning(ws)  % Turn it back on.

for i=1:numel(order)
    fprintf(' SA1100 - order %d error %.2f (mV)\n',i, sqrt(Pa_err{i}.normr*V2mV));
end
fprintf('\n');

% plot(f,Pact*W2mW,'ro'); hold on;
% pop_fit = polyval(Pa_p{3},f,Pa_err{3}); 
% plot(f,pop_fit*W2mW,'b+');  

%% CORTEX A9
% Active power model
% The model for the relation between Power active ($P_{act}$) and frequency ($f$) is 
% $P_{act}=gamma * nu * alpha * C_eq * f * V^2$ 
% We fit to a generic $P_{act}=p_1f^n + p_2f^{n-1} + ... + p_nf + p_{n+1}$ 
% f = [25 50 100 200 300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500 1600]*Mhz2Hz; %Hz 
% V = [850 875 900 925 950 950 950 975 1000 1025 1075 1125 1175 1225 1250 1275 1325 1350]*1/V2mV; %V 

f = [300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500 1600]*Mhz2Hz; %Hz 
V = [950 950 950 975 1000 1025 1075 1125 1175 1225 1250 1275 1325 1350]*1/V2mV; %V 

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

for i=1:numel(order)
    fprintf(' CORTEX A9 - order %d error %.2f (mV)\n',i, sqrt(Pa_err{i}.normr*V2mV));
end
fprintf('\n');
plot(f/Mhz2Hz,Pact*W2mW,'ro'); hold on;
pop_fit = polyval(Pa_p{3},f,Pa_err{3}); 
plot(f/Mhz2Hz,pop_fit*W2mW,'b+-');  

%% CORTEX A15
% Active power model
% The model for the relation between Power active ($P_{act}$) and frequency ($f$) is 
% $P_{act}=p_1f^n + p_2f^{n-1} + ... + p_nf + p_{n+1}$ 

f = [800 900 1000 1100 1200 1300 1400 1500 1600]*1e6; %Mhz (1e6)
f = f*1e-9;

%generate measurements from model in thesis
p = [0.569 -0.426 0.276]; %model params from paper
Pact = p(1).*f.*f + p(2).*f + p(3); %Pact = Pact.* 1e-5 .* rand(1, numel(Pact));
Pact = Pact + 0.05*rand(1,numel(Pact));
scaling_factor = [1 2];
%f=f*1e9;

% model fitting
ws = warning('off','all');  % Turn off warning
for i=1:numel(order)
    [Pa_p{i},Pa_err{i}] = polyfit(f,Pact,order(i));
end
warning (ws);  % Turn on warning


for i=1:numel(order)
    fprintf(' CORTEX A15 - order %d error %.2f (mV)\n',i, sqrt(Pa_err{i}.normr*V2mV));
end
fprintf('\n');
plot(f*1e3,Pact*W2mW,'go'); hold on;
pop_fit = polyval(Pa_p{3},f,Pa_err{3}); 
plot(f*1e3,pop_fit*W2mW,'k+-');  
%% CORTEX A15
% Active power model
% The model for the relation between Power active ($P_{act}$) and frequency ($f$) is 
% $P_{act}=p_1f^n + p_2f^{n-1} + ... + p_nf + p_{n+1}$ 

%data from http://www.usp-forum.de/nexus-10-root-flash-hack/95716-howto-nexus-10-undervolting-overclocking-akku-sparen.html
f = [100 200 300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000]*1e6; %Hz
v = [700 725 750 775 800 825 850 875 900 925 950 975 1000 105 1050 1075 1125 1175 1225 1300]*1e-3; %V

%data from thesis
f = [800 900 1000 1100 1200 1300 1400 1500 1600]*1e6; %Hz
v = [900 925 962 1000 1025 1062 1100 1137 1162]*1e-3; %V

%generate measurements from model in thesis
%...

%% KRAIT 400
% Active power model
% The model for the relation between Power active ($P_{act}$) and frequency ($f$) is 
% $P_{act}=p_1f^n + p_2f^{n-1} + ... + p_nf + p_{n+1}$ 

%data reported in power_profile.xml of nexus 5
f = [.3 .4224 .6528 .7296 .8832 .96 1.0368 1.1904 1.2672 1.4976 1.574 1.728 1.958 2.2656 ]*1e9; %Hz 
I = [57.9 88.2 99.6 138.8 149.6 170.2 178.3 189.1 232.1 256.5 266.4 287.7 325.7 386.2]*1e-3; %A

%stock voltages from http://forum.xda-developers.com/showpost.php?p=47425927&postcount=193
v = [800 800 825 835 855 865 875 900 915 950 965 995 1040 1100]*1e-3; %V
%v = 9;
Pact = I.* v;

% model fitting
ws = warning('off','all');  % Turn off warning
for i=1:numel(order)
    [Pa_p{i},Pa_err{i}] = polyfit(f,Pact,order(i));
end
warning (ws);  % Turn on warning


for i=1:numel(order)
    fprintf(' KRAIT400 - order %d error %.2f (mV)\n',i, sqrt(Pa_err{i}.normr*V2mV));
end
fprintf('\n');
% plot(f/1e6,Pact*W2mW,'co'); hold on;
% pop_fit = polyval(Pa_p{3},f,Pa_err{3}); 
% plot(f/1e6,pop_fit*W2mW,'m+-');  

xlabel('f^p_{clk} (Mhz)'); ylabel('Power consumption (mW)');
legend('Cortex-A9 measurements', 'Cortex-A9 model (3rd order)','Cortex-A15 measurements', 'Cortex-A15 model (3rd order)', 'Location', 'NorthWest');
box off;
axis([275 1600 50 1100]);