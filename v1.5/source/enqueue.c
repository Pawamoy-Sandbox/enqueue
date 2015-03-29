#include "enqueue.h"

/**********************************************************************/
/************************************************ VARIABLES GLOBALES **/
static char PATH_TO_CONFIG[256];
static char PATH_TO_TASKS[256];
static char DEFAULT_TASK[64];
static char CURRENT_TASK_NAME[64];
static int CURRENT_TASK_ID;
static int MAX_RUNNING=8;
static int INIT_QUEUE_SIZE=64;

static int ARGC;
static char** ARGV;

Shared sha = NULL;
int ssid;
Task cur_task = NULL;
CMD addedCommand;
Bool WaitSigcont = true;
int indice;

/**********************************************************************/
/******************************************** FONCTIONS DU PROGRAMME **/
void handler(int signum, siginfo_t *info, void *context) { /////////////
	int num_cmd=0;
	CMD command;
	switch (signum)
	{
		case SIGUSR1 : // programme distant
		{
			if (info->si_code==SI_USER) {
				switch (sha->task[GetTaskWithPid(info->si_pid)].function) {
					case FNCT_LIST :
						if (getLength(cur_task)>0) kill(info->si_pid, SIGUSR2);
						while (num_cmd<getLength(cur_task)) {
							SendCommand(getElem(cur_task, num_cmd), info->si_pid);
							num_cmd++;
						}
						kill(info->si_pid, SIGCONT);
						break;
						
					case FNCT_DELETE :
						kill(info->si_pid, SIGUSR2);
						SendCommand(getTail(cur_task), info->si_pid);
						if (!empty(cur_task)) subTail(cur_task);
						break;
						
					case FNCT_CLEAN : setEmpty(cur_task); break;
					case FNCT_EDIT : break;
					case FNCT_ADD :
						ReceiveCommand(&addedCommand);
						if (!filled(cur_task)) addTail(cur_task, addedCommand);
						break;
						
					default : break;
				}
			}
			break;
		}
		
		case SIGUSR2 : // programme courant
		{
			switch (sha->task[indice].function) {
				case FNCT_LIST :
					while (WaitSigcont)
					{
						ReceiveCommand(&command);
						printSQueue(command);
						deleteSQueue(command);
					}
					break;
					
				case FNCT_DELETE :
					ReceiveCommand(&command);
					printSQueue(command);
					deleteSQueue(command);
					break;
				
				case FNCT_CLEAN : setEmpty(cur_task); break;
				case FNCT_EDIT : break;
				default : break;
			}
			break;
		}
		
		case SIGCONT :
		{
			WaitSigcont=false;
			break;
		}
	}
}

void InitTaskInfo(int indice, char* name, Bool used, pid_t pid, Function fnc) {
	sha->task[indice].inUse = used;
	sha->task[indice].pid = pid;
	sha->task[indice].function = fnc;
	sprintf(sha->task[indice].name, "%s", name);
}

void GetEnv(char* var, char* result) {
	FILE* p = NULL;
	char command[256];
	if (var!=NULL) {
		sprintf(command, "echo %s", var);
		p = popen(command, "r");
	}
	
	if (p!=NULL && result!=NULL) {
		fgets(result, 256, p);
		CleanLineFeed(result);
		pclose(p);
	}
}

void CleanLineFeed(char* buffer) {
	char* p;
	if ((p=strchr(buffer, '\n'))!=NULL) *p = '\0';
}

