#include "../../include/tool.h"
#include <ctype.h>
#include <string.h>

int parse(int argc, char *argv[]) {
  for (int i = 0; i < argc; ++i) {
    if (argv[i][0] == '/') {
      if (argv[i][2] == '\0') {
        argv[i][0] = argv[i][1];
        argv[i][1] = '\0';
      }
    } else
      return -1;
  }

  return 0;
}

int sys_call(const char **cmds, const char *ins, int count) {
  for (int i = 0; i < count; ++i)
    if (strcmp(cmds[i], ins) == 0)
      return i;
  return -1;
}

void transupper(char *dest, char *src) {
  int i;
  int len = strlen(src);
  for (i = 0; i < len; ++i) {
    if (src[i] == '=')
      break;
    if (islower(src[i]))
      dest[i] = (char)toupper(src[i]);
  }

  if (i == len)
    dest[i] = '\0';
}

int output(int fd, const char *msg, ssize_t n) {
  ssize_t writen;
  const char *bufp = msg;
  ssize_t wleft = n;

  while (wleft > 0) {
    if ((writen = write(fd, bufp, wleft)) < 0) {
      if (errno == EINTR)
        writen = 0;
      else
        return errno;
    }
    wleft -= writen;
    bufp += writen;
  }

  return 0;
}

int input(int fd, char *buf) {
  ssize_t nbyte;
  int nread = 0;
  int last = 1;
  while ((nbyte = read(fd, buf, 1)) != 0) {
    if (nbyte < 0 && errno != EINTR)
      return -1;
    else if (nbyte < 0 && errno == EINTR)
      continue;
    ++nread;
    if (*buf == '\n') {
      *buf = '\0';
      last = 0;
      break;
    }
    ++buf;
  }

  if (last == 1 && nread != 0) {
    *buf = '\0';
    ++nread;
  }
  return nread;
}

void push_front(node **head, node *obj) {
  obj->next = (*head);
  (*head) = obj;
}

void push_back(node **tail, node *obj) {
  (*tail)->next = obj;
  (*tail) = obj;
}

node *strnode(const char *src) {
  node *res = malloc(sizeof(node));
  char *tmp = malloc(strlen(src) + 1);
  strcpy(tmp, src);
  res->p = (void *)tmp;
  res->next = NULL;
  return res;
}

int self_strcmp(const char *input, const char *std) {
  for (int i = 0; input[i] != '\0' || std[i] != '\0'; ++i) {
    if (input[i] == '=' && std[i] == '\0')
      break;
    if (input[i] != std[i])
      return (int)(input[i] - std[i]);
  }
  return 0;
}

int compch(char a, char b, int ignore) {
  if (isalpha(a) && isalpha(b) && ignore) {
    a = toupper(a);
    b = toupper(b);
  }
  return (int)(a - b);
}

// dynamic programming
static void build_next(const char *str, int *next, int slen, int ignore) {
  next[0] = 0;
  int prefixl = 0;
  int i = 1;

  while (i < slen) {
    if (compch(str[prefixl], str[i], ignore) == 0) {
      next[i] = prefixl + 1;
      ++i;
    } else {
      if (prefixl == 0) {
        if (prefixl == 0) {
          next[i] = 0;
          ++i;
        } else
          prefixl = next[prefixl - 1];
      }
    }
  }
}

int kmp(const char *ts, const char *ps, int tlen, int plen, int ignore) {

  int next[(MAXLEN << 5)];
  build_next(ps, next, plen, ignore);
  int i = 0;
  int j = 0;
  while (i < tlen && j < plen) {
    if (compch(ts[i], ps[j], ignore) == 0) {
      ++i;
      ++j;
    } else if (j > 0)
      j = next[j - 1];
    else
      ++i;
  }

  return j == plen;
}

char *itos(int integer, char *endp) {
  *endp = '\0';
  while (integer != 0) {
    --endp;
    *endp = '0' + integer % 10;
    integer = integer / 10;
  }
  return endp;
}

void write_num(int interger) {
  char numbuf[MAXLEN];
  char *numbufp = itos(interger, &numbuf[MAXLEN - 1]);
  output(STDOUT_FILENO, numbufp, (&numbuf[MAXLEN - 1] - numbufp));
}

int nread(int fd, char *buf, int n) {
  int nleft = n;
  int nr;
  while ((nr = read(fd, buf, nleft)) != 0) {
    if (nr == -1) {
      if (errno != EINTR)
        return -1;
      nr = 0;
      continue;
    }
    nleft -= nr;
    buf += nr;
  }
  return n - nleft;
}