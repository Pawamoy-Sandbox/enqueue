#include "enqueue.h"

/**********************************************************************/
/************************************************ VARIABLES GLOBALES **/
static char PATH_TO_CONFIG[256];
static char PATH_TO_TASKS[256];
static char PATH_TO_HISTORY[256];
static char DEFAULT_EDITOR[256];
static char DEFAULT_TASK[256];
static int FORCE_TASKS_LOAD=0;
static int MAX_RUNNING=MAXTASK/2;

Shared sha = NULL;
CMD addedCommand;
void(*TaskFunction)(Task*) = NULL;

/**********************************************************************/
/******************************************** FONCTIONS DU PROGRAMME **/
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

void GetConfig() {
	char config_line[256];
	char* ptr_on_equal;
	FILE* config;
	
	GetEnv("$HOME", (char*)PATH_TO_CONFIG);
	sprintf(PATH_TO_TASKS, "%s", PATH_TO_CONFIG);
	sprintf(PATH_TO_HISTORY, "%s", PATH_TO_CONFIG);
	strncat(PATH_TO_CONFIG, "/.enqueue/config.ini", 256);
	strncat(PATH_TO_TASKS, "/.enqueue/tasks", 256);
	strncat(PATH_TO_HISTORY, "/.enqueue/history", 256);

	config = fopen(PATH_TO_CONFIG, "r");
	if (config!=NULL) {
		while (fgets(config_line, 256, config)!=NULL) {
			CleanLineFeed(config_line);
			if ((ptr_on_equal=strchr(config_line, '='))!=NULL) *ptr_on_equal='\0';
			else {
				fprintf(stderr, "*** syntax error (config) : %s\n", config_line);
				continue;
			}
			if (strcmp(config_line, "FORCE_LOAD")==0)
				FORCE_TASKS_LOAD = atoi(ptr_on_equal+1);
			else if (strcmp(config_line, "DEFAULT_EDITOR")==0)
				sprintf(DEFAULT_EDITOR, "%s", ptr_on_equal+1);
			else if (strcmp(config_line, "DEFAULT_TASK")==0)
				sprintf(DEFAULT_TASK, "%s", ptr_on_equal+1);
			else if (strcmp(config_line, "MAX_RUNNING")==0)
				MAX_RUNNING = atoi(ptr_on_equal+1);
			else fprintf(stderr, "*** unknown variable in config : %s\n", config_line);
		}
		fclose(config);
		
		// in case of variable in config file
		if (DEFAULT_EDITOR[0]=='$') GetEnv(DEFAULT_EDITOR, (char*)DEFAULT_EDITOR);
		if (DEFAULT_TASK[0]=='$') GetEnv(DEFAULT_TASK, (char*)DEFAULT_TASK);
	}
	else fprintf(stderr, "*** impossible to open %s for reading\n", PATH_TO_CONFIG);
}

void InitShared() {
	if (sha->instance > 0) {
		sha->instance++;
	}
	else {
		sha->instance=1;
		sha->running=0;
		sha->loaded=0;
		memset(sha->task, 0, MAXTASK*sizeof(Task));
		if (FORCE_TASKS_LOAD) LoadTasks();
	}
	addedCommand.cmd[0]='\0';
}

