/*  This file is part of The Firekylin Operating System.
 *
 *  Copyright 2016 Liuxiaofeng
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef _MM_H
#define _MM_H

#define PAGE_SIZE	4096

typedef unsigned long phys_t;
typedef unsigned long virt_t;

#define __pa(addr)  ((long)(addr)-0xc0000000)
#define __va(addr)  ((long)(addr)+0xc0000000)

struct page_struct {
	int    count;
	phys_t addr;
	struct page_struct *next;
};

extern phys_t get_page(void);
extern void   put_page(phys_t addr);
extern phys_t unmap_page(virt_t line, long pdtr);
extern void   map_page(virt_t va, phys_t pa, long pdtr);
extern long   copy_mm(void);
extern void   alloc_mm(long pdtr, long addr, long size);
extern void   free_mm(void);

#endif
