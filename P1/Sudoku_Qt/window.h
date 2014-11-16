#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "sudokuboard.h"

class Window : public QMainWindow
{
	Q_OBJECT
public:
	Window(QWidget *parent = 0);
	~Window();

private:
	class sudokuBoard *board;
	QPushButton *pbQuit, *pbLoad, *pbSolve, *pbClear, *pbSave;
};

#endif // WINDOW_H
