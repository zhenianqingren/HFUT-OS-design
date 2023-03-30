#include "../../include/tool.h"

#define LEGAL_ARGS 16
#define LISTSIZ 2
#define MACROF 5
static const char *args[] = {"/?",      "/REINSTALL", "/LISTSIZE",
                      "/MACROS", "/HISTORY",   "/MACROFILE"};
static const size_t arglen[] = {2, 10, 9, 7, 8, 10};
const char *doskeyh; // help info /?

static void reinstall(); // reinstall
static void setsiz();    // listsize
static void printm();    // macros
static void printh();    // history
static void loadf();     // macrofile

typedef void (*flist)();
flist operations[] = {reinstall, setsiz, printm, printh, loadf};
static int regis_num[6] = {0, 0, 0, 0, 0, 0};

node *cmdhead = NULL;
node *cmdtail = NULL;

node *pairhead = NULL;

static int listsiz = 10;    // default history size
static char *macrof = NULL; // macrofile name

static void registf(int argc, char *argv[]);

int sys_doskey(int argc, char *argv[]) {
  memset(regis_num, 0, sizeof(int) * 6);

  // according to arguments to choose which function should be performed
  registf(argc, argv);
  for (int i = 0; i < 6; ++i) {
    if (regis_num[i] == 1) {
      if (i == 0) {
        output(STDOUT_FILENO, doskeyh, strlen(doskeyh));
        return 0;
      } else if (i > 0)
        operations[i - 1]();
    }
  }
  return 0;
}

const char *doskeyh =
    "Edit the command line, recall the command, and create a macro.\n\
DOSKEY [/?] [/REINSTALL] [/LISTSIZE=size] [/MACROS] [/HISTORY]\
[/MACROFILE=filename] [macroname=[text]]\n\n\
/REINSTALL  clears the history command buffer and defined macros\n\
/LISTSIZE=size  set the buffer size of command history.\n\
/MACROS displays  all Doskey macros.\n\
/HISTORY  displays all commands stored in memory.\n\
/MACROFILE=filename specifies the macro file to install.\n\
macroname specifies the name of the macro you created.\n\
text Specifies the command to record.\n";

static void reinstall() {
  node *next;
  pair *p;
  node *cur = pairhead;
  while (cur != NULL) {
    p = (pair *)cur->p;
    next = cur->next;
    free(p);
    free(cur);
    cur = next;
  }
  pairhead = NULL;

  cur = cmdhead;
  while (cur != NULL) {
    char *tc = (char *)cur->p;
    next = cur->next;
    free(tc);
    free(cur);
    cur = next;
  }

  cmdhead = NULL;
  cmdtail = NULL;
}

static void setsiz() {
  /*
    This function is empty ,
    just for fill function poiter array
    the change of list is in regis()
  */
}

static void printm() {
  for (node *tmp = pairhead; tmp != NULL; tmp = tmp->next) {
    pair *pp = (pair *)tmp->p;
    output(STDOUT_FILENO, pp->sym, strlen(pp->sym));
    output(STDOUT_FILENO, "=", 1);
    output(STDOUT_FILENO, pp->cmd, strlen(pp->cmd));
    output(STDOUT_FILENO, "\n", 1);
  }
}

static void printh() {
  int i = 0;
  for (node *tmp = cmdhead; tmp != NULL; tmp = tmp->next) {
    if (i == listsiz)
      break;
    char *cmd = (char *)tmp->p;
    output(STDOUT_FILENO, cmd, strlen(cmd));
    output(STDOUT_FILENO, "\n", 1);
    ++i;
  }
}

static void aftereq(int macro, char *arg) {
  char *eq = strstr(arg, "=");
  if (eq != NULL) {
    if (macro == LISTSIZ)
      listsiz = atoi(eq + 1);
    else
      macrof = eq + 1;
  }
}

static void del_alias(const char *arg) {
  node **pp;
  int i = 0;
  for (pp = &pairhead; (*pp) != NULL; pp = &((*pp)->next)) {
    pair *p = (pair *)((*pp)->p);
    if (strcmp(p->sym, arg) == 0) {
      node *nextp = (*pp)->next;
      node *tmp = *pp;
      *pp = nextp;
      if (i == 0)
        pairhead = *pp;
      free(p);
      free(tmp);
      break;
    }
    ++i;
  }
}

static pair *existed(const char *arg) {
  pair *res = NULL;
  for (node *trav = pairhead; trav != NULL; trav = trav->next) {
    pair *t = (pair *)(trav->p);
    if (strcmp(t->sym, arg) == 0) {
      res = t;
      break;
    }
  }

  return res;
}

static void new_alias(char *arg, char *eq) {
  *eq = '\0';
  ++eq;
  if (*eq == '\0') {
    del_alias(arg);
    return;
  }
  pair *newp = existed(arg);
  node *newn;
  if (newp == NULL) {
    newp = malloc(sizeof(pair));
    memset(newp, 0, sizeof(pair));
    strcpy(newp->sym, arg);

    newn = malloc(sizeof(node));
    newn->p = (void *)newp;
    newn->next = NULL;
    if (pairhead == NULL)
      pairhead = newn;
    else
      push_front(&pairhead, newn);
  }
  strcpy(newp->cmd, eq);
}

static void loadf() {
  int fd = open(macrof, O_RDONLY);
  char buf[MAXLEN];
  int end;
  if (fd != -1) {
    while ((end = input(fd, buf)) > 0) {
      char *eq = strstr(buf, "=");
      if (eq != NULL)
        new_alias(buf, eq);
    }

    close(fd);
  }
}

static void registf(int argc, char *argv[]) {
  int i;
  int j;
  char *eqp;
  for (i = 0; i < argc; ++i) {
    if (argv[i][0] == '/') {
      transupper(argv[i] + 1, argv[i] + 1);
      for (j = 0; j < 6; ++j)
        if (self_strcmp(argv[i], args[j]) == 0) {
          if (j == LISTSIZ || j == MACROF)
            aftereq(j, argv[i]);
          regis_num[j] = 1;
          break;
        }
    } else if ((eqp = strstr(argv[i], "=")) != NULL)
      new_alias(argv[i], eqp);
  }
}
