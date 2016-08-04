#/*  This file is part of The Firekylin Operating System.
# *
# *  Copyright 2016 Liuxiaofeng
# *
# *  Licensed under the Apache License, Version 2.0 (the "License");
# *  you may not use this file except in compliance with the License.
# *  You may obtain a copy of the License at
# *
# *      http://www.apache.org/licenses/LICENSE-2.0
# *
# *  Unless required by applicable law or agreed to in writing, software
# *  distributed under the License is distributed on an "AS IS" BASIS,
# *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# *  See the License for the specific language governing permissions and
# *  limitations under the License.
# */

AS=nasm
CC=gcc
LD=ld -m elf_i386 -T ../script/ldscript  ../lib/csu/crt.o

SFLAGS=-f elf32
CFLAGS=-c -x c -Wall -m32 -std=c99 -nostdinc -nostdlib -fno-builtin \
       -fno-stack-protector -I ../include
LIB=../lib/libc/libc.a  ../lib/libm/libm.a

OBJS=tpipe.elf     tsig.elf     t_strcspn.elf  tmath.elf  \
     t_strtod.elf  t_times.elf  tcom1.elf      tioctl.elf \
     tstrrchr.elf  banner.elf
RAW_OBJS=tlua1.lua t1.sh

.s.o:
	@$(AS) $(SFLAGS) -o $@  $<
.c.o:
	@$(CC) $(CFLAGS) -o $@  $<

all:$(OBJS)

install: $(OBJS)
	for obj in $(OBJS) ;                                      \
	do                                                        \
	    cp $$obj `echo $(PREFIX)/$$obj | cut -d '.' -f 1` ;   \
	done
	for obj in $(RAW_OBJS) ; do cp $$obj $(PREFIX)/$$obj; done

clean:
	rm -f *.o $(OBJS)

$(OBJS):%.elf:%.o $(LIB)
	@echo CC       $@
	@$(LD) -o  $@  $<  $(LIB)
