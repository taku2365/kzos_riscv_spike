#!/bin/bash

rm result.txt
rm result.dump

make clean

make kzos

riscv32-hifive1-elf-objdump -D kzos >& result.dump

#spike  -l -m0x80000000:0x50000000 -pc=80000000 --isa=rv32imac kzos 2>&1 | tee result.txt
spike  -l -m0x80000000:0x50000000 -pc=80000000 --isa=rv32imac kzos > result.txt 2>&1 
#spike  -m0x80000000:0x50000000 -pc=80000000 -d  --isa=rv32imac kzos
#spike   -m0x80000000:0x50000000 -pc=80000000 --isa=rv32imac  kzos

