#include "sboard.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

sBoard::sBoard(void)
{
	for (int y = 0; y < S_SIZE; y++)
		for (int x = 0; x < S_SIZE; x++) {
			if (x != 0)
				box[x][y].hPrev = &box[x - 1][y];
			if (x != S_SIZE - 1)
				box[x][y].hNext = &box[x + 1][y];
			if (y != 0)
				box[x][y].vPrev = &box[x][y - 1];
			if (y != S_SIZE - 1)
				box[x][y].vNext = &box[x][y + 1];
			if (x % S_UNIT_SIZE != 0 || y % S_UNIT_SIZE != 0)
				box[x][y].sPrev = &box[(x % S_UNIT_SIZE) == 0 ? x + S_UNIT_SIZE - 1 : x - 1]\
						      [(x % S_UNIT_SIZE) == 0 ? y - 1 : y];
			if (x % S_UNIT_SIZE != S_UNIT_SIZE - 1 || y % S_UNIT_SIZE != S_UNIT_SIZE - 1)
				box[x][y].sNext = &box[(x % S_UNIT_SIZE) == S_UNIT_SIZE - 1 ? x - S_UNIT_SIZE + 1 : x + 1]\
						      [(x % S_UNIT_SIZE) == S_UNIT_SIZE - 1 ? y + 1 : y];
			box[x][y].board = this;
		}
}

uint32_t *sBoard::backup(void)
{
	uint32_t *buff = new uint32_t[S_SIZE * S_SIZE];
	for (int i = 0; i < S_SIZE * S_SIZE; i++)
		buff[i] = box[i % S_SIZE][i / S_SIZE].possible;
	return buff;
}

void sBoard::restore(uint32_t *buff)
{
	for (int i = 0; i < S_SIZE * S_SIZE; i++)
		box[i % S_SIZE][i / S_SIZE].possible = buff[i];
}

bool sBoard::solve(void)
{
	return box[0][0].tryAll();
}

void sBoard::clear(void)
{
	for (int y = 0; y < S_SIZE; y++)
		for (int x = 0; x < S_SIZE; x++)
			box[x][y].possible = POSSIBLE_ALL;
}

ostream& operator<<(ostream& out, const class sBoard& board)
{
	out.unsetf(ios::dec | ios::oct);
	out.setf(ios::hex);
	for (int y = 0; y < S_SIZE; y++) {
		for (int x = 0; x < S_SIZE; x++) {
			if (board.box[x][y].number() != -1)
				out << uppercase << board.box[x][y].number() + (S_SIZE < 16);
			else
				out << "X";
			if (x != S_SIZE - 1) {
				if (x % S_UNIT_SIZE == S_UNIT_SIZE - 1)
					out << "   ";
				else
					out << " ";
			}
		}
		if (y != S_SIZE - 1)
			out << endl;
		if (y % S_UNIT_SIZE == S_UNIT_SIZE - 1 && y != S_SIZE - 1)
			out << endl;
	}
	return out;
}

istream& operator>>(istream& in, class sBoard& board)
{
	uint32_t buff[S_SIZE][S_SIZE];
	int y = 0;
	while (!in.eof()) {
		string line;
		getline(in, line);
		if (line.empty() || line.compare(0, 1, "#", 1) == 0)
			continue;
		int x;
		stringstream stream(line);
		for (x = 0; x < S_SIZE && !stream.eof(); x++) {
			int i;
			stream >> line;
			stringstream token(line);
			token.unsetf(ios::dec | ios::oct);
			token.setf(ios::hex);
			if (!(token >> i))		// Empty
				buff[x][y] = POSSIBLE_ALL;
			else if (i >= 0 + (S_SIZE < 16) && i <= S_SIZE)
				buff[x][y] = 1 << (i - (S_SIZE < 16));
			else if (S_SIZE != 9 && i >= 0x0A && i <= 0x0F)
				buff[x][y] = 1 << i;
			else
				goto failed;		// Invalid format
		}
		if (stream.eof() && x != S_SIZE)
			goto failed;			// Elements count error
		if (++y == S_SIZE)
			break;
	}
	if (y != S_SIZE)
		goto failed;				// Missed some lines
	board.clear();
	for (y = 0; y < S_SIZE; y++)
		for (int x = 0; x < S_SIZE; x++)
			if (buff[x][y] != POSSIBLE_ALL)
				board.box[x][y].set(buff[x][y]);
	return in;
failed:
	in.setstate(ios_base::failbit);
	return in;
}
