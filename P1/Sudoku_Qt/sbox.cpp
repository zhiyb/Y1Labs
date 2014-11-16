#include "sbox.h"
#include "sboard.h"

using namespace std;

sBox::sBox(uint32_t p)
{
	possible = p;
	hPrev = 0;
	hNext = 0;
	vPrev = 0;
	vNext = 0;
	sPrev = 0;
	sNext = 0;
	board = 0;
}

bool sBox::tryNext(void)
{
	if (hNext != 0) {
		if (!hNext->tryAll())
			return false;
	} else if (vNext != 0) {
		class sBox *p = vNext;
		while (p->hPrev != 0)
			p = p->hPrev;
		return p->tryAll();
	}
	return true;
}

bool sBox::tryAll(void)
{
	if (count() == 1)
		return tryNext();
	uint32_t poss = possible;
	uint32_t *buff = board->backup();
	for (uint32_t i = 0x01; i != (1 << S_SIZE); i <<= 1)
		if (poss & i) {
			board->restore(buff);
			if (!set(i) || !tryNext())
				continue;
			delete[] buff;
			return true;
		}
	delete[] buff;
	return false;
}

bool sBox::removeMe(const uint32_t p)
{
	if (count() == 1) {
		if (possible & p)
			return false;
		else
			return true;
	}
	possible &= ~p;
	if (count() == 0)
		return false;
	else if (count() == 1)
		return remove();
	return true;
}

bool sBox::removeHPrev(const uint32_t p)
{
	if (!removeMe(p))
		return false;
	if (hPrev == 0)
		return true;
	return hPrev->removeHPrev(p);
}

bool sBox::removeHNext(const uint32_t p)
{
	if (!removeMe(p))
		return false;
	if (hNext == 0)
		return true;
	return hNext->removeHNext(p);
}

bool sBox::removeVPrev(const uint32_t p)
{
	if (!removeMe(p))
		return false;
	if (vPrev == 0)
		return true;
	return vPrev->removeVPrev(p);
}

bool sBox::removeVNext(const uint32_t p)
{
	if (!removeMe(p))
		return false;
	if (vNext == 0)
		return true;
	return vNext->removeVNext(p);
}

bool sBox::removeSPrev(const uint32_t p)
{
	if (!removeMe(p))
		return false;
	if (sPrev == 0)
		return true;
	return sPrev->removeSPrev(p);
}

bool sBox::removeSNext(const uint32_t p)
{
	if (!removeMe(p))
		return false;
	if (sNext == 0)
		return true;
	return sNext->removeSNext(p);
}

bool sBox::remove(void)
{
	if (hPrev != 0)
		if (!hPrev->removeHPrev(possible))
			return false;
	if (hNext != 0)
		if (!hNext->removeHNext(possible))
			return false;
	if (vPrev != 0)
		if (!vPrev->removeVPrev(possible))
			return false;
	if (vNext != 0)
		if (!vNext->removeVNext(possible))
			return false;
	if (sPrev != 0)
		if (!sPrev->removeSPrev(possible))
			return false;
	if (sNext != 0)
		if (!sNext->removeSNext(possible))
			return false;
	return true;
}

bool sBox::set(const uint32_t p)
{
	if ((possible & p )!= p)
		return false;
	possible = p;
	if (count() == 1)
		return remove();
	return true;
}

int sBox::count(void) const
{
	int cnt = 0;
	for (int i = 0; i < S_SIZE; i++)
		if (possible & (1 << i))
			cnt++;
	return cnt;
}

int sBox::number(void) const
{
	if (!(possible & POSSIBLE_ALL) || count() != 1)
		return -1;
	for (int i = 0; i < S_SIZE; i++)
		if (possible & (1 << i))
			return i;
	return -1;
}
