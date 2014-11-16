#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>

class Creature
{
public:
	// Initialize to human, 10 strength, 10 hit points
	// Initialize creature to new type, strength, hit points
	Creature(int newStrength = 10, int newHit = 10);
	// Returns amount of damage this creature
	// inflicts in one round of combat
	int getDamage();
	// Accessor and mutator functions for strength, and hit points
	void setStrength(int newStrength) {strength = newStrength;}
	void setHit(int newHit) {hitpoints = newHit;}
	int getStrength(void) const {return strength;}
	int getHit(void) const {return hitpoints;}
	
protected:
	virtual std::string getSpecies() {return "Unknown";}	// Returns type of species
	
	//int type;	// 0 human, 1 cyberdemon, 2 balrog, 3 elf
	int strength;	// How much damage we can inflict
	int hitpoints;	// How much damage we can sustain
};

#endif // CREATURE_H

#if 0
class Creature
{
private:
	int type;// 0 human, 1 cyberdemon, 2 balrog, 3 elf
	int strength;// How much damage we can inflict
	int hitpoints;// How much damage we can sustain
	string getSpecies();// Returns type of species
public:
	Creature( );
	// Initialize to human, 10 strength, 10 hit points
	Creature(int newType,int newStrength,int newHit);
	// Initialize creature to new type, strength, hit points
	// Also add appropriate accessor and mutator functions
	// for type, strength, and hit points
	int getDamage();
	// Returns amount of damage this creature
	// inflicts in one round of combat
};

string Creature::getSpecies()
{
	switch (type)
	{
	case 0:return "Human";
	case 1:return "Cyberdemon";
	case 2:return "Balrog";
	case 3:return "Elf";
	}
	return "Unknown";
}

int Creature::getDamage( )
{
	int damage;
	// All creatures inflict damage, which is a
	// random number up to their strength
	damage = (rand( ) % strength) + 1;
	cout << getSpecies( ) << " attacks for " <<
		damage << " points!" << endl;
	// Demons can inflict damage of 50 with a 5% chance
	if ((type = 2) || (type == 1))
		if ((rand( ) % 100) < 5)
		{
			damage = damage + 50;
			cout << "Demonic attack inflicts 50 "
			     << " additional damage points!" << endl;
		}
	// Elves inflict double magical damage with a 10% chance
	if (type == 3)
	{
		if ((rand( ) % 10)==0)
		{
			cout << "Magical attack inflicts " << damage <<
				" additional damage points!" << endl;
			damage = damage * 2;
		}
	}
	// Balrogs are so fast they get to attack twice
	if (type == 2)
	{
		int damage2 = (rand() % strength) + 1;
		cout << "Balrog speed attack inflicts " << damage2 <<
			" additional damage points!" << endl;
		damage = damage + damage2;
	}
	return damage;
}
#endif
