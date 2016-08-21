#ifndef FULLADDER_H
#define FULLADDER_H

#include "object.h"
#include "halfadder.h"
#include "or.h"

class fullAdder : public object
{
public:
	fullAdder(const bool *va, const bool *vb, const bool *vcIn, object *parent = 0);
	void connect(void);
	void setA(const bool *va) {a = va; connect();}
	void setB(const bool *vb) {b = vb; connect();}
	void setCIn(const bool *vcIn) {cIn = vcIn; connect();}
	const bool *getA(void) {return a;}
	const bool *getB(void) {return b;}
	const bool *getCIn(void) {return cIn;}
	const bool *sum(void) {return s;}
	const bool *cOut(void) {return c;}

private:
	halfAdder *ha1, *ha2;
	OR *or1;
	const bool *a, *b, *cIn, *s, *c;
};

#endif // FULLADDER_H