void GetConfig() {
	char config_line[256];
	char* ptr_on_equal;
	FILE* config;
	
	GetEnv("$HOME", (char*)PATH_TO_CONFIG);
	sprintf(PATH_TO_TASKS, "%s", PATH_TO_CONFIG);
	strncat(PATH_TO_CONFIG, "/.enqueue/config.ini", 256);
	strncat(PATH_TO_TASKS, "/.enqueue/tasks", 256);

	config = fopen(PATH_TO_CONFIG, "r");
	if (config!=NULL) {
		while (fgets(config_line, 256, config)!=NULL) {
			CleanLineFeed(config_line);
			if ((ptr_on_equal=strchr(config_line, '='))!=NULL) *ptr_on_equal='\0';
			else {
				fprintf(stderr, "*** syntax error (config) : %s\n", config_line);
				continue;
			}
			if (strcmp(config_line, "DEFAULT_TASK")==0)
				sprintf(DEFAULT_TASK, "%s", ptr_on_equal+1);
			else if (strcmp(config_line, "MAX_RUNNING")==0)
				MAX_RUNNING = atoi(ptr_on_equal+1);
			else if (strcmp(config_line, "INIT_QUEUE_SIZE")==0)
				INIT_QUEUE_SIZE = atoi(ptr_on_equal+1);
			else fprintf(stderr, "*** unknown variable in config : %s\n", config_line);
		}
		fclose(config);
		
		// in case of variable in config file
		if (DEFAULT_TASK[0]=='$') GetEnv(DEFAULT_TASK, (char*)DEFAULT_TASK);
	}
	else fprintf(stderr, "*** impossible to open %s for reading\n", PATH_TO_CONFIG);
}

void InitShared() {
	if (sha->instance > 0) {
		sha->instance++;
	}
	else {
		memset(sha, 0, sizeof(StrShared));
		sha->instance=1;
	}
}

Function GetFunction(char* arg) {
	if (strcmp(arg, "-l")==0 || strcmp(arg, "--list")==0) return FNCT_LIST;
	else if (strcmp(arg, "-d")==0 || strcmp(arg, "--delete")==0) return FNCT_DELETE;
	else if (strcmp(arg, "-s")==0 || strcmp(arg, "--start")==0) return FNCT_START;
	else if (strcmp(arg, "-x")==0 || strcmp(arg, "--stop")==0) return FNCT_STOP;
	else if (strcmp(arg, "-c")==0 || strcmp(arg, "--clean")==0) return FNCT_CLEAN;
	else if (strcmp(arg, "-e")==0 || strcmp(arg, "--edit")==0) return FNCT_EDIT;
	else if (strcmp(arg, "-t")==0 || strcmp(arg, "--task")==0) return FNCT_TASK;
	else if (strcmp(arg, "-i")==0 || strcmp(arg, "--instance")==0) return FNCT_INSTANCE;
	else if (strcmp(arg, "-r")==0 || strcmp(arg, "--running")==0) return FNCT_RUNNING;
	else if (strcmp(arg, "-a")==0 || strcmp(arg, "--all-tasks")==0) return FNCT_TASKLIST;
	else if (strcmp(arg, "-h")==0 || strcmp(arg, "--help")==0) return FNCT_HELP;
	else if (strcmp(arg, "-f")==0 || strcmp(arg, "--free")==0) return FNCT_FREE;
	else if (strcmp(arg, "--set")==0) return FNCT_CONFIG;
	else return FNCT_ADD;
}

int NotUsed() {
	int i;
	for (i=0; i<MAXTASK; i++) {
		if (!sha->task[i].inUse)
			return i;
	}
	return -1;
}

int GetTaskWithName() {
	int i;
	for (i=0; i<MAXTASK; i++)
		if (sha->task[i].inUse)
			if (strcmp(sha->task[i].name, CURRENT_TASK_NAME)==0)
				return i;
	return -1;
}

int GetTaskWithPid(pid_t pid) {
	int i;
	for (i=0; i<MAXTASK; i++)
		if (sha->task[i].inUse)
			if (sha->task[i].pid == pid)
				return i;
	return -1;
}

void SendCommand(CMD sq, pid_t pid) {
	Sync syncbackup = sha->sync;
	char bufferbackup[MAXBUFFER];
	sprintf(bufferbackup, "%s", sha->buffer);
	
	int i=0;
	sha->sync = SYNC_R;
	while (sq.cmd[i] != NULL) {
		if (snprintf(sha->buffer, MAXBUFFER, "%s", sq.cmd[i])>=MAXBUFFER) {
			sha->sync = SYNC_W_OVER+pid;
		}
		else sha->sync = SYNC_W+pid;
		i++;
		while (sha->sync != SYNC_R) ;
	}
	sha->sync = SYNC_END+pid;
	if (snprintf(sha->buffer, MAXBUFFER, "%s", sq.wd)>=MAXBUFFER)
		sha->sync = SYNC_W_OVER+pid;
	else sha->sync = SYNC_W+pid;
	
	while (sha->sync != SYNC_R) ;
	
	sha->sync = syncbackup;
	sprintf(sha->buffer, "%s", bufferbackup);
}

