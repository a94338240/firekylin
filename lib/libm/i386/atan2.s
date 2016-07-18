;/* This file is part of The Firekylin Operating System.
; *
; * Copyright (c) 2016, Liuxiaofeng
; * All rights reserved.
; *
; * This program is free software; you can distribute it and/or modify
; * it under the terms of The BSD License, see LICENSE.
; */

global atan2

atan2:
	fld  qword [esp+4]
	fld  qword [esp+12]
	fpatan
	ret
