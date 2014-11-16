#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QCheckBox>
#include "latinsquarewidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(int size, QWidget *parent = 0);
	~MainWindow();

private slots:
	void solve(void);
	void clear(void);

private:
	LatinSquareWidget *s;
	QListWidget *res;
	QPushButton *pbLoad, *pbSolve, *pbSave, *pbClear, *pbQuit;
};

#endif // MAINWINDOW_H
