#ifndef SIM_H
#define SIM_H

#include <list>

namespace sim {
	using namespace std;

	void halfAdder(const bool a, const bool b, bool& sum, bool& cOut)
	{
		sum = a ^ b;
		cOut = a & b;
	}
	void fullAdder(const bool a, const bool b, const bool cIn, bool& sum, bool& cOut)
	{
		bool t1, t2;
		halfAdder(a, b, t1, t2);
		halfAdder(cIn, t1, sum, t1);
		cOut = t1 | t2;
	}
	void multiFullAdder(const list<bool>& a, const list<bool>& b, const bool f, list<bool>& sum, bool& overflow)
	{
		list<bool> A(a), B(b);
		// Resize to same size
		while (A.size() < B.size())
			A.push_front(*A.begin());
		while (A.size() > B.size())
			B.push_front(*B.begin());
		sum.clear();
		while (A.size() != sum.size())
			sum.push_back(0);
		// Calculate
		bool cIn = 0, cOut = f;
		list<bool>::iterator aIt = A.end(), bIt = B.end(), sIt = sum.end();
		while (aIt != A.begin() && bIt != B.begin() && sIt != sum.begin()) {
			cIn = cOut; aIt--; bIt--; sIt--;
			fullAdder(*aIt, *bIt ^ f, cIn, *sIt, cOut);
		}
		overflow = cIn ^ cOut;
	}
	void multiplierUnit(const bool x, const bool y, const bool sumIn, const bool cIn, bool& sumOut, bool& cOut)
	{
		bool b = x & y;
		fullAdder(sumIn, b, cIn, sumOut, cOut);
	}
	void multiplier(const list<bool>& a, const list<bool>& b, list<bool>& res)
	{
		static int cnt = 0;
		list<bool> sum(a.size(), 0), c(a.size(), 0);
		res.clear();
		res = list<bool>(a.size() + b.size(), 0);
		list<bool>::iterator rIt = --res.end();
		for (list<bool>::const_iterator bIt = b.end(); bIt != b.begin();) {
			bIt--;
			list<bool>::iterator sIt = sum.begin();
			list<bool>::iterator cIt = c.begin();
			for (list<bool>::const_iterator aIt = a.end(); aIt != a.begin(); cIt++) {
				aIt--;
				list<bool>::iterator sItPrev = sIt++;
				multiplierUnit(*aIt, *bIt, sIt == sum.end() ? 0 : *sIt, *cIt, *sItPrev, *cIt);
				//cout << "multiplierUnit(" << *aIt << ", " << *bIt << ", " << (sIt == sum.end() ? 0 : *sIt) << ", " << *cIt << ", " << *sItPrev << ", " << *cIt << ");" << endl;
			}
			*(rIt--) = *sum.begin();
			cout << "Cnt: " << cnt++ << ", sum: " << *sum.begin() << endl;
		}
		for (list<bool>::iterator sIt = sum.begin(); sIt != sum.end(); sIt++)
			cout << "<sum>: " << *sIt << endl;
		for (list<bool>::iterator sIt = ++sum.begin(); sIt != sum.end(); rIt--, sIt++) {
			*rIt = *sIt;
			cout << "Cnt: " << cnt++ << ", sum: " << *sIt << endl;
		}
		*rIt = *(--c.end());
		if (rIt != res.begin())
			cerr << "Error!" << endl;
	}
	int toInt(const list<bool>& l)
	{
		int out = *l.begin() == 1 ? -1 : 0, i = l.size() - 1;
		for (list<bool>::const_iterator it = l.begin(); it != l.end(); it++, i--)
			if (*it)
				out |= 1 << i;
			else
				out &= ~(1 << i);
		return out;
	}
	void fromInt(const int v, list<bool>& l)
	{
		unsigned int mask = 1 << (sizeof(int) * 8 - 1);
		l.clear();
		while (l.size() != sizeof(int) * 8) {
			l.push_back(v & mask);
			mask >>= 1;
		}
	}
}

#endif
