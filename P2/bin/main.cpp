#include <list>
#include <iostream>
#include "sim.h"

using namespace std;

int main(void)
{
	bool overflow, f;
	char c;
	list<bool> a, b, sum, *op;
	op = &a;
next:
	while ((c = cin.get()) > 0) {
		if (c == '0' || c == '1')
			(*op).push_back(c - '0');
		else
			break;
	}
	if (op == &a) {
		op = &b;
		goto next;
	}
	cin >> f;
	sim::multiFullAdder(a, b, f, sum, overflow);
	cout << "A: " << sim::toInt(a) << ", B: " << sim::toInt(b);
	cout << ", F: " << f;
	cout << ", S: " << sim::toInt(sum) << ", O: " << overflow << endl;
	return 0;
}
