%%
close all; clear; clc
%% Spændingstab i den aktive ensretter
% 1. måling
data1 = load('delta_vout_fase1.mat');
% X-akse fra .csv fil (tid [s])
t1 = data1.deltavoutfase1.second;
% Inputspænding fra .csv fil (Volt [V])
vin = data1.deltavoutfase1.Volt1;
% Outputspænding fra .csv fil (Volt [V])
vout = data1.deltavoutfase1.Volt;
% Antal samples i signalerne
N1 = length(vin);
n1 = 0:N1-1;
% Varighed af signalerne
Tdur1 = t1(2000)-t1(1);
% Samplevarighed
Ts1 = Tdur1/N1;
% Samplingfrekvens
fs1 = 1/Ts1;
% Midling af input og output
vin_mid = medfilt1(vin,200);
vout_mid = medfilt1(vout,200);
% Max værdi for vin og vout
vin_mid_max = max(vin_mid);
vout_mid_max = max(vout_mid);


% Plot af hele sigalet
figure
subplot(211)
plot(n1*Ts1,vin_mid,'b'), hold on
plot(n1*Ts1,vout_mid,'r')
xlabel('Tid, [s]'), ylabel('Fase 1 & Vout, [V]')
legend('Fase 1','Vout'), grid
title('Fase 1 vs. Vout, 1. måling')
% Udvælgelse af segmenter, hvor Fase 1 > Vout
vin_seg = vin_mid(924:1452);
vout_seg = vout_mid(924:1452);
% Plot af segmenter
subplot(212)
plot(n1(924:1452)*Ts1,vin_seg), hold on
plot(n1(924:1452)*Ts1,vout_seg )
xlabel('Tid, [s]'), ylabel('Fase 1 & Vout, [V]')
legend('Fase 1','Vout'), grid
title('Segment af Vin og Vout')
% Udregning af spændingstabet, (Vin - Vout) 
v_delta1 = mean(vin_seg)-mean(vout_seg);

%% 2. måling
%close all; clear; clc

data2 = load('delta_vout_fase1_2.mat');

t2 = data2.scope3.second;
vin2 = data2.scope3.Volt1;
vout2 = data2.scope3.Volt;
N2 = length(vin2);
n2 = 0:N2-1;
Tdur2 = t2(2000)-t2(1);
Ts2 = Tdur2/N2;
fs2 = 1/Ts2;

vin_mid2 = medfilt1(vin2,200);
vout_mid2 = medfilt1(vout2,200);
% Max værdi for vin og vout
vin_mid_max2 = max(vin_mid2);
vout_mid_max2 = max(vout_mid2);


figure
subplot(211)
plot(n2*Ts2,vin_mid2,'b'), hold on
plot(n2*Ts2,vout_mid2,'r')
xlabel('Tid, [s]'), ylabel('Fase 1 & Vout, [V]')
legend('Fase 1','Vout'), grid
title('Fase 1 vs. Vout, 2. måling')


start = 640;
slut = 955;
vin_seg2 = vin_mid2(start:slut);
vout_seg2 = vout_mid2(start:slut);
subplot(212)
plot(n2(start:slut)*Ts2,vin_seg2), hold on
plot(n2(start:slut)*Ts2,vout_seg2 )
xlabel('Tid, [s]'), ylabel('Fase 1 & Vout, [V]')
legend('Fase 1','Vout'), grid
title('Segment af Vin og Vout')


v_delta2 =mean(vin_seg2)-mean(vout_seg2);

