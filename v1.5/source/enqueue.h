#ifndef __ENQUEUE_H
#define __ENQUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <errno.h>

#include "queue.h"

#define MAXTASK 1024
#define MAXBUFFER 1024

typedef enum {
	FNCT_LIST,
	FNCT_DELETE,
	FNCT_START,
	FNCT_STOP,
	FNCT_FREE,
	FNCT_CLEAN,
	FNCT_EDIT,
	FNCT_HELP,
	FNCT_ADD,
	FNCT_TASK,
	FNCT_INSTANCE,
	FNCT_TASKLIST,
	FNCT_RUNNING,
	FNCT_CONFIG
} Function;

typedef enum {
	SYNC_R,
	SYNC_W_OVER,
	SYNC_W,
	SYNC_END
} Sync;

typedef Queue Task;

typedef struct str_task_info {
	char name[64];		/**< Identifiant de la tâche */
	Bool inUse;			/**< Tâche en cours d'utilisation */
	pid_t pid;			/**< Pid du pogramme */
	Function function;	/**< Fonction choisie par l'utilisateur */
	
	//~ Bool exec;		/**< Tâche en cours d'exécution */
	//~ Demand demand;	/**< Demandes reçues pas d'autres instances */
} TaskInfo;

typedef struct str_shared {
	int instance;			/**< Nombre d'instances du programme en cours */
	int loaded;				/**< Nombre de tâches chargées en mémoire */
	Sync sync;				/**< Synchronisation pour la communication entre instances */
	char buffer[MAXBUFFER];	/**< Buffer pour la communication entre instances */
	TaskInfo task[MAXTASK];	/**< Informations sur les tâches chargées en mémoire */
} StrShared, *Shared;

void handler(int signum, siginfo_t *info, void *context);
void GetEnv(char* var, char* result);
void CleanLineFeed(char* buffer);
void GetConfig();
void InitShared();
void InitTaskInfo(int indice, char* name, Bool used, pid_t pid, Function fnc);
Function GetFunction(char* arg);
int NotUsed();
int GetTaskWithName();
int GetTaskWithPid(pid_t pid);
void SendCommand(CMD sq, pid_t pid);
void ReceiveCommand(CMD* sq);
Task LoadTask();
void Begin();
void Exit();
Bool InUse(int id);
void SetInUse(int id);
void SetNoUse(int id);
void Execute(char** argv, char* path);
void DeleteFile(char* task);
void UpdateFile();

void Running();
void Help();
void Instances();
void ListAllTasks();
void Free();
void Config();
void StartTask();
void ListTask();
void DeleteLastCommand();
void StopTask();
void CleanTask();
void EditTask();
void AddToTask();

#endif // __ENQUEUE_H