void Begin(int argc, char* argv[]) {
	char task[64],
		buffer[1024];
	int i,
		cmdLength=0,
		cmdBegin=1,
		function;
	Task* workingtask = NULL;
	
	// vérification arguments
	function = CheckArgument(argv[1]);
	int AcceptNull = (function==_H||function==_CF||function==_R||function==_I||function==_LT||function==_LD);
	
	// début de traitement
	switch (AcceptNull)
	{
		// cas des commandes qui n'ont pas besoin d'une tache valide
		case true :
		{
			switch (function)
			{
				case _R : printf("-- number of running task"); TaskFunction = Running; break;
				case _CF : printf("-- open configuration file\n"); TaskFunction = OpenConfig; break;
				case _H : printf("-- help of the program\n"); TaskFunction = Help; break;
				case _I : printf("-- number of running instances"); TaskFunction = Instances; break;
				case _LT : printf("-- list all tasks\n"); TaskFunction = ListAllTasks; break;
				case _LD : printf("-- list loaded tasks\n"); TaskFunction = ListLoadedTasks; break;
			}
			break;
		}
		
		// cas des commandes nécessitant une tache valide
		default :
		{
			// nom de la tache
			if (function != _A && argc > 2) sprintf(task, "%s", argv[2]);
			else sprintf(task, "%s", DEFAULT_TASK);
			// pointeur sur celle-ci
			workingtask=GetTask(task);
			if (workingtask==NULL) {
				workingtask=LoadTask(task);
				if (workingtask==NULL) {
					workingtask=AddTask(task);
					if (workingtask==NULL) {
						// tache introuvable, plus de place
						fprintf(stderr, "*** unable to work on task %s, exit\n", task);
						exit(2);
					}
				}
			}
			// tache valide
			switch (function)
			{
				case _L : printf("-- list %s task\n", task); TaskFunction = ListTask; break;
				case _S : printf("-- start %s task\n", task); TaskFunction = StartTask; break;
				case _D : printf("-- delete last command in %s task\n", task); TaskFunction = DeleteLastCommand; break;
				case _X : printf("-- stop %s task\n", task); TaskFunction = StopTask; break;
				case _C : printf("-- clean %s task\n", task); TaskFunction = CleanTask; break;
				case _M : {
					if (argc > 3) sprintf(DEFAULT_EDITOR, "%s", argv[3]);
					printf("-- modify %s task\n", task);
					TaskFunction = ModifyTask;
					break;
				}
				case _T : cmdBegin+=2;
				case _A : {
					GetEnv("$PWD", addedCommand.wd);
					sprintf(addedCommand.cmd, "%s", argv[cmdBegin]);
					cmdLength = strlen(addedCommand.cmd);
					for (i=cmdBegin+1; i<argc; i++) {
						cmdLength += strlen(argv[i]);
						if (cmdLength >= 1023) {
							fprintf(stderr, "*** attention : command is too long (max. size 1024)\n");
							fprintf(stderr, "                possible unexpected behavior\n"); 
							break;
						}
						sprintf(buffer, " %s", argv[i]);
						strncat(addedCommand.cmd, buffer, 1024);
					}
					printf("-- add '%s' to %s task\n", addedCommand.cmd, task);
					TaskFunction = AddToTask;
					break;
				}
				default : fprintf(stderr, "*** error while interpreting arguments : returning value %d\n", function); break;
			}
			break;
		}
	}
	
	TaskFunction(workingtask);
	
	if (workingtask!=NULL) {
		if ((!workingtask->exec) && (!workingtask->demand))
			workingtask->inuse=0;
	}
}

Task* NotUsed() {
	int i;
	for (i=0; i<MAXTASK; i++) {
		if (!sha->task[i].inuse)
			return &(sha->task[i]);
	}
	return NULL;
}

Task* AddTask(char* task) {
	Task* t = NotUsed();
	if (sha->loaded < MAXTASK) {
		if (task!=NULL) {
			strncpy(t->id, task, 64);
			t->inuse=1;
			setEmpty(&(t->q));
			sha->loaded++;
			return t;
		}
		else {
			fprintf(stderr, "*** impossible to create an empty task");
			return (Task*)NULL;
		}
	}
	else {
		fprintf(stderr, "*** already too much tasks loaded (max. %d)\n", MAXTASK);
		return (Task*)NULL;
	}
}

Task* GetTask(char* task) {
	int i;
	for (i=0; i<sha->loaded; i++) {
		if (strcmp(sha->task[i].id, task)==0) {
			return &(sha->task[i]);
		}
	}
	return NULL;
}

