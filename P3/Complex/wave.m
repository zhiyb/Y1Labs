load wave.dat;
t = wave(:, 1);
psi0 = wave(:, 2);
psi0_5 = wave(:, 3);
psi1 = wave(:, 4);
hold off;
figure(1);
plot(t, psi0, 'b-', t, psi0_5, 'r-', t, psi1, 'g-');
ylabel('amplitude of the real part of \psi');
xlabel('t=0 (blue), t=1/2s (red), t=1s (green)');
title('electron wave packet evolution');
clear wave;
