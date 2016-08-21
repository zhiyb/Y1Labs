/* This is the C++(Qt5) code for host program,
 * to control the boost converter.
 * Wrote by Yubo Zhi (yz39g13@soton.ac.uk)
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtSerialPort>

class Window: public QMainWindow
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
	QLabel *lGet[4], *lSet;
	QSlider *sSet;
	QPushButton *pbApply, *pbConnect, *pbQuit;
	QSerialPort *sp;
	QTimer *t;
};

#endif
