#ifndef ELF_H
#define ELF_H

#include "creature.h"

class Elf : public Creature
{
public:
	Elf(int newStrength = 10, int newHit = 10) : Creature(newStrength, newHit) {}
	// Returns amount of damage this creature
	// inflicts in one round of combat
	int getDamage();

protected:
	std::string getSpecies() {return "Elf";}	// Returns type of species
};

#endif // ELF_H
