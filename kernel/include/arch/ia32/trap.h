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

#ifndef _IA32_TRAP_H
#define _IA32_TRAP_H

struct trapframe {
	unsigned int  eax;
	unsigned int  ebx;
	unsigned int  ecx;
	unsigned int  edx;
	unsigned int  edi;
	unsigned int  esi;
	unsigned int  ebp;
	unsigned int  ds;
	unsigned int  es;
	unsigned int  nr;
	unsigned int  err;
	unsigned int  eip;
	unsigned int  cs;
	unsigned int  eflags;
	unsigned int  esp;
	unsigned int  ss;
};

#define T_DIVIDE         0      /* divide error				*/
#define T_DEBUG          1      /* debug exception			*/
#define T_NMI            2      /* non-maskable interrupt		*/
#define T_BRKPT          3      /* breakpoint				*/
#define T_OFLOW          4      /* overflow				*/
#define T_BOUND          5      /* bounds check				*/
#define T_ILLOP          6      /* illegal opcode 			*/
#define T_DEVICE         7      /* device not available			*/
#define T_DBLFLT         8      /* double fault				*/
#define T_COPROC         9      /* reserved (not used since 486)	*/
#define T_TSS           10      /* invalid task switch segment		*/
#define T_SEGNP         11      /* segment not present			*/
#define T_STACK         12      /* stack exception			*/
#define T_GPFLT         13      /* general protection fault		*/
#define T_PGFLT         14      /* page fault				*/
#define T_RES           15      /* reserved				*/
#define T_FPERR         16      /* floating point error			*/
#define T_ALIGN         17      /* aligment check			*/
#define T_MCHK          18      /* machine check			*/
#define T_SIMDERR       19      /* SIMD floating point error		*/

#define IRQ_CLOCK       32
#define IRQ_KBD         33
#define IRQ_COM1        36
#define IRQ_IDE         46

extern void set_trap_handle(int index, void (*fn)(struct trapframe *tf));

#endif
