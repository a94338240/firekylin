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

global log

; log (base e) m=log (base e) 2 * log (base 2) m

log:
	fldln2			; st0=log (base e) 2
	fld  qword [esp+4]
	fyl2x			; st0=st1 *log (base 2) st0
	ret
