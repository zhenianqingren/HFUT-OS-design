#include "../../include/tool.h"
#define BUFFERSIZE 128
const char *dth = "Displays or sets the date/time.\nDATE/TIME [/T | date/time].\n\
To display the current date/time setting and prompt for entering a new date/time, type\
 DATE/TIME without parameters. \nTo keep the existing date/time, press Enter.\n\
This switch indicates that the command only outputs the \
current date/time without prompting for a new date/time\n";

static char strtime[BUFFERSIZE];
static const char *wbuf = strtime;
static int set = 1;
static struct tm *_time;
static time_t timet;

static int varg(int argc, char *argv[]) {
  if (parse(argc, argv) != 0)
    return -1;
  for (int i = 0; i < argc; ++i) {
    if (argv[i][0] == '?') {
      wbuf = dth;
      set = 0;
      break;
    }
    if (argv[i][0] == 't')
      set = 0;
  }

  return 0;
}

static int transnum(char **strn_addr, char delim) {
  int res = 0;
  while (*(*strn_addr) != delim) {
    if (*(*strn_addr) == '\0')
      break;

    if (isdigit(*(*strn_addr)) == 0)
      return -1;
    res = res * 10 + (*(*strn_addr)) - '0';
    ++(*strn_addr);
  }
  ++(*strn_addr);
  return res;
}
/*
The Ubuntu have two clocks: Real Time Clock(RTC,or hardware clock) and
System Clock(or software clock). When the system power off, RTC will start
which powered by battery. When the system start, the system will synchronize
the System Clock with RTC. But this may be not accurate, if you have set some
time synchronization services like NTP, it will calibrate the offset. Then the
system will only use the System Clock as time resource to deal with something,
like interrupt.

If your system have NTP or SNTP service, the change don't work. You have to
close these services. You can use the commands: systemctl status ntpd,
systemctl status chronyd, systemctl status systemd-timesyncd to check whether
your system have installed these services. I use timedatectl set-ntp false to
close the NTP service. You must note that the settimeofday function can only
change the System Clock. The date command use the System Clock, and hwclock
use RTC. This means that date command can show the change, but hwclock
command can't.

timedatectl set-ntp true
timedatectl set-ntp false
*/

static size_t print_t(const char *format) {
  if (wbuf == strtime) {
    // transform date formate readable
    timet = time(NULL);
    _time = localtime(&timet);
    strftime(strtime, BUFFERSIZE, format, _time);
  }

  ssize_t total = strlen(wbuf);
  output(STDOUT_FILENO, wbuf, total);
  return total;
}

static int setnewt(const char *prompt, size_t offset, int *newt, char delim) {
  // reset current time
  output(STDOUT_FILENO, prompt, strlen(prompt));
  char *bufp = strtime + offset;
  if (input(STDIN_FILENO, bufp) < 0)
    return -1;

  // only \n don't reset time
  newt[0] = transnum(&bufp, delim);
  if (newt[0] == 0)
    return 0;

  newt[1] = transnum(&bufp, delim);
  newt[2] = transnum(&bufp, delim);

  if (newt[0] == -1 || newt[1] == -1 || newt[2] == -1)
    return -1;

  return 0;
}

int sys_date(int argc, char *argv[]) {

  if (varg(argc, argv) != 0)
    return -1;

  size_t offset = print_t("%Y/%m/%d %A\n");

  if (set == 1) {
    // reset current time
    int newt[3];
    if (setnewt("input new time:(year/month/day): ", offset, newt, '/') != 0)
      return -1;
    if (newt[0] == 0)
      return 0;

    _time->tm_year = newt[0] - 1900;
    _time->tm_mon = newt[1] - 1;
    _time->tm_mday = newt[2];

    timet = mktime(_time);
    struct timeval tv = {timet, 0};
    if (settimeofday(&tv, NULL) == -1)
      return errno;
  }

  return 0;
}

int sys_time(int argc, char *argv[]) {
  if (varg(argc, argv) != 0)
    return -1;

  size_t offset = print_t("current time: %H:%M:%S\n");

  if (set == 1) {
    // reset current time
    int newt[3];
    if (setnewt("input new time:(hour:minute:second): ", offset, newt, ':') !=
        0)
      return -1;
    if (newt[0] == 0)
      return 0;

    _time->tm_hour = newt[0];
    _time->tm_min = newt[1];
    _time->tm_sec = newt[2];

    timet = mktime(_time);
    struct timeval tv = {timet, 0};
    if (settimeofday(&tv, NULL) == -1)
      return errno;
  }

  return 0;
}