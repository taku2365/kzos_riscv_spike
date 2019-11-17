# RISCV environment variable must be set
RISCV = /home/suga/risc-v/toolchain
CC=/home/suga/x-tools/riscv32-hifive1-elf/bin/riscv32-hifive1-elf-gcc
#OBJCOPY=$(RISCV)/bin/riscv64-unknown-elf-objcopy
CFLAGS=-march=rv32imac -mabi=ilp32 -mcmodel=medany -nostdlib  -std=gnu11 -Wall -I.  -nostartfiles -fno-common -fno-builtin -g
#CFLAGS=-march=rv32imac -mabi=ilp32 -O2 -std=gnu11 -Wall -I. -nostartfiles -fno-common -fno-builtin
LFLAGS=-static -nostdlib -T ld.scr

TARGET=kzos

$(TARGET): startup.s intr.S main.c interrupt.c serial.c lib.c kozos.c syscall.c memory.c \
		consdrv.c command.c
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

.PHONY: clean
clean::
	rm -rf $(TARGET) *~