int CheckArgument(char* arg) {
	if (strcmp(arg, "-l")==0 || strcmp(arg, "--list")==0) return _L;
	else if (strcmp(arg, "-d")==0 || strcmp(arg, "--delete")==0) return _D;
	else if (strcmp(arg, "-s")==0 || strcmp(arg, "--start")==0) return _S;
	else if (strcmp(arg, "-x")==0 || strcmp(arg, "--stop")==0) return _X;
	else if (strcmp(arg, "-c")==0 || strcmp(arg, "--clean")==0) return _C;
	else if (strcmp(arg, "-cf")==0 || strcmp(arg, "--config")==0) return _CF;
	else if (strcmp(arg, "-m")==0 || strcmp(arg, "--modify")==0) return _M;
	else if (strcmp(arg, "-t")==0 || strcmp(arg, "--task")==0) return _T;
	else if (strcmp(arg, "-i")==0 || strcmp(arg, "--instance")==0) return _I;
	else if (strcmp(arg, "-r")==0 || strcmp(arg, "--running")==0) return _R;
	else if (strcmp(arg, "-rl")==0 || strcmp(arg, "--reload")==0) return _RL;
	else if (strcmp(arg, "-ld")==0 || strcmp(arg, "--loaded-tasks")==0) return _LD;
	else if (strcmp(arg, "-lt")==0 || strcmp(arg, "--list-tasks")==0) return _LT;
	else if (strcmp(arg, "-h")==0 || strcmp(arg, "--help")==0) return _H;
	else return _A;
}

void Parse(char* line, char* argv[]) {
	int i=0, m=0;
	// tant qu'on a pas atteint la fin de la ligne
	while (line[i] != '\0') {
		// on remplace chaque espace par un \0
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n') {
			line[i] = '\0';
			i++;
		}
		// on fait pointer le mot sur le m-ième mot de la ligne
		argv[m] = &line[i];
		// on passe au mot suivant
		m++;
		// on se déplace jusqu'au prochain caractère non "vide"
		while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t' && line[i] != '\n') 
			i++;
	}
	// fin de ligne atteinte
	argv[m] = NULL;
} 

void Execute(char **argv, char* path) {
	pid_t pid;
	int status;
	
	// erreur fork
	if ((pid = fork()) < 0) {
		fprintf(stderr, "*** ERROR: forking child process failed\n");
		exit(4);
	}
	// fils
	else if (pid == 0) {
		if (path!=NULL)
			if (path[0]!='\0')
				if (chdir(path)==-1)
					printf("*** ERROR: chdir failed\n");
		if (execvp(*argv, argv) < 0) {
			fprintf(stderr, "*** ERROR: exec failed\n");
			exit(3);
		}
	}
	// père
	else while (wait(&status) != pid) ;
}

void CleanLineFeed(char* buffer) {
	char* p;
	if ((p=strchr(buffer, '\n'))!=NULL) *p = '\0';
}

void ReloadTask(char* name) { // modif quand CMD.wd
	Task* taskptr;
	FILE* t;
	CMD command;
	char task[1024];
	
	sprintf(task, "%s/%s", PATH_TO_TASKS, name);
	t = fopen(task, "r");
	if (t!=NULL) {
		if ((taskptr = GetTask(name))!=NULL) {
			setEmpty(&(taskptr->q));
			while (fgets(command.cmd, 1024, t)!=NULL) {
				CleanLineFeed(command.cmd);
				if (!filled(&(taskptr->q)))
					addTail(&(taskptr->q), command);
			}
			fclose(t);
		}
	}
	else fprintf(stderr, "*** impossible to load %s task\n", name);
}

Task* LoadTask(char* name) { // modif quand CMD.wd
	FILE* t;
	CMD command;
	char task[1024];
	char* ptr_on_wd;
	Task* tsk = NotUsed();
	
	if (tsk!=NULL) {
		sprintf(task, "%s/%s", PATH_TO_TASKS, name);
		t = fopen(task, "r");
		if (t!=NULL) {
			strncpy(tsk->id, name, 64);
			setEmpty(&(tsk->q));
			tsk->inuse=1;
			tsk->exec=0;
			tsk->demand=0;
			while (fgets(command.cmd, 1024, t)!=NULL) {
				CleanLineFeed(command.cmd);
				if ((ptr_on_wd=strchr(command.cmd, '#'))!=NULL) {
					*ptr_on_wd='\0';
					sprintf(command.wd, "%s", ptr_on_wd+1);
				}
				else command.wd[0]='\0';
				if (!filled(&(tsk->q)))
					addTail(&(tsk->q), command);
			}
			fclose(t);
			sha->loaded++;
			return tsk;
		}
	}
	return NULL;
}

void LoadTasks() { // modif quand CMD.wd
	char tasks[512];
	char line[64];
	FILE* f;
	
	sprintf(tasks, "ls -1 %s/", PATH_TO_TASKS);
	f = popen(tasks, "r");
	if (f!=NULL) {
		while (fgets(line, 64, f)!=NULL && sha->loaded < MAXTASK) {
			CleanLineFeed(line);
			LoadTask(line);
		}
		pclose(f);
	}
	else fprintf(stderr, "*** impossible to load tasks\n");
}

