#ifndef _WINDOW_H
#define _WINDOW_H

#include <qwidget.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qmultilineedit.h>
#include <qgrid.h>
#include "hexbyte.h"
#include "prog.h"

class Form: public QWidget
{
	Q_OBJECT

public:
	Form(QWidget *parent = 0, const char *name = 0, WFlags f = 0);

protected:
	void resizeEvent(QResizeEvent *r);

private slots:
	void read(int i);
	void make(void);
	void uart(void);
	void jtag(void);
	void console(void);
	void flash(void);
	void readFuse(void);
	void writeFuse(void);
	void readEEPROM(void);
	void writeEEPROM(void);

private:
	QPushButton *pbMake, *pbUART, *pbJTAG, *pbConsole;
	QPushButton *pbFlash, *pbRFuse, *pbWFuse, *pbREEPROM, *pbWEEPROM;
	QPushButton *pbQuit;
	HexByte *fuse[3];
	QComboBox *list;
	Program *prog;

	enum FUSE {Extended, High, Low};
};

#endif
