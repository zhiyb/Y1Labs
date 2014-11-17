#include <QGridLayout>
#include <QKeyEvent>
#include "sudokuselector.h"

#define SPACE	3
#define BUTTON	48

sudokuSelector::sudokuSelector(int n, QWidget *parent) :
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	v = -1;
	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(sb = new QSpinBox, 0, 0, 1, n - 1);
	sb->setRange(1, n * n + 1);
	sb->selectAll();
	layout->addWidget(pbAccept = new QPushButton("Ok"), 0, n - 1, 1, 1);
	pbAccept->setMinimumWidth(BUTTON);
	pbAccept->setDefault(true);
	connect(pbAccept, SIGNAL(clicked()), this, SLOT(set()));
	class sudokuSelectorButton *pbNum[n * n];
	for (int i = 0; i < n * n; i++) {
		layout->addWidget(pbNum[i] = new sudokuSelectorButton(i + 1), i / n + 1, i % n);
		connect(pbNum[i], SIGNAL(clicked(int)), this, SLOT(set(int)));
	}
	layout->setSpacing(SPACE);
	resize(parent->size() / 3);
	setWindowTitle("Selector");
}

void sudokuSelector::set(void)
{
	v = sb->value();
	accept();
}

void sudokuSelector::set(int val)
{
	v = val;
	accept();
}

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
