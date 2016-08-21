#include <QtGui>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "sboard.h"

sBoard::sBoard(QWidget *parent) :
	QWidget(parent)
{
	type = sBox::Fixed;
	autoSet = false;
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::black);
	setPalette(pal);
	setAutoFillBackground(true);
	for (int x = 0; x < S_SIZE; x++)
		for (int y = 0; y < S_SIZE; y++)
			box[x][y] = new sBox(this);

	for (int y = 0; y < S_SIZE; y++)
		for (int x = 0; x < S_SIZE; x++) {
			if (x != 0)
				box[x][y]->hPrev = box[x - 1][y];
			if (x != S_SIZE - 1)
				box[x][y]->hNext = box[x + 1][y];
			if (y != 0)
				box[x][y]->vPrev = box[x][y - 1];
			if (y != S_SIZE - 1)
				box[x][y]->vNext = box[x][y + 1];
			if (x % S_UNIT_SIZE != 0 || y % S_UNIT_SIZE != 0)
				box[x][y]->sPrev = box[(x % S_UNIT_SIZE) == 0 ? x + S_UNIT_SIZE - 1 : x - 1]\
						      [(x % S_UNIT_SIZE) == 0 ? y - 1 : y];
			if (x % S_UNIT_SIZE != S_UNIT_SIZE - 1 || y % S_UNIT_SIZE != S_UNIT_SIZE - 1)
				box[x][y]->sNext = box[(x % S_UNIT_SIZE) == S_UNIT_SIZE - 1 ? x - S_UNIT_SIZE + 1 : x + 1]\
						      [(x % S_UNIT_SIZE) == S_UNIT_SIZE - 1 ? y + 1 : y];
			box[x][y]->board = this;
		}

	/*for (int x = 0; x < S_SIZE; x++)
		for (int y = 0; y < S_SIZE; y++) {
			// Horizontal connection
			for (int x2 = 0; x2 < S_SIZE; x2++) {
				connect(box[x][y], SIGNAL(singleStream()), box[x2][0], SLOT(singleVStream()));
				if (x2 != x)
					connect(box[x][y], SIGNAL(valueSet(int)), box[x2][y], SLOT(removePossible(int)));
			}

			// Vertical connection
			for (int y2 = 0; y2 < S_SIZE; y2++) {
				connect(box[x][y], SIGNAL(singleStream()), box[0][y2], SLOT(singleHStream()));
				if (y2 != y)
					connect(box[x][y], SIGNAL(valueSet(int)), box[x][y2], SLOT(removePossible(int)));
			}

			// Square connection
			for (int x2 = 0; x2 < S_UNIT_SIZE; x2++)
				for (int y2 = 0; y2 < S_UNIT_SIZE; y2++) {
					connect(box[x][y], SIGNAL(singleStream()), box[x2 * S_UNIT_SIZE][y2 * S_UNIT_SIZE], SLOT(singleSStream()));
					if (x2 != x % S_UNIT_SIZE || y2 != y % S_UNIT_SIZE)
						connect(box[x][y], SIGNAL(valueSet(int)), \
							box[x - x % S_UNIT_SIZE + x2][y - y % S_UNIT_SIZE + y2], SLOT(removePossible(int)));
				}

			// Horizontal single method stream connection
			if (x != 0)
				connect(box[x][y], SIGNAL(setHOStream(uint32_t)), box[x - 1][y], SLOT(setHIStream(uint32_t)));
			if (x != S_SIZE - 1)
				connect(box[x][y], SIGNAL(singleHOStream(uint32_t)), box[x + 1][y], SLOT(singleHIStream(uint32_t)));
			else
				connect(box[x][y], SIGNAL(singleHOStream(uint32_t)), box[x][y], SLOT(setHIStream(uint32_t)));

			// Vertical single method stream connection
			if (y != 0)
				connect(box[x][y], SIGNAL(setVOStream(uint32_t)), box[x][y - 1], SLOT(setVIStream(uint32_t)));
			if (y != S_SIZE - 1)
				connect(box[x][y], SIGNAL(singleVOStream(uint32_t)), box[x][y + 1], SLOT(singleVIStream(uint32_t)));
			else
				connect(box[x][y], SIGNAL(singleVOStream(uint32_t)), box[x][y], SLOT(setVIStream(uint32_t)));

			// Square single method stream connection
			if ((y % S_UNIT_SIZE) != 0 || (x % S_UNIT_SIZE) != 0)
				connect(box[x][y], SIGNAL(setSOStream(uint32_t)), \
					box[(x % S_UNIT_SIZE) == 0 ? x + S_UNIT_SIZE - 1 : x - 1] \
					   [(x % S_UNIT_SIZE) == 0 ? y - 1 : y], SLOT(setSIStream(uint32_t)));
			if ((y % S_UNIT_SIZE) != S_UNIT_SIZE - 1 || (x % S_UNIT_SIZE) != S_UNIT_SIZE - 1)
				connect(box[x][y], SIGNAL(singleSOStream(uint32_t)), \
					box[(x % S_UNIT_SIZE) == S_UNIT_SIZE - 1 ? x - S_UNIT_SIZE + 1 : x + 1] \
					   [(x % S_UNIT_SIZE) == S_UNIT_SIZE - 1 ? y + 1 : y], SLOT(singleSIStream(uint32_t)));
			else
				connect(box[x][y], SIGNAL(singleSOStream(uint32_t)), box[x][y], SLOT(setSIStream(uint32_t)));
		}*/

