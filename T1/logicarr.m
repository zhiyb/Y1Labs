function z = logicarr(x, y)
figure(1);
plot(x, y);
z = (y >= 0) .* y;
z = z + 0.5 * (y < 0);
z = (x <= 3 * pi / 2) .* z;
figure(2);
plot(x, z);
