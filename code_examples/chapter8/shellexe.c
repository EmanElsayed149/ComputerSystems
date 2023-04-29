#include "csapp.h"
#define MAXARGS   128

/* functions prototypes */
void eval (char *cmdline);
int parseline (char *buf , char **argv);
int builtin_command (char **argv);

int main()
{
    char cmdline[MAXLINE];   /* command line */

    while (1)
    {
        /* Read */
        printf("> ");
        fgets(cmdline, MAXARGS, stdin);
        if(feof(stdin))
        {
            exit(0);
        }


        /* Evaluate */
        eval(cmdline);
    }
}


void eval (char *cmdline)
{
    int bg;                 /* should program run in background or foreground ? */
    char buf[MAXLINE];      /* holds modified command line */
    char *argv[MAXARGS];    /* argument list execve() */
    pid_t pid;              /* process id */

    strcpy(buf, cmdline);
    bg = parseline( buf , argv);

    if(argv[0]== NULL)
    {
        return;  /* ignore empty lines */
    }

    if(!builtin_command(argv))
    {
        if((pid= fork())==0)
        {
            if(execve(argv[0],argv,environ)<0)
            {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }
        /* parent waits for foreground job to terminate */
        if(!bg)
        {
            int status;
	        if (waitpid(pid, &status, 0) < 0)
		        perror("waitfg: waitpid error");
        }
        else
	    printf("%d %s", pid, cmdline);
    }
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv) 
{
    if (!strcmp(argv[0], "quit")) /* quit command */
	exit(0);  
    if (!strcmp(argv[0], "&"))    /* Ignore singleton & */
	return 1;
    return 0;                     /* Not a builtin command */
}

/* $end eval */

/* $begin parseline */
/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv) 
{
    char *delim;         /* Points to first space delimiter */
    int argc;            /* Number of args */
    int bg;              /* Background job? */

    buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
	buf++;

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
	argv[argc++] = buf;
	*delim = '\0';
	buf = delim + 1;
	while (*buf && (*buf == ' ')) /* Ignore spaces */
            buf++;
    }
    argv[argc] = NULL;
    
    if (argc == 0)  /* Ignore blank line */
	return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0)
	argv[--argc] = NULL;

    return bg;
}
/* $end parseline */



