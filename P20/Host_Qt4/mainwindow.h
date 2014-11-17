#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow(void);

private slots:
	void browseInput(void);
	void browseOutput(void);
	void convert(void);

private:
	QLineEdit *tKey, *tInput, *tOutput;
	QPushButton *pbConv, *pbBrowse[2], *pbQuit;
};

#endif // MAINWINDOW_H
