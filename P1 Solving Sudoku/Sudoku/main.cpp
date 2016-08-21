#include <iostream>
#include <fstream>
#include "sboard.h"

#ifdef __linux__
#include <unistd.h>
#else
#include <windows.h>
#define usleep(s) Sleep(s / 1000)
#endif

using namespace std;

int main(int argc, char *argv[])
{
	//usleep(100000);		// Get ride of a wired warning message
	if (argc != 2) {
		cerr << (argc > 2 ? "Too many arguments" : "Need 1 argument, the Sudoku data file path") << endl;
		return 1;
	}
	class sBoard board;
	fstream file(argv[1], ios_base::in);
	if (!file.is_open()) {				// Cannot open file
		cerr << "Error open file!" << endl;
		return 1;
	}
	if (!(file >> board)) {				// Cannot open file
		cerr << "Error read file!" << endl;
		file.close();
		return 1;
	}
	file.close();
	cout << "# Original Sudoku" << endl << board << endl;
	if (!board.solve()) {
		cerr << "Unable to solve this Sudoku!" << endl;
		return 2;
	}
	cout << endl << "# Solved Sudoku" << endl << board << endl;
	return 0;
}
