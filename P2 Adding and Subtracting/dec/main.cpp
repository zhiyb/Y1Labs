#include <list>
#include <iostream>
#include "sim.h"

using namespace std;

int main(void)
{
	bool overflow, f;
	int A, B;
	list<bool> a, b, sum;
	cin >> A >> B >> f;
	sim::fromInt(A, a);
	sim::fromInt(B, b);
	sim::multiFullAdder(a, b, f, sum, overflow);
	cout << "A: " << sim::toInt(a) << ", B: " << sim::toInt(b);
	cout << ", F: " << f;
	cout << ", S: " << sim::toInt(sum) << ", O: " << overflow << endl;
	return 0;
}
