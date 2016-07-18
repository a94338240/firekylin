;/* This file is part of The Firekylin Operating System.
; *
; * Copyright (c) 2016, Liuxiaofeng
; * All rights reserved.
; *
; * This program is free software; you can distribute it and/or modify
; * it under the terms of The BSD License, see LICENSE.
; */

	bits 16
start:
	mov ax,0x07c0
	mov ds,ax
	mov ax,0x800
	mov es,ax
	xor si,si
	xor di,di
	mov cx,256
	rep movsw
	jmp 0x800:disp_load

disp_load:
	mov ax,0x800
	mov ds,ax
	mov es,ax
	mov ss,ax
	mov sp,0x2000
	mov cx,10
	mov di,info
	mov ah,0x0e
	mov bx,0x10
.next:
	mov al,[di]
	int 0x10
	inc di
	loop .next

load_kernel:
	mov ax,0x1000
	mov es,ax    	; buf es:bx
	mov dx,0     	; DH-_head,DL--driver
	mov cl,1    	; bit 0-5 begin socter number,ch:cyl number.
	mov ch,1
.loop1:
	xor bx,bx
	mov ah,0x2
	mov al,18	; ah:cmd 2--read,AL:read number of socters
	int 0x13
	jc  .die
	inc ch
	cmp ch,[size]
	je  ok_load
	mov ax,es
	add ax,0x20*18
	mov es,ax
		     	; echo .
	mov ah,0x0e
	mov bx,0x10
	mov al,'.'
	int 0x10
	jmp .loop1
.die:	jmp $
ok_load:	     	; kill floppy motor
	mov dx,0x3f2
	mov al,0
	out dx,al

clear_screen:
	mov ax,0x0600
	xor cx,cx
	mov dh,24
	mov al,79
	mov bh,0x07
	int 0x10

open_A20:
	cli
	in  al,   0x92
	or  al,   2
	out 0x92, al
	lgdt [gdt_48]
	mov eax,  cr0
	or  eax,  1
	mov cr0,  eax
	jmp dword 0x10:0x10000

info:
	db "Loading..."
	align 8
gdt:
	dd 0,0
	dd 0,0
	dd 0x0000ffff,0x00cf9a00
	dd 0x0000ffff,0x00cf9200
	dd 0x0000ffff,0x00cbfa00
	dd 0x0000ffff,0x00cbf200
gdt_48:
	dw 0x100-1
	dd gdt+0x8000

	times 508-($-$$) db 0
size:	dw  8
	dw  0xaa55
