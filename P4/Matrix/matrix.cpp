#include "complex.h"
#include "matrix.h"

using namespace std;

const Complex randomNumber(const Complex& min, const Complex& max, default_random_engine& dre)
{
	uniform_real_distribution<double> drReal(min.real(), max.real()), drImag(min.imag(), max.imag());
	return Complex(drReal(dre), drImag(dre));
}
