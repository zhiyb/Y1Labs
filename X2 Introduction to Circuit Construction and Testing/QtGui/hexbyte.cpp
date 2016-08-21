#include "hexbyte.h"

BinButton::BinButton(bool defValue, QWidget *parent, const char *name): QPushButton(parent, name)
{
	setToggleButton(true);
	setText(QString::number(defValue));
	setOn(defValue);
	connect(this, SIGNAL(toggled(bool)), this, SLOT(toggle(bool)));
}

void BinButton::setValue(bool v)
{
	setOn(v);
}

void BinButton::toggle(bool v)
{
	setText(QString::number(v));
	emit changed();
}

HexByte::HexByte(QString text, const int v, QWidget *parent, const char *name, WFlags f): QWidget(parent, name, f)
{
	l = new QLabel(text, this);
	l->setAlignment(AlignHCenter | AlignVCenter);

	lcd = new QLCDNumber(2, this);
	lcd->setMode(QLCDNumber::Hex);
	lcd->display(v);

	for (int i = 0; i < 8; i++) {
		bit[i] = new BinButton((v >> (7 - i)) & 0x01, this);
		connect(bit[i], SIGNAL(changed()), this, SLOT(update()));
	}
}

void HexByte::setValue(const int v)
{
	for (int i = 0; i < 8; i++)
		bit[i]->setValue((v >> (7 - i)) & 0x01);
}

void HexByte::update(void)
{
	int n = 0;
	for (int i = 0; i < 8; i++)
		n += bit[i]->isOn() << (7 - i);
	lcd->display(n);
}

#define RSH (r->size().height())
#define RSW (r->size().width())
#define UNIT (RSW / 10)
void HexByte::resizeEvent(QResizeEvent *r)
{
	int x = 0;
	l->setGeometry(x, 0, UNIT, RSH);
	x += UNIT;
	lcd->setGeometry(x, 0, UNIT, RSH);
	x += UNIT;
	for (int i = 0; i < 8; x += UNIT, i++)
		bit[i]->setGeometry(x, 0, UNIT, RSH);
}
