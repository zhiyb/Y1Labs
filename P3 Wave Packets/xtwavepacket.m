alpha = 0.5;
k0 = 4.0;
beta = 0.5785;  %h//2m for electron cm^2/sec
x = linspace(-10,10,200);
t = linspace(0,3,200);
gamma = alpha + i*beta*t;
norm = exp(-k0*k0*alpha)*(alpha/2/pi)^0.25;
[X,T] = meshgrid(x,t);
gamma = alpha + i*beta*T;
phi = (norm./sqrt(gamma)).*exp(((2*alpha*k0+i*X).*(2*alpha*k0+i*X))./(4*gamma));
figure(1);
mesh(X,T,real(phi*phi'));
title('amplitude of the real part of \psi')
ylabel('time');
zlabel('amplitude of the real part of \psi');
xlabel('x');
figure(2)
hold off
t0 = 0.0;
phi0 = PSI(alpha,beta,k0,x,t0);
plot(x,real(phi0));
%pause
hold on
t1= 0.5;
phi1 = PSI(alpha,beta,k0,x,t1);
plot(x,real(phi1),'r-');
%pause;
t2= 1.0;
phi2 = PSI(alpha,beta,k0,x,t2);
plot(x,real(phi2),'g-');
ylabel('amplitude of the real part of \psi');
xlabel('t=0 (blue), t=1/2s (red), t=1s (green)');
title('electron wave packet evolution');