void SaveTask(int num) {
	FILE *f;
	char pro[512];
	char taskempty[1030];
	sprintf(pro, "%s/%s", PATH_TO_TASKS, sha->task[num].id);
	if (empty(&(sha->task[num].q))) {
		sprintf(taskempty, "test -f \"%s\" && rm -f \"%s\"", pro, pro);
		system(taskempty);
	}
	else {
		f = fopen(pro, "w");
		if (f!=NULL) {
			while (!empty(&(sha->task[num].q))) {
				fprintf(f, "%s#", &(getHead(&(sha->task[num].q)).cmd[0]));
				fprintf(f, "%s\n", &(getHead(&(sha->task[num].q)).wd[0]));
				subHead(&(sha->task[num].q));
			}
			fclose(f);
		}
		else fprintf(stderr, "*** impossible to save %s task\n", pro);
	}
}

void SaveTasks() { // modif quand CMD.wd
	int i;
	for (i=0; i<sha->loaded; i++) {
		SaveTask(i);
	}
}

/**********************************************************************/
/********************************************* FONCTIONS UTILISATEUR **/
void ListTask(Task* p) { // modif quand CMD.wd
	p->demand=1;
	printQueue(&(p->q));
	p->demand=0;
}

void StartTask(Task* p) { // modif quand CMD.wd
	if (empty(&(p->q))) return;
	if (p->exec==1) {
		fprintf(stderr, "*** task %s already running\n", p->id);
		return;
	}
	if (sha->running == MAX_RUNNING) {
		fprintf(stderr, "*** too much tasks already running (max. %d)\n", MAX_RUNNING);
		return;
	}
	sha->running++;
	p->exec=1;
	char line[1024];
	char wd[1024];
	char command[128][128];
	while (!empty(&(p->q))) {
		while (p->demand) sleep(1);
		if (p->exec==0) break;
		sprintf(line, "%s", &(getHead(&(p->q)).cmd[0]));
		Parse(line, (char**)command);
		sprintf(wd, "%s", &(getHead(&(p->q)).wd[0]));
		subHead(&(p->q));
		Execute((char**)command, (char*)wd);
	}
	p->exec=0;
	sha->running--;
}

void DeleteLastCommand(Task* p) {
	p->demand=1;
	if (!empty(&(p->q))) subTail(&(p->q));
	p->demand=0;
}

void StopTask(Task* p) {
	p->demand=1;
	if (p->exec==1) p->exec=0;
	p->demand=0;
}

void CleanTask(Task* p) {
	p->demand=1;
	setEmpty(&(p->q));
	p->demand=0;
}

void OpenFile(char* editor, char* path, char* name) {
	char** command;
	command=malloc(3*sizeof(char*));
	command[0]=malloc(128*sizeof(char));
	command[1]=malloc(128*sizeof(char));
	command[2]=NULL;
	sprintf(command[0], "%s", editor);
	if (name==NULL) sprintf(command[1], "%s", path);
	else sprintf(command[1], "%s/%s", path, name);
	
	Execute(command, NULL);
	
	free(command[0]);
	free(command[1]);
	free(command[2]);
	free(command);
}

void ModifyTask(Task* p) { // modif quand CMD.wd
	p->demand=1;
	OpenFile(DEFAULT_EDITOR, PATH_TO_TASKS, p->id);
	//~ ReloadTask(p->id);
	p->demand=0;
}

void AddToTask(Task* p) {
	p->demand=1;
	if (!filled(&(p->q))) addTail(&(p->q), addedCommand);
	p->demand=0;
}

void Instances(Task* p) {
	printf(" : %d\n", sha->instance);
}

void Running(Task* p) {
	printf(" : %d\n", sha->running);
}

void OpenConfig(Task* p) {
	OpenFile(DEFAULT_EDITOR, PATH_TO_CONFIG, NULL);
	// reload config
	GetConfig();
}

void ListAllTasks(Task* p) {
	OpenFile("ls", PATH_TO_TASKS, NULL);
}

