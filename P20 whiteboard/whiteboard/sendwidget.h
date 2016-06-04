#ifndef SENDWIDGET_H
#define SENDWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include "package.h"
#include "connection.h"

class SendWidget : public QWidget
{
	Q_OBJECT
public:
	explicit SendWidget(Connection *c, QWidget *parent = 0);
	~SendWidget();

signals:
	void send(package_t *pkg);

public slots:

protected:
	void resizeEvent(QResizeEvent *e);
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);

private:
	Connection *con;
	QPixmap pix;
	QPoint prev;
};

#endif // SENDWIDGET_H
