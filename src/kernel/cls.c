#include "../../include/tool.h"

const char *cls_sym = "\x1b[2J\x1b[H";
const char *clsh = "clear the whole screen\n";

int sys_cls(int argc, char *argv[]) {

  if (parse(argc, argv) != 0)
    return -1;

  const char *bufp = cls_sym;
  for (int i = 0; i < argc; ++i)
    if (argv[i][0] == '?')
      bufp = clsh;
  ssize_t total = strlen(bufp);

  return output(STDOUT_FILENO, bufp, total);
}