#ifndef _PROG_H
#define _PROG_H

#include <qobject.h>

class Program: public QObject
{
	Q_OBJECT

public:
	Program(const QString des, const QString dir, QWidget *parent = 0, const char *name = 0);
	int fuse(int i) const {return _fuse[i];}
	void setFuse(int *fuse);
	void make(void);
	void flash(void);
	void readFuse(void);
	void writeFuse(void);
	void readEEPROM(void);
	void writeEEPROM(void);
	static int run(QString cmd);

private:
	void warning(void);
	void varRead(QString& var, QString& line, QString name);
	void varRead(int& var, QString& line, QString name);
	void debug(void);
	
	QString _des, _dir, _prog, _mcu;
	int _fuse[3];
};

#endif
