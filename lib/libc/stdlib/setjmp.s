;/* This file is part of The Firekylin Operating System.
; *
; * Copyright (c) 2016, Liuxiaofeng
; * All rights reserved.
; *
; * This program is free software; you can distribute it and/or modify
; * it under the terms of The BSD License, see LICENSE.
; */

; /* see: http://tieba.baidu.com/p/3373589465 */

section .text
global setjmp,longjmp

setjmp:
	mov ecx, [esp]
	mov eax, [esp+4]
	mov [eax],    ebx
	mov [eax+4],  ebp
	mov [eax+8],  esi
	mov [eax+12], edi
	mov [eax+16], esp
	mov [eax+20], ecx
	xor eax, eax
	ret

longjmp:
	mov eax, [esp+8]
	mov ecx, [esp+4]
	mov ebx, [ecx]
	mov ebp, [ecx+4]
	mov esi, [ecx+8]
	mov edi, [ecx+12]
	mov esp, [ecx+16]
	mov edx, [ecx+20]
	mov [esp], edx
	ret
