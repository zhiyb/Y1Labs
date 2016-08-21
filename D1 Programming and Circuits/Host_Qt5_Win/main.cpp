/* This is the C++(Qt5) code for host program,
 * to control the boost converter.
 * Wrote by Yubo Zhi (yz39g13@soton.ac.uk)
 */

#include <QtGui>
#include "window.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setFont(QFont("Courier", 12));
	Window win;
	win.setWindowTitle("Boost Converter Controller Host");
	win.show();
	return a.exec();
}
