#include "defines.h"
#include "serial.h"
#include "lib.h"

// memory関連

void *memset(void *b, int c, long len)
{
  char *p;
  for (p = b; len > 0; len--)
    *(p++) = c;

  return b;
}

void *memcpy(void *dst, const void *src, long len)
{
  char *d = dst;
  const char *s = src;
  for (; len > 0; len--)
    *(d++) = *(s++);

  return dst;
}

int memcmp(const void *b1, const void *b2, long len)
{
  const char *p1 = b1, *p2 = b2;
  for (; len > 0; len--) {
    if (*p1 != *p2)
      return (*p1 > *p2) ? 1 : -1;
  
    p1++;
    p2++;
  }

  return 0;
}

// 文字列関連

int strlen(const char * s)
{
  int len;
  for (len = 0; *s; s++, len++)
    ;

  return len;
}

char *strcpy(char *dst, const char *src)
{
  char *d = dst;
  for (;; dst++, src++) {
    *dst = *src;
    if (!*src) break;
  }

  return d;
}

int strcmp(const char *s1, const char *s2)
{
  while (*s1 || *s2) {
    if (*s1 != *s2)
      return (*s1 > *s2) ? 1 : -1;

    s1++;
    s2++;
  }

  return 0;
}

int strncmp(const char *s1, const char *s2, int len)
{
  while ((*s1 || *s2) && (len > 0)) {
    if (*s1 != *s2)
      return (*s1 > *s2) ? 1 : -1;
    
    s1++;
    s2++;
    len--;
  }

  return 0;
}

volatile uint64_t tohost __attribute__((aligned(64)));
volatile uint64_t fromhost __attribute__((aligned(64)));

uint64_t zeroExtend(long val)
{
	uint64_t ret = val;
	#if __riscv_xlen == 32
		ret = (0x00000000ffffffff & val);
	#endif
	return ret;
}

/* Relay syscall to host */
uint64_t prvSyscallToHost(long which, long arg0, long arg1, long arg2)
{
	volatile uint64_t magic_mem[8] __attribute__((aligned(64)));
//    volatile uint64_t oldfromhost;
	magic_mem[0] = zeroExtend(which);
	magic_mem[1] = zeroExtend(arg0);
	magic_mem[2] = zeroExtend(arg1);
	magic_mem[3] = zeroExtend(arg2);
	__sync_synchronize();
    tohost = zeroExtend(magic_mem);
//    do
//    {
//        oldfromhost = fromhost;
//        fromhost = 0;
//    } while (oldfromhost == 0);
	return magic_mem[0];
}



int putc(char c)
{
  if (c == '\n')
    serial_send_byte(SERIAL_DEFAULT_DEVICE, '\r');

  return serial_send_byte(SERIAL_DEFAULT_DEVICE, c);
}

unsigned char getc(void)
{
  unsigned char c = serial_recv_byte(SERIAL_DEFAULT_DEVICE);
  c = (c == '\r') ? '\n' : c;
  putc(c);			/* エコー・バック */
  return c;
}

int puts(const char *str)
{
  while (*str)
    putc(*(str++));

  return 0;
}

int  puts_spike(const char *str)
{

int returnValue = 0;
int static val[100];

returnValue = prvSyscallToHost(SYS_write, 1, (long) str, strlen(str));
for(int j=0;j<1;j++){
for(int i=0;i<10000;i++){
  int j = i+i*2+i*3;
  val[i/100] = j;
}
}

return 0;

}

int gets(unsigned char *buf)
{
  int i = 0;
  unsigned char c;

  do {
    c = getc();
    if (c == '\n')
      c = '\0';
    buf[i++] = c;
  } while (c);

  return i - 1;
}


int putxval(unsigned long value, int column)
{
  char buf[9];
  char *p;

  p = buf + sizeof(buf) - 1;
  *(p--) = '\0';

  if (!value && !column)
    column++;

  while (value || column) {
    *(p--) = "0123456789abcdef"[value & 0xf];
    value >>= 4;
    if (column) column--;
  }

  puts_spike(p + 1);

  return 0;
}
