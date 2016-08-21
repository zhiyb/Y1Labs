#include <QResizeEvent>
#include "squarewidget.h"

squareWidget::squareWidget(QWidget *parent) :
	QWidget(parent)
{
	QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	policy.setHeightForWidth(true);
	this->setSizePolicy(policy);
}

#define SIZE	(e->size().height() > e->size().width() ? e->size().width() : e->size().height())
void squareWidget::resizeEvent(QResizeEvent *e)
{
	for (int i = 0; i < children().size(); i++)
		((QWidget *)children().at(i))->setGeometry((e->size().width() - SIZE) / 2, \
							   (e->size().height() - SIZE) / 2, SIZE, SIZE);
}
