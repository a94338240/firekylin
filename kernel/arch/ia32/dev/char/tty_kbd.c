/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <kernel.h>
#include <tty.h>
#include <arch/ia32/trap.h>
#include <arch/ia32/portio.h>

/* 
 * keyboard intr rountine 
 *
 *                        casey  2016/7/18
 */

#define false       0
#define true        1
typedef char bool;

static char fCAPS = false;
static char fSHFT_L = false;
static char fSHFT_R = false;
static char fCTRL_L = false;
static char fCTRL_R = false;
static char fALT_L = false;
static char fALT_R = false;
static char fSCRLL = false; /* scroll lock */
static char fNMLOCK = false; /* number lock */

static void proc_final_char(char ch)
{
	PUTCH(&(tty_table[fg_console + 1]->raw), ch);
	copy_to_cook(tty_table[fg_console + 1]);
}

static void combo_key(unsigned long key, bool fmake)
{
	switch (key) {

	case SHIFT_L:
		fSHFT_L = fmake;
		break;

	case SHIFT_R:
		fSHFT_R = fmake;
		break;

	case CTRL_L:
		fCTRL_L = fmake;
		break;

	case CTRL_R:
		fCTRL_R = fmake;
		break;

	case ALT_L:
		fALT_L = fmake;
		break;

	case ALT_R:
		fALT_R = fmake;
		break;

	case CAPS_LOCK:
		if (fmake) {
			fCAPS = !fCAPS;
		}
		break;

	case NUM_LOCK:
		if (fmake) {
			fNMLOCK = !fNMLOCK;
		}
		break;

	case SCROLL_LOCK:
		if (fmake) {
			fSCRLL = !fSCRLL;
		}
		break;
	}

}

static void make_key(unsigned long key, bool combo)
{
	char ch = -1;

	if (combo) {
		key |= fSHFT_L ? FLAG_SHIFT_L : 0;
		key |= fSHFT_R ? FLAG_SHIFT_R : 0;

		key |= fCTRL_L ? FLAG_CTRL_L : 0;
		key |= fCTRL_R ? FLAG_CTRL_R : 0;

		key |= fALT_L ? FLAG_ALT_L : 0;
		key |= fALT_R ? FLAG_ALT_R : 0;
	}

	if (!(key & FLAG_EXT)) { /* visible */
		ch = (unsigned char) key;
	} else {
		switch (key & MASK_RAW) {
		case BACKSPACE:
			ch = '\b';
			break;

		case ESC:
			//printk ("esc");
			break;

		case TAB:
			ch = '\t';
			break;

		case ENTER:
			ch = '\n';
			break;

		case F1:
		case F2:
		case F3:
			select_con(key - F1);
			break;

		case F4:
		case F5:
		case F6:
		case F7:
		case F8:
		case F9:
		case F10:
			break;

		case F11:
			dump_task();
			break;

		case PAUSEBREAK:
			printk("pausebreak");
			break;

		case PRINTSCREEN:
			printk("print screen");
			break;

		case PAGEUP:
			printk("page up");
			break;

		case PAGEDOWN:
			printk("page down");
			break;

		case END:
			printk("end");
			break;

		case DELETE:
			printk("delete");
			break;

		case INSERT:
			printk("insert");
			break;

		case HOME:
			printk("home KEY \n");
			break;

		case UP:
			printk("up");
			break;

		case DOWN:
			printk("down");
			break;

		case LEFT:
			printk("left");
			break;

		case RIGHT:
			printk("right");
			break;

		case GUI_L:
			printk("winL");
			break;

		case GUI_R:
			printk("winR");
			break;

		case APPS:
			printk("rightclick");
			break;

		default:
			if (key >= PAD_SLASH && key <= PAD_9) {
				switch (key) {
				case PAD_SLASH:
					ch = '/';
					break;

				case PAD_STAR:
					ch = '*';
					break;

				case PAD_MINUS:
					ch = '-';
					break;

				case PAD_PLUS:
					ch = '+';
					break;

				case PAD_ENTER:
					ch = '\n';
					break;

				default:
					if (fNMLOCK) {
						if (key >= PAD_0 && key <= PAD_9) {
							ch = key - PAD_0 + 0x30;
						} else if (key == PAD_DOT) {
							ch = '.';
						}
					} else {
						switch (key) {
						case PAD_HOME:
							key = HOME;
							break;

						case PAD_LEFT:
							key = LEFT;
							break;
						}
					}
					break;
				}
				break;
			}
		}
	}

	if (ch >= 0) {
		/*
		 * proceed with the final char
		 */
		proc_final_char(ch);
	}

	/*
	 * Do something with the raw key code
	 */

}

