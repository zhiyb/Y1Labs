#ifndef SSELECTOR_H
#define SSELECTOR_H

#include <QDialog>
#include <QtGui>
#include <QPushButton>
#include <inttypes.h>

#include "sboard.h"
#include "define.h"

class sSelector : public QDialog
{
	Q_OBJECT
public:
	explicit sSelector(QWidget *parent = 0);
	void setValue(uint32_t v);
	uint32_t value(void) {return val;}
	static uint32_t execSelector(QWidget *parent, uint32_t v);

signals:

public slots:

protected:
	void resizeEvent(QResizeEvent *);
	void keyPressEvent(QKeyEvent *e);

private slots:
	void number0(void) {val = (1 << 0x00); accept();}
	void number1(void) {val = (1 << 0x01); accept();}
	void number2(void) {val = (1 << 0x02); accept();}
	void number3(void) {val = (1 << 0x03); accept();}
	void number4(void) {val = (1 << 0x04); accept();}
	void number5(void) {val = (1 << 0x05); accept();}
	void number6(void) {val = (1 << 0x06); accept();}
	void number7(void) {val = (1 << 0x07); accept();}
	void number8(void) {val = (1 << 0x08); accept();}
	void number9(void) {val = (1 << 0x09); accept();}
	void numberA(void) {val = (1 << 0x0A); accept();}
	void numberB(void) {val = (1 << 0x0B); accept();}
	void numberC(void) {val = (1 << 0x0C); accept();}
	void numberD(void) {val = (1 << 0x0D); accept();}
	void numberE(void) {val = (1 << 0x0E); accept();}
	void numberF(void) {val = (1 << 0x0F); accept();}

private:
	QPushButton *pbSelect[S_SIZE], *pbCancel;
	uint32_t val;
};

#endif // SSELECT_H
