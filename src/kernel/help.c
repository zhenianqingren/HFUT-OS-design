#include "../../include/tool.h"
#define CMDCOUNT 11

const char *cmdset[CMDCOUNT] = {"CLS",  "DATE",    "TIME", "DOSKEY",
                                "FIND", "FINDSTR", "COMP", "FC",
                                "EXIT", "HELP",    "MORE"};
const char *helph;

static const char *cmdmsg[CMDCOUNT];
static void init();

int sys_help(int argc, char *argv[]) {
  init();
  for (int i = 0; i < argc; ++i)
    transupper(argv[i], argv[i]);

  int sys_num = 9;
  for (int i = 0; i < CMDCOUNT; ++i) {
    if ((sys_num = sys_call(cmdset, argv[i], CMDCOUNT)) != -1)
      break;
  }

  if (sys_num == -1)
    return -1;

  output(STDOUT_FILENO, cmdmsg[sys_num], strlen(cmdmsg[sys_num]));
  return 0;
}

const char *helph = "Provides help information for commands.\n\
HELP [command]\n\n\
command   displays help information for this command.\n";

static void init() {
  cmdmsg[0] = clsh;
  cmdmsg[1] = dth;
  cmdmsg[2] = dth;
  cmdmsg[3] = doskeyh;
  cmdmsg[4] = findh;
  cmdmsg[5] = findstrh;
  cmdmsg[6] = comph;
  cmdmsg[7] = fch;
  cmdmsg[8] = exith;
  cmdmsg[9] = helph;
  cmdmsg[10] = moreh;
}
