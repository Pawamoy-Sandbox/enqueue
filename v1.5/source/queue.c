#include "queue.h"

/// Queue basic operations ------------------------------------
// return the size
inline int getQSize(Queue q){return q->size;}
// return value of head in structure
inline int getQHead(Queue q){return q->head;}
// return value of tail in structure
inline int getQTail(Queue q){return q->tail;}
// return adress of SQueue array in structure
inline SQueue* getQQueue(Queue q){return q->queue;}
// set head value in structure
inline void setQHead(Queue q, int h){q->head=h;}
// set tail value in structure
inline void setQTail(Queue q, int t){q->tail=t;}
// set size value in structure
inline void setQSize(Queue q, int s){q->size=s;}
// set queue value in structure
inline void setQQueue(Queue q, SQueue* sq){q->queue = sq;}

/// building, display -----------------------------------------
// create a new queue of size s
Queue newQueue(int s){
	Queue q = (Queue)malloc(sizeof(StrQueue));
	setQQueue(q, (SQueue*)malloc(s*sizeof(SQueue)));
	memset(getQQueue(q), 0, s*sizeof(SQueue));
	if (getQQueue(q)!=NULL) {
		setQHead(q,0);
		setQTail(q,0);
		setQSize(q,s);
	}
	else perror(" allocation in newQueue\n");
	return q;
}
// set a new size for the queue (recopy the values)
// s > 0
Queue setSize(Queue q, int s){
	Queue nq = newQueue(s);
	setQHead(nq, getQHead(q));
	setQTail(nq, getQTail(q));
	setQSize(nq, s);
	copyValues(q, nq);
	deleteQueue(q);
	free(q);
	return nq;
}
// write values of q in cq (at same positions in the queue)
void copyValues(Queue q, Queue cq){
	int i, j=getLength(q), k=getQSize(cq), l=getLength(cq);
	for (i=0; i<j && i<k; i++) {
		setElem(cq, getElem(q, i), i);
	}
	if (i-l > 0) setQTail(cq, getQTail(cq)+(i-l));
}
// return an exact copy of q
//~ Queue clone(Queue q){
	//~ Queue cq = newQueue(getQSize(q));
	//~ setQHead(cq, getQHead(q));
	//~ setQTail(cq, getQTail(q));
	//~ setQSize(cq, getQSize(q));
	//~ copyValues(q, cq);
	//~ return cq;
//~ }
// fill the queue with x
// q->queue already allocated
//~ void init(Queue q, SQueue x){
	//~ int i;
	//~ setQHead(q,0);
	//~ setQTail(q,0);
	//~ for (i=0; i<getQSize(q); i++) {
		//~ addTail(q, x);
	//~ }
//~ }
// empty the queue
void setEmpty(Queue q){
	setQHead(q,0);
	setQTail(q,0);
}
// free the allocated memory for the elements of the queue
void deleteQueue(Queue q){
	if (getQQueue(q)!=NULL) {
		while (!empty(q)) subHead(q);
		free(getQQueue(q));
	}
	free(q);
	return ;
} 
// print an entire queue in stdout
void printQueue(Queue q){
	int i, j=getLength(q);
	for (i=0; i<j; i++) {
		printSQueue(getElem(q, i));
	}
	printf("\n");
	return ;
}

/// reading ---------------------------------------------------
// return the head
// !empty(q)
inline SQueue getHead(Queue q){return getQQueue(q)[getQHead(q)%getQSize(q)];}
// return the tail
// !empty(q)
inline SQueue getTail(Queue q){return getQQueue(q)[(getQTail(q)-1)%getQSize(q)];}
// return the element k
// !empty(q)
inline SQueue getElem(Queue q, int k){return getQQueue(q)[(getQHead(q)+k)%getQSize(q)];}
// return the length
inline int getLength(Queue q){return getQTail(q)-getQHead(q);}

