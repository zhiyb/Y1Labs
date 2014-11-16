#include <Qt/QtGui>
#include "window.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setStyle(new QPlastiqueStyle);
	a.setFont(QFont("Courier", 16));
	Window win;
	win.setWindowTitle("Boost Converter Controller Host");
	win.show();
	return a.exec();
}
