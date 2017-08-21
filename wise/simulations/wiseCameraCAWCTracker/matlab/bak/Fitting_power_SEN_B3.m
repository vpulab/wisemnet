close all
clear all
clc

% measured data for B3 processor
f = [10000000    12000000    14000000    16000000    18000000    20000000    22000000    24000000];

% Pactive=c1*f+c2
Pa_c3=0;
Pa_c2=0;
Pa_c1=5.1e-6;
Pa_c0=13.1;
Pact = Pa_c3.*f.*f.*f + Pa_c2.*f.*f + Pa_c1.*f + Pa_c0;

% Pidle=a1*f+a2
Pi_c3=0;
Pi_c2=0;
Pi_c1=3.35e-6;
Pi_c0=4.4;
Pidle = Pi_c3.*f.*f.*f + Pi_c2.*f.*f + Pi_c1.*f + Pi_c0;

figure(3);
plot(f/1e6, Pact, 'r+-', f/1e6, Pidle, 'k*-');
legend('P_{active}', 'P_{idle}', 'Location','SouthEast'); xlabel('f_{clk}^{s} SENSING (MHz)'); ylabel('Power (mW)');
title('POWER CONSUMPTION for B3 SENSING MODULE');