void ReceiveCommand(CMD* sq) {
	pid_t thisPid = getpid();
	int i=0;
	sq->cmd = (char**)malloc(MAXBUFFER*sizeof(char*));
	if (sq->cmd!=NULL) {
		while (true) {
			while (sha->sync != SYNC_W+thisPid && sha->sync != SYNC_W_OVER+thisPid && sha->sync != SYNC_END+thisPid) ;
			if (sha->sync == SYNC_END+thisPid) break;
			sq->cmd[i] = (char*)malloc((strlen(sha->buffer)+1)*sizeof(char));
			if (sq->cmd[i]!=NULL) sprintf(sq->cmd[i], "%s", sha->buffer);
			//~ if (sha->sync == SYNC_W_OVER+thisPid) printf("[...]");
			//~ printf(" ");
			i++;
			sha->sync = SYNC_R;
		}
		sq->cmd[i] = NULL;
		while (sha->sync == SYNC_END+thisPid) ;
		sq->wd = (char*)malloc((strlen(sha->buffer)+1)*sizeof(char));
		if (sq->wd!=NULL) sprintf(sq->wd, "%s", sha->buffer);
		sha->sync = SYNC_R;
	}
}

Task LoadTask() {
	FILE* t;
	CMD command;
	char task[1024];
	char line[1024];
	int nbc, i, wdr=0, cmd=0;
	
	cur_task = newQueue(INIT_QUEUE_SIZE);
	CURRENT_TASK_ID = NotUsed();
	
	if (cur_task!=NULL) {
		sprintf(task, "%s/%s", PATH_TO_TASKS, CURRENT_TASK_NAME);
		
		t = fopen(task, "r");
		if (t!=NULL) {
			
			setEmpty(cur_task);
			SetInUse(CURRENT_TASK_ID);
			/// CHARGEMENT DES DONNEES DEPUIS LE FICHIER
			while (fgets(line, 1024, t)!=NULL) {
				CleanLineFeed(line);
				if (strcmp(line, "--WDR--")==0) {
					// récupération du WDR
					if (fgets(line, 1024, t)!=NULL) {
						CleanLineFeed(line);
						command.wd = (char*)malloc((strlen(line)+1)*sizeof(char));
						if (command.wd!=NULL) sprintf(command.wd, "%s", line);
						wdr=1; // wdr lu
						// si wdr et cmd lus, ajouter commande
						if (cmd && wdr) {
							if (filled(cur_task))
								cur_task = setSize(cur_task, getQSize(cur_task)*2);
							addTail(cur_task, command);
							wdr=0; cmd=0;
						}
					}
					else {
						fprintf(stderr, "*** ERROR: reading working directory while loading %s task\n", CURRENT_TASK_NAME);
						Exit();
						exit(6);
					}
				}
				else if (strcmp(line, "--CMD--")==0) {
					// récupération commande
					if (fgets(line, 1024, t)!=NULL) {
						nbc = atoi(line);
						i=0;
						command.cmd = (char**)malloc((nbc+1)*sizeof(char*));
						if (command.cmd!=NULL) {
							while (i<nbc) {
								if (fgets(line, 1024, t)!=NULL) {
									CleanLineFeed(line);
									command.cmd[i] = (char*)malloc((strlen(line)+1)*sizeof(char));
									if (command.cmd[i]!=NULL) sprintf(command.cmd[i], "%s", line);
									i++;
								}
								else {
									fprintf(stderr, "*** ERROR: reading command while loading %s task\n", CURRENT_TASK_NAME);
									Exit();
									exit(6);
								}
							}
						}
						command.cmd[nbc] = NULL;
						cmd=1; // cmd lue
						// si wdr et cmd lus, ajouter commande
						if (cmd && wdr) {
							if (filled(cur_task))
								cur_task = setSize(cur_task, getQSize(cur_task)+INIT_QUEUE_SIZE);
							addTail(cur_task, command);
							wdr=0; cmd=0;
						}
					}
					else {
						fprintf(stderr, "*** ERROR: reading number of command while loading %s task\n", CURRENT_TASK_NAME);
						Exit();
						exit(6);
					}
				}
				else {
					fprintf(stderr, "*** ERROR: invalid line, loading %s task\n", CURRENT_TASK_NAME);
					Exit();
					exit(6);
				}
			}
			
			fclose(t);
			sha->loaded++;
			return cur_task;
		}
		else deleteQueue(cur_task);
	}
	return NULL;
}

