#include <QGridLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QElapsedTimer>
#include <fstream>
#include <iostream>
#include "sudokuboard.h"

using namespace std;

sudokuBoard::sudokuBoard(QWidget *parent) :
	QWidget(parent)
{
	QGridLayout *layout = new QGridLayout(this);
	layout->setSpacing(SPACE_SQARE);
	QGridLayout *square[S_UNIT_SIZE][S_UNIT_SIZE];
	for (int y = 0; y < S_UNIT_SIZE; y++)
		for (int x = 0; x < S_UNIT_SIZE; x++) {
			layout->addLayout(square[x][y] = new QGridLayout, y, x);
			square[x][y]->setSpacing(SPACE_BOX);
			/*for (int i = 0; i < S_UNIT_SIZE; i++) {
				square[x][y]->setColumnStretch(i, 1);
				square[x][y]->setRowStretch(i, 1);
			}*/
		}
	for (int y = 0; y < S_SIZE; y++)
		for (int x = 0; x < S_SIZE; x++)
			square[x / S_UNIT_SIZE][y / S_UNIT_SIZE]->addWidget(box[x][y] = new sudokuBox, \
									    y % S_UNIT_SIZE, x % S_UNIT_SIZE);

	board = new sBoard;

	setAutoFillBackground(true);
	QPalette pal(palette());
	pal.setColor(QPalette::Background, COLOUR_LINE);
	setPalette(pal);
}

bool sudokuBoard::load(void)
{
	QString path = QFileDialog::getOpenFileName(topLevelWidget(), "Open Sudoku data file", QString(), "Text file (*.txt)");
	if (path.isEmpty())
		return false;
	fstream file(path.toLocal8Bit(), ios_base::in);
	if (!file.is_open()) {
		QMessageBox::critical(topLevelWidget(), "Error", "Cannot open file for read!");
		return false;
	}
	if (!(file >> *board)) {
		QMessageBox::critical(topLevelWidget(), "Error", "Error read file context!");
		file.close();
		return false;
	}
	QPalette fixed(box[0][0]->palette()), set(box[0][0]->palette());
	fixed.setColor(QPalette::Foreground, COLOUR_FIXED);
	set.setColor(QPalette::Foreground, COLOUR_SET);
	for (int y = 0; y < S_SIZE; y++)
		for (int x = 0; x < S_SIZE; x++) {
			if (board->getBox(x, y)->count() == 1) {
				box[x][y]->setPalette(fixed);
				box[x][y]->setText(QString::number(board->getBox(x, y)->number() + (S_SIZE < 16), 16).toUpper());
			} else {
				box[x][y]->setPalette(set);
				box[x][y]->setText(QString());
			}
			box[x][y]->setReadOnly(false);
		}
	file.close();
	return true;
}

bool sudokuBoard::save(void)
{
	QString path = QFileDialog::getSaveFileName(topLevelWidget(), "Open Sudoku data file", QString(), "Text file (*.txt)");
	if (path.isEmpty())
		return false;
	fstream file(path.toLocal8Bit(), ios_base::out);
	if (!file.is_open()) {
		QMessageBox::critical(topLevelWidget(), "Error", "Cannot open file for write!");
		return false;
	}
	bool solved = true;
	board->clear();
	for (int y = 0; y < S_SIZE; y++)
		for (int x = 0; x < S_SIZE; x++) {
			if (box[x][y]->text().isEmpty())
				solved = false;
			else if (box[x][y]->palette().foreground().color() == COLOUR_FIXED)
				board->getBox(x, y)->setPossible(1 << (box[x][y]->text().toInt(0, 16) - (S_SIZE < 16)));
		}
	file << "# Original Sudoku" << endl << *board << endl;
	if (!solved)
		goto ret;
	board->clear();
	for (int y = 0; y < S_SIZE; y++)
		for (int x = 0; x < S_SIZE; x++)
			if (!box[x][y]->text().isEmpty())
				board->getBox(x, y)->setPossible(1 << (box[x][y]->text().toInt(0, 16) - (S_SIZE < 16)));
	file << endl << "# Solved Sudoku" << endl << *board << endl;
ret:
	file.unsetf(ios::hex);
	file.setf(ios::dec);
	file << endl << "# Original data" << endl;
	for (int y = 0; y < S_SIZE; y++)
		for (int x = 0; x < S_SIZE; x++) {
			if (!box[x][y]->text().isEmpty() && box[x][y]->palette().foreground().color() == COLOUR_FIXED)
				file << y * S_SIZE * S_SIZE + x * S_SIZE + board->getBox(x, y)->number() << " ";
		}
	file << endl;
	file.close();
	return true;
}

bool sudokuBoard::solve(void)
{
	board->clear();
	for (int y = 0; y < S_SIZE; y++)
		for (int x = 0; x < S_SIZE; x++)
			if (!box[x][y]->text().isEmpty())
				board->getBox(x, y)->set(1 << (box[x][y]->text().toInt(0, 16) - (S_SIZE < 16)));
	QElapsedTimer timer;
	timer.start();
	if (!board->solve()) {
		QMessageBox::critical(topLevelWidget(), "Error", "Unable to solve this Sudoku!");
		return false;
	}
	qint64 elapsed = timer.nsecsElapsed();
	for (int y = 0; y < S_SIZE; y++)
		for (int x = 0; x < S_SIZE; x++) {
			if (board->getBox(x, y)->count() == 1)
				box[x][y]->setText(QString::number(board->getBox(x, y)->number() + (S_SIZE < 16), 16).toUpper());
			else	// Should not happened
				box[x][y]->setText(QString());
			box[x][y]->setReadOnly(true);
		}
	QMessageBox::information(topLevelWidget(), "Finished", \
				 "Solve finished in " + QString::number((double)elapsed / 1000000000, 'f') + " seconds.");
	return true;
}

void sudokuBoard::clear(void)
{
	QPalette set(box[0][0]->palette());
	set.setColor(QPalette::Foreground, COLOUR_SET);
	for (int y = 0; y < S_SIZE; y++)
		for (int x = 0; x < S_SIZE; x++) {
			box[x][y]->setReadOnly(false);
			box[x][y]->setText(QString());
			box[x][y]->setPalette(set);
		}
}
