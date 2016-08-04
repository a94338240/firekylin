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

#ifndef _TERMIOS_H
#define _TERMIOS_H

typedef unsigned short tcflag_t;

struct termios {
	tcflag_t 	c_iflag;
	tcflag_t 	c_oflag;
	tcflag_t 	c_cflag;
	tcflag_t 	c_lflag;
	unsigned char	c_cc[12];
};

/* Values for termios c_iflag bit.  */
#define ICRNL		0x0001	/* map CR to NL on input */
#define IGNBRK		0x0002	/* ignore break */
#define IGNCR		0x0004	/* ignore CR */
#define INLCR		0x0008	/* map NL to CR on input */

/* Values for termios c_oflag bit.  */
#define ONLCR		0x0001

/* Values for termios c_lflag bit.  */
#define ISIG		0x0001
#define ICANON		0x0002
#define ECHO		0x0004

/* Indices into c_cc array.  Default values in parentheses. */
#define VEOF                 0	/* cc_c[VEOF] = EOF char (^D) */
#define VEOL                 1	/* cc_c[VEOL] = EOL char (undef) */
#define VERASE               2	/* cc_c[VERASE] = ERASE char (^H) */
#define VINTR                3	/* cc_c[VINTR] = INTR char (DEL) */
#define VKILL                4	/* cc_c[VKILL] = KILL char (^U) */
#define VMIN                 5	/* cc_c[VMIN] = MIN value for timer */
#define VQUIT                6	/* cc_c[VQUIT] = QUIT char (^\) */
#define VTIME                7	/* cc_c[VTIME] = TIME value for timer */
#define VSUSP                8	/* cc_c[VSUSP] = SUSP (^Z, ignored) */
#define VSTART               9	/* cc_c[VSTART] = START char (^S) */
#define VSTOP               10	/* cc_c[VSTOP] = STOP char (^Q) */

struct winsize
{
	unsigned short	ws_row;		/* rows, in characters */
	unsigned short	ws_col;		/* columns, in characters */
	unsigned short	ws_xpixel;	/* horizontal size, pixels */
	unsigned short	ws_ypixel;	/* vertical size, pixels */
};

/* tty ioctl cmds */
enum{
	TTY_IOCTL_CMD = 0x7700,
	TCGETS,			/* get tty termios  	*/
	TCSETS,			/* set tty termios	*/
};

#endif
