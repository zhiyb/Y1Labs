#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtGui>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>
#include "sboard.h"
#include "define.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow() {}

protected:
	void resizeEvent(QResizeEvent *);

private:
	class sBoard *board;
	QCheckBox *cbAutoSet;
	QPushButton *pbFinish, *pbOpen, *pbSave, *pbClear, *pbRestart, *pbQuit, *pbRefresh;
	QWidget *button;
	QVBoxLayout *vbLayout;
};

#endif // MAINWINDOW_H
