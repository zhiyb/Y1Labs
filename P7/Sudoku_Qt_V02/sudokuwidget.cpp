#include "sudokuwidget.h"
#include "sudokuselector.h"
#include <QPainter>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

#define H	height()
#define W	width()
#define MINSIZE	12
#define FRAME	3

SudokuWidget::SudokuWidget(int size, QWidget *parent) :
	QWidget(parent)
{
	n = size;
	s = new Sudoku(n);
	selected[0] = -1;
	selected[1] = -1;
	QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	policy.setHeightForWidth(true);
	setSizePolicy(policy);
	setMinimumSize(NN * MINSIZE + FRAME * (n + 1) + (n - 1) * n, NN * MINSIZE + FRAME * (n + 1) + (n - 1) * n);
}

SudokuWidget::~SudokuWidget(void)
{
	delete s;
}

void SudokuWidget::paintEvent(QPaintEvent *)
{
	int size = H < W ? H : W;
	size -= (size - FRAME * (n + 1) - (n - 1) * n) % NN;
	int side = (size - FRAME * (n + 1) - (n - 1) * n) / NN;
	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.setPen(Qt::black);
	painter.drawRect((W - size) / 2, (H - size) / 2, size - 1, size - 1);
	for (int r = 0; r < NN; r++)
		for (int c = 0; c < NN; c++) {
			int x = (W - size) / 2 - n + 1 + (FRAME + n - 1) * (c / n + 1) + c % n + side * c;
			int y = (H - size) / 2 - n + 1 + (FRAME + n - 1) * (r / n + 1) + r % n + side * r;
			if (r == selected[0] && c == selected[1]) {
				painter.setBrush(Qt::gray);
				painter.setPen(Qt::gray);
			} else {
				painter.setBrush(Qt::white);
				painter.setPen(Qt::white);
			}
			painter.drawRect(x, y, side - 1, side - 1);
		}
	QFont f(font());
	f.setPixelSize(0.8 * side);
	setFont(f);
	painter.setPen(Qt::blue);
	for (std::vector<int>::size_type i = 0; i < res.size(); i++) {
		int num = res.at(i) % NN, r = res.at(i) / NN / NN, c = (res.at(i) / NN) % NN;
		int x = (W - size) / 2 - n + 1 + (FRAME + n - 1) * (c / n + 1) + c % n + side * c;
		int y = (H - size) / 2 - n + 1 + (FRAME + n - 1) * (r / n + 1) + r % n + side * r;
		painter.drawText(x, y, side, side, Qt::AlignCenter, QString::number(num + 1));
	}
	painter.setPen(Qt::black);
	for (std::vector<int>::size_type i = 0; i < pre.size(); i++) {
		int num = pre.at(i) % NN, r = pre.at(i) / NN / NN, c = (pre.at(i) / NN) % NN;
		int x = (W - size) / 2 - n + 1 + (FRAME + n - 1) * (c / n + 1) + c % n + side * c;
		int y = (H - size) / 2 - n + 1 + (FRAME + n - 1) * (r / n + 1) + r % n + side * r;
		painter.drawText(x, y, side, side, Qt::AlignCenter, QString::number(num + 1));
	}
}

void SudokuWidget::mouseReleaseEvent(QMouseEvent *e)
{
	int size = H < W ? H : W;
	size -= (size - FRAME * (n + 1) - (n - 1) * n) % NN;
	int y = e->y() - (H - size) / 2 - FRAME, x = e->x() - (W - size) / 2 - FRAME;
	int side = (size - FRAME * (n + 1) - (n - 1) * n) / NN;
	int r = y / (side * n + n - 1 + FRAME) * n, c = x / (side * n + n - 1 + FRAME) * n;
	r += (y % (side * n + n - 1 + FRAME)) / (side + 1);
	c += (x % (side * n + n - 1 + FRAME)) / (side + 1);
	if (r < 0 || c < 0 || r >= NN || c >= NN)
		return;
	for (std::vector<int>::iterator it = pre.begin(); it != pre.end(); it++) {
		int preR = *it / NN / NN, preC = (*it / NN) % NN;
		if (preR == r && preC == c) {
			pre.erase(it);
			res.clear();
			emit doClear();
			repaint();
			return;
		}
	}
	selected[0] = r;
	selected[1] = c;
	repaint();
	sudokuSelector sel(n, this);
	sel.exec();
	if (sel.value() != -1) {
		pre.push_back(r * NN * NN + c * NN + sel.value() - 1);
		res.clear();
		emit doClear();
	}
	selected[0] = -1;
	selected[1] = -1;
	repaint();
}

void SudokuWidget::clear(void)
{
	pre.clear();
	res.clear();
	emit doClear();
	repaint();
}

void SudokuWidget::load(void)
{
	//QString path = "C:\\Users\\zhiyb\\SkyDrive\\Documents\\Labs\\P7\\Example\\Example_36x36.txt";
	QString path = QFileDialog::getOpenFileName(topLevelWidget(), "Load Sudoku data", QString(), "Text file (*.txt)");
	if (path.isEmpty())
		return;
	QFile file(path);
	if (!file.open(QFile::ReadOnly)) {
		QMessageBox::critical(topLevelWidget(), "Error", "Cannot read selected file!");
		return;
	}
	QTextStream text(&file);
	while (!text.atEnd()) {
		QString line = text.readLine();
		if (line.isEmpty() || line.startsWith("#"))
			continue;
		pre.clear();
		res.clear();
		emit doClear();
		pre = s->fromString(line);
		break;
	}
	file.close();
	repaint();
}

void SudokuWidget::save(void)
{
	QString path = QFileDialog::getSaveFileName(topLevelWidget(), "Save Sudoku data", QString(), "Text file (*.txt)");
	if (path.isEmpty())
		return;
	QFile file(path);
	if (!file.open(QFile::WriteOnly)) {
		QMessageBox::critical(topLevelWidget(), "Error", "Cannot write selected file!");
		return;
	}
	QTextStream text(&file);
	text << "# Original data\r\n";
	text << Sudoku::toString(pre) << "\r\n";
	file.close();
}

void SudokuWidget::solve(void)
{
	s->solve(pre);
	QMessageBox::information(this, "Solved", QString("Got %1 solution(s)").arg(s->solutions().size()));
}

void SudokuWidget::loadSolution(int index)
{
	if (index < 0) {
		res.clear();
		repaint();
		return;
	}
	res = s->solutions().at(index);
	repaint();
}