void Begin() {
	Function function = GetFunction(ARGV[0]);
	Bool AcceptNull = (function==FNCT_HELP
		||function==FNCT_RUNNING
		||function==FNCT_INSTANCE
		||function==FNCT_FREE
		||function==FNCT_CONFIG
		||function==FNCT_TASKLIST);
	
	// début de traitement
	switch (AcceptNull)
	{
		// cas des commandes qui n'ont pas besoin d'une tache valide
		case true :
		{
			switch (function)
			{
				case FNCT_RUNNING 	: Running();		break;
				case FNCT_HELP 		: Help();			break;
				case FNCT_INSTANCE 	: Instances();		break;
				case FNCT_FREE		: Free();			break;
				case FNCT_TASKLIST 	: ListAllTasks();	break;
				case FNCT_CONFIG 	: Config();			break;
				default :								break;
			}
			break;
		}
		
		// cas des commandes nécessitant une tache valide
		default :
		{
			// nom de la tache
			if (function != FNCT_ADD && ARGC > 2) sprintf(CURRENT_TASK_NAME, "%s", ARGV[1]);
			else sprintf(CURRENT_TASK_NAME, "%s", DEFAULT_TASK);
			
			switch (function)
			{
				case FNCT_LIST 		: ListTask();			break;
				case FNCT_START 	: StartTask();			break;
				case FNCT_DELETE 	: DeleteLastCommand();	break;
				case FNCT_STOP 		: StopTask();			break;
				case FNCT_CLEAN 	: CleanTask();			break;
				case FNCT_EDIT 		: EditTask();			break;
				case FNCT_TASK 		: ARGV=&(ARGV[2]); ARGC-=2;		// do NOT break
				case FNCT_ADD 		: AddToTask();			break;
				default :
					fprintf(stderr, "*** error while interpreting arguments : returning value %d\n", function);
					break;
			}
			break;
		}
	}
}

void Exit() {
	if (sha->instance > 1) {
		sha->instance--;
		shmdt(sha);
	}
	else {
		sha->instance--;
		shmdt(sha);
		shmctl(ssid, IPC_RMID, NULL);
	}
}

Bool InUse(int id) {
	return (sha->task[id].inUse) ;
}

void SetInUse(int id) {
	sha->task[id].inUse=true;
}

void SetNoUse(int id) {
	sha->task[id].inUse=false;
}

void Execute(char** argv, char* path) {
	pid_t pid;
	int status;
	
	// erreur fork
	if ((pid = fork()) < 0) {
		fprintf(stderr, "*** ERROR: forking child process failed\n");
		Exit();
		exit(4);
	}
	// fils
	else if (pid == 0) {
		if (path!=NULL)
			if (path[0]!='\0')
				if (chdir(path)==-1) {
					fprintf(stderr, "*** ERROR: chdir failed\n");
					Exit();
					exit(5);
				}
		if (execvp(*argv, argv) < 0) {
			fprintf(stderr, "*** ERROR: exec failed\n");
			Exit();
			exit(3);
		}
	}
	// père
	while (wait(&status)!=pid) ;
}

void DeleteFile(char* task) {
	char command[2048];
	sprintf(command, "test -f %s && rm %s", task, task);
	system(command);
}

