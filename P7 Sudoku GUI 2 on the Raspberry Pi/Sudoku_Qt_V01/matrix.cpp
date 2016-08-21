#include "matrix.h"
#include <QPainter>
#include <QtCore>
#include <QString>
#include <QMessageBox>
#include <vector>

#define ZOOM	(600 / MAT_R)

using namespace std;

Matrix::Matrix(int s, QWidget *parent) :
	QWidget(parent)
{
	n = s;
	//ls = new LatinSquares(n);
	//ls->solve(true);
	this->s = new Sudoku(n);
	//this->s->solve();
	//display();
	setMinimumSize(MAT_C * ZOOM, MAT_R * ZOOM);
}

void Matrix::display(void)
{
	//QMessageBox::information(this, "Solutions", QString("Total %1 solutions").arg(ls->count));
	/*vector<vector<int> > *resList = &ls->solutions();
	QMessageBox::information(this, "Solutions", QString("Total %1 solutions").arg(resList->size()));
	for (vector<vector<int> >::size_type i = 0; i < resList->size(); i++) {
		int s[n][n];
		for (vector<int>::size_type j = 0; j < resList->at(i).size(); j++)
			s[resList->at(i).at(j) / (n * n)][(resList->at(i).at(j) / n) % n] = resList->at(i).at(j) % n;
		QString str;
		for (int r = 0; r < n; r++) {
			for (int c = 0; c < n; c++)
				str.append(QString::number(s[r][c] + 1) + ", ");
			if (r != n - 1)
				str.append('\n');
		}
		QMessageBox::information(this, "Solutions", QString("Solution No. %1\n" + str).arg(i + 1));
	}*/
}

void Matrix::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	for (int c = 0; c < MAT_C && s->head()->next(Node::Right, c + 1) != s->head(); c++) {
		Node *p = s->head()->next(Node::Right, c + 1)->d[Node::Down];
		while (p->r != -1) {
			painter.setPen(Qt::black);
			painter.setBrush(Qt::black);
			if (ZOOM > 1)
				painter.drawRect(c * ZOOM, p->r * ZOOM, ZOOM, ZOOM);
			else
				painter.drawPoint(c, p->r);
			p = p->d[Node::Down];
		}
	}
}
