#include <iostream>
#include "balrog.h"
#include "cyberdemon.h"
#include "elf.h"
#include "human.h"

#ifdef __linux__
#include <unistd.h>
#define msleep(ms) usleep(ms * 1000)
#else
#include <windows.h>
#define msleep(ms) Sleep(ms)
#endif

using namespace std;

int main()
{
	Balrog barlog;
	Cyberdemon cyberdemon;
	Elf elf;
	Human human;
	for (int i = 0; i < 60; i++) {
		cout << "****** New round! (" << i << ") ******" << endl;
		barlog.getDamage();
		cyberdemon.getDamage();
		elf.getDamage();
		human.getDamage();
		msleep(1000);
		cout << endl;
	}
	return 0;
}
