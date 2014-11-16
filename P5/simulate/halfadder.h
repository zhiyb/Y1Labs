#ifndef HALFADDER_H
#define HALFADDER_H

#include "object.h"
#include "xor.h"
#include "and.h"

class halfAdder : public object
{
public:
	halfAdder(const bool *va, const bool *vb, object *parent = 0);
	void connect(void);
	void setA(const bool *va) {a = va; connect();}
	void setB(const bool *vb) {b = vb; connect();}
	const bool *sum(void) {return s;}
	const bool *cOut(void) {return c;}

private:
	XOR *xor1;
	AND *and1;
	const bool *a, *b, *s, *c;
};

#endif // HALFADDER_H
