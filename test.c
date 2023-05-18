#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

void backspace()
{
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size); // get terminal size
  int col = size.ws_col;

  // move cursor back by one space
  asm("movl $1, %%edx\n\t"
      "movl $0, %%eax\n\t"
      "int $0x80\n\t"
      :
      :
      : "edx", "eax");

  // clear existing output at corresponding position
  asm("movl $1, %%edx\n\t"
      "movl $0x08, %%eax\n\t"
      "int $0x80\n\t"
      "movl $1, %%edx\n\t"
      "movl $32, %%eax\n\t"
      "int $0x80\n\t"
      "movl $1, %%edx\n\t"
      "movl $0, %%eax\n\t"
      "int $0x80\n\t"
      "movl %0, %%edx\n\t"
      "movl $0, %%eax\n\t"
      "int $0x80\n\t"
      :
      : "r"(col - 1)
      : "edx", "eax");
}

int main()
{
  printf("Enter some text: ");
  fflush(stdout);

  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt); // save old terminal settings
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);        // disable canonical mode and echo
  tcsetattr(STDIN_FILENO, TCSANOW, &newt); // apply new terminal settings

  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != '\n')
  {
    if (c == 0x08)
    { // Backspace key
      backspace();
    }
    else
    {
      putchar(c);
    }
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old terminal settings
  printf("\n");
  return 0;
}