#ifndef BALROG_H
#define BALROG_H

#include "demon.h"

class Balrog : public Demon
{
public:
	Balrog(int newStrength = 10, int newHit = 10) : Demon(newStrength, newHit) {}
	// Returns amount of damage this creature
	// inflicts in one round of combat
	int getDamage();

protected:
	std::string getSpecies() {return "Balrog";}	// Returns type of species
};

#endif // BALROG_H
