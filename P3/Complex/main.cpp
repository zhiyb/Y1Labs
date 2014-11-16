#include <iostream>
#include <complex>
#include <cmath>
#include <fstream>
#include "complex.h"

#ifdef __linux__
#include <unistd.h>
#define Sleep(s)	usleep(s * 1000)
#else
#include <windows.h>
#endif

using namespace std;

void test(void)
{
	class Complex a(3, 8), b(-2, 5);
	complex<double> sa(3, 8), sb(-2, 5);

	cout << "Info: class Complex / std::complex" << endl << endl;
	cout << "a: " << a << " / " << sa << endl;
	cout << "a.real(): " << a.real() << " / " << real(sa) << endl;
	cout << "a.imag(): " << a.imag() << " / " << imag(sa) << endl;
	cout << "a.conj(): " << a.conj() << " / " << conj(sa) << endl;
	cout << "a.abs(): " << a.abs() << " / " << abs(sa) << endl;
	cout << "a.arg(): " << a.arg() << " / " << arg(sa) << endl;
	cout << "a.sqrt(): " << a.sqrt() << " / " << sqrt(sa) << endl;
	cout << "a.exp(): " << a.exp() << " / " << exp(sa) << endl;

	cout << endl << "b: " << b << " / " << sb << endl;
	//cout << "-b: " << -b << " / " << -sb << endl;
	cout << "b.real(): " << b.real() << " / " << real(sb) << endl;
	cout << "b.imag(): " << b.imag() << " / " << imag(sb) << endl;
	cout << "b.conj(): " << b.conj() << " / " << conj(sb) << endl;
	cout << "b.abs(): " << b.abs() << " / " << abs(sb) << endl;
	cout << "b.arg(): " << b.arg() << " / " << arg(sb) << endl;
	cout << "b.sqrt(): " << b.sqrt() << " / " << sqrt(sb) << endl;
	cout << "b.exp(): " << b.exp() << " / " << exp(sb) << endl;

	cout << endl << "a + b: " << (a + b) << " / " << (sa + sb) << endl;
	cout << "a - b: " << (a - b) << " / " << (sa - sb) << endl;
	cout << "a * b: " << (a * b) << " / " << (sa * sb) << endl;
	cout << "a / b: " << (a / b) << " / " << (sa / sb) << endl;
	cout << "a == b: " << (a == b) << " / " << (sa == sb) << endl;
	cout << "a != b: " << (a != b) << " / " << (sa != sb) << endl;
}

#define PI	3.14159265359
class Complex psi(double t, double x)
{
	double alpha = 0.5, k0 = 4.0, beta = 0.5785;
	class Complex gamma(alpha, beta * t);
	double norm = exp(-k0 * k0 * alpha) * pow(alpha / 2.0 / PI, 0.25);
	class Complex L(2.0 * alpha * k0, x);
	return (norm / gamma.sqrt()) * Complex(L * L / 4.0 / gamma).exp();
}

#define N	4096
#define L	25
#define PLOT_FILE	"wave"
#define PLOT_MIN	-10
#define PLOT_MAX	10
#define PLOT_STEP	0.001
int main(void)
{
	Sleep(1000);		// Get ride of a wired warning message
#if 0
	//test();
	double x;
	cout << "Enter x value for evaluate:" << endl;
	cin >> x;
	cout << endl << "t = 0:  \t" << psi(0, x) << endl;
	cout << "t = 0.5:\t" << psi(0.5, x) << endl;
	cout << "t = 1:  \t" << psi(1, x) << endl << endl;

	double sum = 0;
	for (double x = -L; x <= L; x += 2.0 * L / N) {
		class Complex res = psi(0, x);
		if (x == -L || x == L)
			sum += (res * res.conj()).real() / 2;
		else
			sum += (res * res.conj()).real();
	}
	sum *= 2.0 * L / N;
	cout << "Integration of psi * psi.conj() from " << -L << " to " << L << " with " << N << " steps:" << endl;
	cout << sum << endl;
#else
	fstream data(PLOT_FILE ".dat", fstream::out), m(PLOT_FILE ".m", fstream::out);
	if (!data.is_open() || !m.is_open()) {
		cerr << "Cannot open output file!" << endl;
		return 1;
	}
	for (double x = PLOT_MIN; x <= PLOT_MAX; x += PLOT_STEP)
		data << x << '\t' << psi(0, x).real() << '\t' << psi(0.5, x).real() << '\t' << psi(1, x).real() << endl;
	m << "load " PLOT_FILE ".dat;" << endl;
	m << "t = " PLOT_FILE "(:, 1);" << endl;
	m << "psi0 = " PLOT_FILE "(:, 2);" << endl;
	m << "psi0_5 = " PLOT_FILE "(:, 3);" << endl;
	m << "psi1 = " PLOT_FILE "(:, 4);" << endl;
	m << "hold off;" << endl;
	m << "figure(1);" << endl;
	m << "plot(t, psi0, 'b-', t, psi0_5, 'r-', t, psi1, 'g-');" << endl;
	m << "ylabel('amplitude of the real part of \\psi');" << endl;
	m << "xlabel('t=0 (blue), t=1/2s (red), t=1s (green)');" << endl;
	m << "title('electron wave packet evolution');" << endl;
	m << "clear wave;" << endl;
	data.close();
	m.close();
#endif

	return 0;
}
