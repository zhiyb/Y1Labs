global v_in R C L T d
v_in=1.5;
R=680;
C=200 * 10 ^ -6;
L=180 * 10 ^ -6;
f_pwm = 10e3;
T = 0.000027; %1/f_pwm;
options = odeset('MaxStep', 1e-5);
d=0.85; %0.24;
v_con = v_in/(1-d);
[t, x] = ode23(@boost, [0:1e-7:0.2], [0 0], options);
plot(t, pwm(t,T,d), t, x);
%legend('PWM', 'iL (0.24)', 'vout (0.24)', 'vout - continuous (0.24)');
xlabel('time/s');
title('Boost Converter');
