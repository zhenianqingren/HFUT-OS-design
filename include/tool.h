#ifndef TOOL_H
#define TOOL_H
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

#define MAXLEN 32

#define PRE 32
#define NEX 64

int parse(int argc, char *argv[]);
int output(int fd, const char *msg, ssize_t n);
int input(int fd, char *buf);
int nread(int fd, char *buf, int n);

// doskey structure
typedef struct pair
{
  char sym[MAXLEN];
  char cmd[MAXLEN];
} pair;

// list node with head insert
typedef struct node
{
  void *p;
  struct node *pre;
  struct node *next;
} node;

extern node *cmdhead;
extern node *cmdtail;
extern node *pairhead;
extern const char *cls_sym;

extern const char *clsh;
extern const char *dth;
extern const char *doskeyh;
extern const char *findh;
extern const char *findstrh;
extern const char *comph;
extern const char *fch;
extern const char *exith;
extern const char *helph;
extern const char *moreh;

void transupper(char *dest, char *src);  // argument from lower to upper, which
                                         // is convinient for comparing
void push_front(node **head, node *obj); // list macros
void push_back(node **tail, node *obj);  // list history
node *strnode(const char *);             // new history

int self_strcmp(const char *input,
                const char *std); // compare parameter before =

int kmp(const char *ts, const char *ps, int tlen, int plen,
        int ignore);                    // kmp algorithm
int compch(char a, char b, int ignore); // compare two characters and ignore
                                        // upper or lower(depend on ignore)

char *itos(int integer, char *endp);
void write_num(int interger);
int sys_call(const char **cmds, const char *ins, int count);
int tty_cbreak(int fd);
int tty_reset(int fd);

#endif