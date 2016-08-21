#ifndef DEMON_H
#define DEMON_H

#include "creature.h"

class Demon : public Creature
{
public:
	Demon(int newStrength = 10, int newHit = 10) : Creature(newStrength, newHit) {}
	// Returns amount of damage this creature
	// inflicts in one round of combat
	int getDamage();
};

#endif // DEMON_H
