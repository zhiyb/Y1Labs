#ifndef SBOX_H
#define SBOX_H

#include <QtGui>
#include <QFrame>
#include <QLabel>
#include <inttypes.h>
#include "define.h"

class sBox : public QFrame
{
	Q_OBJECT

	friend class sBoard;

public:
	explicit sBox(class sBoard *parent = 0);
	uint32_t possible(void) {return poss;}

	enum Box_Type {Empty, Fixed, Set, Conflict, ConflictFixed};

signals:
	void valueSet(int);
	void singleStream(void);
	void valueConflict(int);
	void singleHOStream(uint32_t);						// Stream format: sum(16b) + single(16b)
	void singleVOStream(uint32_t);
	void singleSOStream(uint32_t);
	void setHOStream(uint32_t);						// Stream format: sum(16b) + single(16b)
	void setVOStream(uint32_t);
	void setSOStream(uint32_t);

public slots:
	void set(uint32_t v);
	void setFixed(uint32_t v);
	void setPossible(uint32_t v);
	void removePossible(int v);
	void singleHIStream(uint32_t v) {emit singleHOStream(singleConv(v));}	// Horizontal stream
	void singleVIStream(uint32_t v) {emit singleVOStream(singleConv(v));}	// Vertical stream
	void singleSIStream(uint32_t v) {emit singleSOStream(singleConv(v));}	// Square stream
	void singleHStream() {emit singleHOStream(poss << 16 | poss);}
	void singleVStream() {emit singleVOStream(poss << 16 | poss);}
	void singleSStream() {emit singleSOStream(poss << 16 | poss);}
	void setHIStream(uint32_t v) {emit setHOStream(setStream(v));}		// Horizontal stream
	void setVIStream(uint32_t v) {emit setVOStream(setStream(v));}		// Vertical stream
	void setSIStream(uint32_t v) {emit setSOStream(setStream(v));}		// Square stream

protected:
	void resizeEvent(QResizeEvent *);
	void mouseReleaseEvent(QMouseEvent *);

private:
	void updateDisplay(void);
	int number(void);
	int count(void);
	uint32_t singleConv(uint32_t v);
	uint32_t setStream(uint32_t v);

	class sBox *hPrev, *hNext, *vPrev, *vNext, *sPrev, *sNext;
	class sBoard *board;
	Box_Type type;
	uint32_t poss;
	QLabel *label[S_UNIT_SIZE][S_UNIT_SIZE];
};

#endif // SNODE_H
