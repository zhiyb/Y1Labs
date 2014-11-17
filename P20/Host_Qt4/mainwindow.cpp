#include <QtCore>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QFont>
#include <QFile>
#include <QDataStream>
#include "mainwindow.h"
#include "bcm2835.h"
#include "op.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	QWidget *w = new QWidget(this);
	QGridLayout *layout = new QGridLayout(w);

	layout->addWidget(tKey = new QLineEdit("Key phrase"), 1, 1);
	layout->addWidget(pbConv = new QPushButton("Convert"), 1, 2);
	connect(pbConv, SIGNAL(clicked()), this, SLOT(convert()));
	layout->addWidget(tInput = new QLineEdit("Input file path"), 2, 1);
	layout->addWidget(pbBrowse[0] = new QPushButton("Browse"), 2, 2);
	connect(pbBrowse[0], SIGNAL(clicked()), this, SLOT(browseInput()));
	layout->addWidget(tOutput = new QLineEdit("Output file path"), 3, 1);
	layout->addWidget(pbBrowse[1] = new QPushButton("Browse"), 3, 2);
	connect(pbBrowse[1], SIGNAL(clicked()), this, SLOT(browseOutput()));
	layout->addWidget(pbQuit = new QPushButton("Quit"), 4, 1, 1, 2);
	connect(pbQuit, SIGNAL(clicked()), qApp, SLOT(quit()));

	setCentralWidget(w);
}

MainWindow::~MainWindow(void)
{
}

void MainWindow::browseInput(void)
{
	QString path = QFileDialog::getOpenFileName(this, "Input file");
	if (path.isEmpty())
		return;
	tInput->setText(path);
}

void MainWindow::browseOutput(void)
{
	QString path = QFileDialog::getSaveFileName(this, "Output file", tInput->text());
	if (path.isEmpty())
		return;
	tOutput->setText(path);
}

#define TRANSFER(v)	bcm2835_spi_transfer(v)
void MainWindow::convert(void)
{
	QString key = tKey->text().toUtf8();
	unsigned int len = key.toLocal8Bit().length();
	if (len == 0 || len > 256) {
		QMessageBox::critical(this, "Error", "Key length not acceptable!");
		return;
	}

	QFile input(tInput->text()), output(tOutput->text());
	if (!input.open(QFile::ReadOnly)) {
		QMessageBox::critical(this, "Error", "Cannot open input file for read!");
		return;
	}
	if (!output.open(QFile::WriteOnly)) {
		QMessageBox::critical(this, "Error", "Cannot open output file for write!");
		input.close();
		return;
	}

	QDataStream in(&input), out(&output);

	// Acknowledge
	if (TRANSFER(0xFF) != HSM_KEY || TRANSFER(HSM_KEY) != HSM_KEY) {
		QMessageBox::critical(this, "Error", "HSM not accessible");
		goto err;
	}

	// Send key
	TRANSFER(len & 0xFF);
	for (unsigned int i = 0; i < len; i++)
		TRANSFER((unsigned char)key.toLocal8Bit().at(i));

	//Wait for MCU
	while (TRANSFER(0xFF) != HSM_KEY + 1);
	TRANSFER(HSM_KEY + 1);

	// Receive key stream & codec
	while (!in.atEnd()) {
		char c;
		in.readRawData(&c, 1);
		c ^= TRANSFER(0);
		out.writeRawData(&c, 1);
	}

	// Transfer finished
	TRANSFER(0xFF);
	QMessageBox::information(this, "Succeed", "Convertion finished!");
err:
	input.close();
	output.close();
	return;
}
