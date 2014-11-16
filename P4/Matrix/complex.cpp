#include "complex.h"

Complex::Complex(double x, double y)
{
	this->x = x;
	this->y = y;
}

class Complex& Complex::operator/=(const double a)
{
	x /= a;
	y /= a;
	return *this;
}

class Complex& Complex::operator/=(const class Complex& a)
{
	*this = *this / a;
	return *this;
}

const class Complex operator+(const class Complex& a, const class Complex& b)
{
	return Complex(a.real() + b.real(), a.imag() + b.imag());
}

const class Complex operator-(const class Complex& a, const class Complex& b)
{
	return Complex(a.real() - b.real(), a.imag() - b.imag());
}

const class Complex operator-(const class Complex& a)
{
	return Complex(-a.real(), -a.imag());
}

const class Complex operator*(const class Complex& a, const double b)
{
	return Complex(a.real() * b, a.imag() * b);
}

const class Complex operator*(const class Complex& a, const class Complex& b)
{
	return Complex(a.real() * b.real() - a.imag() * b.imag(), a.real() * b.imag() + a.imag() * b.real());
}

const class Complex operator/(const class Complex& a, const double b)
{
	return Complex(a.real() / b, a.imag() / b);
}

const class Complex operator/(const class Complex& a, const class Complex& b)
{
	return a * b.conj() / (b.real() * b.real() + b.imag() * b.imag());
}

bool operator==(const class Complex& a, const class Complex& b)
{
	return a.real() == b.real() && a.imag() == b.imag();
}

bool operator!=(const class Complex& a, const class Complex& b)
{
	return !(a == b);
}

std::ostream& operator<<(std::ostream& out, const class Complex& c)
{
	return out << "(" << c.real() << "," << c.imag() << ")";
}
