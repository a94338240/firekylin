/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <firekylin/kernel.h>
#include <firekylin/sched.h>
#include <firekylin/mm.h>
#include <firekylin/fs.h>
#include <arch/ia32/trap.h>
#include <multiboot2.h>

#define HIGH_MEM	0x800000

static unsigned long memsize;
static unsigned long NR_PAGE;

static struct page_struct *page_table;

phys_t get_page(void)
{
	struct page_struct *page = page_table;

	for (int i = 0; i < NR_PAGE; i++, page++) {
		if (!page->count) {
			page->count++;
			return (i << 12) + HIGH_MEM;
		}
	}
	panic("out of memory");
	return 0L;
}

void put_page(phys_t addr)
{
	long tmp;

	if (addr & 0xfff)
		panic("Try to free Not align 4kB page :%x", addr);
	if (addr < HIGH_MEM) {
		printk("Try to free kernel page:%x\n", addr);
		return;
	}

	tmp = (addr - HIGH_MEM) >> 12;
	if ((page_table + tmp)->count != 1) {
		printk("Try to err page:%x", addr);
	}
	(page_table + tmp)->count--;
}

void map_page(virt_t va, phys_t pa, long pdtr)
{
	unsigned long *p;
	unsigned long i;
	unsigned long tmp;

	p = (unsigned long*) __va(pdtr);

	if (!(p[va >> 22 & 0x3ff] & 1)) { //PTE not exist.
		tmp = get_page();
		memset((char*) __va(tmp), 0, 4096);
		p[va >> 22 & 0x3ff] = tmp + 7;
	}

	i = p[va >> 22 & 0x3ff] & 0xfffff000;
	p = (unsigned long *) __va(i);
	p[va >> 12 & 0x3ff] = pa + 7;
}

phys_t unmap_page(virt_t line, long pdtr)
{
	unsigned long *p;
	unsigned long i;

	p = (unsigned long*) __va(pdtr);
	i = p[line >> 22 & 0x3ff] & 0xfffff000;
	p = (unsigned long *) __va(i);
	i = p[line >> 12 & 0x3ff] & 0xfffff000;
	return i;
}

void do_page_fault(struct trapframe *tf)
{
	unsigned long cr2;
	struct task *current;

	__asm__("movl %%cr2,%%eax":"=a"(cr2));

	if (cr2 == 0)
		return;

	if (cr2 > 0x41000000 || cr2 < 0x40000000) {
		printk("CS:EIP=%x:%x EFLAGS=%x SS:ESP=%x:%x\n", tf->cs, tf->eip,
				tf->eflags, tf->ss, tf->esp);
		if (tf->cs & 3) {
			printk("Process Memory err:%x\n", cr2);
			do_exit(12);
		}
		panic("cr2=%x\n", cr2);
	}

	current = CURRENT_TASK();
	map_page(cr2 & 0xfffff000, get_page(), current->pdtr);
	current->stack = cr2 & 0xfffff000;
}

long copy_mm(void)
{
	long addr, tmp_addr;
	long ret = get_page();
	struct task *current = CURRENT_TASK();

	memset((char*) __va(ret), 0, 3072);
	memcpy((char*) __va(ret) + 3072, (char*) __va(current->pdtr) + 3072,
			1024);

	for (addr = current->stack; addr < current->sbrk; addr += 4096) {
		tmp_addr = get_page();
		memcpy((char*) __va(tmp_addr), (char*) addr, 4096);
		map_page(addr, tmp_addr, ret);
	}
	return ret;
}

void alloc_mm(long pdtr, long addr, long size)
{
	long start = addr & 0xfffff000;
	long end = addr + ((size + 0xfff) & 0xfffff000);
	for (int i = start; i < end; i += 4096) {
		map_page(i, get_page(), pdtr);
	}
}

/*
 *  Note : just free the page, not pdt ,pte . will lost some page.
 */
void free_mm(void)
{
	unsigned long tmp;
	struct task *current = CURRENT_TASK();
	for (long addr = current->stack; addr < current->sbrk; addr += 4096) {
		if ((tmp = unmap_page(addr, current->pdtr)))
			put_page(tmp);
	}
	memset((char*) __va(current->pdtr), 0, 3072);
	__asm__( " movl %%eax,%%cr3"::"a"(current->pdtr));
}

void dump_mem(void)
{
	int free = 0;
	struct page_struct *p = page_table;

	for (int i = 0; i < NR_PAGE; i++) {
		if (!p->count)
			free++;
		p++;
	}

	printk("Mem :%dMB  page :%d free :%d\n", memsize >> 20, NR_PAGE, free);
}

void mm_init(void)
{
	int page_table_page_use;
	unsigned long i, *p;

	int addr = __va(0x1000 + 8);
	struct multiboot_tag_mmap *mm_map = NULL;
	struct multiboot_tag *tag;

	do {
		tag = (struct multiboot_tag *) addr;
		if (tag->type == MULTIBOOT_TAG_TYPE_MMAP) {
			mm_map = (struct multiboot_tag_mmap *) tag;
			break;
		}
		addr = (addr + tag->size + 7) & ~7;
	} while (tag->type != MULTIBOOT_HEADER_TAG_END);

	if (!mm_map)
		printk("Not find memory map by GRUB\n");
	else {
		struct multiboot_mmap_entry *mm_map_entry = mm_map->entries;
		while ((long) mm_map_entry < addr + mm_map->size) {
			if (mm_map_entry->type == MULTIBOOT_MEMORY_AVAILABLE)
				memsize = mm_map_entry->addr
						+ mm_map_entry->len;
			mm_map_entry++;
		}
	}

	if (memsize > 256 * 1024 * 1024)
		memsize = 256 * 1024 * 1024;

	p = (unsigned long*) __va(0);
	*p = 0;
	for (i = 0; i < memsize >> 22; i++)
		*(p + i + 0x300) = 0x100007 + 0x1000 * i;

	p = (unsigned long*) __va(0x100000);
	for (i = 0; i < memsize >> 12; i++)
		*(p + i) = 7 + 0x1000 * i;

	NR_PAGE = memsize / PAGE_SIZE;
	page_table = (struct page_struct *) __va(HIGH_MEM);

	page_table_page_use = (NR_PAGE * sizeof(struct page_struct) + PAGE_SIZE
			- 1) / PAGE_SIZE;
	for (int i = 0; i < page_table_page_use; i++)
		(page_table + i)->count = 100;

	for (int i = page_table_page_use; i < NR_PAGE; i++)
		(page_table + i)->count = 0;

	set_trap_handle(14, do_page_fault);
	dump_mem();
}
