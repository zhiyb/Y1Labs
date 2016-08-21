#ifndef SBOARD_H
#define SBOARD_H

#include <QWidget>
#include <inttypes.h>
#include "define.h"
#include "sbox.h"

class sBoard : public QWidget
{
	Q_OBJECT

	friend class sBox;

public:
	explicit sBoard(QWidget *parent = 0);

signals:

public slots:
	void start(void) {type = sBox::Set;}
	void restart(void);
	void open(void);
	void save(void);
	void clear(void);
	void refresh(void);
	void setAutoSet(bool e) {autoSet = e;}

protected:
	void resizeEvent(QResizeEvent *);

private:
	class sBox *box[S_SIZE][S_SIZE];
	bool autoSet;
	sBox::Box_Type type;
};

#endif // SBOARD_H
