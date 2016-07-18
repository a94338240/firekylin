#/* This file is part of The Firekylin Operating System.
# *
# * Copyright (c) 2016, Liuxiaofeng
# * All rights reserved.
# *
# * This program is free software; you can distribute it and/or modify
# * it under the terms of The BSD License, see LICENSE.
# */

complie:
	-make -C lua
	-make -C tcc
#	-make -C nasm

install:
	-make PREFIX=$(PREFIX)  install -C lua
	-make PREFIX=$(PREFIX)  install -C tcc
#	-make PREFIX=$(PREFIX)  install -C nasm

clean: 
	-make clean -C lua
	-make clean -C tcc
#	-make clean -C nasm
