#ifndef __ENQUEUE_H
#define __ENQUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <errno.h>

#include "queue.h"

#define MAXTASK 16

#define _L 0
#define _D 1
#define _S 2
#define _X 3
#define _C 4
#define _M 5
#define _H 6
#define _A 7
#define _T 8
#define _E 9
#define _I 10
#define _LT 11
#define _R 12
#define _CF 13
#define _LD 14
#define _RL 15

typedef struct str_task {
	int inuse;
	int exec;
	int demand;
	char id[64];
	StrQueue q;
} Task;

typedef struct str_shared {
	int instance;
	int running;
	int loaded;
	Task task[MAXTASK];
} StrShared, *Shared;

Task* AddTask(char* task);
Task* GetTask(char* task);
void GetEnv(char* var, char* result);
void GetConfig();
void InitShared();
void Begin(int argc, char* argv[]);
int CheckArgument(char* arg);
void Parse(char* line, char* argv[]);
void Execute(char **argv, char* path);
void CleanLineFeed(char* buffer);
void ReloadTask(char* name);
Task* LoadTask(char* name);
void LoadTasks();
void SaveTasks();
void ListTask(Task* p);
void StartTask(Task* p);
void DeleteLastCommand(Task* p);
void StopTask(Task* p);
void CleanTask(Task* p);
void OpenFile(char* editor, char* path, char* name);
void ModifyTask(Task* p);
void History(Task* p);
void AddToTask(Task* p);
void Instances(Task* p);
void Running(Task* p);
void OpenConfig(Task* p);
void ListAllTasks(Task* p);
void ListLoadedTasks(Task* p);
void Help(Task* p);

#endif // __ENQUEUE_H
