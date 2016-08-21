#include "demon.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

int Demon::getDamage()
{
	int damage = Creature::getDamage();
	// Demons can inflict damage of 50 with a 5% chance
	if ((rand() % 100) < 5) {
		damage = damage + 50;
		cout << "Demonic attack inflicts 50 "
		     << " additional damage points!" << endl;
	}
	return damage;
}
