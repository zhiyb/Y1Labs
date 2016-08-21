#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "connection.h"
#include "sendwidget.h"
#include "recvwidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

signals:

public slots:

private:
	QThread conThread;
	Connection *con;
	SendWidget *send;
	RecvWidget *recv;
};

#endif // MAINWINDOW_H
