#include "dancinglinks.h"

DancingLinks::DancingLinks()
{
	h = new Node(-1);
}

DancingLinks::~DancingLinks()
{
	/*Node *c = h->to(Node::Right);
	do {
		Node *r = c;
		c = c->to(Node::Right);
		do {
			r = r->to(Node::Up);
			delete r->to(Node::Down);
		} while (r != c->to(Node::Left));
	} while (c != h);*/
	delete h;
}

void DancingLinks::solve(void)
{
	std::vector<int> res;
	solve(res);
}

#include <iostream>
bool DancingLinks::solve(std::vector<int>& res)
{
	if (h == h->to(Node::Right))
		return solved(res);
#ifndef QT_NO_DEBUG
	status(res);
#endif
	// Choose a column object
	Node *col = h->to(Node::Right);
	for (Node *c = col->to(Node::Right); c != h; c = c->to(Node::Right)) {
		if (c->value() > col->value())	// Node count recorded negative
			col = c;
#ifndef QT_NO_DEBUG
		if (col->value() >= 0)
			std::cerr << "Something wrong happend!" << std::endl;
#endif
	}
	//col = h->to(Node::Right);
	col->coverColumn();
	for (col = col->to(Node::Down); col->value() >= 0; col = col->to(Node::Down)) {
		res.push_back(col->value());
		//col->coverRow();
		for (Node *c = col->to(Node::Right); c != col; c = c->to(Node::Right))
			c->coverColumn();
		bool next = solve(res);
		res.pop_back();		// Backtrack
		for (Node *c = col->to(Node::Left); c != col; c = c->to(Node::Left))
			c->unCoverColumn();
		if (!next) {
			col->unCoverColumn();
			return false;
		}
		//col->unCoverRow();
	}
	col->unCoverColumn();
	return true;
}