void UpdateFile() {
	CMD sq;
	char task[512];
	int i, j, nbrc;
	FILE* uf;
	if (cur_task!=NULL) {
		sprintf(task, "%s/%s", PATH_TO_TASKS, CURRENT_TASK_NAME);
		if (empty(cur_task)) DeleteFile(task);
		else {
			uf = fopen(task, "w");
			if (uf!=NULL) {
				for (i=0; i<getLength(cur_task); i++) {
					sq = getElem(cur_task, i);
					fprintf(uf, "--WDR--\n");
					fprintf(uf, "%s\n", sq.wd);
					nbrc=0;
					while (sq.cmd[nbrc]!=NULL) nbrc++;
					fprintf(uf, "--CMD--\n");
					fprintf(uf, "%d\n", nbrc);
					j=0;
					while (j!=nbrc) {
						fprintf(uf, "%s\n", sq.cmd[j]);
						j++;
					}
				}
				fclose(uf);
			}
			else fprintf(stderr, "*** ERROR: unable to update %s task\n", CURRENT_TASK_NAME);
		}
		deleteQueue(cur_task);
	}
}

/**********************************************************************/
/********************************************* FONCTIONS UTILISATEUR **/
void Running() {
	int i, j=0;
	printf("-- running tasks :\n");
	for (i=0; i<MAXTASK && j<sha->loaded; i++) {
		if (sha->task[i].inUse) {
			if (sha->task[i].function==FNCT_START) printf("\t%s\n", sha->task[i].name);
			j++;
		}
	}
}

void Help() {
	printf("SYNOPSIS\n");
	printf("\tenqueue <OPTION> [TASK]\n");
	printf("\tenqueue [-t TASK] <command>\n");
	printf("\tenqueue --set PARAM=VALUE\n\n");
	
	printf("DESCRIPTION\n");
	printf("\tThis program allows you to enqueue command from terminal into tasks.\n");
	printf("\tYou can run %d different tasks at one time (see --set option)\n", MAX_RUNNING);
	printf("\tIt may be useful when you have to leave and want to let your computer on\n");
	printf("\tfor executing commands in the terminal, one after another.\n\n");
	
	printf("OPTIONS\n");
	printf("\t\tNo need of TASK for those\n");
	printf("\t-a, --alltasks\t: display all available tasks\n");
	printf("\t-f, --free\t: destroy leaks of shared memory (be careful)\n");
	printf("\t-h, --help\t: print this help and exit\n");
	printf("\t-i, --instance\t: display the number of instances\n");
	printf("\t-r, --running\t: display the running tasks\n");
	printf("\t    --set\t: set PARAM to VALUE in configuration file\n\n");
	printf("\t\tNeed to specify TASK for those\n");
	printf("\t-c, --clean\t: empty TASK waiting queue\n");
	printf("\t-d, --delete\t: delete last command in TASK\n");
	printf("\t-e, --edit\t: open TASK for modifications (in dev)\n");
	printf("\t-l, --list\t: display the list of waiting commands in TASK\n");
	printf("\t-s, --start\t: start execution of TASK\n");
	printf("\t-t, --task\t: add a command at the end of TASK\n");
	printf("\t-x, --stop\t: stop execution of TASK\n\n");
	printf("\tIf no task is given, working task is set as DEFAULT_TASK.\n");
	printf("\tIf no option is given, then adds 'command' at the end of DEFAULT_TASK.\n");
	printf("\tIf TASK doesn't already exist, then it is created.\n\n");
	
	printf("DETAILS\n");
	printf("\tDEFAULT_TASK can be modified in configuration file,\n");
	printf("\tor by using option --set PARAM=VALUE.\n\n");
	printf("\tPARAM can be :\n");
	printf("\tDEFAULT_TASK    --  name of default task\n");
	printf("\tMAX_RUNNING     --  tells how many tasks can be started at one time\n");
	printf("\tINIT_QUEUE_SIZE --  size of task at creation (number of commands)\n\n");
	
	printf("RETURN VALUE\n");
	printf("\t0 -- everything ok\n");
	printf("\t1 -- not enough argument\n");
	printf("\t2 -- too many tasks load\n");
	printf("\t3 -- command execution problem\n");
	printf("\t4 -- problem during child fork (execution of a command)\n");
	printf("\t6 -- configuration file is invalid\n");
}

void Instances() {
	printf("-- number of instances : %d\n", sha->instance);
}

void ListAllTasks() {
	printf("-- all available tasks :\n");
	char command[1024];
	sprintf(command, "ls -1 %s", PATH_TO_TASKS);
	system(command);
}

