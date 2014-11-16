#ifndef OR_H
#define OR_H

#include "gate2to1.h"

class OR : public gate2to1
{
public:
	OR(const bool* va, const bool *vb, object *parent = 0) : gate2to1(va, vb, parent) {}
	void update(void) {o = *a | *b;}
};

#endif // XOR_H
