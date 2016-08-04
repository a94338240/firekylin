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

#include <firekylin/kernel.h>
#include <firekylin/lock.h>
#include <arch/ia32/sched.h>
#include <arch/ia32/trap.h>
#include <arch/ia32/portio.h>

extern void div_zero(void);
extern void debug(void);
extern void nmi(void);
extern void breakpoint(void);
extern void overflow(void);
extern void bound(void);
extern void invalid_opcode(void);
extern void device_not_invalid(void);
extern void double_fault(void);
extern void coprocessor_overrun(void);
extern void invalid_tss(void);
extern void segment_not_exsit(void);
extern void stack(void);
extern void general_protection(void);
extern void page_fault(void);
extern void reserved(void);
extern void coprocessor(void);
extern void align_check(void);
extern void machine_check(void);
extern void simd_float(void);
extern void hwint0(void);
extern void hwint1(void);
extern void hwint2(void);
extern void hwint3(void);
extern void hwint4(void);
extern void hwint5(void);
extern void hwint6(void);
extern void hwint7(void);
extern void hwint8(void);
extern void hwint9(void);
extern void hwintA(void);
extern void hwintB(void);
extern void hwintC(void);
extern void hwintD(void);
extern void hwintE(void);
extern void hwintF(void);
extern void syscall(void);

struct tss_struct tss;

#define set_gate(fun,index,dpl) 				\
    __asm__("movl %%eax, (%%edx);"  				\
	    "movl %%ebx, 4(%%edx);"				\
	    ::"a"(((long)fun&0xffff)|0x00080000), 		\
	      "b"(((long)fun&0xffff0000)|0x8e00|(dpl<<13)), 	\
	      "d"(&(idt_table[index])))

static void (*trap_handle[0x30])(struct trapframe *tf);

static struct gdt_desc {
	unsigned long low;
	unsigned long high;
} gdt_table[6] = {
	{ 0, 0 }, 			/* 0x00 NULL  		*/
	{ 0x0000ffff, 0x00cf9a00 }, 	/* 0x08 Kernel Code 	*/
	{ 0x0000ffff, 0x00cf9200 }, 	/* 0x10 Kernel Data	*/
	{ 0x0000ffff, 0x00cbfa00 }, 	/* 0x18 User   Code	*/
	{ 0x0000ffff, 0x00cbf200 }, 	/* 0x20 User   Data	*/
	{ 0, 0 } 			/* 0x28 Tss		*/
};

static struct idt_desc {
	unsigned long low;
	unsigned long high;
} idt_table[0x31];

static void gdt_init(void)
{
	long addr = (long) &tss;
	short tmp[3] = { sizeof(gdt_table) - 1, 0, 0 };
	tmp[1] = ((long) &gdt_table) & 0xffff;
	tmp[2] = (((long) &gdt_table) >> 16) & 0xffff;
	__asm__("lgdt (%%eax);"
		"jmp  $0x8,$next;"
		"next:movl $0x10,%%eax;"
		"movw %%ax,%%ds;"
		"movw %%ax,%%ss;"
		"movw %%ax,%%es;"
		"movw %%ax,%%fs;"
		"movw %%ax,%%gs"::"a"(tmp));
	tss.ss0 = 0x10;
	gdt_table[5].low = ((addr << 16) & 0xffff0000) | 104;
	gdt_table[5].high = (addr & 0xff000000) | 0xe900
			| ((addr >> 16) & 0xff);
	__asm__("ltr %%ax"::"a"(0x28));
}

static void idt_init(void)
{
	short idt[3] = { 0x31 * 8 - 1, 0, 0 };
	set_gate(div_zero, 0, 0);
	set_gate(debug, 1, 0);
	set_gate(nmi, 2, 0);
	set_gate(breakpoint, 3, 3);
	set_gate(overflow, 4, 3);
	set_gate(bound, 5, 3);
	set_gate(invalid_opcode, 6, 0);
	set_gate(device_not_invalid, 7, 0);
	set_gate(double_fault, 8, 0);
	set_gate(coprocessor_overrun, 9, 0);
	set_gate(invalid_tss, 10, 0);
	set_gate(segment_not_exsit, 11, 0);
	set_gate(stack, 12, 0);
	set_gate(general_protection, 13, 0);
	set_gate(page_fault, 14, 3);
	set_gate(reserved, 15, 0);
	set_gate(coprocessor, 16, 0);
	set_gate(align_check, 17, 0);
	set_gate(machine_check, 18, 0);
	set_gate(simd_float, 19, 0);
	for (int i = 20; i < 0x20; i++)
		set_gate(reserved, i, 0);
	set_gate(hwint0, 0x20, 0);
	set_gate(hwint1, 0x21, 0);
	set_gate(hwint2, 0x22, 0);
	set_gate(hwint3, 0x23, 0);
	set_gate(hwint4, 0x24, 0);
	set_gate(hwint5, 0x25, 0);
	set_gate(hwint6, 0x26, 0);
	set_gate(hwint7, 0x27, 0);
	set_gate(hwint8, 0x28, 0);
	set_gate(hwint9, 0x29, 0);
	set_gate(hwintA, 0x2A, 0);
	set_gate(hwintB, 0x2B, 0);
	set_gate(hwintC, 0x2C, 0);
	set_gate(hwintD, 0x2D, 0);
	set_gate(hwintE, 0x2E, 0);
	set_gate(hwintF, 0x2F, 0);
	set_gate(syscall, 0x30, 3);
	idt[1] = ((long) &idt_table) & 0xffff;
	idt[2] = (((long) &idt_table) >> 16) & 0xffff;
	__asm__("lidt (%%eax) "::"a"(idt));
}

static void i8259_init(void)
{
	outb(0x20, 0x11);
	outb(0xa0, 0x11);
	outb(0x21, 0x20);
	outb(0xa1, 0x28);
	outb(0x21, 0x04);
	outb(0xa1, 0x02);
	outb(0x21, 0x01);
	outb(0xa1, 0x01);
	outb(0x21, 0xfb);
	outb(0xa1, 0xff);
}

void arch_init(void)
{
	gdt_init();
	idt_init();
	i8259_init();
	irq_enable();
}

void set_trap_handle(int index, void (*fn)(struct trapframe *tf))
{
	if (index < 0 || index > 0x30) {
		panic("set_trap_handle:index=%d", index);
	}

	trap_handle[index] = fn;
}

void execption(unsigned long unuesd)
{
	struct trapframe *tf = (struct trapframe*) &unuesd;

	if (trap_handle[tf->nr] != NULL) {
		(*trap_handle[tf->nr])(tf);
		return;
	}

	if (tf->nr >= 0x20) {
		printk("Uncatched Interrupt %x\n", tf->nr);
		return;
	}

	printk("Exception:%d\tError code:%d\n", tf->nr, tf->err);
	printk("CS:EIP=04%:%08x EFLAGS=%x SS:ESP=%04x:%08x\n", tf->cs, tf->eip,
			tf->eflags, tf->ss, tf->esp);
	panic("");
	//panic("Current pid:%d\n", (CURRENT_TASK() )->pid);
}
