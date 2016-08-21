#ifndef MULTIBITADDER_H
#define MULTIBITADDER_H

#include <vector>
#include "object.h"
#include "fulladder.h"
#include "xor.h"

class multibitAdder : public object	// LSB first
{
public:
	multibitAdder(std::vector<bool *> *va, std::vector<bool *> *vb, const bool *vf, object *parent = 0);
	multibitAdder(const std::vector<bool>& va, const std::vector<bool>& vb, const bool *vf, object *parent = 0);
	multibitAdder(const int va, const int vb, const bool *vf, object *parent = 0);
	~multibitAdder(void);
	const bool *cOut(void) {return c;}
	const bool *overflow(void) {return o;}
	std::vector<const bool *> *sum(void) {return &s;}
	int sumInt(void) const;

private:
	std::vector<bool *> *fromInt(const int v);
	void build(void);

	std::vector<bool *> *a, *b;
	std::vector<const bool *> s;
	std::vector<fullAdder *> fas;
	std::vector<XOR *> xors;
	XOR *xorOverflow;
	const bool *f, *c, *o;
	bool alloc;
};

#endif // MULTIBITADDER_H
