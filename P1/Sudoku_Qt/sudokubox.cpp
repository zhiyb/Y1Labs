#include <QFont>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QDialog>
#include "sudokuselector.h"
#include "sudokubox.h"
#include "define.h"

sudokuBox::sudokuBox(QWidget *parent) :
	QLabel(parent)
{
	readOnly = false;
	setAutoFillBackground(true);
	QPalette pal(palette());
	pal.setColor(QPalette::Background, COLOUR_BOX_BGC);
	pal.setColor(QPalette::Foreground, COLOUR_SET);
	setPalette(pal);
	setAlignment(Qt::AlignCenter);
	setText(QString());
}

void sudokuBox::resizeEvent(QResizeEvent *e)
{
	QFont f(font());
	f.setPixelSize(e->size().width() * 0.9);
	setFont(f);
}

void sudokuBox::mouseReleaseEvent(QMouseEvent *)
{
	QPalette pal(palette());
	if (readOnly)
		return;
	if (!text().isEmpty()) {
		pal.setColor(QPalette::Foreground, COLOUR_SET);
		setPalette(pal);
		setText(QString());
		return;
	}
	pal.setColor(QPalette::Background, COLOUR_BOX_SEL);
	setPalette(pal);
	class sudokuSelector selector(topLevelWidget());
	if (selector.exec() == QDialog::Accepted) {
		pal.setColor(QPalette::Foreground, COLOUR_FIXED);
		setText(QString::number(selector.value(), 16).toUpper());
	}
	pal.setColor(QPalette::Background, COLOUR_BOX_BGC);
	setPalette(pal);
}
