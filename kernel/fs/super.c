/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <firekylin/kernel.h>
#include <firekylin/driver.h>
#include <firekylin/fs.h>
#include <errno.h>

extern struct fs_operation minix_fs_operation;

static struct super super_table[NR_SUPER];
static sleeplock_t super_lock;

#define lock_super_table()	require_lock(&super_lock)
#define unlock_super_table()	release_lock(&super_lock)

static struct fs_type fs_type_table[] = {
	{ "minix", &minix_fs_operation }
};

struct super * get_super(dev_t dev)
{
	struct super *super = super_table;

	lock_super_table();
	while (super < super_table + NR_SUPER) {
		if (super->s_dev == dev) {
			super->s_count++;
			unlock_super_table();
			lock_super(super);
			return super;
		}
		super++;
	}
	printk("Super Block NOT Load %x", dev);
	return NULL;
}

void put_super(struct super *super)
{
	if (!super) {
		printk("put NULL super block");
		return;
	}

	if (--super->s_count < 0)
		panic("put free super block");

	unlock_super(super);
}

dev_t mount_inode(struct inode *inode)
{
	struct super *super;

	lock_super_table();
	for (super = super_table; super < super_table + NR_SUPER; super++)
		if (super->s_imount && (super->s_imount == inode)) {
			unlock_super_table();
			return super->s_dev;
		}
	unlock_super_table();
	return 0;
}

long sys_mount(char *dev_name, char *dir_name, char *type, long ro_flag)
{
	struct inode *dev_i, *dir_i;
	struct super *super;
	struct fs_operation *fs_op = NULL;
	int dev;

	for (int i = 0; i < sizeof(fs_type_table) / sizeof(struct fs_type);
			i++) {
		if (!strcmp(type, fs_type_table[i].fst_name)) {
			fs_op = fs_type_table[i].fst_op;
			break;
		}
	}

	if (!fs_op) {
		printk("Un support file system type %s\n", type);
		return -ERROR;
	}

	if (!(dev_i = namei(dev_name, NULL)))
		return -ENOENT;
	if (!S_ISBLK(dev_i->i_mode)) {
		printk("Not a block dev %s:%x", dev_name, dev_i->i_rdev);
		iput(dev_i);
		return -EPERM;
	}

	dev = dev_i->i_rdev;
	iput(dev_i);

	if (!(dir_i = namei(dir_name, NULL)))
		return -ENOENT;

	if (dir_i->i_count != 1 || dir_i->i_ino == 1) {
		iput(dir_i);
		return -EBUSY;
	}

	if (!S_ISDIR(dir_i->i_mode)) {
		iput(dir_i);
		return -EPERM;
	}

	lock_super_table();
	for (super = super_table; super < super_table + NR_SUPER; super++)
		if (!super->s_dev)
			break;
	if (super >= super_table + NR_SUPER) {
		unlock_super_table();
		iput(dir_i);
		printk("super table use over");
		return -EAGAIN;
	}
	lock_super(super);
	unlock_super_table();

	super->s_dev = dev;
	super->s_op = fs_op;

	if (super->s_op->super_read(super)) {
		super->s_dev = 0;
		unlock_super(super);
		iput(dir_i);
		return -EBUSY;
	}

	super->s_imount = dir_i;
	dir_i->i_flag |= (I_MOUNT | I_DIRTY);
	unlock_super(super);
	unlock_inode(dir_i);
	return 0;
}

long sys_umount(char *dev_name)
{
	struct inode *inode;
	struct super *super;
	int dev;

	if (!(inode = namei(dev_name, NULL)))
		return -ENOENT;
	if (!S_ISBLK(inode->i_mode)) {
		iput(inode);
		return -ENOTBLK;
	}
	dev = inode->i_rdev;
	iput(inode);
	if (dev == ROOT_DEV)
		return -EBUSY;
	if (!(super = get_super(dev)) || !(super->s_imount))
		return -ENOENT;

	if (!(super->s_imount->i_flag & I_MOUNT))
		printk("Mounted inode has flag without I_MOUNT\n");
	//for(inode=inode_table;inode <inode_table +NR_INODE;inode++)
	//	if(inode->i_dev==dev && inode->i_count)
	//		return -EBUSY;
	super->s_imount->i_flag &= ~I_MOUNT;
	iput(super->s_imount);
	super->s_dev = 0;
	put_super(super);
	return 0;
}

void mount_root(void)
{
	extern struct inode *root_inode;
	struct super *super = super_table;
	struct task *task = CURRENT_TASK();

	printk("Mounting root file system on dev:%x", ROOT_DEV);
	super->s_dev = ROOT_DEV;
	super->s_op = &minix_fs_operation;
	if (super->s_op->super_read(super))
		printk("root dev mount error");
	root_inode = iget(ROOT_DEV, 1);
	task->pwd = idup(root_inode);
	unlock_inode(root_inode);
	printk("    [done]\n");
}
