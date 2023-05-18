#include "../../include/tool.h"
#include <string.h>
#include <unistd.h>

#define L 0
#define A 1
#define N 2
#define C 3
#define D 4
#define T 5
#define W 6

#define COMP 4
#define FC 7

#define BUFSIZE 64
#define ADDRWITHSPACE 12
#define FNAMESPACE 3

static const char *args[] = {"/L", "/A", "/N", "/C", "/D", "/T", "/W", "/?"};

const char *comph;
const char *fch;

static int fd1 = -1;
static int fd2 = -1;
static const char *fn1 = NULL;
static const char *fn2 = NULL;

static void varg(int argc, char *argv[], int macro);
static void regis_enable(const char *arg, int macro);
static void openf(const char *fn);

// only compare whether equal or not
static int cmp1(char c1, char c2); // ascii compare
static int cmp2(char c1, char c2); // binary compare
static int enable[] = {0, 0, 0, 0, 0, 0, 0, 0};

static int ascii(int macro);
static int comp_bin();
static void fc_bin();
static void prin2line(char *line1, char *line2, int line);

static void tabtrans(char *line);
static void del_mspace(char *line);

static void fcbuf(char *buf1, char *buf2, unsigned int base, int n1, int n2);
static void transnum(char *last, unsigned int addr, int mod,
                     char (*transch)(int));

static void print_diff(unsigned int base, unsigned int ind, char c1, char c2,
                       int c1p, int c2p);

static unsigned long diff = 0;
static int diffline = 0;
static int nl = -1;

int sys_comp(int argc, char *argv[])
{

  varg(argc, argv, COMP);
  if (enable[7] == 1)
  {
    output(STDOUT_FILENO, comph, strlen(comph));
    return 0;
  }

  if (fd1 == -1 || fd2 == -1)
    return -1;

  if (enable[A] == 1)
  {
    ascii(COMP);
    if (enable[L] == 1)
    {
      if (enable[N] == 0 && diffline != 0)
        write_num(diffline);
      else if (enable[N] == 1 && diffline != 0)
        write_num(1);
      else
        output(STDOUT_FILENO, "0", 1);
      output(STDOUT_FILENO, "\n", 1);
    }
  }
  else
  {
    comp_bin();
  }
  if (diff != 0 || diffline != 0)
    output(STDOUT_FILENO, "two files are different!\n", 25);
  else
    output(STDOUT_FILENO, "two files are same!\n", 20);

  close(fd1);
  close(fd2);
  return 0;
}

int sys_fc(int argc, char *argv[])
{
  varg(argc, argv, FC);
  if (enable[7] == 1)
  {
    output(STDOUT_FILENO, fch, strlen(fch));
    return 0;
  }

  output(STDOUT_FILENO, "            ", ADDRWITHSPACE);
  output(STDOUT_FILENO, "file1   ", 8);
  output(STDOUT_FILENO, "file2\n", 6);

  if (fd1 == -1 || fd2 == -1)
    return -1;

  if (enable[A] == 1)
  {
    ascii(FC);
    if (enable[L] == 1)
    {
      if (enable[N] == 0 && diffline != 0)
        write_num(diffline);
      else if (enable[N] == 1 && diffline != 0)
        write_num(1);
      else
        output(STDOUT_FILENO, "0", 1);
      output(STDOUT_FILENO, "\n", 1);
    }
  }
  else
  {
    fc_bin();
  }

  if (diff != 0 || diffline != 0)
    output(STDOUT_FILENO, "two files are different!\n", 25);
  else
    output(STDOUT_FILENO, "two files are same!\n", 20);
  return 0;
}

static void regis_enable(const char *arg, int macro)
{
  for (int i = 0; i < macro; ++i)
    if (self_strcmp(arg, args[i]) == 0)
    {
      enable[i] = 1;
      break;
    }
    else if (strcmp(arg, "/?") == 0)
    {
      enable[7] = 1;
      break;
    }
}

