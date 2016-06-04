#ifndef RECVWIDGET_H
#define RECVWIDGET_H

#include <QWidget>
#include "package.h"

class RecvWidget : public QWidget
{
	Q_OBJECT
public:
	explicit RecvWidget(QWidget *parent = 0);
	~RecvWidget();

signals:

public slots:
	void received(package_t *pkg);

protected:
	void paintEvent(QPaintEvent *);

private:
	QPixmap pix;
};

#endif // RECVWIDGET_H
