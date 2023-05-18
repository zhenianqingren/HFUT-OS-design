#ifndef SYS_CALLS
#define SYS_CALLS
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define CMDCOUNT 11
#define SYS_cls 0
#define SYS_date 1
#define SYS_time 2
#define SYS_doskey 3
#define SYS_find 4
#define SYS_findstr 5
#define SYS_comp 6
#define SYS_fc 7
#define SYS_exit 8
#define SYS_help 9
#define SYS_more 10
#define HOME_DIR "user@ubuntu:~/>"

#define INPUTBUFFER 1024
#define MAXARGS 512

extern int sys_cls(int argc, char *argv[]);
extern int sys_date(int argc, char *argv[]);
extern int sys_time(int argc, char *argv[]);
extern int sys_doskey(int argc, char *argv[]);
extern int sys_find(int argc, char *argv[]);
extern int sys_findstr(int argc, char *argv[]);
extern int sys_comp(int argc, char *argv[]);
extern int sys_fc(int argc, char *argv[]);
extern int sys_exit(int argc, char *argv[]);
extern int sys_help(int argc, char *argv[]);
extern int sys_more(int argc, char *argv[]);

void err_print();

#endif