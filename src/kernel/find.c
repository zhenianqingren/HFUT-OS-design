#include "../../include/tool.h"

#define ACCORDING(res) (enable[V] == 0 ? (res) != 0 : (res) == 0)
#define PRINT_PATTERN(res, s1, s2)                                             \
  (enable[X] == 1 ? (strcmp((s1), (s2)) == 0) : ACCORDING(res))
#define MAXFILE_COUNT 8
#define MAXLINE 1024
#define FIND 5
#define FIND_STR 8

#define V 0
#define C 1
#define N 2
#define I 3

#define S 1
#define X 4
#define M 5
#define T 6

#define FILE_TYPE 11

static int fds[MAXFILE_COUNT];              // descriptor of file
static const char *filename[MAXFILE_COUNT]; // name of relevant file
static int nfds = 0;                        // number of descriptors
static int legalf = 0; // legal file exists? if exists, choose the first one
static const char *args1[] = {"/V", "/C", "/N", "/I", "/?"}; // all args
static int enable[] = {0, 0, 0, 0, 0, 0, 0, 0};              // relevant arg enable
static int lines = 0;                                        // total number of lines
static int account = 0;   // total number of lines fit in standard
static char **str = NULL; // the str needed to be find in file,
                   // for findstr, it maybe multi.
static int strs = 0;

static const char *args2[] = {"/V", "/S", "/N", "/I", "/X", "/M", "/T", "/?"};
static const char *ftype[] = {"json", "txt", "c", "cpp",  "py", "bat",
                       "sh",   "md",  "h", "java", "log"};

static void varg_find(int argc, char *argv[]);
static void matchf(int fd, char *model);

static void varg_findstr(int argc, char *argv[]);
static void matchf_s(int fd);
static void findstr_p(int fd, const char *fn);
static int recursive(char *fullpath);

const char *findh;
const char *findstrh;

int sys_find(int argc, char *argv[]) {

  varg_find(argc, argv);

  if (enable[4] == 1) {
    output(STDOUT_FILENO, findh, strlen(findh));
    return 0;
  }

  if (str == NULL || nfds == 0)
    return -1;

  char *tstr = *str;
  if (nfds == 1)
    matchf(fds[0], tstr);

  if (enable[C] == 1) {
    output(fds[0], "total line: ", 12);
    write_num(account);
    output(STDOUT_FILENO, "\n", 1);
  }
  return 0;
}

int sys_findstr(int argc, char *argv[]) {
  varg_findstr(argc, argv);
  if (enable[7] == 1) {
    output(STDOUT_FILENO, findstrh, strlen(findstrh));
    return 0;
  }

  if (strs == 0)
    return -1;

  if (enable[S] == 0 && nfds != 0) {
    for (int i = 0; i < nfds; ++i) {
      findstr_p(fds[i], filename[i]);
      lines = 0;
      account = 0;
    }
  } else {
    for (int i = 0; i < nfds; ++i)
      close(fds[i]);

    char buf[(2 << 10)] = "./";
    return recursive(buf);
  }

  return 0;
}

static void findstr_p(int fd, const char *fn) {
  output(STDOUT_FILENO, fn, strlen(fn));
  output(STDOUT_FILENO, "----------------\n\n", 18);
  matchf_s(fd);
  output(STDOUT_FILENO, "----------------\n\n", 18);
}

static void matchf(int fd, char *model) {
  char buf[MAXLINE];
  char *bufp = buf;
  int rdlen;
  int mlen = strlen(model);
  while ((rdlen = input(fd, bufp)) > 0) {
    ++lines;
    if (ACCORDING(kmp(bufp, model, rdlen - 1, mlen, enable[I]))) {
      ++account;
      if (enable[C] == 0) {
        if (enable[N] == 1) {
          write_num(lines);
          output(STDOUT_FILENO, ": ", 2);
        }
        output(STDOUT_FILENO, bufp, strlen(bufp));
        output(STDOUT_FILENO, "\n", 1);
      }
    }
  }
}

static void matchf_s(int fd) {
  char buf[(MAXLINE << 1)];
  char *bufp = buf;
  int rdlen;
  int pl;
  while ((rdlen = input(fd, bufp)) > 0) {
    ++lines;
    int match_count = 0;
    int protect = 0;

    for (int i = 0; i < strs; ++i) {

      pl = strlen(str[i]);
      if (PRINT_PATTERN(kmp(bufp, str[i], rdlen - 1, pl, enable[I]), bufp,
                        str[i])) {
        if (protect == 0) {
          ++account;
          protect = 1;
        }
        ++match_count;
        if (enable[V] == 0)
          break;
      }
    }

    if ((enable[V] == 0 && match_count > 0) ||
        (enable[V] == 1 && match_count == strs)) {
      if (enable[N] == 1) {
        write_num(lines);
        output(STDOUT_FILENO, ": ", 2);
      }
      output(STDOUT_FILENO, bufp, strlen(bufp));
      output(STDOUT_FILENO, "\n", 1);
    }
  }
}

static void strextract(char *line) {
  int l = strlen(line);
  if (line[l - 1] != '"' || strs != 0) // only take first find pattern
    return;
  line[l - 1] = '\0';
  ++line;
  str = malloc((2 << 10));
  while ((str[strs] = strsep(&line, " ")) != NULL)
    ++strs;
}

