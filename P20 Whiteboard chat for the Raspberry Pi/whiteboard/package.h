#ifndef PACKAGE_H
#define PACKAGE_H

#include <QByteArray>

#define PKG_SIZE	64

struct package_t {
	enum Commands {Clear = 0, Resize, Line};
	quint8 cmd;
	QByteArray data;
};

#endif // PACKAGE_H

