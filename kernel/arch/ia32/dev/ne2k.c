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
#include <firekylin/pci.h>
#include <firekylin/mm.h>
#include <firekylin/skbuf.h>
#include <arch/ia32/trap.h>
#include <arch/ia32/bits.h>
#include <net/ether.h>
#include <net/arp.h>

/*
 * ne2k_pci rquipped by bochs or qemu. other unknow.
 */
#define NE2K_VENDOR	0x10EC
#define NE2K_DEVICE	0x8029

/* register offset */
#define CR		0x00

/* page 0, read */
#define CLDA0		0x01
#define CLDA1		0x02
#define BNRY		0x03    /* rw */
#define TSR		0x04
#define NCR		0x05
#define FIFO		0x06
#define ISR		0x07	/* rw */
#define CRDA0		0x08
#define CRDA1		0x09
#define RSR		0x0C
#define CNTR0		0x0D
#define CNTR1		0x0E
#define CNTR2		0x0F

/* page 0 write */
#define PSTART		0x01	/* read page 2 */
#define PSTOP		0x02	/* read page 2 */
#define TPSR		0x04	/* read page 2 */
#define TBCR0		0x05
#define TBCR1		0x06
#define RSAR0		0x08
#define RSAR1		0x09
#define RBCR0		0x0A
#define RBCR1		0x0B
#define RCR		0x0C	/* read page 2 */
#define TCR		0x0D	/* read page 2 */
#define DCR		0x0E	/* read page 2 */
#define IMR		0x0F	/* read page 2 */

/* page 1 read/write */
#define PAR0		0x01
#define PAR1		0x02
#define PAR2		0x03
#define PAR3		0x04
#define PAR4		0x05
#define PAR5		0x06
#define CURR		0x07
#define MAR0		0x08
#define MAR1		0x09
#define MAR2		0x0A
#define MAR3		0x0B
#define MAR4		0x0C
#define MAR5		0x0D
#define MAR6		0x0E
#define MAR7		0x0F

#define DATA		0x10
#define RESET		0x1F

static struct pci_device *ne2k;
static unsigned short base;
static unsigned char irq;
static unsigned char mac[6];
static unsigned short rx_next = 0x47;

int ne2k_send(char *data, short len)
{
	while (inb(base + CR) == 0x26)
		;

	len = (len + 1) & ~1;

	outb(base + RSAR0, 0);
	outb(base + RSAR1, 0x40);
	outb(base + RBCR0, len & 0xff);
	outb(base + RBCR1, (len >> 8) & 0xff);
	outb(base + CR,    0x12); 	/* write and start. */
	outsw(base + DATA, data, len);
	while ((inb(base + ISR) & 0x40) == 0)
		;
	outb(base + ISR, 0x40);

	outb(base + TPSR, 0x40);
	outb(base + TBCR0, len & 0xff);
	outb(base + TBCR1, (len >> 8) & 0xff);
	outb(base + CR, 0x26);
	return 0;
}

void ne2k_receive(void)
{
	struct {
		unsigned char rsr;
		unsigned char next;
		unsigned short len;
	} info;

	struct skbuf *skb=alloc_skbuf();

	outb(base + RSAR0, 0);
	outb(base + RSAR1, rx_next);
	outb(base + RBCR0, 4);
	outb(base + RBCR1, 0);
	outb(base + CR, 0x12); // write and start.
	insw(base + DATA, &info, 4);

	outb(base + RSAR0, 4);
	outb(base + RSAR1, rx_next);
	outb(base + RBCR0, info.len & 0xff);
	outb(base + RBCR1, (info.len >> 8) & 0xff);
	insw(base + DATA,  skb->data, info.len);

	while ((inb(base + ISR) & 0x40) == 0);
	outb(base + ISR, 0x40);

	rx_next = info.next;
	if (rx_next == 0x40)
		outb(base + BNRY, 0x80);
	else
		outb(base + BNRY, rx_next - 1);

	softirq_raise(SOFTIRQ_INET,(long)skb);
}

void do_ne2k(struct trapframe *tf)
{
	unsigned char isr;
	isr = inb(base + ISR);
	if (isr & 1) {
		outb(base + ISR, 0x01);
		if (irq >= 8)
			outb(0xa0, 0x20);
		outb(0x20, 0x20);
		ne2k_receive();
		return;
	}
	if (isr & 2) {
		printk("send packet ok \n");
		outb(base + ISR, 0x02);
		if (irq >= 8)
			outb(0xa0, 0x20);
		outb(0x20, 0x20);
		return;
	}
	printk("ne2k intrrupt happen:%x", inb(base + ISR));
	outb(base + ISR, 0xff);
	if (irq >= 8)
		outb(0xa0, 0x20);
	outb(0x20, 0x20);
}

void ne2k_init(void)
{
	if (!(ne2k = pci_find_device(NE2K_VENDOR, NE2K_DEVICE)))
		return (void) printk("ne2k not exsit on system\n");

	base = ne2k->bar0 & ~3;
	irq = ne2k->interrput_line;

	printk("ne2k--iobase:%x\n", base);
	printk("ne2k--irq:%d\n", irq);

	set_trap_handle(irq + 0x20, do_ne2k);
	if (irq >= 8)
		outb(0xa1, inb(0xa1) & ~(1 << (irq - 8)));
	else
		outb(0x21, inb(0xa1) & ~(1 << irq));

	outb(base + RESET, inb(base + RESET));
	while ((inb(base + ISR) & 0x80) == 0)
		;
	printk("ne2k reset done\n");

	outb(base + CR, 0x21);
	outb(base + DCR, 0x49);
	outb(base + TCR, 0x00);
	outb(base + RCR, 0xFF);
	outb(base + IMR, 0x00);
	outb(base + ISR, 0xFF);

	outb(base + TPSR, 0x40);
	outb(base + PSTART, rx_next - 1);
	outb(base + PSTOP, 0x80);
	outb(base + BNRY, rx_next - 1);
	outb(base + CR, 0x61);
	outb(base + CURR, rx_next);
	outb(base + CR, 0x21);

	outb(base + RSAR0, 0);
	outb(base + RSAR1, 0);
	outb(base + RBCR0, 24);
	outb(base + RBCR1, 0);
	outb(base + CR, 0x0A);
	printk("ne2k MAC: ");
	for (int i = 0; i < 6; i++) {
		mac[i] = inb(base + DATA);
		printk("%x:", mac[i]);
	}
	printk("\b\n");

	outb(base + CR, 0x61);
	outb(base + PAR0, mac[0]);
	outb(base + PAR1, mac[1]);
	outb(base + PAR2, mac[2]);
	outb(base + PAR3, mac[3]);
	outb(base + PAR4, mac[4]);
	outb(base + PAR5, mac[5]);

	outb(base + CR, 0x22);
	outb(base + IMR, 0x1b);
}
