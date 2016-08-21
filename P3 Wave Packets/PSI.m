function psi = PSI(a,b,k0,x,t)
gamma = a + i*b*t;
norm = exp(-k0*k0*a)*(a/2/pi)^0.25;
L = 2*a*k0+i*x;
psi = (norm/sqrt(gamma))*exp((L.*L)/(4*gamma));
