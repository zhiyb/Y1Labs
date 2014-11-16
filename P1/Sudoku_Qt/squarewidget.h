#ifndef SQUAREWIDGET_H
#define SQUAREWIDGET_H

#include <QWidget>

class squareWidget : public QWidget
{
	Q_OBJECT
public:
	explicit squareWidget(QWidget *parent = 0);

signals:

public slots:

private:
	void resizeEvent(QResizeEvent *e);
	int heightForWidth(int w) const {return w;}
};

#endif // SQUAREWIDGET_H
