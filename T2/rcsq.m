function dv = rcsq(t, v)
c = 0.1 * 10 ^ -6;
r = 1590;
f = 200;
dv(1) = -1 / r / c * v(1) + 1 / r / c * sign(sin((2 * pi * f).*t));