#include "window.h"

Window::Window(QWidget *parent): QWidget(parent)
{
	leCom = new QLineEdit("/dev/ttyUSB0", this);

	pbConnect = new QPushButton("Connect", this);
	pbConnect->setCheckable(true);

	lGet = new QLabel("Current: ---", this);
	lSet = new QLabel("Set: 12V", this);

	sSet = new QSlider(Qt::Horizontal, this);
	sSet->setMinimum(0);
	sSet->setMaximum(150);
	sSet->setSingleStep(1);
	sSet->setPageStep(10);
	sSet->setSliderPosition(120);

	pbApply = new QPushButton("Apply", this);

	pbQuit = new QPushButton("Quit", this);

	connect(sSet, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
	connect(pbQuit, SIGNAL(clicked()), qApp, SLOT(quit()));

	setMinimumSize(240, 180);
}

void Window::setValue(int v)
{
	lSet->setText("Set: " + \
			QString::number((double)sSet->value() / 10) + \
			"V");
}

#define W	(e->size().width())
#define H	(e->size().height())
#define STDH	24
void Window::resizeEvent(QResizeEvent *e)
{
	leCom->setGeometry(0, 0, W * 3 / 4, STDH);
	pbConnect->setGeometry(W * 3 / 4, 0, W / 4, STDH);
	lGet->setGeometry(0, STDH, W, STDH);
	lSet->setGeometry(0, STDH * 2, W, STDH);
	sSet->setGeometry(0, STDH * 3, W, STDH);
	pbApply->setGeometry(0, H - STDH, W / 2, STDH);
	pbQuit->setGeometry(W / 2, H - STDH, W / 2, STDH);
}
