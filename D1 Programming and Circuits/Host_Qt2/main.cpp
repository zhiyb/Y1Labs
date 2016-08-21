#include <qapplication.h>
#include "window.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//a.setStyle(new QPlastiqueStyle);
	a.setFont(QFont("Simsun", 13));
	Window win;
	win.setWindowTitle("Boost Converter Controller Host");
	win.show();
	return a.exec();
}
