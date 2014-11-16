#ifndef _HEXBYTE_H
#define _HEXBYTE_H

#include <qpushbutton.h>
#include <qlabel.h>
#include <qlcdnumber.h>

class BinButton: public QPushButton
{
	Q_OBJECT

public:
	BinButton(bool defValue = 0, QWidget *parent = 0, const char *name = 0);
	void setValue(bool v);

signals:
	void changed(void);

private slots:
	void toggle(bool v);
};

class HexByte: public QWidget
{
	Q_OBJECT

public:
	HexByte(const QString text, const int v, QWidget *parent = 0, const char *name = 0, WFlags f = 0);
	void setValue(const int v);
	int value(void) const {return lcd->intValue();}

protected:
	void resizeEvent(QResizeEvent *r);

private:
	QLabel *l;
	QLCDNumber *lcd;
	BinButton *bit[8];

private slots:
	void update(void);
};

#endif
