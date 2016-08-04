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

dd if=/dev/zero of=$HOME/ramdisk.img bs=1M count=2 2> /dev/null
mkfs.minix -1 $HOME/ramdisk.img > /dev/null

# create tmpdir to mount ramdisk

mkdir -p $HOME/tmpdir && sudo mount -t minix $HOME/ramdisk.img $HOME/tmpdir

# create needed dirs
echo "creating dirs"
sudo mkdir -p ~/tmpdir/bin
sudo mkdir -p ~/tmpdir/dev
sudo mkdir -p ~/tmpdir/boot
sudo mkdir -p ~/tmpdir/lib
sudo mkdir -p ~/tmpdir/home
sudo mkdir -p ~/tmpdir/test
sudo mkdir -p ~/tmpdir/etc

# create some test file 

sudo cp /etc/crontab ~/tmpdir/etc/crontab
sudo cp /etc/shadow  ~/tmpdir/etc/shadow
sudo cp /etc/shells  ~/tmpdir/etc/shells
sudo cp /etc/mtab    ~/tmpdir/etc/mtab
sudo cp /etc/fstab   ~/tmpdir/etc/fstab

echo "creating dev nodes"
sudo mknod ~/tmpdir/dev/mem  c  1  1
sudo mknod ~/tmpdir/dev/port c  1  2
sudo mknod ~/tmpdir/dev/null c  1  3
sudo mknod ~/tmpdir/dev/full c  1  4

sudo mknod ~/tmpdir/dev/tty  c  2  0
sudo mknod ~/tmpdir/dev/tty1 c  2  1
sudo mknod ~/tmpdir/dev/tty2 c  2  2
sudo mknod ~/tmpdir/dev/tty3 c  2  3

sudo mknod ~/tmpdir/dev/com1 c  2  4
sudo mknod ~/tmpdir/dev/com2 c  2  5

sudo mknod ~/tmpdir/dev/rd   b  1  0

#sudo mknod ~/tmpdir/dev/fd0  b  2  0
#sudo mknod ~/tmpdir/dev/fd1  b  2  1

sudo mknod ~/tmpdir/dev/hda  b  3  0
sudo mknod ~/tmpdir/dev/hda1 b  3  1
sudo mknod ~/tmpdir/dev/hda2 b  3  2
#sudo mknod ~/tmpdir/dev/hda3 b  3  3
#sudo mknod ~/tmpdir/dev/hda4 b  3  4

echo "installing bin ..."
sudo make PREFIX=$HOME/tmpdir/bin  install -C bin     2>&1 > /dev/null

echo "installing test ..."
sudo make PREFIX=$HOME/tmpdir/test install -C test    2>&1 > /dev/null

echo "installing contrib ..."
sudo make PREFIX=$HOME/tmpdir/bin  install -C contrib 2>&1 > /dev/null

sudo umount $HOME/ramdisk.img && rm -rf $HOME/tmpdir
