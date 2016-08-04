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

# Note: make flat format image, support by bochs and qemu, other will not.
	
echo "create hd.img ... "
dd if=/dev/zero of=$HOME/hd.img bs=1M count=256 2> /dev/null

echo "create partion ... "
fdisk $HOME/hd.img > /dev/null 2> /dev/null << EOF
o
n
p
1

+64M
n
p
2

+64M
w
EOF

#arr=$(sudo kpartx -av $HOME/hd.img | cut -d ' ' -f 3 | sed -e 's!^!/dev/mapper/!')
arr=$(sudo kpartx -av $HOME/hd.img | awk '{printf ("/dev/mapper/%s ",$3)}')

sync        # <==== we'd better do this here 
sleep 1     # break to sync 

n=0;
for devn in $arr;
do
    n=`expr $n + 1`;
    echo "part"$n"======>"$devn
    mkdir -p part$n
    sudo mkfs.minix -1 $devn
    sudo mount -t minix $devn part$n
    sudo cp /etc/mtab part$n/test.txt
    echo "umount part"
    sudo umount part$n
    #echo "remove part"
    #rm -rf part$n              # in casey's PC ,this can not work,
                                # we do this later or we need a delay  
    sync
done

sudo kpartx -dv $HOME/hd.img 2>&1 > /dev/null
cp   $HOME/hd.img hd.img  && rm -f $HOME/hd.img
sync

# loop again 
for i in `seq 1 $n`
do
    echo "removing " part$i;
    rm -rf part$i;
done

sleep 1
sync

