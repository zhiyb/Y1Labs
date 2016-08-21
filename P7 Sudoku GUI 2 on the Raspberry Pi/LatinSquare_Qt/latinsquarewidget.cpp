#include "latinsquarewidget.h"
#include <QPainter>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QInputDialog>

#define H	height()
#define W	width()
#define MINSIZE	16
#define FRAME	3

LatinSquareWidget::LatinSquareWidget(int size, QWidget *parent) :
	QWidget(parent)
{
	n = size;
	h = new LatinSquare(n);
	selected[0] = -1;
	selected[1] = -1;
	QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	policy.setHeightForWidth(true);
	setSizePolicy(policy);
	setMinimumSize(n * MINSIZE + FRAME * 2, n * MINSIZE + FRAME * 2);
}

LatinSquareWidget::~LatinSquareWidget(void)
{
	delete h;
}

void LatinSquareWidget::paintEvent(QPaintEvent *)
{
	int size = H < W ? H : W;
	size -= (size - FRAME * 2 - (n - 1)) % n;
	int side = (size - FRAME * 2 - (n - 1)) / n - 1;
	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.setPen(Qt::black);
	painter.drawRect((W - size) / 2, (H - size) / 2, size - 1, size - 1);
	for (int r = 0; r < n; r++)
		for (int c = 0; c < n; c++) {
			int x = (W - size) / 2 + FRAME + (side + 2) * c;
			int y = (H - size) / 2 + FRAME + (side + 2) * r;
			if (r == selected[0] && c == selected[1]) {
				painter.setBrush(Qt::gray);
				painter.setPen(Qt::gray);
			} else {
				painter.setBrush(Qt::white);
				painter.setPen(Qt::white);
			}
			painter.drawRect(x, y, side, side);
		}
	QFont f(font());
	f.setPixelSize(0.9 * side);
	setFont(f);
	painter.setPen(Qt::blue);
	for (std::vector<int>::size_type i = 0; i < res.size(); i++) {
		int num = res.at(i) % n, r = res.at(i) / n / n, c = (res.at(i) / n) % n;
		int x = (W - size) / 2 + FRAME + (side + 2) * c;
		int y = (H - size) / 2 + FRAME + (side + 2) * r;
		painter.drawText(x, y, side, side, Qt::AlignCenter, QString::number(num + 1));
	}
	painter.setPen(Qt::black);
	for (std::vector<int>::size_type i = 0; i < pre.size(); i++) {
		int num = pre.at(i) % n, r = pre.at(i) / n / n, c = (pre.at(i) / n) % n;
		int x = (W - size) / 2 + FRAME + (side + 2) * c;
		int y = (H - size) / 2 + FRAME + (side + 2) * r;
		painter.drawText(x, y, side, side, Qt::AlignCenter, QString::number(num + 1));
	}
}

void LatinSquareWidget::mouseReleaseEvent(QMouseEvent *e)
{
	int size = H < W ? H : W;
	size -= (size - FRAME * 2 - (n - 1)) % n;
	int side = (size - FRAME * 2 - (n - 1)) / n - 1;
	int y = e->y() - (H - size) / 2 - FRAME, x = e->x() - (W - size) / 2 - FRAME;
	int r = y / (side + 2), c = x / (side + 2);
	if (r < 0 || c < 0 || r >= n || c >= n)
		return;
	for (std::vector<int>::iterator it = pre.begin(); it != pre.end(); it++) {
		int preR = *it / n / n, preC = (*it / n) % n;
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
	bool ok;
	int num = QInputDialog::getInt(this, "Select a value", "Select a value to insert into board", 1, 1, n, 1, &ok);
	if (ok) {
		pre.push_back(r * n * n + c * n + num - 1);
		res.clear();
		emit doClear();
	}
	selected[0] = -1;
	selected[1] = -1;
	repaint();
}

void LatinSquareWidget::clear(void)
{
	pre.clear();
	res.clear();
	emit doClear();
	repaint();
}

void LatinSquareWidget::load(void)
{
	//QString path = "C:\\Users\\zhiyb\\SkyDrive\\Documents\\Labs\\P7\\Example\\Example_36x36.txt";
	QString path = QFileDialog::getOpenFileName(topLevelWidget(), "Load LatinSquare data", QString(), "Text file (*.txt)");
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
		pre = h->fromString(line);
		break;
	}
	file.close();
	repaint();
}

void LatinSquareWidget::save(void)
{
	QString path = QFileDialog::getSaveFileName(topLevelWidget(), "Save LatinSquare data", QString(), "Text file (*.txt)");
	if (path.isEmpty())
		return;
	QFile file(path);
	if (!file.open(QFile::WriteOnly)) {
		QMessageBox::critical(topLevelWidget(), "Error", "Cannot write selected file!");
		return;
	}
	QTextStream text(&file);
	text << "# Original data\r\n";
	text << LatinSquare::toString(pre) << "\r\n";
	file.close();
}

void LatinSquareWidget::solve(void)
{
	//delete h;
	//h = new LatinSquare(n);
	h->solve(pre);
	QMessageBox::information(this, "Solved", QString("Got %1 solution(s)").arg(h->solutions().size()));
}

void LatinSquareWidget::loadSolution(int index)
{
	if (index < 0) {
		res.clear();
		repaint();
		return;
	}
	res = h->solutions().at(index);
	repaint();
}
