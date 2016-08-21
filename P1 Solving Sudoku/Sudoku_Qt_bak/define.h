#ifndef DEFINE_H
#define DEFINE_H

#define S_UNIT_SIZE	4
#define S_SIZE		(S_UNIT_SIZE * S_UNIT_SIZE)
#define POSSIBLE_ALL	(0xFFFF >> (16 - S_SIZE))

#define COLOUR_POSSIBLE		Qt::blue
#define COLOUR_FIXED		Qt::black
#define COLOUR_SET		Qt::darkGreen
#define COLOUR_ERROR		Qt::red
#define COLOUR_CONFLICT		Qt::red
#define COLOUR_CONFLICTFIXED	Qt::darkRed
#define COLOUR_BOXBGC		Qt::white
#define COLOUR_CLICKED		Qt::gray

#endif // DEFINE_H
