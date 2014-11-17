#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <chrono>
#include "complex.h"
#include "matrix.h"

using namespace std;

int main(void)
{
	const unsigned int size = 3;
	default_random_engine dre = default_random_engine(chrono::system_clock::now().time_since_epoch().count());
#if 1
	vector<vector<Complex> > m, tmp;
	vector<Complex> R, L;
	const Complex min(5.0, 5.0), max(25.0, 25.0);
#else
	vector<vector<double> > m, tmp;
	vector<double> R, L;
	const double min(5.0), max(25.0);
#endif
	randomFill(size, min, max, dre, tmp);
	randomFillTridiagonal(size, min, max, dre, m);
	randomFill(size, min, max, dre, R);
	TridiagonalSolve(m, R, L);
	cout << "tmp:" << endl << tmp;
	cout << "A:" << endl << m;
	cout << "L:" << endl << L << endl;
	cout << "R:" << endl << R << endl;
	return 0;
}
