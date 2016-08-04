/*  This file is part of The Firekylin Operating System.
 *
 *  Copyright 2016 Liuxiaofeng
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef _LIMITS_H
#define _LIMITS_H

/* definitions of char */
#define CHAR_BIT	          8
#define CHAR_MAX	        127
#define CHAR_MIN	       -128
#define UCHAR_MAX	        255

/* definitions of short */
#define SHRT_MIN	     -32768
#define SHRT_MAX	      32767
#define USHRT_MAX	     65535U

/* definitions of int */
#define INT_MIN		-2147483648
#define INT_MAX		 2147483647
#define UINT_MAX        4294967295U

/* Definitions of long */
#define LONG_MIN	-LONG_MAX-1
#define LONG_MAX	 2147483647
#define ULONG_MAX	4294967295U

#define PATH_MAX	        512

#define RAND_MAX	0x7ffffffff

#endif
