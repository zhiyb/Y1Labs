#include "sudoku.h"
#include <QMessageBox>

using namespace std;

Sudoku::Sudoku(int size)
{
	n = size;
	for (int c = 0; c < MAT_C; c++)		// Columns
		h->connect(Node::Left, new Node(-1))->connect(Node::Top, h);
	for (int r = 0; r < MAT_R; r++) {	// Rows
		int num = r % NN, x = (r / NN) % NN, y = r / (NN * NN);
		// Row group 1: Positions
		Node *p = new Node(r);
		p->connect(Node::Top, h->next(Node::Right, y * NN + x + 1))->connect(Node::Up, p);
		// Row group 2: Rows
		p = p->connect(Node::Right, new Node(r));
		p->connect(Node::Top, h->next(Node::Right, NN * NN + y * NN + num + 1))->connect(Node::Up, p);
		// Row group 3: Columns
		p = p->connect(Node::Right, new Node(r));
		p->connect(Node::Top, h->next(Node::Right, NN * NN * 2 + x * NN + num + 1))->connect(Node::Up, p);
		// Row group 3: Boxes
		p = p->connect(Node::Right, new Node(r));
		p->connect(Node::Top, h->next(Node::Right, NN * NN * 3 + (y - y % n + x / n) * NN + num + 1))->connect(Node::Up, p);
	}
}

bool Sudoku::solved(const std::vector<int> &res)
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

#ifndef QT_NO_DEBUG
#include "sudokuwidget.h"
#include <QDialog>
void Sudoku::status(const std::vector<int> &res)
{
	static int count = 0;
	if (count++ % 1000000)
		return;
	QDialog d;
	SudokuWidget *s = new SudokuWidget(n, &d);
	s->fill(res);
	d.exec();
}
#endif

QString Sudoku::toString(const std::vector<int> &res)
{
	QString str;
	for (std::vector<int>::size_type i = 0; i < res.size(); i++)
		str.append(QString::number(res.at(i)) + " ");
	return str;
}

vector<int> Sudoku::fromString(const QString& line)
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

void Sudoku::solve(const std::vector<int> &pre)
{
	std::vector<int> res(pre);
	std::vector<Node *> rm;
	for (std::vector<int>::size_type i = 0; i < pre.size(); i++) {
		int num = pre.at(i) % NN, x = (pre.at(i) / NN) % NN, y = pre.at(i) / (NN * NN);
		rm.push_back(h->next(Node::Right, y * NN + x + 1)->next(Node::Down, num + 1));
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
