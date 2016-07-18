;/* This file is part of The Firekylin Operating System.
; *
; * Copyright (c) 2016, Liuxiaofeng
; * All rights reserved.
; *
; * This program is free software; you can distribute it and/or modify
; * it under the terms of The BSD License, see LICENSE.
; */

global log10

;log (base 10) m=log (base 10) 2 * log (base 2) m

log10:
	fldlg2			; st0=log (base 10) 2
	fld  qword [esp+4]
	fyl2x			; st0=st1 *log (base 2) st0
	ret