void Free() {
	printf("-- free memory\n");
	memset(sha, 0, sizeof(StrShared));
	shmdt(sha);
	shmctl(ssid, IPC_RMID, NULL);
	exit(0);
}

void StartTask() {
	char* wd=NULL;
	char** cmd=NULL;
	
	printf("-- start %s task :\n", CURRENT_TASK_NAME);
	CURRENT_TASK_ID = GetTaskWithName();
	if (CURRENT_TASK_ID!=-1) {
		if (sha->task[CURRENT_TASK_ID].function==FNCT_START) {
		// la tâche existe et est en cours d'exécution
			fprintf(stderr, "*** task already running\n");
			return;
		}
		// la tâche existe et est en demande, on attend
		else while (InUse(CURRENT_TASK_ID)) sleep(1);
	}
	
	cur_task = LoadTask();
	
	if (cur_task==NULL) {
		fprintf(stderr, "*** task is empty\n");
		return;
	}
	
	InitTaskInfo(CURRENT_TASK_ID, CURRENT_TASK_NAME, true, getpid(), FNCT_START);
	
	while (!empty(cur_task) && WaitSigcont)
	{
		wd = getHead(cur_task).wd;
		cmd = getHead(cur_task).cmd;
		Execute(cmd, wd);
		if (!empty(cur_task)) subHead(cur_task);
	}
	
	SetNoUse(CURRENT_TASK_ID);
}

void ListTask() { 
	printf("-- commands in %s task :\n", CURRENT_TASK_NAME);
	indice = NotUsed();
	CURRENT_TASK_ID = GetTaskWithName();
	if (CURRENT_TASK_ID!=-1) {
		InitTaskInfo(indice, "", true,  getpid(), FNCT_LIST);
		kill(sha->task[CURRENT_TASK_ID].pid, SIGUSR1);
		SetNoUse(indice);
	}
	else {
		cur_task = LoadTask();
		if (cur_task!=NULL) {
			InitTaskInfo(indice, CURRENT_TASK_NAME, true,  getpid(), FNCT_LIST);
			printQueue(cur_task);
			SetNoUse(indice);
			deleteQueue(cur_task);
			cur_task=NULL;
		}
	}
}

void DeleteLastCommand() {
	printf("-- delete last command from %s task :\n", CURRENT_TASK_NAME);
	indice = NotUsed();
	CURRENT_TASK_ID = GetTaskWithName();
	if (CURRENT_TASK_ID!=-1) {
		InitTaskInfo(indice, "", true,  getpid(), FNCT_DELETE);
		kill(sha->task[CURRENT_TASK_ID].pid, SIGUSR1);
		SetNoUse(indice);
	}
	else {
		cur_task = LoadTask();
		if (cur_task!=NULL) {
			InitTaskInfo(indice, CURRENT_TASK_NAME, true, getpid(), FNCT_DELETE);
			printSQueue(getTail(cur_task));
			if (!empty(cur_task)) subTail(cur_task);
			SetNoUse(indice);
		}
	}
}

void StopTask() {
	printf("-- stop %s task\n", CURRENT_TASK_NAME);
	indice = NotUsed();
	CURRENT_TASK_ID = GetTaskWithName();
	if (CURRENT_TASK_ID!=-1) {
		InitTaskInfo(indice, "", true,  getpid(), FNCT_STOP);
		kill(sha->task[CURRENT_TASK_ID].pid, SIGCONT);
		SetNoUse(indice);
	}
	else fprintf(stderr, "*** %s task is not running\n", CURRENT_TASK_NAME);
}

void CleanTask() {
	char task[512];
	printf("-- clean %s task\n", CURRENT_TASK_NAME);
	indice = NotUsed();
	CURRENT_TASK_ID = GetTaskWithName();
	if (CURRENT_TASK_ID!=-1) {
		InitTaskInfo(indice, "", true,  getpid(), FNCT_CLEAN);
		kill(sha->task[CURRENT_TASK_ID].pid, SIGUSR1);
		SetNoUse(indice);
	}
	else {
		sprintf(task, "%s/%s", PATH_TO_TASKS, CURRENT_TASK_NAME);
		DeleteFile(task);
	}
}

