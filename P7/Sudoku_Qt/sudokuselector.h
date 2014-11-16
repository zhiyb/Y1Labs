#ifndef SUDOKUSELECTOR_H
#define SUDOKUSELECTOR_H

#include <QDialog>
#include <QPushButton>
#include <QSpinBox>

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
	explicit sudokuSelector(int n, QWidget *parent = 0);
	int value(void) const {return v;}

private slots:
	void set(void);
	void set(int val);

private:
	int v;
	QPushButton *pbCancel, *pbAccept;
	QSpinBox *sb;
};

#endif // SUDOKUSELECTOR_H
