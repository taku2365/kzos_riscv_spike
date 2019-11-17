#include "defines.h"
#include "kozos.h"
#include "lib.h"

int test08_1_main(int argc, char *argv[])
{
  char buf[32];

  puts_spike("test08_1 started.\n");

  while (1) {
    puts_spike("> ");
    gets((unsigned char *)buf);

    if (!strncmp(buf, "echo ", 5)) {
      puts_spike(buf + 5);
      puts_spike("\n");
    } else if (!strcmp(buf, "exit")) {
      break;
    } else {
      puts_spike("unknown.\n");
    }
  }

  puts_spike("test08_1 exit.\n");

  return 0;
}
  
  
