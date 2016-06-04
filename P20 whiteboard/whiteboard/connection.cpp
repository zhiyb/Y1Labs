#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include <QDebug>
#include "connection.h"

// Hardware connection simulation
volatile struct hw_t {
	bool cmd;	// Command byte & transmit start signal
	bool data;	// Serial data
	bool txSync;	// Data ready sync
	bool rxSync;	// Data received sync
} hwTx, &hwRx = hwTx;	// Transmit & receive using the same data (loopback)

ConnectionRxPool::ConnectionRxPool(QObject *parent) : QObject(parent), exit(false)
{
	hwRx.rxSync = false;
}

void ConnectionRxPool::pool()
{
	while (!exit) {
		if (hwRx.cmd)
			receive();
		QThread::currentThread()->usleep(10);
	}
}

void ConnectionRxPool::receive()
{
	package_t *pkg = new package_t;
	pkg->cmd = readByte();
	int bytes = readByte();
	while (bytes--)
		pkg->data.append(readByte());
	emit received(pkg);
}

quint8 ConnectionRxPool::readByte()
{
	quint8 data = 0;
	for (int i = 0; i < 8; i++) {
		while (!hwRx.txSync)
			;//QThread::currentThread()->usleep(1);
		data <<= 1;
		data |= hwRx.data;
		hwRx.rxSync = true;
		while (hwRx.txSync)
			;//QThread::currentThread()->usleep(1);
		hwRx.rxSync = false;
	}
	return data;
}

Connection::Connection(QObject *parent) : QObject(parent), exit(false)
{
	hwTx.cmd = false;
	hwTx.data = false;
	hwTx.txSync = false;
	rxPool.moveToThread(&rxThread);
	connect(&rxPool, SIGNAL(received(package_t*)), this, SIGNAL(received(package_t*)));
	connect(&rxThread, SIGNAL(started()), &rxPool, SLOT(pool()));
	connect(&rxThread, SIGNAL(finished()), &rxPool, SLOT(quit()));
}

Connection::~Connection()
{
	rxPool.quit();
	rxThread.quit();
	rxThread.wait();
}

void Connection::loop()
{
	rxThread.start();
	while (!exit) {
		//loopback();
		while (send.count()) {
			sendLocker.lock();
			if (!send.count()) {
				sendLocker.unlock();
				break;
			}
			sendPkg(send.dequeue());
			sendLocker.unlock();
		}
		QThread::currentThread()->usleep(10);
	}
}

void Connection::sendPackage(package_t *pkg)
{
	sendLocker.lock();
	send.enqueue(*pkg);
	sendLocker.unlock();
}

void Connection::loopback()
{
	while (send.count()) {
		sendLocker.lock();
		emit received(new package_t(send.dequeue()));
		sendLocker.unlock();
	}
}

void Connection::sendPkg(package_t pkg)
{
	hwTx.cmd = true;
	writeByte(pkg.cmd);
	hwTx.cmd = false;
	writeByte(pkg.data.size());
	for (int i = 0; i < pkg.data.size(); i++)
		writeByte(pkg.data.at(i));
}

void Connection::writeByte(quint8 data)
{
	for (int i = 0; i < 8; i++) {
		while (hwTx.rxSync)
			;//QThread::currentThread()->usleep(1);
		hwTx.data = data & 0x80;
		data <<= 1;
		hwTx.txSync = true;
		while (!hwTx.rxSync)
			;//QThread::currentThread()->usleep(1);
		hwTx.txSync = false;
	}
}
