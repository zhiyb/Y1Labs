#include <qmessagebox.h>
#include <qfile.h>
#include <qtextstream.h>
#include <stdlib.h>
#include "prog.h"

#define PATH "/mnt/NFS/root/AVR/Labs/X2"
#define PROG "c232hm"
#define MCU "ATMEGA644P"
#define CONSOLE "embeddedkonsole "

#define HEX(n) QString::number(n, 16)

const int fuseDefault[3] = {0xFF, 0x9C, 0xE7};

Program::Program(const QString des, const QString dir, QWidget *parent, const char *name): QObject(parent, name)
{
	_des = des;
	_dir = dir;
	_prog = QString::null;
	_mcu = QString::null;
	for (int i = 0; i < 3; i++)
		_fuse[i] = -1;

	//Read Makefile
	QFile f(PATH "/" + _dir + "/Makefile");
	if (!f.open(IO_ReadOnly))
		goto _default;
	else {
		QTextStream t(&f);
		QString line;
		while (!t.eof()) {
			line = t.readLine();
			if (_prog.isEmpty())
				varRead(_prog, line, "PROG");
			if (_mcu.isEmpty())
				varRead(_mcu, line, "MCU");
			if (_fuse[0] < 0)
				varRead(_fuse[0], line, "EFUSE");
			if (_fuse[1] < 0)
				varRead(_fuse[1], line, "HFUSE");
			if (_fuse[2] < 0)
				varRead(_fuse[2], line, "LFUSE");
		}
		f.close();
	}

	// Validation check
	if (_prog.isEmpty() || _mcu.isEmpty())
		goto _default;
	for (int i = 0; i < 3; i++)
		if (_fuse[i] < 0)
			goto _default;
	return;

_default:
	// Not valid, use default values
	warning();
	_prog = PROG;
	_mcu = MCU;
	for (int i = 0; i < 3; i++)
		_fuse[i] = fuseDefault[i];
}

void Program::setFuse(int *fuse)
{
	for (int i = 0; i < 3; i++)
		_fuse[i] = *(fuse + i);
}

void Program::make(void)
{
	run(CONSOLE "\"cd " PATH "/" + _dir + " && make\"");
}

void Program::flash(void)
{
	run(CONSOLE "\"cd " PATH "/" + _dir + " && make flash\"");
}

void Program::readFuse(void)
{
	run("mkdir -p /tmp/fuse");
	if (run("avrdude -c " + _prog + " -p " + _mcu + \
			" -U efuse:r:/tmp/fuse/e.txt:h" \
			" -U hfuse:r:/tmp/fuse/h.txt:h" \
			" -U lfuse:r:/tmp/fuse/l.txt:h"
			" > /tmp/fuse/output 2>&1") != 0) {
		run("cat /tmp/fuse/output");
		QMessageBox::critical(0, "Error", "Read fuse bytes failed!");
		run("ebook /tmp/fuse/output");
	}
	run("rm -f /tmp/fuse/e.txt /tmp/fuse/h.txt /tmp/fuse/l.txt " \
			"/tmp/fuse/output");
	run("rmdir /tmp/fuse");
}

void Program::writeFuse(void)
{
	run(CONSOLE "\"avrdude -c " + _prog + " -p " + _mcu + \
			" -U efuse:w:0x" + HEX(_fuse[0]) + ":m" \
			" -U hfuse:w:0x" + HEX(_fuse[1]) + ":m" \
			" -U lfuse:w:0x" + HEX(_fuse[2]) + ":m\"");
}

void Program::readEEPROM(void)
{
	run(CONSOLE "\"cd " PATH "/" + _dir + " && make readeeprom\"");
}

void Program::writeEEPROM(void)
{
	run(CONSOLE "\"cd " PATH "/" + _dir + " && make eeprom\"");
}

int Program::run(QString cmd)
{
	qDebug(cmd);
	return system(cmd);
}

void Program::debug(void)
{
	qDebug("Debug output: \"" + \
		_des + "\"\n" + \
		"Path: " PATH "\n" \
		"Directory: " + _dir + "\n" \
		"Programmer: " PROG "\n" \
		"MCU: " MCU "\n" \
		"0x" + QString::number(_fuse[0], 16) + " / " \
		"0x" + QString::number(_fuse[1], 16) + " / " \
		"0x" + QString::number(_fuse[2], 16));
}

void Program::varRead(QString& var, QString& line, const QString name)
{
	if (line.startsWith(name + " ") || \
			line.startsWith(name + ":") || \
			line.startsWith(name + "="))
		var = line.replace(QRegExp(" *" + name + " *:*= *"), "");
	else
		var = QString::null;
}

void Program::varRead(int& var, QString& line, const QString name)
{
	QString sVar;
	varRead(sVar, line, name);
	if (sVar.isEmpty())
		var = -1;
	else
		var = sVar.replace(QRegExp("0x"), "").toInt(0, 16);
}

void Program::warning(void)
{
	QMessageBox::warning(0, "Warning", \
			QString("Failed to read \"") + \
			_des + "\"\n" + \
			"Path: " PATH "\n" \
			"Directory: " + _dir + "\n\n" \
			"Will use default configurations:\n" \
			"Programmer: " PROG "\n" \
			"MCU: " MCU "\n" \
			"0x" + QString::number(fuseDefault[0], 16) + " / " \
			"0x" + QString::number(fuseDefault[1], 16) + " / " \
			"0x" + QString::number(fuseDefault[2], 16));
}
