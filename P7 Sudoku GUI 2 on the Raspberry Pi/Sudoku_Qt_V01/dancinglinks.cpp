#include "dancinglinks.h"

DancingLinks::DancingLinks()
{
	h = new Node(-1);
}

DancingLinks::~DancingLinks()
{
	Node *c = h;
	do {
		Node *r = c;
		c = c->d[Node::Right];
		do {
			r = r->d[Node::Up];
			delete r->d[Node::Down];
		} while (r != c->d[Node::Left]);
	} while (c != h);
}

void DancingLinks::solve(void)
{
	std::vector<int> res;
	solve(res);
}

bool DancingLinks::solve(std::vector<int>& res)
{
	if (h == h->d[Node::Right]) {
		return solved(res);
	}
	status(res);
	Node *col = h->d[Node::Right];	// Choose a column object
	col->coverColumn();
	for (col = col->d[Node::Down]; col->r != -1; col = col->d[Node::Down]) {
		res.push_back(col->r);
		for (Node *c = col->d[Node::Right]; c != col; c = c->d[Node::Right])
			c->coverColumn();
		bool next = solve(res);
		res.pop_back();		// Backtrack
		for (Node *c = col->d[Node::Left]; c != col; c = c->d[Node::Left])
			c->unCoverColumn();
		if (!next) {
			col->unCoverColumn();
			return false;
		}
	}
	col->unCoverColumn();
	return true;
}
