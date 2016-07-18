/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <kernel.h>
#include <driver.h>
#include <tty.h>
#include <arch/ia32/trap.h>
#include <arch/ia32/portio.h>

#define COM1	0x3f8
#define COM2	0x2f8
#define COM3	0x3e8
#define COM4	0x2e8

#define DATA	0	/* Data register */
#define IER	1	/* Interrupt enable register */
#define LDLAB	0	/* Low DLAB */
#define HDLAB	1	/* High DLAB */
#define IIR	2	/* Interrupt Identy & FIFO control registers */
#define LCR	3	/* Line Control Register. bit 8 is DLAB */
#define MCR	4	/* Modem Control Register */
#define LSR	5	/* Line Status Register. */
#define MSR	6	/* Modem Status Register. */
#define SR	7	/* Scratch Register.  */

static struct tty_struct com_tty[MAX_COM];

static void init_com_control(unsigned short port)
{
	outb(port + IER  , 0x00);
	outb(port + LCR  , 0x80);
	outb(port + LDLAB, 0x30);
	outb(port + HDLAB, 0x00);
	outb(port + LCR  , 0x03);
	outb(port + IIR  , 0xC7);
	outb(port + MCR  , 0x0B);
	outb(port + IER  , 0x0D);
}

static int com_write(struct tty_struct *tty)
{
	char ch;
	short port = tty->private;

	while (!isempty(&(tty->out))) {
		ch = GETCH(&(tty->out));
		while ((inb(port + LSR) & 0x20) == 0)
			;
		outb(port + DATA, ch);
	}
	wake_up(&(tty->out.wait));
	return 0;
}

void do_com(struct trapframe *tf)
{
	char iir, data;
	short port;
	struct tty_struct *tty;

	outb(0x20, 0x20);
	
	if (tf->nr == 0x24) {
		port = COM1;
		tty = &com_tty[0];
	} else if (tf->nr == 0x23) {
		port = COM2;
		tty = &com_tty[1];
	} else {
		printk("wrong com intr %x", tf->nr);
		return;
	}

	iir = inb(port + IIR);
	if ((iir & 0x6) == 4) {
		data = inb(port + DATA);
		if (!isfull(&tty->raw)) {
			PUTCH(&tty->raw, data);
			copy_to_cook(tty);
		}
	}
}

void com_init(void)
{
	init_com_control(COM1);
	init_com_control(COM2);
	set_trap_handle(0x24, do_com);
	set_trap_handle(0x23, do_com);
	outb(0x21, inb(0x21) & (~0x18));

	tty_table[1 + MAX_CON] = &com_tty[0];
	tty_table[1 + MAX_CON + 1] = &com_tty[1];

	com_tty[0].write = com_write;
	com_tty[0].private = COM1;
	com_tty[0].termios.c_oflag = ONLCR;
	com_tty[1].write = com_write;
	com_tty[1].private = COM2;
	com_tty[1].termios.c_oflag = ONLCR;
}
