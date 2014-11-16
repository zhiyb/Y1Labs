#ifndef HUMAN_H
#define HUMAN_H

#include "creature.h"

class Human : public Creature
{
public:
	Human(int newStrength = 10, int newHit = 10) : Creature(newStrength, newHit) {}

protected:
	std::string getSpecies() {return "Human";}	// Returns type of species
};

#endif // HUMAN_H
