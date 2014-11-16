#include <QGridLayout>
#include <QKeyEvent>
#include "sudokuselector.h"

#define SPACE	3
#define BUTTON	64

sudokuSelector::sudokuSelector(int n, QWidget *parent) :
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	v = -1;
	class sudokuSelectorButton *pbNum[n * n];
	QGridLayout *layout = new QGridLayout(this);
	for (int i = 0; i < n * n; i++) {
		layout->addWidget(pbNum[i] = new sudokuSelectorButton(i + 1), i / n, i % n);
		connect(pbNum[i], SIGNAL(clicked(int)), this, SLOT(set(int)));
	}
	layout->setSpacing(SPACE);
	resize(parent->size() / 3);
	setWindowTitle("Selector");
}

void sudokuSelector::set(int val)
{
	v = val;
	accept();
}

/*void sudokuSelector::keyPressEvent(QKeyEvent *e)
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
}*/

sudokuSelectorButton::sudokuSelectorButton(int num, QWidget *parent) : QPushButton(QString::number(num), parent)
{
	setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	setMinimumSize(BUTTON, BUTTON);
	connect(this, SIGNAL(clicked()), this, SLOT(output()));
}

void sudokuSelectorButton::output(void)
{
	emit clicked(text().toInt());
}
