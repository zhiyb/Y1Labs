#include "halfadder.h"

halfAdder::halfAdder(const bool *va, const bool *vb, object *parent): object(parent)
{
	a = va;
	b = vb;
	and1 = new AND(a, b, this);
	xor1 = new XOR(a, b, this);
	s = xor1->output();
	c = and1->output();
}

void halfAdder::connect(void)
{
	and1->setA(a);
	and1->setB(b);
	xor1->setA(a);
	xor1->setB(b);
}
