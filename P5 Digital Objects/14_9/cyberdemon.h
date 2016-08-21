#ifndef CYBERDEMON_H
#define CYBERDEMON_H

#include "demon.h"

class Cyberdemon : public Demon
{
public:
	Cyberdemon(int newStrength = 10, int newHit = 10) : Demon(newStrength, newHit) {}

protected:
	std::string getSpecies() {return "Cyberdemon";}	// Returns type of species
};

#endif // CYBERDEMON_H
