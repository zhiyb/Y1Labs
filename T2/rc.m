function dv = rc(t, v)
c = 0.1 * 10 ^ -6;
r = 1590;
f = 10000;
dv(1) = -1 / r / c * v(1) + 1 / r / c * sin((2 * pi * f) .* t);