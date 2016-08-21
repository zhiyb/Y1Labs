#include "creature.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Creature::Creature(int newStrength, int newHit)
{
	strength = newStrength;
	hitpoints = newHit;
}

int Creature::getDamage()
{
	int damage;
	// All creatures inflict damage, which is a
	// random number up to their strength
	damage = (rand() % strength) + 1;
	cout << getSpecies() << " attacks for " <<
		damage << " points!" << endl;
	return damage;
}
