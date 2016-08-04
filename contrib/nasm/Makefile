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

SFLAGS=-f elf32
CFLAGS=-c -x c  -m32 -std=c99 -nostdinc -nostdlib -fno-builtin \
       -fno-stack-protector -I ../../include 
LIB=../../lib/libc/libc.a  ../../lib/libm/libm.a

DOWN_DIR= ../../Download
S=$(DOWN_DIR)/nasm-2.12

OBJS=$(S)/nasm.o $(S)/nasmlib.o $(S)/ver.o    \
     $(S)/raa.o  $(S)/saa.o     $(S)/rbtree.o \
     $(S)/realpath.o \
     $(S)/float.o $(S)/insnsa.o $(S)/insnsb.o \
     $(S)/directiv.o \
     $(S)/assemble.o $(S)/labels.o $(S)/hashtbl.o $(S)/crc64.o $(S)/parser.o \
     $(S)/output/outform.o $(S)/output/outlib.o $(S)/output/nulldbg.o \
     $(S)/output/nullout.o \
     $(S)/output/outbin.o $(S)/output/outaout.o  $(S)/output/outcoff.o  \
     $(S)/output/outelf.o $(S)/output/outelf32.o $(S)/output/outelf64.o \
     $(S)/output/outelfx32.o \
     $(S)/output/outobj.o $(S)/output/outas86.o $(S)/output/outrdf2.o \
     $(S)/output/outdbg.o $(S)/output/outieee.o $(S)/output/outmacho.o \
     $(S)/md5c.o          $(S)/output/codeview.o \
     $(S)/preproc.o       $(S)/quote.o          $(S)/pptok.o \
     $(S)/macros.o $(S)/listing.o $(S)/eval.o $(S)/exprlib.o $(S)/stdscan.o \
     $(S)/strfunc.o $(S)/tokhash.o $(S)/regvals.o $(S)/regflags.o \
     $(S)/ilog2.o \
     $(S)/lib/strlcpy.o \
     $(S)/preproc-nop.o \
     $(S)/disp8.o \
     $(S)/iflag.o
     
.s.o:
	@echo         AS	$<
	@$(AS) $(SFLAGS) -o $@  $<
.c.o:
	@echo         CC	$<
	@$(CC) $(CFLAGS) -o $@  $<

CFLAGS+=-DOF_ONLY -DOF_BIN -DOF_COFF -DOF_ELF32 -DHAVE_SNPRINTF \
        -DHAVE_VSNPRINTF -DHAVE_STRICMP -DHAVE_STRNICMP -I . -I $(S)

nasm.elf:$(S) $(OBJS) $(LIB) 
	@echo  LD  nasm.elf
	@$(LD) -o $@  $(OBJS)  $(LIB)

install: 
	cp nasm.elf   $(PREFIX)/nasm

clean:
	@echo cleaning nasm ...
	@rm nasm.elf  $(OBJS) 
		
$(S):
	mkdir -p $(DOWN_DIR)
	cd $(DOWN_DIR) &&                             \
	wget http://www.nasm.us/pub/nasm/releasebuilds/2.12/nasm-2.12.tar.gz && \
	tar -zxf nasm-2.12.tar.gz
