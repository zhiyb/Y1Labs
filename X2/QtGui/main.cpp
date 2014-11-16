#include <qapplication.h>
#include "form.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setFont(QFont("Simsun", 13), true);
	Form w;
	a.setMainWidget(&w);
	w.setCaption("AVR - Auto");
	w.showMaximized();
	return a.exec();
}
