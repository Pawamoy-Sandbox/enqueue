#ifndef __SQUEUE_H
#define __SQUEUE_H

#include "base.h"

/// SQueue type
typedef struct str_command {
	char wd[1024];
	char cmd[1024];
} CMD;

typedef CMD SQueue;

/// SQueue operations (comparisons, display)
//~ inline Bool ltSQueue(SQueue a, SQueue b);
//~ inline Bool leSQueue(SQueue a, SQueue b);
//~ inline Bool eqSQueue(SQueue a, SQueue b);
//~ inline Bool geSQueue(SQueue a, SQueue b);
//~ inline Bool gtSQueue(SQueue a, SQueue b);
void printSQueue(SQueue a);

#endif // __S_QUEUE_H
