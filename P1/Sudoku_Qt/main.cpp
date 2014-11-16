#include "window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Window w;
	w.setWindowTitle("Sudoku solver - by backtrace algorithm");
	w.show();

	return a.exec();
}
