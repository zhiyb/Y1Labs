#ifndef DEFINE_H
#define DEFINE_H

#include <inttypes.h>

#define S_UNIT_SIZE	4
#define S_SIZE		(S_UNIT_SIZE * S_UNIT_SIZE)

#define POSSIBLE_ALL	(~(0xFFFFFFFF << S_SIZE))

#endif // DEFINE_H
