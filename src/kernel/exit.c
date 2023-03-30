#include "../../include/tool.h"

const char *exith;

int sys_exit(int argc, char *argv[]) {
  int exit_sym = 1;
  int exitCode = 0;
  for (int i = 0; i < argc; ++i) {
    if (strcmp("/?", argv[i]) == 0) {
      output(STDOUT_FILENO, exith, strlen(exith));
      exit_sym = 0;
    }
    if (argv[i][1] == '\0' && isdigit(argv[i][0]))
      exitCode = argv[i][0] - '0';
  }

  if (exit_sym == 1)
    exit(exitCode);

  return -1;
}

const char *exith = "exit the current shell.\n\
exit [/?] [exitCode]\n\
If exitCode(between 0 and 9) is specified, when you exit the shell,\
that number will be set as process exit code.\n";

