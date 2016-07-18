#/* This file is part of The Firekylin Operating System.
# *
# * Copyright (c) 2016, Liuxiaofeng
# * All rights reserved.
# *
# * This program is free software; you can distribute it and/or modify
# * it under the terms of The BSD License, see LICENSE.
# */

AS=nasm
CC=gcc

SFLAGS=-g -f elf32
CFLAGS=-g -c -x c -Wall -m32 -std=c99 -nostdinc -nostdlib -fno-builtin \
       -fno-stack-protector -I ./include -I ../include

T     =arch/ia32

# entry 
ENTRY_OBJ=$(T)/head.o

# kernel objects 
KERN_OBJS=init/main.o  			\
          kern/sched.o 			\
          kern/signal.o  		\
          kern/timer.o 			\
          kern/lock.o  			\
          kern/softirq.o 		\
          kern/sys.o   			\
          kern/util.o 			\
          kern/fork.o  			\
          kern/exec.o    		\
          kern/wait.o  			\
          kern/exit.o  			\
          kern/trace.o 

# fs objects 
FS_OBJS=  fs/buffer.o 			\
          fs/super.o 			\
          fs/inode.o  			\
          fs/read.o 			\
          fs/stat.o  			\
          fs/open.o  			\
          fs/write.o  			\
          fs/fcntl.o 			\
          fs/create.o 			\
          fs/pipe.o 			\
          fs/ioctl.o 			\
          fs/close.o 			\
          fs/minix/super.o 		\
          fs/minix/inode.o 		\
          fs/minix/bitmap.o 		\
          fs/minix/namei.o 		\
          fs/minix/file.o  		\
          fs/minix/operation.o 

# arch objects 
ARCH_OBJS=$(T)/entry.o 			\
          $(T)/trap.o  			\
          $(T)/sched.o 			\
          $(T)/signal.o 		\
          $(T)/memory.o 		\
          $(T)/dev/dev.o      		\
          $(T)/dev/char/mem.o 		\
          $(T)/dev/char/tty_con.o  	\
          $(T)/dev/char/tty_kbd.o 	\
          $(T)/dev/char/tty_com.o  	\
          $(T)/dev/char/tty_io.o 	\
          $(T)/dev/char/codemap.o 	\
          $(T)/dev/block/ramdisk.o 	\
          $(T)/dev/block/atapi.o 	\
          $(T)/dev/pci.o		\
          $(T)/dev/ne2k.o

# net part 
NET_OBJS= net/skbuf.o 			\
          net/inet.o

# lib objects 
KLIB_OBJS=klib/ctype.o    		\
	  klib/mktime.o   		\
	  klib/vsprintf.o		\
	  klib/string.o

# total objects 
OBJS=     $(ENTRY_OBJ) 			\
	  $(ARCH_OBJS)			\
	  $(KERN_OBJS)			\
	  $(FS_OBJS)			\
	  $(NET_OBJS)			\
	  $(KLIB_OBJS)

.s.o:
	@echo         AS	$<
	@$(AS) $(SFLAGS) -o $@  $<
.c.o:
	@echo         CC	$<
	@$(CC) $(CFLAGS) -o $@  $<

kernel.bin: $(OBJS)
	@echo         LD      OBJS
	@ld -m elf_i386 -e _start -Ttext 0xC0010000 --oformat binary \
	    -Map kernel.map -o kernel.bin $(OBJS)
	@ld -m elf_i386 -e _start -Ttext 0xC0010000  \
	    -Map kernel.map -o kernel.elf $(OBJS)
	
install:kernel.bin
	cp kernel.bin $(PREFIX)/kernel.bin
	
clean:
	@echo kernel cleaning...
	@-rm -f kernel.map kernel.bin kernel.elf $(OBJS)
