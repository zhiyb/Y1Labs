#ifndef SUDOKUSELECTOR_H
#define SUDOKUSELECTOR_H

#include <QDialog>
#include <QPushButton>
#include "define.h"

class sudokuSelectorButton : public QPushButton
{
	Q_OBJECT
public:
	explicit sudokuSelectorButton(int num = 0, QWidget *parent = 0);

signals:
	void clicked(int);

private slots:
	void output(void);
};

class sudokuSelector : public QDialog
{
	Q_OBJECT
public:
	explicit sudokuSelector(QWidget *parent = 0);
	int value(void) const {return v;}

signals:

public slots:

private slots:
	void set(int val);

private:
	void keyPressEvent(QKeyEvent *e);

	int v;
	class sudokuSelectorButton *pbNum[S_SIZE];
	QPushButton *pbCancel;
};

#endif // SUDOKUSELECTOR_H
