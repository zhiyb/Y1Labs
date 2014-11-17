#ifndef DANCINGLINKS_H
#define DANCINGLINKS_H

#include "node.h"
#include <vector>

class DancingLinks
{
public:
	DancingLinks();
	virtual ~DancingLinks();
	void solve(void);
	Node *head(void) const {return h;}

protected:
	// For output selected rows
	virtual bool solved(const std::vector<int>&) {return true;}
#ifndef QT_NO_DEBUG
	virtual void status(const std::vector<int>&) {return;}
#endif
	bool solve(std::vector<int>& res);

	Node *h;
};

#endif // DANCINGLINKS_H