static void decode_scode(struct tty_struct *tty)
{
	unsigned char code = 0;
	unsigned char codet = 0;
	int col = 0;
	struct tty_buf *buf = &tty->kbq;
	unsigned long key = 0, *p_row = (void *) 0;
	bool fMAKE = false; /* need make code ? */
	bool fE0 = false; /* 0xE0 code contains */

	/*
	 * fMAKE : true     : pressed
	 *       : false    : released
	 *
	 */

	while (!isempty(buf)) {

		key = 0;
		fE0 = false;

		/*
		 * first to check the count of codes ,so we need
		 * peek the queue instead of deque them ....
		 * if the number equals ,then check the codemap
		 * and decode the VK,if the codes don't match the
		 * codemap ,we still deque them in case of the
		 * que full situationi.
		 *
		 *                              casey 2016/7/18
		 */
		code = PEEKCH(buf);

		switch (code) {
		case 0xE1:
			/*
			 * count queued codes
			 * less than 3 code,return to wait others
			 */
			if (buf->count < 3) {
				return;
			}

			/*
			 * decode as PAUSEBREAK UP/DOWN
			 */

			GETCH(buf); /* deque the first code */
			codet = GETCH(buf); /* get the 2nd code */

			if (codet == pausebrk_up[1]) { /* up */
				codet = GETCH(buf); /* get the 3rd code */
				if (codet == pausebrk_up[2]) {
					key = PAUSEBREAK;
				}
			} else if (codet == pausebrk_down[1]) {/* down */
				codet = GETCH(buf); /* get the 3rd code */
				if (codet == pausebrk_down[2]) {
					key = PAUSEBREAK;
				}
			}

			break;

		case 0xE0:
			/*
			 * count queued codes
			 * less than 2 codes ,return to wait others
			 */
			if (buf->count < 2)
				return;

			fE0 = true;

			/*
			 * print screen UP/DOWN
			 *
			 * VERY SAD about this ,print screen is not in the keycodemap
			 * so we need handle it by ourselves .
			 *
			 */
			GETCH(buf); /* deque the first code */
			codet = PEEKCH(buf); /* get the 2nd code */

			if (codet == prtscrn_up[1]) { /* UP */
				fMAKE = false;
				key = PRINTSCREEN;
				fE0 = true;
				GETCH(buf);
			} else if (codet == prtscrn_down[1]) { /* DOWN */
				fMAKE = true;
				key = PRINTSCREEN;
				fE0 = true;
				GETCH(buf);
			} else {
				//
				code = codet;
			}

			break;
		}

		if (key != PAUSEBREAK && key != PRINTSCREEN) {
			col = 0; /* normal column */
			p_row = (unsigned long *) &keymap[(code & 0x7F)
					* MAP_COLS];

			bool caps = fSHFT_L || fSHFT_R;
			if (fCAPS) {
				if (p_row[0] >= 'a' && p_row[1] <= 'z') {
					caps = !caps;
				}
			}

			if (caps) /* shift  column */
				col = 1;
			if (fE0) { /* combo  column */
				col = 2;
				fE0 = false;
			}

			fMAKE = ((code >> 7) == 0);

			key = p_row[col];

			/*
			 * deque this code
			 */
			GETCH(buf);

			combo_key(key, fMAKE);
			if (fMAKE)
				make_key(key, true);

		} else if (PAUSEBREAK == key) {
			make_key(key, false);
		} else if (PRINTSCREEN == key) {
			make_key(key, false);
		}

	}
}

static void do_kbd(struct trapframe *tf)
{
	unsigned char ch = inb(KBDATA_PORT); /* read a byte */
	struct tty_struct *tty = tty_table[fg_console + 1]; /* store to kbd queue */

	PUTCH(&(tty->kbq), ch); /* store to kbd queue */
	//printk ("%x ",ch);
	decode_scode(tty); /* decode scan code */
	outb(0x20, 0x20); /* clear mask */
}

void kbd_init(void)
{
	set_trap_handle(0x21, &do_kbd);
	outb(0x21, inb(0x21) & ~2);
}
