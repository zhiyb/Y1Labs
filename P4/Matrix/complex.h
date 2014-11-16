#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>

const class Complex operator+(const class Complex& a, const class Complex& b);
const class Complex operator-(const class Complex& a, const class Complex& b);
const class Complex operator-(const class Complex& a);
const class Complex operator*(const class Complex& a, const double b);
const class Complex operator*(const class Complex& a, const class Complex& b);
const class Complex operator/(const class Complex& a, const double b);
const class Complex operator/(const class Complex& a, const class Complex& b);
bool operator==(const class Complex& a, const class Complex& b);
bool operator!=(const class Complex& a, const class Complex& b);
std::ostream& operator<<(std::ostream& out, const class Complex& c);

class Complex
{
public:
	Complex(double x = 0, double y = 0);
	double real(void) const {return x;}
	double imag(void) const {return y;}
	class Complex conj(void) const {return Complex(x, -y);}
	double abs(void) const {return std::sqrt(x * x + y * y);}
	double arg(void) const {return atan2(y, x);}
	class Complex pow(double p) const {return std::pow(abs(), p) * Complex(cos(arg() * p), sin(arg() * p));}
	class Complex sqrt(void) const {return pow(0.5);}
	class Complex exp(void) const {return std::exp(x) * Complex(cos(y), sin(y));}
	class Complex& operator/=(const double a);
	class Complex& operator/=(const class Complex& a);

private:
	double x, y;
};

#endif // COMPLEX_H