/// writing ---------------------------------------------------
// set the head at x
// !empty(q)
void setHead(Queue q, SQueue x){
	getQQueue(q)[getQHead(q)%getQSize(q)] = x;
}
// set the tail at x
// !empty(q)
void setTail(Queue q, SQueue x){
	getQQueue(q)[(getQTail(q)-1)%getQSize(q)] = x;
}
// set the element k at x
// !empty(q)
void setElem(Queue q, SQueue x, int k){
	getQQueue(q)[(getQHead(q)+k)%getQSize(q)] = x;
}
// add x in head
// !filled(q)
void addHead(Queue q, SQueue x){
	setQHead(q, getQHead(q)-1);
	if (getQHead(q)<0) {
		setQHead(q, getQSize(q)+getQHead(q));
		setQTail(q, getQTail(q)+getQSize(q));
	}
	getQQueue(q)[getQHead(q)%getQSize(q)] = x;
}
// add x in tail
// !filled(q)
void addTail(Queue q, SQueue x){
	getQQueue(q)[getQTail(q)%getQSize(q)] = x;
	setQTail(q, getQTail(q)+1);
}
// add x at position k
// 0 <= k (< getQSize(q))
// !filled(q)
void addElem(Queue q, SQueue x, int k){
	int i;
	if (k >= getLength(q)) addTail(q, x);
	else if (k==0) addHead(q, x);
	else {
		if (k >= getLength(q)/2) {
			for (i=getLength(q)-1; i>=k; i--) {
				setElem(q, getElem(q, i), i+1);
			}
			setElem(q, x, i+1);
			setQTail(q, getQTail(q)+1);
		}
		else {
			for (i=0; i<k; i++) {
				setElem(q, getElem(q, i), i-1);
			}
			setElem(q, x, i-1);
			setQHead(q, getQHead(q)-1);
			if (getQHead(q)<0) {
				setQHead(q, getQSize(q)+getQHead(q));
				setQTail(q, getQTail(q)+getQSize(q));
			}
		}
	}
}
// delete the head
// !empty(q)
void subHead(Queue q){
	deleteSQueue(getHead(q));
	setQHead(q, getQHead(q)+1);
}
// delete the tail
// !empty(q)
void subTail(Queue q){
	deleteSQueue(getTail(q));
	setQTail(q, getQTail(q)-1);
}
// delete the element at position k
// 0 <= k < q.tail
// !empty(q)
void subElem(Queue q, int k){
	int i,j;
	if (k > getLength(q)-1) ;
	else if (k == getLength(q)-1) subTail(q);
	else if (k==0) subHead(q);
	else {
		deleteSQueue(getElem(q, k));
		j = getLength(q)-1;
		if (k >= getLength(q)/2) {
			for (i=k; i<j; i++) {
				setElem(q, getElem(q, i+1), i);
			}
			setQTail(q, getQTail(q)-1);
		}
		else {
			for (i=k; i>0; i--) {
				setElem(q, getElem(q, i-1), i);
			}
			setQHead(q, getQHead(q)+1);
		}
	}
}

/// searching -------------------------------------------------
// return position of first element x in queue, -1 if x doesn't exist
//~ int find(Queue q, SQueue x){
	//~ int i, j = getLength(q);
	//~ for (i=0; i<j; i++) {
		//~ if  (eqSQueue(x, getElem(q, i))) {
			//~ return i;
		//~ }
	//~ }
	//~ return -1;
//~ }

/// boolean tests ---------------------------------------------
// queue is empty ?
inline Bool empty(Queue q){return (getLength(q)<1);}
// queue is filled ?
inline Bool filled(Queue q){return (getLength(q)==getQSize(q));}
// queue a equal queue b ?
//~ Bool equal(Queue qa, Queue qb){
	//~ int i, j;
	//~ if (getLength(qa)!=getLength(qb)) return false;
	//~ j = getLength(qa);
	//~ for (i=0; i<j; i++) {
		//~ if (!eqSQueue(getElem(qa, i), getElem(qb, i))) return false;
	//~ }
	//~ return true;
//~ }
