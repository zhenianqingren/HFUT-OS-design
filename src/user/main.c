#include "../../include/sys_calls.h"
#include "../../include/tool.h"

// command set
const char *command[CMDCOUNT] = {"CLS", "DATE", "TIME", "DOSKEY",
                                 "FIND", "FINDSTR", "COMP", "FC",
                                 "EXIT", "HELP", "MORE"};
const char *exit_msg;

// function pointer set
typedef int (*call_ptr)(int argc, char *argv[]);
call_ptr sys_calls[CMDCOUNT] = {sys_cls, sys_date, sys_time, sys_doskey,
                                sys_find, sys_findstr, sys_comp, sys_fc,
                                sys_exit, sys_help, sys_more};

// input command
char cmd[INPUTBUFFER << 1];
const char *version;

void getarg(int *argc, char **argv);
int verify(char *icmd);
void exe_child(int sys_num, int argc, char **argv);

node *cur = NULL;
char *history;

int main()
{

  printf("%s\n\n", version);
  const int promptl = strlen(HOME_DIR);

  while (1)
  {
    fprintf(stderr, "\033[1;32m");
    // stderr indicates output won't be buffered, so color can valid
    // immediately. Otherwise we can't see the color change.
    output(STDOUT_FILENO, HOME_DIR, promptl);
    fprintf(stderr, "\033[0m");

    int argc;
    char *argv[MAXARGS];
    getarg(&argc, argv);

    char *ap = argv[0];
    if (*ap == '\0')
      continue;
    int sys_num;
    if ((sys_num = verify(ap)) < 0)
    {
      fprintf(stderr, "error command!\n");
      continue;
    }

    // only take command arguments /... into consideration
    --argc;
    // fork and child process perform command
    if (sys_num == SYS_doskey)
      sys_doskey(argc, &argv[1]);
    else if (sys_num == SYS_exit)
      sys_exit(argc, &argv[1]);
    else
      exe_child(sys_num, argc, &argv[1]);

    cur = NULL;
  }

  return 0;
}

void err_print()
{
  fprintf(stderr, "error: %s\n", strerror(errno));
  exit(-1);
}

const char *version = "Microsoft Windows [Version 10.0.19045.2486]\n\
(c) Microsoft Corporation. All rights reserved.";

void getarg(int *argc, char **argv)
{
  int res = input(STDIN_FILENO, cmd);
  tty_reset(STDIN_FILENO);

  // record new command
  if (cmdtail == NULL)
  {
    cmdtail = strnode(cmd);
    cmdhead = cmdtail;
  }
  else
    push_back(&cmdtail, strnode(cmd));

  char *cmdp = cmd;
  *argc = 0;

  while ((argv[*argc] = strsep(&cmdp, " ")) != NULL)
    ++(*argc);
}

int verify(char *icmd)
{
  char tmp[16];
  memset(tmp, 0, 16);
  // tranform cmd to upper
  transupper(tmp, icmd);

  int sys_num;
  // match the cmd
  if ((sys_num = sys_call(command, tmp, CMDCOUNT)) != -1)
    return sys_num;

  // match alias
  for (node *tp = pairhead; tp != NULL; tp = tp->next)
  {
    pair *p = (pair *)(tp->p);
    if (strcmp(p->sym, icmd) == 0)
    { // find alias
      transupper(tmp, p->cmd);
      for (int i = 0; i < CMDCOUNT; ++i)
        if (strncmp(tmp, command[i], strlen(command[i])) == 0)
          return i;
    }
  }

  return -1;
}

void exe_child(int sys_num, int argc, char **argv)
{
  pid_t pid;
  int wstatus;
  if ((pid = fork()) < 0)
    err_print();

  else if (pid == 0) // child process
    exit(sys_calls[sys_num](argc, argv));

  else
  { // parent process
    memset(cmd, 0, INPUTBUFFER);
    if (wait(&wstatus) < 0)
      err_print();
  }

  if (WEXITSTATUS(wstatus) != 0)
    fprintf(stderr, "error: %s or error format!\n",
            strerror(WEXITSTATUS(wstatus)));
}
