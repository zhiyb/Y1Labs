#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include <QWidget>
#include <QtCore>
#include "define.h"
#include "sudokubox.h"
#include "sboard.h"

class sudokuBoard : public QWidget
{
	Q_OBJECT
public:
	explicit sudokuBoard(QWidget *parent = 0);

signals:

public slots:
	bool load(void);
	bool solve(void);
	void clear(void);
	bool save(void);

private:
	class sudokuBox *box[S_SIZE][S_SIZE];
	class sBoard *board;
};

#endif // SUDOKUBOARD_H
