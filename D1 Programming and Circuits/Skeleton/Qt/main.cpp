#include <Qt/QtGui>
#include "window.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setFont(QFont("Simsun", 13));
	Window win;
	win.show();
	return a.exec();
}
