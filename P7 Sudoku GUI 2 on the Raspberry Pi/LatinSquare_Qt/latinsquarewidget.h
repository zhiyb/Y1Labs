#ifndef LATINSQUAREWIDGET_H
#define LATINSQUAREWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <vector>
#include "latinsquare.h"

class LatinSquareWidget : public QWidget
{
	Q_OBJECT
public:
	explicit LatinSquareWidget(int size, QWidget *parent = 0);
	~LatinSquareWidget(void);
	std::vector<std::vector<int> > solutions(void) {return h->solutions();}
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
	LatinSquare *h;
	int n, selected[2];
};

#endif // LATINSQUAREWIDGET_H
