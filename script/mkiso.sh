#!/bin/sh

#/* This file is part of The Firekylin Operating System.
# *
# * Copyright (c) 2016, Liuxiaofeng
# * All rights reserved.
# *
# * This program is free software; you can distribute it and/or modify
# * it under the terms of The BSD License, see LICENSE.
# */

mkdir -p iso/boot/grub
cp script/grub.cfg    iso/boot/grub/grub.cfg
cp kernel/kernel.bin  iso/boot/kernel.bin

# if file none.img not
if [ ! -f iso/boot/none ]; then
	echo "creating file iso/boot/none.img"
	dd if=/dev/zero of=iso/boot/none.img bs=1024 count=1024 2> /dev/null
fi

sh script/mkramdisk.sh
cp $HOME/ramdisk.img iso/boot/ramdisk.img && rm -f $HOME/ramdisk.img

echo "creating source tar ..."
tar -zcf iso/src.tgz ` git ls-files `

echo "creating VERSION ... "
date > iso/VERSION

echo "creating cdrom.iso ..."
grub-mkrescue -o cdrom.iso iso 2> /dev/null

if [ ! $? ]; then
	echo "Error: create cdrom.iso failed !"
fi
