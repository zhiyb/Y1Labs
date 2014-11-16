#include "fulladder.h"

fullAdder::fullAdder(const bool *va, const bool *vb, const bool *vcIn, object *parent) : object(parent)
{
	a = va;
	b = vb;
	cIn = vcIn;
	ha1 = new halfAdder(a, b, this);
	ha2 = new halfAdder(cIn, ha1->sum(), this);
	or1 = new OR(ha2->cOut(), ha1->cOut(), this);
	s = ha2->sum();
	c = or1->output();
}

void fullAdder::connect(void)
{
	ha1->setA(a);
	ha1->setB(b);
	ha2->setA(cIn);
}
