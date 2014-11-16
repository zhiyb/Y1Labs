function dx = boost(t, x)
global v_in R C L T d
dx = zeros(2, 1);
if (pwm(t,T,d) == 1)
    dx(1) = 0 * x(1) + 0 * x(2) + 1/L * v_in;
    dx(2) = 0 * x(1) + -1/R/C * x(2) + 0 * v_in;
end
if ((pwm(t,T,d) == 0) && (x(1) > 0))
    dx(1) = 0 * x(1) + -1/L * x(2) + 1/L * v_in;
    dx(2) = 1/C * x(1) + -1/R/C * x(2) + 0 * v_in;
end
if ((pwm(t,T,d) == 0) && (x(1) <= 0))
    dx(1) = 0 * x(1) + 0 * x(2) + 0 * v_in;
    dx(2) = 0 * x(1) + -1/R/C * x(2) + 0 * v_in;
end
end
