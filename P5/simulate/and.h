#ifndef AND_H
#define AND_H

#include "gate2to1.h"

class AND : public gate2to1
{
public:
	AND(const bool *va, const bool *vb, object *parent = 0) : gate2to1(va, vb, parent) {}
	void update(void) {o = *a & *b;}
};

#endif // AND_H
