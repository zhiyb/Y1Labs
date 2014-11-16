#include "balrog.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

int Balrog::getDamage()
{
	int damage = Demon::getDamage();
	// Balrogs are so fast they get to attack twice
	int damage2 = (rand() % strength) + 1;
	cout << "Balrog speed attack inflicts " << damage2 <<
		" additional damage points!" << endl;
	damage = damage + damage2;
	return damage;
}
