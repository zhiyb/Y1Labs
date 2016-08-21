#include <iostream>
#include <vector>
#include "multibitadder.h"

using namespace std;

int main()
{
	int a, b;
	cout << "Please input a and b:" << endl;
	cin >> a >> b;
	bool f = 0;
	multibitAdder *ma = new multibitAdder(a, b, &f);
	ma->update();
	cout << "Sum: " << ma->sumInt() << ", cOut: " << *ma->cOut() << ", overflow: " << *ma->overflow() << endl;
	f = 1;
	ma->update();
	cout << "Sub: " << ma->sumInt() << ", cOut: " << *ma->cOut() << ", overflow: " << *ma->overflow() << endl;
	delete ma;
	return 0;
}
