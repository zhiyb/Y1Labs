#ifndef MATRIX_H
#define MATRIX_H

#include <random>
#include <algorithm>
#include <vector>
#include <chrono>
#include "complex.h"

using namespace std;

template <typename T> T randomNumber(const T& min, const T& max, default_random_engine& dre);
const Complex randomNumber(const Complex& min, const Complex& max, default_random_engine& dre);

template <typename T> void randomFill(const unsigned int size, const T& min, const T& max, default_random_engine& dre, vector<T>& v);
template <typename T> void randomFill(const unsigned int size, const T& min, const T& max, default_random_engine& dre, vector<vector<T> >& m);
template <typename T> void randomFillTridiagonal(const unsigned int size, const T& min, const T& max, default_random_engine& dre, vector<vector<T> >& m);

template <typename T> void TridiagonalSolve(const vector<vector<T> >& m, vector<T> R, vector<T>& L);

template <typename T> ostream& operator<<(ostream& out, const vector<vector<T> >& m);
template <typename T> ostream& operator<<(ostream& out, const vector<T>& v);

template <typename T> void TridiagonalSolve(const vector<vector<T> >& m, vector<T> R, vector<T>& L)
{
	T E = m[0][1];
	vector<T> D, c(m.size());
	for (unsigned int r = 0; r < m.size(); r++)
		D.push_back(m[r][r]);
	L.clear();
	L.resize(R.size());
	// Set the off diagonal elements
	for (unsigned int i = 0; i < m.size(); i++)
		c[i] = E;
	// forward bit
	c[0] /= D[0];	// if /0 rearrange equations
	R[0] /= D[0];
	for (unsigned int i = 1; i < m.size(); i++){
		T id = D[i] - c[i - 1] * E;
		c[i] /= id;	// Last value calculated is redundant.
		R[i] = (R[i] - R[i - 1] * E) / id;
	}
	// Now back substitute.
	L[m.size() - 1] = R[m.size() - 1];
	for (int i = m.size() - 2; i >= 0; i--)
		L[i] = R[i] - c[i] * L[i + 1];
}

template <typename T> T randomNumber(const T& min, const T& max, default_random_engine& dre)
{
	uniform_real_distribution<T> dr(min, max);
	return dr(dre);
}

template <typename T> void randomFill(const unsigned int size, const T &min, const T &max, default_random_engine& dre, vector<T>& v)
{
	v.clear();
	for (unsigned int i = 0; i < size; i++)
		v.push_back(randomNumber(min, max, dre));
}

template <typename T> void randomFill(const unsigned int size, const T& min, const T& max, default_random_engine& dre, vector<vector<T> >& m)
{
	for (unsigned int i = 0; i < m.size(); i++)
		m[i].clear();
	m.clear();
	for (unsigned int r = 0; r < size; r++) {
		vector<T> tmp;
		randomFill(size, min, max, dre, tmp);
		m.push_back(tmp);
	}
}

template <typename T> void randomFillTridiagonal(const unsigned int size, const T& min, const T& max, default_random_engine& dre, vector<vector<T> >& m)
{
	for (unsigned int i = 0; i < m.size(); i++)
		m[i].clear();
	m.clear();
	T E(randomNumber(min, max, dre));
	for (unsigned int r = 0; r < size; r++) {
		vector<T> tmp;
		m.push_back(tmp);
		for (unsigned int c = 0; c < size; c++)
			if (r == c)
				m[r].push_back(randomNumber(min, max, dre));
			else if (r == c + 1 || r + 1 == c)
				m[r].push_back(E);
			else
				m[r].push_back(0);
	}
}

template <typename T> ostream& operator<<(ostream& out, const vector<vector<T> >& m)
{
	for (unsigned int r = 0; r < m.size(); r++) {
		for (unsigned int c = 0; c < m[r].size(); c++) {
			out << m[r][c];
			if (c == m[r].size() - 1)
				out << endl;
			else
				out << ",\t";
		}
	}
	return out;
}

template <typename T> ostream& operator<<(ostream& out, const vector<T>& v)
{
	for (unsigned int i = 0; i < v.size(); i++) {
		out << v[i];
		if (i != v.size() - 1)
			out << ",\t";
	}
	return out;
}

#endif // MATRIX_H
