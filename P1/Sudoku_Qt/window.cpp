#include <QHBoxLayout>
#include <QVBoxLayout>
#include "window.h"
#include "squarewidget.h"
#include "define.h"

Window::Window(QWidget *parent)
	: QMainWindow(parent)
{
	QWidget *w = new QWidget;
	setCentralWidget(w);
	setMinimumSize(BOX_SIZE * S_SIZE * 5 / 4, BOX_SIZE * S_SIZE);

	QHBoxLayout *layout = new QHBoxLayout(w);
	class squareWidget *square = new squareWidget;
	board = new sudokuBoard(square);
	layout->addWidget(square, 4);

	QVBoxLayout *pbGroup = new QVBoxLayout;
	layout->addLayout(pbGroup, 1);

	pbGroup->addWidget(pbLoad = new QPushButton("Load"));
	pbGroup->addWidget(pbSolve = new QPushButton("Solve"));
	pbGroup->addWidget(pbClear = new QPushButton("Clear"));
	pbGroup->addWidget(pbSave = new QPushButton("Save"));
	pbGroup->addWidget(pbQuit = new QPushButton("Quit"));

	pbLoad->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	pbSolve->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	pbClear->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	pbSave->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	pbQuit->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

	connect(pbLoad, SIGNAL(clicked()), board, SLOT(load()));
	connect(pbSolve, SIGNAL(clicked()), board, SLOT(solve()));
	connect(pbClear, SIGNAL(clicked()), board, SLOT(clear()));
	connect(pbSave, SIGNAL(clicked()), board, SLOT(save()));
	connect(pbQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

Window::~Window()
{
}
