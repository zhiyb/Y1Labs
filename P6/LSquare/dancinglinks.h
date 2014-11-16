#ifndef DANCINGLINKS_H
#define DANCINGLINKS_H

#include "node.h"
#include <vector>

class DancingLinks
{
public:
	DancingLinks();
	~DancingLinks();
	void solve(void);
	Node *head(void) const {return h;}

protected:
	// For output selected rows
	virtual void solved(const std::vector<int>&) {}
	void solve(std::vector<int>& res);

	Node *h;
};

#endif // DANCINGLINKS_H