void EditTask() { //////////////////////////////////////////////////////
}
/* Nouvelle instance.
//~ Modification d'une tache :
	//~ - tache en exécution :
		//~ - envoie d'une demande MODIF
		//~ - traitement de la demande :
			//~ - exécution en pause
			//~ - lancer le mode raw (affichage commande, récup appuis clavier suppr, i, e)
			//~ - arreter le mode raw en appuyant sur une touche ou un bouton
			//~ (les modifs se font en mémoire, sur la file)
		//~ - reprise de l'exécution
	//~ - sinon
		//~ - charger la tache
		//~ - lancer le mode raw
		//~ - sauvegarder les modifs dans le fichier (Refresh();)
		//~ - quitter
	*/

void AddToTask() {
	char pwd[256];
	GetEnv("$PWD", (char*)pwd);
	newSQueue(&addedCommand, ARGC, ARGV, pwd);
	printf("-- add command :\n");
	printSQueue(addedCommand);
	printf("   in %s task\n", CURRENT_TASK_NAME);
	indice = NotUsed();
	CURRENT_TASK_ID = GetTaskWithName();
	if (CURRENT_TASK_ID!=-1) {
		InitTaskInfo(indice, "", true,  getpid(), FNCT_ADD);
		kill(sha->task[CURRENT_TASK_ID].pid, SIGUSR1);
		SendCommand(addedCommand, sha->task[CURRENT_TASK_ID].pid);
		SetNoUse(indice);
	}
	else {
		InitTaskInfo(indice, CURRENT_TASK_NAME, true, getpid(), FNCT_ADD);
		cur_task = LoadTask();
		if (cur_task!=NULL) {
			if (!filled(cur_task)) addTail(cur_task, addedCommand);
		}
		else {
			cur_task = newQueue(INIT_QUEUE_SIZE);
			addTail(cur_task, addedCommand);
		}
		SetNoUse(indice);
	}
}

void Config() {
	char* ptrOnEqu=NULL;
	FILE* conf=NULL;
	if (ARGV[1]==NULL) {
		fprintf(stderr, "*** ERROR : missing parameter for --set option\n");
		return ;
	}
	
	if ((ptrOnEqu=strchr(ARGV[1], '='))!=NULL) {
		*ptrOnEqu='\0';
		if (strcmp(ARGV[1], "DEFAULT_TASK")==0)
			sprintf(DEFAULT_TASK, "%s", (char*)ptrOnEqu+1);
		else if (strcmp(ARGV[1], "MAX_RUNNING")==0)
			MAX_RUNNING = atoi((char*)ptrOnEqu+1);
		else if (strcmp(ARGV[1], "INIT_QUEUE_SIZE")==0)
			INIT_QUEUE_SIZE = atoi((char*)ptrOnEqu+1);
		else {
			fprintf(stderr, "*** ERROR : unknown config parameter %s\n", ARGV[1]);
			exit(0);
		}
		if ((conf=fopen(PATH_TO_CONFIG, "w"))!=NULL) {
			fprintf(conf, "DEFAULT_TASK=%s\n", DEFAULT_TASK);
			fprintf(conf, "MAX_RUNNING=%d\n", MAX_RUNNING);
			fprintf(conf, "INIT_QUEUE_SIZE=%d\n", INIT_QUEUE_SIZE);
			fclose(conf);
		}
	}
	else fprintf(stderr, "*** ERROR : incorrect syntax\n");
}

/**********************************************************************/
/*********************************************** PROGRAMME PRINCIPAL **/
int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("usage : %s <OPTION|command> [TASK]\n%s --help to print some help\n", argv[0], argv[0]);
		exit(1);
	}
	
	struct sigaction action;
	action.sa_handler=(void*)handler;
	action.sa_flags=SA_SIGINFO;
	action.sa_sigaction=(void*)handler;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	sigaction(SIGCONT, &action, NULL);
	
	ARGC=argc;
	ARGV=&(argv[1]);
	
	key_t k = ftok(argv[0], 'x');
	ssid = shmget(k, sizeof(StrShared), IPC_CREAT | 0777);
	sha = shmat(ssid, NULL, 0);
	
	GetConfig();
	InitShared();
	Begin();
	UpdateFile();
	Exit();
	
	return 0;
}












