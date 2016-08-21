#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QThread>
#include "package.h"

class ConnectionRxPool : public QObject
{
	Q_OBJECT
public:
	ConnectionRxPool(QObject *parent = 0);

public slots:
	void pool(void);
	void quit(void) {exit = true;}

signals:
	void received(package_t *pkg);

private:
	void receive(void);
	quint8 readByte(void);

	bool exit;
};

class Connection : public QObject
{
	Q_OBJECT
public:
	explicit Connection(QObject *parent = 0);
	~Connection();

	ConnectionRxPool rxPool;

signals:
	void received(package_t *pkg);

public slots:
	void loop(void);
	void quit(void) {exit = true;}
	void sendPackage(package_t *pkg);

private:
	void loopback(void);
	void sendPkg(package_t pkg);
	void writeByte(quint8 data);

	bool exit;
	QQueue<package_t> send;
	QMutex sendLocker;
	QThread rxThread;
};

#endif // CONNECTION_H
