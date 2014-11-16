#ifndef LATINSQUARES_H
#define LATINSQUARES_H

#include "dancinglinks.h"

#define MAT_R	(n * n * n)
#define MAT_C	(3 * n * n)

class LatinSquares : public DancingLinks
{
public:
	LatinSquares(int size);
	int count(void) const {return c;}
	void solve(const bool ordered);

private:
	bool check(const std::vector<int> &res);
	void solved(const std::vector<int> &res);

	int n, c;
};

#endif // LATINSQUARES_H
