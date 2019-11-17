#include "defines.h"
#include "kozos.h"
#include "lib.h"

int test09_2_main(int argc, char *argv[])
{
  puts_spike("test09_2 started.\n");

  puts_spike("test09_2 sleep in.\n");
  kz_sleep();
  puts_spike("test09_2 sleep out.\n");

  puts_spike("test09_2 chpri in.\n");
  kz_chpri(3);
  puts_spike("test09_2 chpri out.\n");

  puts_spike("test09_2 wait in.\n");
  kz_wait();
  puts_spike("test09_2 wait out.\n");

  puts_spike("test09_2 exit.\n");

  return 0;
}
