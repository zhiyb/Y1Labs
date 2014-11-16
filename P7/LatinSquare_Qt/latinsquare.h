#ifndef LATINSQUARES_H
#define LATINSQUARES_H

#include "dancinglinks.h"
#include <QString>

#define MAT_R	(n * n * n)
#define MAT_C	(3 * n * n)

class LatinSquare : public DancingLinks
{
public:
	LatinSquare(int size);
	int count(void) const {return c;}
	void solve(const bool ordered);
	std::vector<std::vector<int> > solutions(void) const {return solution;}
	static QString toString(const std::vector<int>& res);
	std::vector<int> fromString(const QString& line);
	void solve(const std::vector<int>& pre);

private:
	bool check(const std::vector<int> &res);
	bool solved(const std::vector<int> &res);

	int n, c;
	std::vector<std::vector<int> > solution;
};

#endif // LATINSQUARES_H
