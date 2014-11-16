#include "multibitadder.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

multibitAdder::multibitAdder(std::vector<bool *> *va, std::vector<bool *> *vb, const bool *vf, object *parent) : object(parent)
{
	if (va->size() != vb->size()) {
		std::cerr << "multibitAdder: a & b size are not equal!" << std::endl;
		exit(1);
	}
	f = vf;
	alloc = false;
	a = va;
	b = vb;
	build();
}

multibitAdder::multibitAdder(const vector<bool> &va, const vector<bool> &vb, const bool *vf, object *parent) : object(parent)
{
	if (va.size() != vb.size()) {
		std::cerr << "multibitAdder: a & b size are not equal!" << std::endl;
		exit(1);
	}
	f = vf;
	alloc = true;
	a = new vector<bool *>;
	b = new vector<bool *>;
	for (vector<bool>::size_type i = 0; i < va.size(); i++) {
		a->push_back(new bool(va[i]));
		b->push_back(new bool(vb[i]));
	}
	build();
}

multibitAdder::multibitAdder(const int va, const int vb, const bool *vf, object *parent) : object(parent)
{
	f = vf;
	alloc = true;
	a = fromInt(va);
	b = fromInt(vb);
	build();
}

multibitAdder::~multibitAdder(void)
{
	if (alloc)
		while (a->size()) {
			delete a->back();
			a->pop_back();
			delete b->back();
			b->pop_back();
		}
}

void multibitAdder::build(void)
{
	for (vector<bool>::size_type i = 0; i < a->size(); i++) {
		xors.push_back(new XOR(b->at(i), f, this));
		fas.push_back(new fullAdder(a->at(i), xors[i]->output(), i == 0 ? f : fas[i - 1]->cOut(), this));
		s.push_back(fas[i]->sum());
	}
	xorOverflow = new XOR(fas.back()->cOut(), fas.back()->getCIn(), this);
	o = xorOverflow->output();
	c = fas.back()->cOut();
}

std::vector<bool *> *multibitAdder::fromInt(const int v)
{
	vector<bool *> *res = new vector<bool *>;
	unsigned int mask = 1;
	while (res->size() != sizeof(int) * 8) {
		res->push_back(new bool(v & mask));
		mask <<= 1;
	}
	return res;
}

int multibitAdder::sumInt(void) const
{
	int res = *(s.front()) ? -1 : 0;
	for (vector<bool *>::size_type i = 0; i < s.size(); i++)
		if (*s[i])
			res |= (1 << i);
		else
			res &= ~(1 << i);
	return res;
}
