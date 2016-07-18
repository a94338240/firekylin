;/* This file is part of The Firekylin Operating System.
; *
; * Copyright (c) 2016, Liuxiaofeng
; * All rights reserved.
; *
; * This program is free software; you can distribute it and/or modify
; * it under the terms of The BSD License, see LICENSE.
; */

MB2_HEAD_MAGIC		EQU 	0xe85250d6
MB2_HEAD_ARCH_I386	EQU	0
MB2_HEAD_TAG_ADDR	EQU	2
MB2_HEAD_TAG_OPT	EQU	1
MB2_HEAD_TAG_ENT_ADDR	EQU	3
MB2_HEAD_TAG_MOD_ALIGN  EQU	6
MB2_HEAD_TAG_END	EQU	0
MB2_HEAD_LEN		EQU	mbhead_end-mbhead_start
MB2_LOAD_MAGIC		EQU	0x36d76289

bits 32

section .text

global  _start
extern  start

_start:
	cli
	jmp real_start

	align 8
mbhead_start:
	dd MB2_HEAD_MAGIC			; magic
	dd MB2_HEAD_ARCH_I386			; arch
	dd MB2_HEAD_LEN				; len
	dd 0x100000000-(MB2_HEAD_MAGIC+MB2_HEAD_ARCH_I386+MB2_HEAD_LEN)	; check
address_tag_start:
	dw MB2_HEAD_TAG_ADDR
	dw MB2_HEAD_TAG_OPT
	dd address_tag_end-address_tag_start
	dd 0x10008				; header_addr
	dd 0x10000				; load_addr
	dd 0x20000				; load_end_addr
	dd 0x20000				; bss_end_addr
address_tag_end:
enter_address_tag_start:
	dw MB2_HEAD_TAG_ENT_ADDR
	dw MB2_HEAD_TAG_OPT
	dd enter_address_tag_end - enter_address_tag_start
	dd 0x10000				; entry ponit
	dd 0  					; padding
enter_address_tag_end:
module_align_tag:
	dw MB2_HEAD_TAG_MOD_ALIGN
	dw 0
	dd 8
end_tag:
	dw MB2_HEAD_TAG_END
	dw 0
	dd 8
mbhead_end:

real_start:
	mov ax,0x18
	mov ds,ax
	mov es,ax
	mov ss,ax

	; copy grub multiboot info to physical address:0x1000
	mov esi,ebx
	mov edi,0x1000
	mov ecx,0x1000
	rep movsb

setup_page_table:	; set simple page table, map 0~4MB
	xor eax,eax
	xor edi,edi
	mov ecx,4096
	rep stosb
		; PDE
	mov eax,0x100007
	xor edi,edi
	mov [edi],eax
	mov edi,3072
	mov [edi],eax
		; PTE
	mov edi,0x100000
	mov ecx,1024
	mov eax,7
.next:
	mov [edi],eax
	add edi,4
	add eax,0x1000
	loop .next

	xor eax,eax
	mov cr3,eax
	mov eax,cr0
	or  eax,0x80000000
	mov cr0,eax
	mov esp,0xc0010000
	push start
	ret