#if (S_SIZE == 9)
	setMinimumSize(350, 350);
#else
	setMinimumSize(700, 700);
#endif
}

void sBoard::open(void)
{
	bool readFixed = false, readAll = false;
	int y = 0;
	uint32_t fixed[S_SIZE][S_SIZE], all[S_SIZE][S_SIZE];
	QString path = QFileDialog::getOpenFileName(topLevelWidget(), "Open Sudoku file", QString(), "Text File (*.txt)");
	if (path.isEmpty())
		return;
	QFile file(path);
	if (!file.open(QFile::ReadOnly)) {
		QMessageBox::critical(topLevelWidget(), "Error", "Cannot open selected file!");
		return;
	}
	QTextStream text(&file);
	while (!text.atEnd()) {
		QString line = text.readLine();
		if (line.isEmpty() || line.startsWith("//"))
			continue;
		QStringList l = line.split(" ", QString::SkipEmptyParts);
		if (l.count() != S_SIZE) {
			QMessageBox::critical(topLevelWidget(), "Error", "Invalid file context!");
			goto ret;
		}
		for (int x = 0; x < S_SIZE; x++) {
			int i = l.at(x).toInt(0, 16);
			if (l.at(x).startsWith('x', Qt::CaseInsensitive)) {
				if (readFixed)
					all[x][y] = POSSIBLE_ALL;
				else
					fixed[x][y] = POSSIBLE_ALL;
			} else if (i >= (S_SIZE == 9) && i <= S_SIZE) {
				if (readFixed)
					all[x][y] = 1 << (i - (S_SIZE == 9));
				else
					fixed[x][y] = 1 << (i - (S_SIZE == 9));
			} else {
				QMessageBox::critical(topLevelWidget(), "Error", "Invalid file context!");
				goto ret;
			}
		}
		if (++y == S_SIZE) {
			if (readFixed) {
				readAll = true;
				goto output;
			} else {
				readFixed = true;
				y = 0;
			}
		}
	}
output:
	clear();
	if (readAll)
		for (int x = 0; x < S_SIZE; x++)
			for (y = 0; y < S_SIZE; y++)
				if (all[x][y] == POSSIBLE_ALL)
					continue;
				else if (all[x][y] == fixed[x][y])
					box[x][y]->setFixed(all[x][y]);
				else
					box[x][y]->set(all[x][y]);
	else if (readFixed)
		for (int x = 0; x < S_SIZE; x++)
			for (y = 0; y < S_SIZE; y++)
				if (fixed[x][y] == POSSIBLE_ALL)
					continue;
				else
					box[x][y]->setFixed(fixed[x][y]);
ret:
	file.close();
}

