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

SFLAGS=-g -f elf32
CFLAGS=-g -c -x c -Wall -m32 -std=c99 -nostdinc -nostdlib -fno-builtin \
       -fno-stack-protector -I ../include
LIB=../lib/libc/libc.a  ../lib/libm/libm.a

OBJS=init.elf  sh.elf     ls.elf  cat.elf  sync.elf   mkdir.elf   cp.elf \
     rm.elf    rmdir.elf  ln.elf  vi.elf   mount.elf  umount.elf  basename.elf \
     dirname.elf date.elf cal.elf chmod.elf cmp.elf   env.elf     head.elf \
     kill.elf  tee.elf    split.elf time.elf

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

clean:
	rm -f *.o $(OBJS)

$(OBJS):%.elf:%.o $(LIB)
	@echo CC       $@
	@$(LD) -o  $@  $<  $(LIB)
