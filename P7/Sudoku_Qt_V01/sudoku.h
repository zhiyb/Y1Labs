#ifndef SUDOKU_H
#define SUDOKU_H

#include "dancinglinks.h"
#include <QString>

#define NN	(n * n)
#define MAT_R	(NN * NN * NN)
#define MAT_C	(4 * NN * NN)

class Sudoku : public DancingLinks
{
public:
	Sudoku(int size);
	//int count(void) const {return c;}
	void solve(const std::vector<int>& pre);
	std::vector<std::vector<int> > solutions(void) const {return solution;}
	static QString toString(const std::vector<int>& res);
	static std::vector<int> fromString(const QString& line);

private:
	bool solved(const std::vector<int>& res);
	void status(const std::vector<int>& res);

	int n;
	std::vector<std::vector<int> > solution;
};

#endif // SUDOKU_H
