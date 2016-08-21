#ifndef SUDOKUWIDGET_H
#define SUDOKUWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <vector>
#include "sudoku.h"

class SudokuWidget : public QWidget
{
	Q_OBJECT
public:
	explicit SudokuWidget(int size, QWidget *parent = 0);
	~SudokuWidget(void);
	std::vector<std::vector<int> > solutions(void) {return s->solutions();}
	void fill(const std::vector<int>& p) {pre = p;}

public slots:
	void clear(void);
	void load(void);
	void save(void);
	void solve(void);
	void loadSolution(int index);

signals:
	void doClear(void);

private:
	void paintEvent(QPaintEvent *);
	void mouseReleaseEvent(QMouseEvent *e);

	std::vector<int> pre, res;
	Sudoku *s;
	int n, selected[2];
};

#endif // SUDOKUWIDGET_H
