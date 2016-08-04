#!/bin/sh
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
