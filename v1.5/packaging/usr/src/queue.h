#ifndef __QUEUE_H
#define __QUEUE_H

#include "squeue.h"

#define MAXQUEUE 128

/// Queue structure
typedef struct str_queue {
	SQueue queue[MAXQUEUE];
	int head;
	int tail;
	//~ int size;
} StrQueue, *Queue;

/// Queue basic operations
inline int getQSize();
inline int getQHead(Queue q);
inline int getQTail(Queue q);
inline SQueue* getQQueue(Queue q);
inline void setQHead(Queue q, int h);
inline void setQTail(Queue q, int t);
//~ inline void setQSize(Queue q, int s);
//~ inline void setQQueue(Queue q, SQueue* sq);

/// building, display
//~ Queue newQueue(int s);
//~ Queue setSize(Queue q, int s);
void copyValues(Queue q, Queue cq);
//~ Queue clone(Queue q);
void init(Queue q, SQueue x);
void setEmpty(Queue q);
void deleteQueue(Queue q);
void printQueue(Queue q);

/// reading
inline SQueue getHead(Queue q);
inline SQueue getTail(Queue q);
inline SQueue getElem(Queue q, int k);
inline int getLength(Queue q);

/// writing
void setHead(Queue q, SQueue x);
void setTail(Queue q, SQueue x);
void setElem(Queue q, SQueue x, int k);
void addHead(Queue q, SQueue x);
void addTail(Queue q, SQueue x);
void addElem(Queue q, SQueue x, int k);
void subHead(Queue q);
void subTail(Queue q);
void subElem(Queue q, int k);

/// searching
//~ int find(Queue q, SQueue x);

/// boolean tests
inline Bool empty(Queue q);
inline Bool filled(Queue q);
//~ Bool equal(Queue qa, Queue qb);

#endif // __QUEUE_H
