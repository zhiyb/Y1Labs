%n = 35.0966;
%is = 1.422*10^-7;
%v = (-2 : 0.01 : 2);
%vt = 25.85*10^-3;
%iem = diode(is, v, n, vt);

load data.txt;
vdata = data(:, 1);
idata = data(:, 2);
pdata = data(:, 3);

hold off;
%plot(v, iem, vdata, idata);
plot(vdata, idata, vdata, pdata);

clear data;
