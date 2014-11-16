#include "latinsquare.h"
#include <iostream>
#include <QMessageBox>

using namespace std;

LatinSquare::LatinSquare(int size) : DancingLinks()
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

bool LatinSquare::check(const std::vector<int> &res)
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

bool LatinSquare::solved(const std::vector<int> &res)
{
	solution.push_back(res);
	if (solution.size() == 1)
		return QMessageBox::information(0, "Solved", \
						QString("Got %1 solution!\nContinue?").arg(solution.size()), \
						QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes;
	if (solution.size() % 10 != 0)
		return true;
	return QMessageBox::information(0, "Too many solutions", \
					QString("Got %1 solutions!\nContinue?").arg(solution.size()), \
					QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes;
}

void LatinSquare::solve(const bool ordered)
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

QString LatinSquare::toString(const std::vector<int> &res)
{
	QString str;
	for (std::vector<int>::size_type i = 0; i < res.size(); i++)
		str.append(QString::number(res.at(i)) + " ");
	return str;
}

vector<int> LatinSquare::fromString(const QString& line)
{
	vector<int> res;
	if (line.isEmpty() || line.startsWith("#"))
		return res;
	QStringList l = line.split(" ", QString::SkipEmptyParts);
	for (QStringList::size_type i = 0; i < l.size(); i++)
		if (l.at(i).toInt() > 0 && l.at(i).toInt() < MAT_R)
			res.push_back(l.at(i).toInt());
	return res;
}

void LatinSquare::solve(const std::vector<int> &pre)
{
	std::vector<int> res(pre);
	std::vector<Node *> rm;
	for (std::vector<int>::size_type i = 0; i < pre.size(); i++) {
		int num = pre.at(i) % n, x = (pre.at(i) / n) % n, y = pre.at(i) / (n * n);
		rm.push_back(h->next(Node::Right, y * n + x + 1)->next(Node::Down, num + 1));
	}
	for (std::vector<Node *>::size_type i = 0; i < rm.size(); i++)
		rm.at(i)->coverRow();
	solution.clear();
	DancingLinks::solve(res);
	while (rm.size() != 0) {
		rm.back()->unCoverRow();
		rm.pop_back();
	}
}
