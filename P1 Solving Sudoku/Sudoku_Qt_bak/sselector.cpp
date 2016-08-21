#include "sselector.h"
#include "ctype.h"

sSelector::sSelector(QWidget *parent) :
	QDialog(parent,  Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	val = POSSIBLE_ALL;
	for (int i = 0; i < S_SIZE; i++)
		pbSelect[i] = new QPushButton(QString::number(i + (S_UNIT_SIZE == 3), 16).toUpper(), this);
	pbCancel = new QPushButton("Cancel", this);
	pbCancel->setDefault(true);
	connect(pbSelect[0x00], SIGNAL(clicked()), this, SLOT(number0()));
	connect(pbSelect[0x01], SIGNAL(clicked()), this, SLOT(number1()));
	connect(pbSelect[0x02], SIGNAL(clicked()), this, SLOT(number2()));
	connect(pbSelect[0x03], SIGNAL(clicked()), this, SLOT(number3()));
	connect(pbSelect[0x04], SIGNAL(clicked()), this, SLOT(number4()));
	connect(pbSelect[0x05], SIGNAL(clicked()), this, SLOT(number5()));
	connect(pbSelect[0x06], SIGNAL(clicked()), this, SLOT(number6()));
	connect(pbSelect[0x07], SIGNAL(clicked()), this, SLOT(number7()));
	connect(pbSelect[0x08], SIGNAL(clicked()), this, SLOT(number8()));
#if (S_SIZE == 16)
	connect(pbSelect[0x09], SIGNAL(clicked()), this, SLOT(number9()));
	connect(pbSelect[0x0A], SIGNAL(clicked()), this, SLOT(numberA()));
	connect(pbSelect[0x0B], SIGNAL(clicked()), this, SLOT(numberB()));
	connect(pbSelect[0x0C], SIGNAL(clicked()), this, SLOT(numberC()));
	connect(pbSelect[0x0D], SIGNAL(clicked()), this, SLOT(numberD()));
	connect(pbSelect[0x0E], SIGNAL(clicked()), this, SLOT(numberE()));
	connect(pbSelect[0x0F], SIGNAL(clicked()), this, SLOT(numberF()));
#endif
	connect(pbCancel, SIGNAL(clicked()), this, SLOT(reject()));
	setMinimumSize(48 * S_UNIT_SIZE, 32 * (S_UNIT_SIZE + 1));
	setWindowTitle("Selector");
	resize(parent->size() / 3);
}

void sSelector::setValue(uint32_t v)
{
	val = v;
	for (int i = 0; i < S_SIZE; i++)
		pbSelect[i]->setVisible(v & (1 << i));
}

uint32_t sSelector::execSelector(QWidget *parent, uint32_t v)
{
	sSelector *selector = new sSelector(parent);
	selector->setValue(v);
	if (selector->exec() == selector->Accepted)
		v = selector->value();
	delete selector;
	return v;
}

void sSelector::keyPressEvent(QKeyEvent *e)
{
	if (e->key() - (S_UNIT_SIZE == 3) >= '0' && e->key() <= '9' && pbSelect[e->key() - '0' - (S_UNIT_SIZE == 3)]->isVisible()) {
		val = (1 << (e->key() - '0' - (S_UNIT_SIZE == 3)));
		accept();
#if (S_SIZE == 16)
	} else if (e->key() >= 'a' && e->key() <= 'f' && pbSelect[e->key() - 'a' + 0x0A]->isVisible()) {
		val = (1 << (e->key() - 'a' + 0x0A));
		accept();
	} else if (e->key() >= 'A' && e->key() <= 'F' && pbSelect[e->key() - 'A' + 0x0A]->isVisible()) {
		val = (1 << (e->key() - 'A' + 0x0A));
		accept();
#endif
	} else if (e->key() == Qt::Key_Escape)
		reject();
}

#define W	(e->size().width())
#define H	(e->size().height())
void sSelector::resizeEvent(QResizeEvent *e)
{
	for (int x = 0; x < S_UNIT_SIZE; x++)
		for (int y = 0; y < S_UNIT_SIZE; y++)
			pbSelect[y * S_UNIT_SIZE + x]->setGeometry(W / S_UNIT_SIZE * x, H / (S_UNIT_SIZE + 1) * y, W / S_UNIT_SIZE, H / (S_UNIT_SIZE + 1));
	pbCancel->setGeometry(0, H * S_UNIT_SIZE / (S_UNIT_SIZE + 1), W, H / (S_UNIT_SIZE + 1));
}
