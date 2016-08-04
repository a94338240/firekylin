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
LD=ld -m elf_i386 -T ../../script/ldscript  ../../lib/csu/crt.o

SFLAGS=-g -f elf32
CFLAGS=-g -c -x c -Wall -m32 -std=c99 -nostdinc -nostdlib -fno-builtin \
       -fno-stack-protector -I ../../include 
LIB=../../lib/libc/libc.a  ../../lib/libm/libm.a

DOWN_DIR= ../../Download
LUA_DIR	= $(DOWN_DIR)/lua-5.1
S=$(LUA_DIR)/src

OBJS=$(S)/lapi.o     $(S)/lcode.o    $(S)/ldebug.o   $(S)/ldo.o      \
     $(S)/ldump.o    $(S)/lfunc.o    $(S)/lgc.o      $(S)/llex.o     \
     $(S)/lmem.o     $(S)/lobject.o  $(S)/lopcodes.o $(S)/lparser.o  \
     $(S)/lstate.o   $(S)/lstring.o  $(S)/ltable.o   $(S)/ltm.o      \
     $(S)/lundump.o  $(S)/lvm.o      $(S)/lzio.o     $(S)/lauxlib.o  \
     $(S)/lbaselib.o $(S)/ldblib.o   $(S)/liolib.o   $(S)/lmathlib.o \
     $(S)/loslib.o   $(S)/ltablib.o  $(S)/lstrlib.o  $(S)/loadlib.o  \
     $(S)/linit.o

.s.o:
	@echo         AS	$<
	@$(AS) $(SFLAGS) -o $@  $<
.c.o:
	@echo         CC	$<
	@$(CC) $(CFLAGS) -o $@  $<

lua.elf: $(LUA_DIR) $(S)/lua.o lualib.a $(LIB)
	@echo LD  lua.elf
	@$(LD) -o  $@ $(S)/lua.o lualib.a $(LIB)

lualib.a:$(OBJS)
	@echo  AR  OBJS
	@ar rcs lualib.a $(OBJS)

install: 
	cp lua.elf   $(PREFIX)/lua

clean:
	@echo cleaning lua ...
	@rm -f lua.elf $(S)/lua.o lualib.a $(OBJS)

$(LUA_DIR):
	mkdir -p $(DOWN_DIR)
	cd $(DOWN_DIR) &&                             \
	wget http://www.lua.org/ftp/lua-5.1.tar.gz && \
	tar xzf lua-5.1.tar.gz  
