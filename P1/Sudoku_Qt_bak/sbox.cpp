#include <QtGui>
#include "sbox.h"
#include "sboard.h"
#include "sselector.h"

sBox::sBox(class sBoard *parent) :
	QFrame(parent)
{
	hPrev = 0;
	hNext = 0;
	vPrev = 0;
	vNext = 0;
	sPrev = 0;
	sNext = 0;
	board = 0;
	QPalette pal = palette();
	pal.setColor(QPalette::Background, COLOUR_BOXBGC);
	pal.setColor(QPalette::Foreground, Qt::black);
	setAutoFillBackground(true);
	setFrameShape(QFrame::Box);
	setPalette(pal);
	for (int x = 0; x < S_UNIT_SIZE; x++)
		for (int y = 0; y < S_UNIT_SIZE; y++) {
			label[x][y] = new QLabel(QString::number(y * S_UNIT_SIZE + x + (S_UNIT_SIZE == 3), 16).toUpper(), this);
			label[x][y]->setAlignment(Qt::AlignCenter);
			label[x][y]->setScaledContents(true);
		}
	setPossible(POSSIBLE_ALL);
}

uint32_t sBox::singleConv(uint32_t v)
{
	uint32_t sum = v >> 16, single = v & 0xFFFF, num = poss & 0xFFFF;
	single = ((single & ~num) | (~sum & num)) & 0xFFFF;
	sum |= num;
	//qDebug() << QString::number(v, 16) << QString::number(sum, 16) << QString::number(single, 16) << QString::number(num, 16);
	return (sum << 16) | single;
}

uint32_t sBox::setStream(uint32_t v)
{
	//qDebug() << QString::number(v, 16);
	if (((class sBoard *)parent())->autoSet && type == Empty && (v & poss) != 0)
		set(v & poss);
	return v;
}

void sBox::mouseReleaseEvent(QMouseEvent *)
{
	uint32_t v;
	QPalette pal = palette();
	switch (type)
	{
	case Empty:
		pal.setColor(QPalette::Background, COLOUR_CLICKED);
		setPalette(pal);
		v = sSelector::execSelector(topLevelWidget(), poss);
		pal.setColor(QPalette::Background, COLOUR_BOXBGC);
		setPalette(pal);
		if (v != poss || count() == 1)
			switch (((class sBoard *)parent())->type) {
			case Set:
				set(v);
				break;
			case Fixed:
				setFixed(v);
			default:
				break;
			}
		break;
	case Fixed:
	case ConflictFixed:
		if (((class sBoard *)parent())->type != Fixed)
			break;
	case Set:
	case Conflict:
		setPossible(POSSIBLE_ALL);
	default:
		break;
	}
}

void sBox::set(uint32_t v)
{
	type = Set;
	poss = v;
	updateDisplay();
	emit valueSet(number());
	emit singleStream();
}

void sBox::setFixed(uint32_t v)
{
	type = Fixed;
	poss = v;
	updateDisplay();
	emit valueSet(number());
	emit singleStream();
}

void sBox::setPossible(uint32_t v)
{
	poss = v;
	type = Empty;
	updateDisplay();
}

void sBox::updateDisplay(void)
{
	QPalette pal = label[0][0]->palette();
	int v = number();
	if (v == -1) {
		for (int x = 0; x < S_UNIT_SIZE; x++)
			for (int y = 0; y < S_UNIT_SIZE; y++)
				label[x][y]->setVisible(false);
		pal = palette();
		pal.setColor(QPalette::Background, COLOUR_ERROR);
		setPalette(pal);
		return;
	}
	switch (type) {
	case Empty:
		pal.setColor(QPalette::Foreground, COLOUR_POSSIBLE);
		for (int x = 0; x < S_UNIT_SIZE; x++)
			for (int y = 0; y < S_UNIT_SIZE; y++) {
				label[x][y]->setPalette(pal);
				label[x][y]->setVisible(poss & (1 << (y * S_UNIT_SIZE + x)));
			}
		goto ret;
	case Fixed:
		pal.setColor(QPalette::Foreground, COLOUR_FIXED);
		break;
	case Set:
		pal.setColor(QPalette::Foreground, COLOUR_SET);
		break;
	case Conflict:
		pal.setColor(QPalette::Foreground, COLOUR_CONFLICT);
		break;
	case ConflictFixed:
		pal.setColor(QPalette::Foreground, COLOUR_CONFLICTFIXED);
		break;
	}
	for (int x = 0; x < S_UNIT_SIZE; x++)
		for (int y = 0; y < S_UNIT_SIZE; y++)
			label[x][y]->setVisible(false);
	label[v % S_UNIT_SIZE][v / S_UNIT_SIZE]->setPalette(pal);
	label[v % S_UNIT_SIZE][v / S_UNIT_SIZE]->setVisible(true);
ret:
	resizeEvent(NULL);
}

int sBox::number(void)
{
	for (uint32_t i = 1, j = 0; i != (1 << S_SIZE); i <<= 1, j++)
		if (poss & i)
			return j;
	return -1;
}

int sBox::count(void)
{
	int cnt = 0;
	for (uint32_t i = 1; i != (1 << S_SIZE); i <<= 1)
		cnt += (poss & i) != 0;
	return cnt;
}

void sBox::removePossible(int v)
{
	switch (type) {
	case Conflict:
	case ConflictFixed:
		return;
	case Empty:
		poss &= ~(1 << v);
		if (((class sBoard *)parent())->autoSet && count() == 1)
			set(poss);
		break;
	case Fixed:
		if (number() == v) {
			type = ConflictFixed;
			emit valueConflict(v);
			break;
		}
		return;
	case Set:
		if (number() == v) {
			type = Conflict;
			emit valueConflict(v);
			break;
		}
		return;
	}
	updateDisplay();
}

#define W	(size().width())
#define H	(size().height())
void sBox::resizeEvent(QResizeEvent *)
{
	QFont f = font();
	switch (type) {
	case Empty:
		f.setPixelSize(H / S_UNIT_SIZE);
		for (int x = 0; x < S_UNIT_SIZE; x++)
			for (int y = 0; y < S_UNIT_SIZE; y++)
				label[x][y]->setGeometry(W / S_UNIT_SIZE * x, H / S_UNIT_SIZE * y, W / S_UNIT_SIZE, H / S_UNIT_SIZE);
		break;
	case Fixed:
	case Set:
	case Conflict:
	case ConflictFixed:
		f.setPixelSize(H);
		for (int x = 0; x < S_UNIT_SIZE; x++)
			for (int y = 0; y < S_UNIT_SIZE; y++)
				label[x][y]->setGeometry(0, 0, W, H);
	}
	setFont(f);
}
