#include <iostream>
#include <cstdlib>
#include "latinsquares.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3) {
		cerr << "Wrong argument number!" << endl;
		return 1;
	}
	LatinSquares ls(atoi(argv[1]));
	ls.solve(atoi(argv[2]));
	cout << "Total " << ls.count() << " solutions." << endl;
	return 0;
}