static void openf(const char *fn)
{
  int fd;

  while ((fd = open(fn, O_RDONLY)) == -1)
  {
    if (errno != EINTR)
      break;
  }
  if (fd1 == -1)
  {
    fd1 = fd;
    fn1 = fn;
    return;
  }
  if (fd2 == -1)
  {
    fd2 = fd;
    fn2 = fn;
  }
}

static void varg(int argc, char *argv[], int macro)
{
  for (int i = 0; i < argc; ++i)
  {
    if (argv[i][0] == '/')
    {
      regis_enable(argv[i], macro);

      if (argv[i][1] == 'N' && argv[i][2] == '=')
        nl = atoi(&argv[i][3]);
    }
    else
      openf(argv[i]);
  }
}

static int cmp1(char c1, char c2)
{ // ascii from 0 to 127
  if (c1 & 0x80 || c2 & 0x80)
    return -1;

  if (enable[C] == 1)
  {
    c1 = toupper(c1);
    c2 = toupper(c2);
  }

  return c1 & c2;
}

static int cmp2(char c1, char c2) { return c1 & c2; }

static int compbuf(char *buf1, char *buf2, int n)
{
  int i;
  for (i = 0; i < n; ++i)
    if (buf1[i] != buf2[i])
    {
      ++diff;
      break;
    }

  return diff;
}

static int linecmp(char *s1, char *s2)
{
  int l1 = strlen(s1);
  int l2 = strlen(s2);

  for (int i = 0; i < l1 && i < l2; ++i)
    if (compch(s1[i], s2[i], enable[C]) != 0)
      return 1;

  return l1 - l2 == 0 ? 0 : 1;
}

static void tabtrans(char *line)
{
  while (*line != '\0')
  {
    if (*line == '\t')
      *line = ' ';
    ++line;
  }
}

static void del_mspace(char *line)
{
  char *faster = line + 1;
  while (1)
  {
    if ((*line == ' ' || *line == '\t') && *line == *faster)
      ++faster;
    else
    {
      ++line;
      *line = *faster;
      ++faster;
    }

    if (*line == '\0')
      break;
  }
}

static void prin2line(char *line1, char *line2, int line)
{
  write_num(line);
  output(STDOUT_FILENO, ":\n", 2);
  int l = strlen(line1);
  line1[l] = '\n';

  if (l != 0)
    output(STDOUT_FILENO, line1, l + 1);
  else
    output(STDOUT_FILENO, "null\n", 5);

  l = strlen(line2);
  line2[l] = '\n';
  if (l != 0)
    output(STDOUT_FILENO, line2, l + 1);
  else
    output(STDOUT_FILENO, "null\n", 5);
}

static int ascii(int macro)
{
  char buf1[(MAXLEN << 5)];
  char buf2[(MAXLEN << 5)];
  int n1 = 1, n2 = 1;

  int lines = 0; // line which is going to compared
  while (n1 != 0 || n2 != 0)
  {
    n1 = input(fd1, buf1);
    n2 = input(fd2, buf2);
    ++lines;
    if (n1 == 0)
      buf1[0] = '\0';
    if (n2 == 0)
      buf2[0] = '\0';

    if (n1 == 0 && n2 == 0)
      break;
    if (enable[T] == 1)
    {
      tabtrans(buf1);
      tabtrans(buf2);
    }

    if (enable[W] == 1)
    {
      if (buf1[0] != '\0' && buf1[1] != '\0')
        del_mspace(buf1);

      if (buf2[0] != '\0' && buf2[1] != '\0')
        del_mspace(buf2);
    }

    if (enable[N] == 0 || (enable[N] == 1 && lines == nl))
      diffline += linecmp(buf1, buf2);
    if (macro == FC && enable[L] == 1 &&
        (enable[N] == 0 || (enable[N] == 1 && lines == nl)))
      prin2line(buf1, buf2, lines);
  }

  return 0;
}

static int comp_bin()
{

  int nread1 = 1;
  int nread2 = 1;
  //   avoid segmentation fault
  char ch1[BUFSIZE << 1];
  char ch2[BUFSIZE << 1];
  while (nread1 != 0 || nread2 != 0)
  {
    nread1 = nread(fd1, ch1, BUFSIZE);
    nread2 = nread(fd2, ch2, BUFSIZE);
    if (nread1 != nread2)
    {
      ++diff;
      return 0;
    }
    if (compbuf(ch1, ch2, nread1) > 0)
      return 0;
  }

  return 0;
}

