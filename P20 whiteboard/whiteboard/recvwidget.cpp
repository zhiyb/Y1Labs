#include <QPainter>
#include <QQueue>
#include <QDebug>
#include "recvwidget.h"

RecvWidget::RecvWidget(QWidget *parent) : QWidget(parent)
{
	setAutoFillBackground(true);
	pix = QPixmap(size());
	pix.fill(Qt::white);
}

RecvWidget::~RecvWidget()
{
}

void RecvWidget::received(package_t *pkg)
{
	switch (pkg->cmd) {
	case package_t::Clear:
		pix.fill();
		break;
	case package_t::Resize: {
		QSize size = *(QSize *)pkg->data.constData();
		resize(size);
		pix = QPixmap(size);
		pix.fill();
		break;
	}
	case package_t::Line: {
		QPoint *points = (QPoint *)pkg->data.constData();
		QPainter painter(&pix);
		painter.drawLine(points[0], points[1]);
		break;
	}
	}
	update();
	delete pkg;
}

void RecvWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawPixmap(rect(), pix);
}
