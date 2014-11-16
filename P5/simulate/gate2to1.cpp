#include "gate2to1.h"
#include <iostream>

gate2to1::gate2to1(const bool *va, const bool *vb, object *parent) : object(parent)
{
	a = va;
	b = vb;
	o = 0;
}