void sBoard::save(void)
{
	QString path = QFileDialog::getSaveFileName(topLevelWidget(), "Open Sudoku file", QString(), "Text File (*.txt)");
	if (path.isEmpty())
		return;
	QFile file(path);
	if (!file.open(QFile::WriteOnly)) {
		QMessageBox::critical(topLevelWidget(), "Error", "Cannot open selected file!");
		return;
	}
	QTextStream text(&file);
	text << "// Original Sudoku\r\n";
	for (int y = 0; y < S_SIZE; y++) {
		for (int x = 0; x < S_SIZE; x++) {
			switch (box[x][y]->type) {
			case sBox::ConflictFixed:
			case sBox::Fixed:
				text << QString::number(box[x][y]->number() + (S_SIZE == 9), 16).toUpper();
				break;
			default:
				text << 'X';
			}
			switch (x % S_UNIT_SIZE) {
			case S_UNIT_SIZE - 1:
				text << (x == S_SIZE - 1 ? "\r\n" : "   ");
				break;
			default:
				text << ' ';
			}
		}
		if (y % S_UNIT_SIZE == S_UNIT_SIZE - 1 && y != S_SIZE - 1)
			text << "\r\n";
	}
	text << "\r\n// Current State\r\n";
	for (int y = 0; y < S_SIZE; y++) {
		for (int x = 0; x < S_SIZE; x++) {
			switch (box[x][y]->type) {
			case sBox::ConflictFixed:
			case sBox::Conflict:
			case sBox::Fixed:
			case sBox::Set:
				text << QString::number(box[x][y]->number() + (S_SIZE == 9), 16).toUpper();
				break;
			default:
				text << 'X';
			}
			switch (x % S_UNIT_SIZE) {
			case S_UNIT_SIZE - 1:
				text << (x == S_SIZE - 1 ? "\r\n" : "   ");
				break;
			default:
				text << ' ';
			}
		}
		if (y % S_UNIT_SIZE == S_UNIT_SIZE - 1 && y != S_SIZE - 1)
			text << "\r\n";
	}
	file.close();
}

void sBoard::clear(void)
{
	for (int x = 0; x < S_SIZE; x++)
		for (int y = 0; y < S_SIZE; y++)
			box[x][y]->setPossible(POSSIBLE_ALL);
}

void sBoard::refresh(void)
{
	int board[S_SIZE][S_SIZE];
	for (int x = 0; x < S_SIZE; x++)
		for (int y = 0; y < S_SIZE; y++)
			switch (box[x][y]->type) {
			case sBox::Conflict:
			case sBox::Empty:
				board[x][y] = 0xFF000000;			// Ignore
				break;
			case sBox::ConflictFixed:
			case sBox::Fixed:
				board[x][y] = box[x][y]->possible();			// Fixed
				break;
			case sBox::Set:
				board[x][y] = box[x][y]->possible() | 0x00FF0000;	// Set
			}
	clear();
	for (int x = 0; x < S_SIZE; x++)
		for (int y = 0; y < S_SIZE; y++)
			if (board[x][y] & 0xFF000000)				// Ignore
				continue;
			else if (board[x][y] & 0x00FF0000)			// Set
				box[x][y]->set(board[x][y] & 0x0000FFFF);
			else							// Fixed
				box[x][y]->setFixed(board[x][y]);
}

void sBoard::restart(void)
{
	for (int x = 0; x < S_SIZE; x++)
		for (int y = 0; y < S_SIZE; y++)
			switch (box[x][y]->type) {
			case sBox::Conflict:
			case sBox::Empty:
			case sBox::Set:
				box[x][y]->setPossible(POSSIBLE_ALL);
				break;
			case sBox::ConflictFixed:
				box[x][y]->type = sBox::Fixed;
				box[x][y]->updateDisplay();
			case sBox::Fixed:
				break;
			}
}

#define W		(e->size().width())
#define H		(e->size().height())
#define S		(W < H ? W : H)
#define S_OFF		((H - BOX_SIZE * S_SIZE - BOX_OFF * (S_UNIT_SIZE + 1)) / 2 + BOX_OFF)
#define BOX_OFF		2
#define BOX_SIZE	((S - BOX_OFF * (S_UNIT_SIZE + 1)) / S_SIZE)
void sBoard::resizeEvent(QResizeEvent *e)
{
	for (int x = 0; x < S_SIZE; x++)
		for (int y = 0; y < S_SIZE; y++)
			box[x][y]->setGeometry(S_OFF + x * BOX_SIZE + x / S_UNIT_SIZE * BOX_OFF, \
					       S_OFF + y * BOX_SIZE + y / S_UNIT_SIZE * BOX_OFF, BOX_SIZE, BOX_SIZE);
}
