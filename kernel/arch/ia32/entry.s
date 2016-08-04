;/*  This file is part of The Firekylin Operating System.
; *
; *  Copyright 2016 Liuxiaofeng
; *
; *  Licensed under the Apache License, Version 2.0 (the "License");
; *  you may not use this file except in compliance with the License.
; *  You may obtain a copy of the License at
; *
; *      http://www.apache.org/licenses/LICENSE-2.0
; *
; *  Unless required by applicable law or agreed to in writing, software
; *  distributed under the License is distributed on an "AS IS" BASIS,
; *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; *  See the License for the specific language governing permissions and
; *  limitations under the License.
; */

global  div_zero, debug, nmi, breakpoint, overflow, bound,invalid_opcode
global  device_not_invalid,double_fault,coprocessor_overrun,invalid_tss
global  segment_not_exsit,stack,general_protection,page_fault
global  reserved,coprocessor,align_check,machine_check,simd_float
global  hwint0,hwint1,hwint2,hwint3,hwint4,hwint5,hwint6,hwint7
global  hwint8,hwint9,hwintA,hwintB,hwintC,hwintD,hwintE,hwintF
global  syscall

extern  execption, do_signal, syscall_table

div_zero:
	push 0
	push 0
	jmp  _execption
debug:
	push 0
	push 1
	jmp  _execption
nmi:
	push 0
	push 2
	jmp  _execption
breakpoint:
	push 0
	push 3
	jmp  _execption
overflow:
	push 0
	push 4
	jmp  _execption
bound:
	push 0
	push 5
	jmp  _execption
invalid_opcode:
	push 0
	push 6
	jmp  _execption
device_not_invalid:
	push 0
	push 7
	jmp  _execption
double_fault:
	push 8
	jmp  _execption
coprocessor_overrun:
	push 0
	push 9
	jmp  _execption
invalid_tss:
	push 10
	jmp  _execption
segment_not_exsit:
	push 11
	jmp  _execption
stack:
	push 12
	jmp  _execption
general_protection:
	push 13
	jmp  _execption
page_fault:
	push 14
	jmp  _execption
reserved:
	push 0
	push 15
	jmp  _execption
coprocessor:
	push 0
	push 16
	jmp  _execption
align_check:
	push 17
	jmp  _execption
machine_check:
	push 0
	push 18
	jmp  _execption
simd_float:
	push 0
	push 19
	jmp  _execption
hwint0:
	push 0
	push 0x20
	jmp  _execption
hwint1:
	push 0
	push 0x21
	jmp  _execption
hwint2:
	push 0
	push 0x22
	jmp  _execption
hwint3:
	push 0
	push 0x23
	jmp  _execption
hwint4:
	push 0
	push 0x24
	jmp  _execption
hwint5:
	push 0
	push 0x25
	jmp  _execption
hwint6:
	push 0
	push 0x26
	jmp  _execption
hwint7:
	push 0
	push 0x27
	jmp  _execption
hwint8:
	push 0
	push 0x28
	jmp  _execption
hwint9:
	push 0
	push 0x29
	jmp  _execption
hwintA:
	push 0
	push 0x2a
	jmp  _execption
hwintB:
	push 0
	push 0x2b
	jmp  _execption
hwintC:
	push 0
	push 0x2c
	jmp  _execption
hwintD:
	push 0
	push 0x2d
	jmp  _execption
hwintE:
	push 0
	push 0x2e
	jmp  _execption
hwintF:
	push 0
	push 0x2f
_execption:
	push es
	push ds
	push ebp
	push esi
	push edi
	push edx
	push ecx
	push ebx
	push eax
	mov  ax,0x10
	mov  ds,ax
	mov  es,ax
	call execption
	jmp  _syscall_return

syscall:
	sub  esp,8
	push es
	push ds
	push ebp
	push esi
	push edi
	push edx
	push ecx
	push ebx
	mov  ebx,0x10
	mov  ds,bx
	mov  es,bx
	sti
	call [syscall_table+4*eax]
	push eax
_syscall_return:
	call do_signal
	cli
	pop eax
	pop ebx
	pop ecx
	pop edx
	pop edi
	pop esi
	pop ebp
	pop ds
	pop es
	add esp,8
	iret