char hexdigit(int digit) { return digit > 9 ? 'a' + digit - 10 : digit + '0'; }

char decdigit(int digit) { return '0' + digit; }

static void transnum(char *last, unsigned int addr, int mod,
                     char (*transch)(int))
{
  while (addr != 0)
  {
    *last = transch(addr % mod);
    addr /= mod;
    --last;
  }
}

static void print_diff(unsigned int base, unsigned int ind, char c1, char c2,
                       int c1p, int c2p)
{
  unsigned int addr = base * BUFSIZE + ind;
  char buf[16] = "0x00000000: ";
  transnum(&buf[9], addr, 16, hexdigit);
  output(STDOUT_FILENO, buf, ADDRWITHSPACE);
  char num1[8 << 1];
  char num2[8 << 1];
  if (enable[D] == 0)
  {
    strcpy(num1, "0x00    ");
    strcpy(num2, "0x00\n");
    if (c1p > 0)
      transnum(&num1[3], c1 & 0xff, 16, hexdigit);
    if (c2p > 0)
      transnum(&num2[3], c2 & 0xff, 16, hexdigit);
  }
  else
  {
    strcpy(num1, "0000    ");
    strcpy(num2, "0000\n");
    if (c1p > 0)
      transnum(&num1[3], c1 & 0xff, 10, decdigit);
    if (c2p > 0)
      transnum(&num2[3], c2 & 0xff, 10, decdigit);
  }

  // debug
  if (strncmp("7295", num1, 4) == 0)
  {
    num1[15] = 'a';
  }

  if (c1p > 0)
    output(STDOUT_FILENO, num1, 8);
  else
    output(STDOUT_FILENO, "null    ", 8);

  if (c2p > 0)
    output(STDOUT_FILENO, num2, 5);
  else
    output(STDOUT_FILENO, "null\n", 5);
}

static void fcbuf(char *buf1, char *buf2, unsigned int base, int n1, int n2)
{
  int i;
  for (i = 0; i < n1 || i < n2; ++i)
  {
    if (buf1[i] != buf2[i])
    {
      print_diff(base, i, buf1[i], buf2[i], n1, n2);
      ++diff;
      --n1;
      --n2;
    }
  }
}

static void fc_bin()
{

  int nread1 = 1;
  int nread2 = 1;
  //   avoid segmentation fault
  char ch1[BUFSIZE << 1];
  char ch2[BUFSIZE << 1];
  int base = 0;
  while (nread1 != 0 || nread2 != 0)
  {
    nread1 = nread(fd1, ch1, BUFSIZE);
    nread2 = nread(fd2, ch2, BUFSIZE);
    fcbuf(ch1, ch2, base, nread1, nread2);
    ++base;
  }
}

const char *comph = "Compare the contents of two files.\n\
COMP [file1] [file2] [/A] [/L] [/N=number] [/C]\n\n\
file1   specifies the location and name of the first file to compare.\n\
File2   specifies the location and name of the second file to compare.\n\
/L   displays the different number of rows.\n\
/A   Compare in ASCII (default is binary)\n\
/N=number   when is compared in ASCII, only the number of lines specified by N in each file are compared.\n\
/C   ASCII letters are not case-sensitive when comparing files.\n";

const char *fch = "Compare two files and show the differences between them\n\
FC [/A] [/L] [/N=number] [/T] [/W] file1 file2\n\n\
/D    displays different places in decimal form (default is hexadecimal).\n\
/C    Compares in ASCII regardless of case.\n\
/A    Compare files as ASCII text.\n\
/L    Displays different number of lines when compared in ASCII.\n\
/T    Converts tabs to spaces.\n\
/W    Compresses white space for comparison (continuous tabs and continuous spaces).\n\
/N=number   when is compared in ASCII, only the number of lines specified by N in each file are compared.\n\
file1    specifies the first file to compare.\n\
file2    specifies the second file to compare.\n";
