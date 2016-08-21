#include <QPainter>
#include <QPalette>
#include <QResizeEvent>
#include <QDebug>
#include "sendwidget.h"

SendWidget::SendWidget(Connection *c, QWidget *parent) : QWidget(parent)
{
	con = c;

	setAutoFillBackground(true);
	QPalette pal(palette());
	pal.setColor(QPalette::Background, Qt::white);
	setPalette(pal);
}

SendWidget::~SendWidget()
{
}

void SendWidget::resizeEvent(QResizeEvent *e)
{
	pix = QPixmap(e->size().width(), e->size().height());
	pix.fill();
	package_t pkg;
	pkg.cmd = package_t::Resize;
	pkg.data.append((const char *)&e->size(), sizeof(e->size()));
	con->sendPackage(&pkg);
}

void SendWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawPixmap(rect(), pix);
}

void SendWidget::mousePressEvent(QMouseEvent *e)
{
	prev = e->pos();
}

void SendWidget::mouseMoveEvent(QMouseEvent *e)
{
	QPainter painter(&pix);
	painter.setPen(Qt::black);
	painter.setBrush(QBrush(Qt::black));
	painter.drawLine(prev, e->pos());

	package_t pkg;
	pkg.cmd = package_t::Line;
	pkg.data.append((const char *)&prev, sizeof(prev));
	QPoint p = e->pos();
	pkg.data.append((const char *)&p, sizeof(prev));
	con->sendPackage(&pkg);

	prev = e->pos();
	painter.end();
	update();
}