static void openf(char *filen) {
  while ((fds[nfds] = open(filen, O_RDONLY)) < 0) {
    if (errno == EINTR)
      continue;
    else
      break;
  }
  if (fds[nfds] > 0) {
    filename[nfds] = filen;
    ++nfds;
  }
}

static void regis_enable(const char *para, int macro) {
  const char **args = macro == FIND ? args1 : args2;
  for (int j = 0; j < macro; ++j)
    if (j != T && strcmp(para, args[j]) == 0) {
      enable[j] = 1;
      break;
    }
}

static void varg_find(int argc, char *argv[]) {
  for (int i = 0; i < argc; ++i) {
    if (argv[i][0] == '/')
      regis_enable(argv[i], FIND);
    else if (argv[i][0] == '"') {
      int l = strlen(argv[i]);
      if (argv[i][l - 1] == '"') { //"......"
        argv[i][l - 1] = '\0';
        ++argv[i];
        str = &argv[i];
      }
    } else if (nfds == 0)
      openf(argv[i]);
  }
}

static void strtrans(char *left, char *right) {
  while (left != right) {

    if (*left == '\\' && *(left + 1) == '"') {
      char *t = left;
      while (t != right - 1) {
        *t = *(t + 1);
        ++t;
      }
      --right;
      *right = '\0';
    }

    if (*left == '\0')
      *left = ' ';

    ++left;
  }
}

// process /T:"...." in which the content of str can involve space, but " should
// be involved with '\'
static int process_spacestr(int argc, char **argv, int ind) {
  char *left = argv[ind] + 4;
  char *right;
  while (ind < argc) {
    int l = strlen(argv[ind]);
    if (argv[ind][l - 1] == '"' && argv[ind][l - 2] != '\\' &&
        ((argv[ind] + l) != left)) {
      /*from left to right*/
      right = argv[ind] + l - 1;
      *right = '\0';
      strtrans(left, right);
      if (*left != '\0') {
        if (str == NULL)
          str = malloc((2 << 10));
        str[strs++] = left;
      }
      break;
    }
    ++ind;
  }
  return ind;
}

static void varg_findstr(int argc, char *argv[]) {
  for (int i = 0; i < argc; ++i) {
    if (argv[i][0] == '/') {
      if (strncmp(argv[i], "/T:\"", 4) == 0)
        i = process_spacestr(argc, argv, i);
      else
        regis_enable(argv[i], FIND_STR);
    } else if (argv[i][0] == '"') {
      int l = strlen(argv[i]);
      if (argv[i][l - 1] == '"') { //"......"
        if (str == NULL)
          str = malloc((2 << 10));
        argv[i][l - 1] = '\0';
        ++argv[i];
        str[strs++] = argv[i];
      }
    } else
      openf(argv[i]);
  }
}

static int istext(const char *fullpath) {

  char *type = rindex(fullpath, '.') + 1;
  for (int i = 0; i < FILE_TYPE; ++i)
    if (strcmp(type, ftype[i]) == 0)
      return 0;
  return -1;
}

static int recursive(char *fullpath) {

  struct stat statbuf;
  struct dirent *dirp;
  DIR *dp;
  int ret;
  int n;

  int l = strlen(fullpath);
  if ((dp = opendir(fullpath)) != NULL) {
    while ((dirp = readdir(dp)) != NULL) {
      if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
        continue;
      strcpy(&fullpath[l], dirp->d_name);

      if (stat(fullpath, &statbuf) < 0)
        return errno;

      mode_t mode = statbuf.st_mode;
      if (S_ISREG(mode)) {
        if (istext(fullpath) == 0) {
          int fd = open(fullpath, O_RDONLY);
          if (fd < 0)
            return errno;
          findstr_p(fd, fullpath);
          close(fd);
          lines = 0;
        }
      } else {
        n = strlen(fullpath);
        fullpath[n] = '/';
        fullpath[n + 1] = '\0';
        ret = recursive(fullpath);
        if (ret != 0)
          return ret;
      }
    }
  }

  return 0;
}

const char *findh = "Search for strings in the file.\n\
FIND [/V] [/C] [/N] [/I] \"string\" path\n\n\
/V Displays all lines that do not contain the specified string.\n\
/C Displays only the number of lines containing the string.\n\
/N Displays the line number.\n\
/I Ignore case when searching for strings.\n\
\"string\" specifies the text string to search.\n\
path specifies the file to search.\n";

const char *findstrh = "Find the string in the file.\n\
FINDSTR [/S] [/I] [/X] [/V] [/N]\n\
[/T:string] [/G:file] strings [[drive:][path]filename[ ...]]\n\n\
/S searches for matching files in the current directory and all subdirectories.\n\
/I Specifies that the search is case-insensitive.\n\
/X prints exactly matched lines.\n\
/V only prints lines that do not contain matches.\n\
/N Print the number of lines before each matching line.\n\
/T Specifies the printed string (can contain spaces)\n\
strings The text to find.\n\
path specifies the file to find.\n\
Unless the parameter has the/T prefix, separate the search string with spaces\n";
