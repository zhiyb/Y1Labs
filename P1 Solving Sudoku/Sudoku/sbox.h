#ifndef SBOX_H
#define SBOX_H

#include <iostream>
#include "define.h"

class sBox
{
	friend class sBoard;
	friend std::ostream& operator<<(std::ostream&, const class sBoard);

public:
	sBox(uint32_t p = POSSIBLE_ALL);
	int number(void) const;
	int count(void) const;
	bool set(const uint32_t p);
	void setPossible(const uint32_t p) {possible = p;}
	bool tryAll(void);
	bool tryNext(void);

private:
	bool remove(void);
	bool removeMe(const uint32_t p);
	bool removeHPrev(const uint32_t p);
	bool removeHNext(const uint32_t p);
	bool removeVPrev(const uint32_t p);
	bool removeVNext(const uint32_t p);
	bool removeSPrev(const uint32_t p);
	bool removeSNext(const uint32_t p);

	uint32_t possible;
	class sBox *hPrev, *hNext, *vPrev, *vNext, *sPrev, *sNext;
	class sBoard *board;
};

#endif // SBOX_H
