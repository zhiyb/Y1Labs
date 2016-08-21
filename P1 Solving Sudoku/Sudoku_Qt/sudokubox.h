#ifndef SUDOKUBOX_H
#define SUDOKUBOX_H

#include <QLabel>

class sudokuBox : public QLabel
{
	Q_OBJECT
public:
	explicit sudokuBox(QWidget *parent = 0);
	bool isReadOnly(void) const {return readOnly;}

signals:

public slots:
	void setReadOnly(bool e) {readOnly = e;}

private:
	void resizeEvent(QResizeEvent *e);
	void mouseReleaseEvent(QMouseEvent *);

	bool readOnly;
};

#endif // SUDOKUBOX_H
