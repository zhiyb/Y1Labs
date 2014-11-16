#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>
#include <QtCore>

#define MAXSIZE	36

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	int size;
	if (argc != 2) {
		bool ok;
		size = QInputDialog::getInt(0, "Size of Latin Square", "Please input the size of Latin Square:", 3, 1, MAXSIZE, 1, &ok);
		if (!ok)
			return 0;
	} else
		size = atoi(argv[1]);
	if (size <= 0 || size > MAXSIZE) {
		QMessageBox::critical(0, "Error", "Unacceptable Latin Square size!");
		return 1;
	}
	MainWindow w(size);
	w.show();

	return a.exec();
}
