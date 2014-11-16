#include "latinsquares.h"
#include <iostream>

using namespace std;

LatinSquares::LatinSquares(int size) : DancingLinks()
{
	n = size;
	c = 0;
	for (int c = 0; c < MAT_C; c++)		// Columns
		h->connect(Node::Left, new Node(-1));
	for (int r = 0; r < MAT_R; r++) {	// Rows
		int num = r % n, x = (r / n) % n, y = r / (n * n);
		// Row group 1: Positions
		h->next(Node::Right, y * n + x + 1)->connect(Node::Up, new Node(r))
		// Row group 2: Rows
			->connect(Node::Right, h->next(Node::Right, n * n + y * n + num + 1)
				  ->connect(Node::Up, new Node(r)))
		// Row group 3: Columns
			->connect(Node::Right, h->next(Node::Right, n * n * 2 + x * n + num + 1)
				  ->connect(Node::Up, new Node(r)));
	}
}

bool LatinSquares::check(const std::vector<int> &res)
{
	int s[n][n];	// Initialisation of squares
	for (int r = 0; r < n; r++)
		for (int c = 0; c < n; c++)
			s[r][c] = -1;	// Fill squares
	for (vector<int>::size_type i = 0; i < res.size(); i++)
		s[res.at(i) / (n * n)][(res.at(i) / n) % n] = res.at(i) % n;
	int mask[n * 2];	// Correct number & only once & no repeat check
	for (int i = 0; i < n * 2; i++)
		mask[i] = ((int)-1) << n;
	for (int r = 0; r < n; r++)
		for (int c = 0; c < n; c++) {
			if (s[r][c] == -1)	// Empty check
				return false;
			mask[r] |= 1 << s[r][c];
			mask[n + c] |= 1 << s[r][c];
		}
	for (int i = 0; i < n * 2; i++)
		if (mask[i] != (int)-1)
			return false;
	return true;
}

void LatinSquares::solved(const std::vector<int> &res)
{
	if (!check(res)) {	// Check correctness
		cerr << "Check failed: ";
		for (vector<int>::size_type i = 0; i < res.size(); i++)
			cerr << res.at(i) << ", ";
		cerr << endl;
		return;
	}
	int s[n][n];	// Fill squares
	for (vector<int>::size_type i = 0; i < res.size(); i++)
		s[res.at(i) / (n * n)][(res.at(i) / n) % n] = res.at(i) % n;
#if 0	// Orded latin squares filter
	for (int i = 0; i < n - 1; i++)
		if (s[i][0] > s[i + 1][0] || s[0][i] > s[0][i + 1])
			return;
#endif	// Output
	c++;
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++)
			cout << s[r][c] + 1 << " ";
		cout << endl;
	}
	cout << endl;
}

void LatinSquares::solve(const bool ordered)
{
	std::vector<int> res;
	std::vector<Node *> rm;
	if (ordered)
		for (int i = 0; i < n; i++) {
			rm.push_back(h->next(Node::Right, i + 1)->next(Node::Down, i + 1));
			res.push_back(rm.back()->row());
			rm.push_back(h->next(Node::Right, i * n + 1)->next(Node::Down, i + 1));
			res.push_back(rm.back()->row());
		}
	for (std::vector<Node *>::size_type i = 0; i < rm.size(); i++)
		rm.at(i)->coverRow();
	DancingLinks::solve(res);
	while (rm.size() != 0) {
		rm.back()->unCoverRow();
		rm.pop_back();
	}
}