void ListLoadedTasks(Task* p) {
	int i;
	for (i=0; i<sha->loaded; i++) {
		if (sha->task[i].exec) printf("%s (running)\n", sha->task[i].id);
		else printf("%s\n", sha->task[i].id);
	}
}

void Help(Task* p) {
	printf("SYNTAX\n\tenqueue <OPTION> [TASK]\n");
	printf("\tenqueue [-t TASK] <command>\n");
	printf("\tenqueue --set PARAM=VALUE\n\n");
	
	printf("DESCRIPTION\n");
	printf("\tThis program allows you to enqueue command from terminal\n");
	printf("\tinto tasks (or waiting queues). You can run %d different tasks\n", MAXTASK);
	printf("\tat one time. Each task can store %d command at one time.\n", MAXQUEUE);
	printf("\tIt may be useful when you have to leave and want to let your computer on\n");
	printf("\tfor executing commands in the terminal, one after another.\n\n");
	
	printf("OPTIONS\n");
	printf("\t-l, --list\t\t: display the list of waiting commands in TASK\n");
	printf("\t-d, --delete\t\t: delete last command in TASK\n");
	printf("\t-s, --start\t\t: start execution of TASK\n");
	printf("\t-x, --stop\t\t: stop execution of TASK\n");
	printf("\t-c, --clean\t\t: empty TASK waiting queue\n");
	printf("\t-m, --modify [EDITOR]\t: open TASK for modifications with EDITOR\n");
	printf("\t-t, --task\t\t: set the working task to TASK and add a command\n");
	printf("\t-i, --instance\t\t: display the number of running instances\n");
	printf("\t-h, --help\t\t: print this help and exit\n\n");
	printf("\tIf no task is given, working task is set as DEFAULT_TASK.\n");
	printf("\tIf no option is given, then adds 'command' at the end of DEFAULT_TASK.\n");
	printf("\tIf no EDITOR is given for modify option, opens TASK with DEFAULT_EDITOR.\n");
	printf("\tIf TASK doesn't already exist, then it is created.\n\n");
	
	printf("DETAILS\n");
	printf("\tDEFAULT_TASK and DEFAULT_EDITOR can be modified in configuration file,\n");
	printf("\tor by using option --set PARAM=VALUE.\n");
	printf("\tPARAM can be :\n");
	printf("\t\tDEFAULT_EDITOR  --  editor for opening and modifying files or tasks\n");
	printf("\t\tDEFAULT_TASK  --  name of default task\n");
	printf("\t\tFORCE_LOAD  --  load (1) or not load (0) the first %d tasks at startup\n", MAXTASK);
	printf("\t\tMAX_RUNNING  --  set how many tasks can be started in the same time\n");
	printf("\tSyntax for modifying tasks in your favorite editor is :\n");
	printf("\t\tcommand arg1 ... argn#working directory\n");
	printf("\tOne command per line, and you must add an empty line at the end of file.\n\n");
	
	printf("RETURN VALUE\n");
	printf("\t0 -- everything ok\n");
	printf("\t1 -- not enough argument\n");
	printf("\t2 -- too many tasks load\n");
	printf("\t3 -- command execution problem\n");
	printf("\t4 -- problem during child fork (execution of a command)\n");
}

/**********************************************************************/
/*********************************************** PROGRAMME PRINCIPAL **/
int main(int argc, char* argv[]) {
	// vérification nombre arguments
	if (argc < 2) {
		printf("usage : %s <OPTION|command> [TASK]\n%s --help to print some help\n", argv[0], argv[0]);
		exit(1);
	}
	
	// création de la structure partagée
	key_t k = ftok(argv[0], 'x');
	int ssid = shmget(k, sizeof(StrShared), IPC_CREAT | 0777);
	sha = shmat(ssid, NULL, 0);
	
	// lecture de la configuration
	GetConfig();
	
	// initialisation de la structure
	InitShared();
	
	// début du traitement
	Begin(argc, argv);
	
	// ne pas détruire la mémoire s'il reste des instances
	if (sha->instance > 1) {
		sha->instance--;
		shmdt(sha);
	}
	else {
		// dernière instance en cours
		sha->instance--;
		// sauvegarde des files d'attente
		SaveTasks();
		
		// destruction structure partagée
		shmdt(sha);
		shmctl(ssid, IPC_RMID, NULL);
	}
	
	return 0;
}

