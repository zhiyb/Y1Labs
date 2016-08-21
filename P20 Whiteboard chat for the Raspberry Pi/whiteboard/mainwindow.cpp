#include <QtGui>
#include <QHBoxLayout>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	QWidget *w = new QWidget(this);
	setCentralWidget(w);

	QHBoxLayout *layout = new QHBoxLayout(w);

	con = new Connection;

	layout->addWidget(send = new SendWidget(con));
	layout->addWidget(recv = new RecvWidget);

	con->moveToThread(&conThread);
	connect(&conThread, SIGNAL(started()), con, SLOT(loop()));
	connect(&conThread, SIGNAL(finished()), con, SLOT(quit()));

	connect(send, SIGNAL(send(package_t*)), con, SLOT(sendPackage(package_t*)));
	connect(&con->rxPool, SIGNAL(received(package_t*)), recv, SLOT(received(package_t*)));

	conThread.start();
}

MainWindow::~MainWindow()
{
	con->quit();
	conThread.quit();
	conThread.wait();
	delete con;
}
