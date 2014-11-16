#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QtCore>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	if (argc != 2) {
		qDebug() << "Wrong argument number!";
		return 1;
	}
	int size = atoi(argv[1]);
	MainWindow w(size);
	w.show();

	return a.exec();
}
