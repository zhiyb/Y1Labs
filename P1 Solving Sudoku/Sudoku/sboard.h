#ifndef SBOARD_H
#define SBOARD_H

#include <inttypes.h>
#include <iostream>
#include "define.h"
#include "sbox.h"

class sBoard
{
	friend class sBox;
	friend std::ostream& operator<<(std::ostream&, const class sBoard&);
	friend std::istream& operator>>(std::istream&, class sBoard&);

public:
	sBoard(void);
	void clear(void);
	bool solve(void);
	uint32_t *backup(void);
	void restore(uint32_t *buff);
	class sBox *getBox(int x, int y) {return &box[x][y];}

private:
	class sBox box[S_SIZE][S_SIZE];
};

std::ostream& operator<<(std::ostream& out, const class sBoard& board);
std::istream& operator>>(std::istream& in, class sBoard& board);

#endif // SBOARD_H
