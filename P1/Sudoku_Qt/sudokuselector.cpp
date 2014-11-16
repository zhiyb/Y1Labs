#include <QGridLayout>
#include <QKeyEvent>
#include "sudokuselector.h"
#include "define.h"

sudokuSelector::sudokuSelector(QWidget *parent) :
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	QGridLayout *layout = new QGridLayout(this);
	for (int i = 0; i < S_SIZE; i++) {
		layout->addWidget(pbNum[i] = new sudokuSelectorButton(i + (S_SIZE < 16)), i / S_UNIT_SIZE, i % S_UNIT_SIZE);
		pbNum[i]->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
		pbNum[i]->setMinimumSize(BOX_SIZE, BOX_SIZE);
		connect(pbNum[i], SIGNAL(clicked(int)), this, SLOT(set(int)));
	}
	layout->setSpacing(SPACE_BOX);
	setWindowTitle("Selector");
	resize(parent->size() / 3);
}

void sudokuSelector::set(int val)
{
	v = val;
	accept();
}

void sudokuSelector::keyPressEvent(QKeyEvent *e)
{
	if (e->key() - (S_SIZE < 16) >= '0' && e->key() <= '9') {
		v = e->key() - '0' - (S_SIZE < 16);
		accept();
#if (S_SIZE >= 16)
	} else if (e->key() >= 'a' && e->key() <= 'f') {
		v = e->key() - 'a' + 0x0A;
		accept();
	} else if (e->key() >= 'A' && e->key() <= 'F') {
		v = e->key() - 'A' + 0x0A;
		accept();
#endif
	} else if (e->key() == Qt::Key_Escape)
		reject();
}

sudokuSelectorButton::sudokuSelectorButton(int num, QWidget *parent) : QPushButton(QString::number(num, 16).toUpper(), parent)
{
	connect(this, SIGNAL(clicked()), this, SLOT(output()));
}

void sudokuSelectorButton::output(void)
{
	emit clicked(text().toInt(0, 16));
}
