#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtCore>

MainWindow::MainWindow(int size, QWidget *parent)
	: QMainWindow(parent)
{
	QWidget *m = new QWidget(this);
	setCentralWidget(m);
	QHBoxLayout *hb = new QHBoxLayout(m);
	hb->addWidget(s = new SudokuWidget(size), 4);
	hb->addWidget(res = new QListWidget, 1);
	res->setMinimumWidth(128);
	QVBoxLayout *vb = new QVBoxLayout;
	hb->addLayout(vb, 1);
	vb->addWidget(pbLoad = new QPushButton("Load"));
	vb->addWidget(pbSolve = new QPushButton("Solve"));
	vb->addWidget(pbSave = new QPushButton("Save"));
	vb->addWidget(pbClear = new QPushButton("Clear"));
	vb->addWidget(pbQuit = new QPushButton("Quit"));
	pbLoad->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	pbSolve->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	pbSave->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	pbClear->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	pbQuit->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	connect(res, SIGNAL(currentRowChanged(int)), s, SLOT(loadSolution(int)));
	connect(s, SIGNAL(doClear()), this, SLOT(clear()));
	connect(pbLoad, SIGNAL(clicked()), s, SLOT(load()));
	connect(pbSolve, SIGNAL(clicked()), this, SLOT(solve()));
	connect(pbSave, SIGNAL(clicked()), s, SLOT(save()));
	connect(pbClear, SIGNAL(clicked()), s, SLOT(clear()));
	connect(pbQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
	//resize(minimumSize());
	setWindowTitle("Sudoku solver - by Dancing Links");
}

MainWindow::~MainWindow()
{
}

void MainWindow::solve(void)
{
	res->clear();
	s->solve();
	for (std::vector<std::vector<int> >::size_type i = 0; i < s->solutions().size(); i++)
		res->addItem(QString("Solution %1").arg(i + 1));
}

void MainWindow::clear(void)
{
	res->clear();
}
