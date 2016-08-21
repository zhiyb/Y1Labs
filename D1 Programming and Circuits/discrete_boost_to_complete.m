
%Circuit data
v_in=
R=
C=
L=

%Voltage divider
R_1=
R_2=
gamma=R_2/(R_1+R_2);

%Total Resistance:
R_T=1/(1/R+1/(R_1+R_2));

%Iniital duty cycle:
d=0.8;

%system matrices:
A_closed= 
A_open_forward= 
A_open_reverse= 
B_closed= 
B_open_forward= 
B_open_reverse= 

%pwm frequency:
f_pwm = 10e3;
T = 1/f_pwm;

%simulation sample length:
h = T/1e3;

%control update sample length:
f_control =  f_pwm/10;
tau = 1/f_control; 

%Simulation paramters:
final_time = 1;

%Initialisation
x=zeros(2,round(final_time/h));
duty_cycle=zeros(1,round(final_time/h));

I=[1 0; 0 1];

% x(1) = i_L
% x(2) = v_out

%initial condition
x(:,1)=[0 0.5];

%control setpoint 
r=10;

%controller gains
k_p=0.0015;

for t=2*h:h:final_time
    
    % measured voltage via voltage divider:
    v_adc = gamma* x(2,round(t/h));
    % voltage error to desired setpoint value r:
    v_error=v_adc/gamma-r;
    
    %duty cycle update:
      if rem(t,tau)==0
      d=d-k_p*(v_error);
  end 
      if pwm(t,T,d)==1 
        A=A_closed;
        B=B_closed;
    end
    if pwm(t,T,d)==0 && x(1,round(t/h))>0
            A=A_open_forward;
            B=B_open_forward;
    end
    if pwm(t,T,d)==0 && x(1,round(t/h)) <=0
        A=A_open_reverse;
        B=B_open_reverse;
    end
    x(:,round(t/h) +1)= (I+h*A)*x(:,round(t/h)) + v_in*h*B;
    duty_cycle(round(t/h) +1)= d;
end

t= [2*h:h:final_time+2*h];
plot(t,x)
hold on 
 plot(t,pwm(t,T,duty_cycle),'r')
 plot(t,duty_cycle,'m') 
 xlabel('Time (s)','FontSize',16)
 ylabel('Voltage (V), Current (A) ','FontSize',16)
 legend('i_L','v_{\rm out}','pwm')
hold off
