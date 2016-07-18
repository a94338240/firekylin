;/* This file is part of The Firekylin Operating System.
; *
; * Copyright (c) 2016, Liuxiaofeng
; * All rights reserved.
; *
; * This program is free software; you can distribute it and/or modify
; * it under the terms of The BSD License, see LICENSE.
; */

global exp

exp:				;e^x=2^(x*log(base 2) e)
	fld    qword [esp+4]
	fldl2e			; st0=log(base 2) e
	fmulp
	f2xm1			; st0=st0*2^st1-1
	fld1
	faddp st1,st0
	ret
