function i=diode(is, v, n, vt)
i = is * (exp(v / (n * vt)) - 1);
