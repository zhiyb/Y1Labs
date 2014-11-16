#ifndef GATE2TO1_H
#define GATE2TO1_H

#include "object.h"

class gate2to1 : public object
{
public:
	gate2to1(const bool *va, const bool *vb, object *parent = 0);
	void setA(const bool *va) {a = va;}
	void setB(const bool *vb) {b = vb;}
	bool *output(void) {return &o;}

protected:
	const bool *a, *b;
	bool o;
};

#endif // GATE2TO1_H
