#ifndef MATRIX_H
#define MATRIX_H

#include <QWidget>
#include <QPaintEvent>
#include <vector>
//#include "node.h"
//#include "latinsquares.h"
#include "sudoku.h"

class Matrix : public QWidget
{
	Q_OBJECT
public:
	explicit Matrix(int s, QWidget *parent = 0);

public slots:
	void display(void);

private:
	void paintEvent(QPaintEvent *);

	//LatinSquares *ls;
	Sudoku *s;
	int n;
};

#endif // MATRIX_H
