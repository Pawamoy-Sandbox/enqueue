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
void printSQueue(SQueue a) {
	int i=0;
	printf("\t");
	while (a.cmd[i]!=NULL) {
		printf("%s ",a.cmd[i]);
		i++;
	}
	printf("in %s\n", a.wd);
}

/// SQueue construction functions
void newSQueue(SQueue* sq, int argc, char* argv[], char* path) {
	sq->wd = (char*)malloc((strlen(path)+1)*sizeof(char));
	sq->cmd = (char**)malloc(argc*sizeof(char*));
	
	int i;
	if (sq->wd!=NULL) sprintf(sq->wd, "%s", path);
	if (sq->cmd!=NULL) {
		for (i=0; i<argc-1; i++) {
			sq->cmd[i] = (char*)malloc((strlen(argv[i])+1)*sizeof(char));
			if (sq->cmd[i]!=NULL) sprintf(sq->cmd[i], "%s", argv[i]);
		}
		sq->cmd[argc-1]=NULL;
	}
}
	
void deleteSQueue(SQueue sq) {
	int i=0;
	if (sq.wd!=NULL) free(sq.wd);
	if (sq.cmd!=NULL) {
		while (sq.cmd[i]!=NULL) {
			free(sq.cmd[i]);
			i++;
		}
		free(sq.cmd);
	}
}
