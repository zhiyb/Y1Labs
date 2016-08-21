#ifndef XOR_H
#define XOR_H

#include "gate2to1.h"

class XOR : public gate2to1
{
public:
	XOR(const bool* va, const bool *vb, object *parent = 0) : gate2to1(va, vb, parent) {}
	void update(void) {o = *a ^ *b;}
};

#endif // XOR_H
