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
