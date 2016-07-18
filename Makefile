#/* This file is part of The Firekylin Operating System.
# *
# * Copyright (c) 2016, Liuxiaofeng
# * All rights reserved.
# *
# * This program is free software; you can distribute it and/or modify
# * it under the terms of The BSD License, see LICENSE.
# */

QEMU=qemu-system-i386 -boot d                                     \
	 -net nic,model=ne2k_pci,vlan=1,macaddr=12:54:00:12:34:56 \
	 -net tap,vlan=1,ifname=tap1                              \
	 -serial tcp::4444,server,nowait                          \
	 -serial tcp::4445,server,nowait                          \
	 -cdrom cdrom.iso                                         \
	 -hda hd.img

QEMU_CASEY=sudo qemu-system-i386 -boot d                          \
	 -serial tcp::4444,server,nowait                          \
	 -serial tcp::4445,server,nowait                          \
	 -cdrom cdrom.iso                                         \
	 -hda hd.img

all: complie cdrom hd.img

complie:
	make -C kernel
	make -C lib
	make -C bin
	make -C test
	make -C contrib
	
cdrom:
	@make complie 2>&1 > /dev/null
	@sh script/mkiso.sh
	
hd.img:
	@make complie 2>&1 > /dev/null
	@sh script/mkhdimg.sh
	
pdf:
	@sh script/mkpdf.sh

clean:
	@-make clean -C kernel
	@-make clean -C lib
	@-make clean -C bin
	@-make clean -C test
	@-make clean -C contrib
	@-rm -f cdrom.iso hd.img
	@-rm -f firekylin-source.pdf

distclean:clean
	@-rm -rf iso
	@-rm -rf Download
	
qemu:
	$(QEMU)

# for the QEMU without net-part 
#
qemu_c:
	$(QEMU_CASEY)

qemuS:
	$(QEMU) -S -gdb tcp::1234
