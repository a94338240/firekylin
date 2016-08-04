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

extern main, exit, _edata, _end
global _start,environ

section .text
_start:
	mov  ax,ss
	mov  ds,ax
	mov  es,ax
	mov  eax,[esp+8]
	mov  dword [environ],eax
	mov  edi, _edata
	mov  ecx, _end
	sub  ecx, edi
	xor  eax,eax
	rep  stosb
	call main
	push eax
	call exit
	mov  eax,4
	int  0x30

section .data
environ:
	dd 0
