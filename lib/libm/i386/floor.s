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

global floor

floor:
	push ebp
	mov  ebp,esp
	sub  esp,8
	fstcw [ebp-4]  ;  -4 =old CW -2 =new CW
	fwait
	mov  ax,[ebp-4]
	and  ax,0xf3ff
	or   ax,0x0400
	mov  [ebp-2],ax
	fldcw[ebp-2]
	fld  qword [ebp+8]
	frndint
	fldcw [ebp-4]
	leave
	ret
