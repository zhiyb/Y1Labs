#ifndef WINDOW_H
#define WINDOW_H

#include <Qt/QtCore>
#include <Qt/QtGui>

class Window: public QWidget
{
	Q_OBJECT

public:
	Window(QWidget *parent = 0);

protected:
	void resizeEvent(QResizeEvent *e);

private slots:
	void setValue(int v);

private:
	QLineEdit *leCom;
	QLabel *lGet, *lSet;
	QSlider *sSet;
	QPushButton *pbApply, *pbConnect, *pbQuit;
};

#endif
