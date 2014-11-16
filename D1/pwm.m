function v = pwm(t, T, d)
    v = (mod(t, T) / T) <= d;
end
