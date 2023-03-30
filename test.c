#include <asm-generic/ioctls.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define BACKSPACE 0x08

int getrows() {
  struct winsize size;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, (char *)&size) < 0)
    return -1;
  return size.ws_row;
}

int main() {
  // printf("\x1b[2J\x1b[H");
  // for (int i = 0; i < 6; ++i) {
  //   int lines = getrows();
  //   for (int j = 0; j < lines - 1; ++j)
  //     printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");

  //   printf("sleep");
  //   fflush(stdout);
  //   for (int j = 0; j < 5; ++j) {
  //     printf("-");
  //     fflush(stdout);
  //     sleep(2);
  //   }
  //   printf("\n");
  // }
  // printf("sleep-------");
  // fflush(stdout);
  char bs = BACKSPACE;
  char buf[6];
  read(STDIN_FILENO, buf, 6);
  // for (int i = 0; i < 5; ++i) {
  //   write(STDIN_FILENO, &bs, 1);
  // }

  // for (int i = 0; i < 5; ++i) {
  //   read(STDIN_FILENO, &bs, 1);
  //   sleep(1);
  // }
  printf("\033[A");
  printf("---------------------------------\n");
  return 0;
}