#ifndef DEFINE_H
#define DEFINE_H

#include <inttypes.h>
#include <QtCore>

#define S_UNIT_SIZE	4
#define S_SIZE		(S_UNIT_SIZE * S_UNIT_SIZE)

#define POSSIBLE_ALL	(~(0xFFFFFFFF << S_SIZE))

#define SPACE_BOX	1
#define SPACE_SQARE	4
#define BOX_SIZE	32
#define COLOUR_LINE	Qt::black
#define COLOUR_BOX_BGC	Qt::white
#define COLOUR_BOX_SEL	Qt::gray
#define COLOUR_FIXED	Qt::black
#define COLOUR_SET	Qt::blue

#endif // DEFINE_H
