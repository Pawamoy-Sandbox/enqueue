#ifndef __SQUEUE_H
#define __SQUEUE_H

#include <string.h>
#include "base.h"

/// SQueue type
typedef struct str_command {
	char* wd;
	char** cmd;
} CMD;

typedef CMD SQueue;

/// SQueue operations (comparisons, display)
//~ inline Bool ltSQueue(SQueue a, SQueue b);
//~ inline Bool leSQueue(SQueue a, SQueue b);
//~ inline Bool eqSQueue(SQueue a, SQueue b);
//~ inline Bool geSQueue(SQueue a, SQueue b);
//~ inline Bool gtSQueue(SQueue a, SQueue b);
void printSQueue(SQueue a);

/// SQueue construction functions
void newSQueue(SQueue* sq, int argc, char* argv[], char* path);

/// SQueue suppression
void deleteSQueue(SQueue sq);

#endif // __S_QUEUE_H
