#include <QtGui>
#include "mainwindow.h"
#include "define.h"

#define W	(size().width())
#define H	(size().height())
#define S	128
#define SX	(W - S)
#define SQ	((W - S) < H ? (W - S) : H)
#define STDH	32

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	board = new sBoard(this);
	button = new QWidget(this);
	vbLayout = new QVBoxLayout(button);
	vbLayout->addWidget(cbAutoSet = new QCheckBox("Auto set"));
	vbLayout->addWidget(pbFinish = new QPushButton("Start"));
	vbLayout->addWidget(pbRefresh = new QPushButton("Refresh"));
	vbLayout->addWidget(pbRestart = new QPushButton("Restart"));
	vbLayout->addWidget(pbClear = new QPushButton("Clear"));
	vbLayout->addWidget(pbOpen = new QPushButton("Open"));
	vbLayout->addWidget(pbSave = new QPushButton("Save"));
	vbLayout->addWidget(pbQuit = new QPushButton("Quit"));

	connect(pbFinish, SIGNAL(clicked()), board, SLOT(start()));
	connect(pbRefresh, SIGNAL(clicked()), board, SLOT(refresh()));
	connect(pbRestart, SIGNAL(clicked()), board, SLOT(restart()));
	connect(pbClear, SIGNAL(clicked()), board, SLOT(clear()));
	connect(pbOpen, SIGNAL(clicked()), board, SLOT(open()));
	connect(pbSave, SIGNAL(clicked()), board, SLOT(save()));
	connect(pbQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
	connect(cbAutoSet, SIGNAL(toggled(bool)), board, SLOT(setAutoSet(bool)));

	cbAutoSet->setChecked(false);

	setMinimumSize(board->minimumSize() + QSize(S, 0));
	resize(minimumSize());
}

void MainWindow::resizeEvent(QResizeEvent *)
{
	if (SX != H)
		resize(SQ + S, SQ);
	board->setGeometry(0, 0, H, H);
	button->setGeometry(SX, 0, S, H);
}
