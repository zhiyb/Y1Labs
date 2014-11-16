#include <stdio.h>
#include <math.h>

#define SQR(m) ((m) * (m))
#define RATIO(R, L, C, w) (1.0 / (sqrt(SQR(1.0 - SQR(w) * (L) * (C)) + \
	SQR((w) * (R) * (C)))))

#ifdef linux
#define NOTEC "\e[93m"
#define TITLEC "\e[94m"
#define FREQC "\e[91m"
#define RATIOC "\e[92m"
#define MAXC "\e[97m"
#define ENDC "\e[0m"
#else
#define NOTEC
#define TITLEC
#define FREQC
#define RATIOC
#define MAXC
#define ENDC
#endif

int main(void)
{
	const double L = 30.0 / 1000.0, R = 2.2 * 1000, C = 10.0 / 1000000000.0;
	double o, maxo = 20 * 1000;
	printf(NOTEC "L = %g, R = %g, C = %g\n", L, R, C);
	puts(TITLEC "Freq (Rad/s)\tRatio");
	for (o = 20 * 1000; o <= 250 * 1000; o += 20 * 1000) {
		double r = RATIO(R, L, C, o);
		printf(FREQC "%.2f\t" RATIOC "%.2f\n", o, r);
		maxo = RATIO(R, L, C, maxo) > r ? maxo : o;
	}
	puts(MAXC "****** Maximum ******");
	printf(FREQC "%.2f\t" RATIOC "%.2f\t" ENDC "\n", \
		maxo, RATIO(R, L, C, maxo));
	return 0;
}

