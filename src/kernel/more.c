#include "../../include/tool.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#define BACKSPACE 0x08

const char *moreh;
const char *info = "MORE:";
const char *erase = "\033[A";
char backspace[6];

int startn = -1; // from which line begin to show
int ln = 0;      // whether show line num or not

int fd = -1;
static int getrows();
static void varg(int argc, char *argv[]);
static int print_oneline(); // if the return value is 1,
                            // then arrive the end of the file

static void getch();

int control = -1;

int sys_more(int argc, char *argv[]) {
  memset(backspace, BACKSPACE, 6);
  varg(argc, argv);

  if (fd == -1)
    return -1;

  if (fd == -2) {
    output(STDOUT_FILENO, moreh, strlen(moreh));
    return 0;
  }

  int len = strlen(cls_sym);
  output(STDOUT_FILENO, cls_sym, len); // clear the screen

  int lines = 1;
  while (1) {
    int pl = getrows();
    int res;
    int li = control == -1 ? pl : (control + 1);

    for (int i = 1; i < li; ++i) {
      if (ln != 0 && (startn == -1 || (startn != -1 && startn <= lines))) {
        write_num(lines);
        output(STDOUT_FILENO, ":", 1);
      }

      if (startn == -1 || (startn != -1 && startn <= lines))
        res = print_oneline();
      if (res == 1)
        return 0;
      if (res == -1)
        return -1;
      ++lines;
    }
    control = -1;
    output(STDOUT_FILENO, info, 5);
    getch();
  }
  return 0;
}

static int getrows() {
  struct winsize size;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, (char *)&size) < 0)
    return -1;
  return size.ws_row;
}

static void openf(const char *fn) {
  while ((fd = open(fn, O_RDONLY)) == -1) {
    if (errno != EINTR)
      break;
  }
}

static void varg(int argc, char *argv[]) {
  for (int i = 0; i < argc; ++i) {
    if (strcmp(argv[i], "/=") == 0)
      ln = 1;
    else if (self_strcmp(argv[i], "/N") == 0) {
      char *eq = index(argv[i], '=');
      startn = atoi(eq + 1);
    } else if (strcmp(argv[i], "/?") == 0)
      fd = -2;
    else
      openf(argv[i]);
  }
}

static int print_oneline() {
  int end = 1;
  ssize_t nbyte;

  char ch;
  while ((nbyte = read(fd, &ch, 1)) != 0) {
    if (nbyte < 0 && errno != EINTR)
      return -1;
    else if (nbyte < 0 && errno == EINTR)
      continue;
    write(STDOUT_FILENO, &ch, 1);
    if (ch == '\n') {
      end = 0;
      break;
    }
  }

  if (end == 1)
    return 1;
  return 0;
}

static void getch() {
  char ch;
  char backspace = BACKSPACE;
  while (1) {
    nread(STDIN_FILENO, &ch, 1);
    if (ch == ' ')
      break;
    if (isdigit(ch)) {
      control = ch - '0';
      if (control >= 1 && control <= 9)
        break;
    }
    if (ch == 'q')
      exit(0);
  }

  output(STDOUT_FILENO, erase, strlen(erase));
}

const char *moreh = "Display the output screen by screen.\n\
MORE [/=] [/N=n] filename\n\n\
filename   Specifies the file to display one screen at a time.\n\
/N=n   Display the first file from line n\n\
/=   Display line number\n\
Internal options:\n\
space   continue output\n\
[1~9]   Specify the number of output lines\n\
q   exit\n";
