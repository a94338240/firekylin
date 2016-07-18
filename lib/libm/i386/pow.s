;/* This file is part of The Firekylin Operating System.
; *
; * Copyright (c) 2016, Liuxiaofeng
; * All rights reserved.
; *
; * This program is free software; you can distribute it and/or modify
; * it under the terms of The BSD License, see LICENSE.
; */

global pow

; x^y=2^(y*log(base 2) x)

pow:
	fld    qword [esp+12]
	fld    qword [esp+4]
	fyl2x			; st0=st1*log(base 2) st0
	f2xm1			; st0=st0*2^st1-1
	fld1
	faddp st1,st0
	ret
