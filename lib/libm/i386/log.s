;/* This file is part of The Firekylin Operating System.
; *
; * Copyright (c) 2016, Liuxiaofeng
; * All rights reserved.
; *
; * This program is free software; you can distribute it and/or modify
; * it under the terms of The BSD License, see LICENSE.
; */

global log

; log (base e) m=log (base e) 2 * log (base 2) m

log:
	fldln2			; st0=log (base e) 2
	fld  qword [esp+4]
	fyl2x			; st0=st1 *log (base 2) st0
	ret
