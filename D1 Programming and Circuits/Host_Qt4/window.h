#ifndef WINDOW_H
#define WINDOW_H

#include <Qt/QtCore>
#include <Qt/QtGui>
#include <QtExtSerialPort/qextserialport.h>

class Window: public QWidget
{
	Q_OBJECT

public:
	Window(QWidget *parent = 0);

protected:
	void resizeEvent(QResizeEvent *e);

private slots:
	void setValue(int v);
	void COMConnect(bool e);
	void COMUpdate(void);
	void apply(void);

private:
	int Conv2ADC(float v);
	float Conv2Volt(int adc);

	QLineEdit *leCom;
	QLabel *lGet[3], *lSet;
	QSlider *sSet;
	QPushButton *pbApply, *pbConnect, *pbQuit;
	QextSerialPort *sp;
	QTimer *t;
};

#endif