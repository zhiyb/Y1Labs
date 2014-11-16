function v=pwm2(t,T,d)

T=2;
d=0.8;

for k=0:4
    t=k*T:0.001:(k+1)*T;
    v=mod(t,(k+1)*d*T)./t;
    v(v<1)=0;
    plot(t,v); hold on
end
