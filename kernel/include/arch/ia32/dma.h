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

#ifndef _IA32_DMA_H
#define _IA32_DMA_H

#define DMA_CHANNELS	       8

/* 8237 DMA controllers */
#define DMA1_BASE	    0x00        /* 8 bit slave DMA, channels 0..3 */
#define DMA2_BASE	    0xC0        /* 16 bit master DMA, channels 4..7 */

/* DMA controller registers */
#define DMA1_CMD            0x08        /* command register (w) */
#define DMA1_STAT           0x08        /* status register (r) */
#define DMA1_REQ            0x09        /* request register (w) */
#define DMA1_MASK           0x0A        /* single-channel mask (w) */
#define DMA1_MODE           0x0B        /* mode register (w) */
#define DMA1_CLEAR_FF       0x0C        /* clear pointer flip-flop (w) */
#define DMA1_TEMP           0x0D        /* Temporary Register (r) */
#define DMA1_RESET          0x0D        /* Master Clear (w) */
#define DMA1_CLR_MASK       0x0E        /* Clear Mask */
#define DMA1_MASK_ALL       0x0F        /* all-channels mask (w) */

#define DMA2_CMD            0xD0        /* command register (w) */
#define DMA2_STAT           0xD0        /* status register (r) */
#define DMA2_REQ            0xD2        /* request register (w) */
#define DMA2_MASK           0xD4        /* single-channel mask (w) */
#define DMA2_MODE           0xD6        /* mode register (w) */
#define DMA2_CLEAR_FF       0xD8        /* clear pointer flip-flop (w) */
#define DMA2_TEMP           0xDA        /* Temporary Register (r) */
#define DMA2_RESET          0xDA        /* Master Clear (w) */
#define DMA2_CLR_MASK       0xDC        /* Clear Mask */
#define DMA2_MASK_ALL       0xDE        /* all-channels mask (w) */

#define DMA_ADDR_0          0x00        /* DMA address registers */
#define DMA_ADDR_1          0x02
#define DMA_ADDR_2          0x04
#define DMA_ADDR_3          0x06
#define DMA_ADDR_4          0xC0
#define DMA_ADDR_5          0xC4
#define DMA_ADDR_6          0xC8
#define DMA_ADDR_7          0xCC

#define DMA_CNT_0           0x01        /* DMA count registers */
#define DMA_CNT_1           0x03
#define DMA_CNT_2           0x05
#define DMA_CNT_3           0x07
#define DMA_CNT_4           0xC2
#define DMA_CNT_5           0xC6
#define DMA_CNT_6           0xCA
#define DMA_CNT_7           0xCE

#define DMA_PAGE_0          0x87        /* DMA page registers */
#define DMA_PAGE_1          0x83
#define DMA_PAGE_2          0x81
#define DMA_PAGE_3          0x82
#define DMA_PAGE_5          0x8B
#define DMA_PAGE_6          0x89
#define DMA_PAGE_7          0x8A

/* I/O to memory, no autoinit, increment, single mode */
#define DMA_MODE_READ       0x44

/* memory to I/O, no autoinit, increment, single mode */
#define DMA_MODE_WRITE      0x48

/* pass thru DREQ->HRQ, DACK<-HLDA only */
#define DMA_MODE_CASCADE    0xC0

#include <arch/ia32/portio.h>

static inline void dma_enable(unsigned int dmanr)
{
	if (dmanr <= 3)
		outb(DMA1_MASK, dmanr);
	else
		outb(DMA2_MASK, dmanr & 3);
}

static inline void dma_disable(unsigned int dmanr)
{
	if (dmanr <= 3)
		outb( DMA1_MASK, dmanr | 4);
	else
		outb( DMA2_MASK, (dmanr & 3) | 4);
}

static inline void dma_clearFF(unsigned int dmanr)
{
	if (dmanr <= 3)
		outb(DMA1_CLEAR_FF, 0);
	else
		outb(DMA2_CLEAR_FF, 0);
}

static inline void dma_setmode(unsigned int dmanr, char mode)
{
	if (dmanr <= 3)
		outb( DMA1_MODE, mode | dmanr);
	else
		outb( DMA2_MODE, mode | (dmanr & 3));
}

static inline void dma_setpage(unsigned int dmanr, char pagenr)
{
	switch (dmanr) {
	case 0:
		outb(DMA_PAGE_0, pagenr);
		break;
	case 1:
		outb( DMA_PAGE_1, pagenr);
		break;
	case 2:
		outb( DMA_PAGE_2, pagenr);
		break;
	case 3:
		outb( DMA_PAGE_3, pagenr);
		break;
	case 5:
		outb( DMA_PAGE_5, pagenr & 0xfe);
		break;
	case 6:
		outb( DMA_PAGE_6, pagenr & 0xfe);
		break;
	case 7:
		outb( DMA_PAGE_7, pagenr & 0xfe);
		break;
	}
}

static inline void dma_setaddr(unsigned int dmanr, unsigned int a)
{
	dma_setpage(dmanr, a >> 16);
	if (dmanr <= 3) {
		outb(((dmanr & 3) << 1) + DMA1_BASE, a & 0xff);
		outb(((dmanr & 3) << 1) + DMA1_BASE, (a >> 8) & 0xff);
	} else {
		outb(((dmanr & 3) << 2) + DMA2_BASE, (a >> 1) & 0xff);
		outb(((dmanr & 3) << 2) + DMA2_BASE, (a >> 9) & 0xff);
	}
}

static inline void dma_setcount(unsigned int dmanr, unsigned int count)
{
	count--;
	if (dmanr <= 3) {
		outb(((dmanr & 3) << 1) + 1 + DMA1_BASE, count & 0xff);
		outb(((dmanr & 3) << 1) + 1 + DMA1_BASE, (count >> 8) & 0xff);
	} else {
		outb(((dmanr & 3) << 2) + 2 + DMA2_BASE, (count >> 1) & 0xff);
		outb(((dmanr & 3) << 2) + 2 + DMA2_BASE, (count >> 9) & 0xff);
	}
}

static inline int dma_getresidue(unsigned int dmanr)
{
	int io_port = (dmanr <= 3) ?
			((dmanr & 3) << 1) + 1 + DMA1_BASE :
			((dmanr & 3) << 2) + 2 + DMA2_BASE;

	/* using short to get 16-bit wrap around */
	unsigned short count;

	count = 1 + inb(io_port);
	count += inb(io_port) << 8;

	return (dmanr <= 3) ? count : (count << 1);
}

#endif
