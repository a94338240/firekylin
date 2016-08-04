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

SFLAGS=-f elf32
CFLAGS=-c -x c -Wall -m32 -std=c99 -nostdinc -nostdlib -fno-builtin \
       -fno-stack-protector -I ../../include
T     =i386
      
LIBM_OBJ= $(T)/sin.o   $(T)/cos.o   $(T)/tan.o   asin.o  acos.o  \
          $(T)/atan.o  $(T)/atan2.o sinh.o       cosh.o  tanh.o  \
	  asinh.o      acosh.o      atanh.o      \
          $(T)/exp.o   $(T)/pow.o   $(T)/log.o   $(T)/log10.o    \
	  $(T)/sqrt.o  hypot.o                   \
          $(T)/fabs.o  $(T)/floor.o $(T)/ceil.o  $(T)/fmod.o     \
	  modf.o       ldexp.o      frexp.o      \
          __divdi3.o   __udivdi3.o  __moddi3.o   __umoddi3.o
.s.o:
	@echo         AS	$<
	@$(AS) $(SFLAGS) -o $@  $<
.c.o:
	@echo         CC	$<
	@$(CC) $(CFLAGS) -o $@  $<

libm.a: $(LIBM_OBJ)
	@echo         AR       libm
	@ar rcs   libm.a       $(LIBM_OBJ) 

install:libc.a
	@echo installing libm ...
	@-cp  libc.a  $(PREFIX)/libm.a

clean: 
	@echo cleaning libm ...
	@-rm -f libm.a $(LIBM_OBJ)
