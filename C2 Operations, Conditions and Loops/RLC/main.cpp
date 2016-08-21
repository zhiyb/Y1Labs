#include <iostream>
#include <math.h>

#define SQR(m) ((m) * (m))
#define RATIO(w) (1.0 / (sqrt(SQR(1.0 - SQR(w) * L * C) + SQR((w) * R * C))))

using namespace std;

int main(void)
{
	const double L = 30.0 / 1000.0, R = 2.2 * 1000, C = 10.0 / 1000000000.0;
	double omega;
	cout << "L = " << L << ", R = " << R << ", C = " << C << endl;
	for (omega = 20 * 1000; omega <= 250 * 1000; omega += 20 * 1000)
		cout << "omega = " << omega \
			<< ", ratio = " << RATIO(omega) << endl;
	return 0;
}

