#include "squeue.h"

/// SQueue operations (comparisons, display)
// a less than b
//~ inline Bool ltSQueue(SQueue a, SQueue b){return (a<b);}
// a less or equal b
//~ inline Bool leSQueue(SQueue a, SQueue b){return (a<=b);}
// a equal b
//~ inline Bool eqSQueue(SQueue a, SQueue b){return (a==b);}
// a greater or equal b
//~ inline Bool geSQueue(SQueue a, SQueue b){return (a>=b);}
// a greater than b
//~ inline Bool gtSQueue(SQueue a, SQueue b){return (a>b);}
// print SQueue variable on stdout
void printSQueue(SQueue a){printf("\t%s in %s\n",a.cmd,a.wd);}
