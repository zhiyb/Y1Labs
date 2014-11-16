/* This is the C++(Qt5) code for host program,
 * to control the boost converter.
 * Wrote by Yubo Zhi (yz39g13@soton.ac.uk)
 */

#include "window.h"
#include "comm.h"
#include <unistd.h>

#define BAUDRATE	QSerialPort::Baud9600
#define UPDATESPEED	200		// ms
#define UARTDELAY	50		// ms
#define ADCMAX		1024
#define PWMMAX		1024

#define VIN	1.5
#define VREF	3.3
#define R1	22000
#define R2	4700
#define R3	0.22

Window::Window(QWidget *parent): QMainWindow(parent)
{
	leCom = new QLineEdit("COM2", this);

	pbConnect = new QPushButton("Connect", this);
	pbConnect->setCheckable(true);

	lGet[0] = new QLabel("Readings - Set: ---", this);
	lGet[1] = new QLabel("Readings - ADC: ---", this);
	lGet[2] = new QLabel("Readings - PWM: ---", this);
	lGet[3] = new QLabel("Readings - Current: ---", this);
	lSet = new QLabel(this);
	Window::setValue(120);

	sSet = new QSlider(Qt::Horizontal, this);
	sSet->setMinimum(VIN * 10);
	sSet->setMaximum(170);
	sSet->setSingleStep(1);
	sSet->setPageStep(10);
	sSet->setSliderPosition(120);

	pbApply = new QPushButton("Apply", this);
	pbApply->setDefault(true);

	pbQuit = new QPushButton("Quit", this);

	sp = new QSerialPort(this);

	t = new QTimer(this);
	t->stop();
	t->setSingleShot(false);

	connect(sSet, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
	connect(pbConnect, SIGNAL(toggled(bool)), this, SLOT(COMConnect(bool)));
	connect(pbApply, SIGNAL(clicked()), this, SLOT(apply()));
	connect(pbQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
	connect(t, SIGNAL(timeout()), this, SLOT(COMUpdate()));

	setMinimumSize(400, 230);
}

float Window::Conv2Volt(int adc)
{
	return ((float)adc / ADCMAX * VREF) / R2 * (R1 + R2);
}

int Window::Conv2ADC(float v)
{
	return (int)(ADCMAX * (v / (R1 + R2) * R2) / VREF);
}

void Window::apply(void)
{
	if (!sp->isOpen()) {
		QMessageBox::critical(this, "Error", "Serial Port not opened!");
		return;
	}
	t->stop();
	int set = Conv2ADC(sSet->value() / 10.0);
	QString cmd(COMM_SET + QString::number(set) + ' ');
	qDebug() << "Send: " + cmd;
	sp->clear();
	sp->write(cmd.toLatin1(), cmd.length());
	sp->flush();
	QThread::currentThread()->msleep(UARTDELAY);
	sp->waitForReadyRead(UARTDELAY);
	QString get(sp->readAll());
	if (set != get/*QString(sp->readAll())*/.toInt()) {
		qDebug() << "Read: " + get;
		QMessageBox::warning(this, "Warning", "The settings may not transfered to the controller!");
	}
	t->start();
}

void Window::setValue(int v)
{
	float volt = v / 10.0;
	lSet->setText("Settings: " + QString::number(volt) + "V (" + QString::number(Conv2Volt(Conv2ADC(volt))) + "V)");
}

void Window::COMConnect(bool e)
{
	if (!e) {
		t->stop();
		sp->close();
		lGet[0]->setText("Readings - Set: ---");
		lGet[1]->setText("Readings - ADC: ---");
		lGet[2]->setText("Readings - PWM: ---");
		lGet[3]->setText("Readings - Current: ---");
		return;
	}
	sp->setPortName(leCom->text());
	if (!sp->open(QIODevice::ReadWrite)) {
		QMessageBox::critical(this, "Error", "Cannot open serial port!");
		pbConnect->setChecked(false);
		return;
	}
	sp->setBaudRate(BAUDRATE);
	sp->setDataBits(QSerialPort::Data8);
	sp->setFlowControl(QSerialPort::NoFlowControl);
	t->start(UPDATESPEED);
	COMUpdate();
}

void Window::COMUpdate(void)
{
	char data[2] = {COMM_GET, '\n'};
	sp->clear();
	sp->write(data, 2);
	sp->flush();
	QThread::currentThread()->msleep(UARTDELAY);
	sp->waitForReadyRead(UARTDELAY);
	sp->waitForReadyRead(UARTDELAY);
	QString rep(QString(sp->readAll().simplified()));
	if (rep.isEmpty()) {
		lGet[0]->setText("Readings - Set: N/A");
		lGet[1]->setText("Readings - ADC: N/A");
		lGet[2]->setText("Readings - PWM: N/A");
		lGet[3]->setText("Readings - Current: N/A");
		return;
	}
	QStringList value = rep.split(" ", QString::SkipEmptyParts);
	if (value.count() != 4) {
		qDebug() << rep;
		lGet[0]->setText("Readings - Set: Error!");
		lGet[1]->setText("Readings - ADC: Error!");
		lGet[2]->setText("Readings - PWM: Error!");
		lGet[3]->setText("Readings - Current: Error!");
		return;
	}
	QString set = QString::number(Conv2Volt(value.at(1).toInt()));
	QString adc = QString::number(Conv2Volt(value.at(0).toInt()));
	QString pwm = QString::number((value.at(2).toFloat() + 1) / PWMMAX * 100);
	QString cur = QString::number(value.at(3).toFloat() / ADCMAX * VREF / R3);
	lGet[0]->setText("Readings - Set: " + set + "V");
	lGet[1]->setText("Readings - ADC: " + adc + "V");
	lGet[2]->setText("Readings - PWM: " + pwm + "% (" + value.at(2) + "/" + QString::number(PWMMAX) + ")");
	lGet[3]->setText("Readings - Current: " + cur + "A");
}

#define SPACE	16
#define STDH	24
#define W	(e->size().width() - SPACE * 2)
#define H	(e->size().height() - SPACE * 2)
void Window::resizeEvent(QResizeEvent *e)
{
	leCom->setGeometry(SPACE, SPACE, W * 3 / 4, STDH);
	pbConnect->setGeometry(SPACE + W * 3 / 4, SPACE, W / 4, STDH);
	lGet[0]->setGeometry(SPACE, SPACE + STDH, W, STDH);
	lGet[1]->setGeometry(SPACE, SPACE + STDH * 2, W, STDH);
	lGet[2]->setGeometry(SPACE, SPACE + STDH * 3, W, STDH);
	lGet[3]->setGeometry(SPACE, SPACE + STDH * 4, W, STDH);
	lSet->setGeometry(SPACE, SPACE + STDH * 5, W, STDH);
	sSet->setGeometry(SPACE, SPACE + STDH * 6, W, STDH);
	pbApply->setGeometry(SPACE, SPACE + H - STDH, W / 2, STDH);
	pbQuit->setGeometry(SPACE + W / 2, SPACE + H - STDH, W / 2, STDH);
}
