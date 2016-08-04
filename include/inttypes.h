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

#ifndef _INTTYPES_H
#define _INTTYPES_H

#include <stdint.h>

#define _scn8			"hh"
#define _pri8			""
#define INT8_C(x)		x
#define UINT8_C(x)		x ## U

#define _scn16			"h"
#define _pri16			""
#define INT16_C(x)		x
#define UINT16_C(x)		x ## U

#define _scn32			""
#define _pri32			""
#define INT32_C(x)		x
#define UINT32_C(x)		x ## U

#define _scn64			"ll"
#define _pri64			"ll"
#define INT64_C(x)		x ## LL
#define UINT64_C(x)		x ## ULL

#define PRId8			_pri8  "d"
#define PRId16			_pri16 "d"
#define PRId32			_pri32 "d"
#define PRId64			_pri64 "d"

#define PRIi8			_pri8  "i"
#define PRIi16			_pri16 "i"
#define PRIi32			_pri32 "i"
#define PRIi64			_pri64 "i"

#define PRIo8			_pri8  "o"
#define PRIo16			_pri16 "o"
#define PRIo32			_pri32 "o"
#define PRIo64			_pri64 "o"

#define PRIu8			_pri8  "u"
#define PRIu16			_pri16 "u"
#define PRIu32			_pri32 "u"
#define PRIu64			_pri64 "u"

#define PRIx8			_pri8  "x"
#define PRIx16			_pri16 "x"
#define PRIx32			_pri32 "x"
#define PRIx64			_pri64 "x"

#define PRIX8			_pri8  "X"
#define PRIX16			_pri16 "X"
#define PRIX32			_pri32 "X"
#define PRIX64			_pri64 "X"

#define SCNd8			_scn8  "d"
#define SCNd16			_scn16 "d"
#define SCNd32			_scn32 "d"
#define SCNd64			_scn64 "d"

#define SCNi8			_scn8  "i"
#define SCNi16			_scn16 "i"
#define SCNi32			_scn32 "i"
#define SCNi64			_scn64 "i"

#define SCNo8			_scn8  "o"
#define SCNo16			_scn16 "o"
#define SCNo32			_scn32 "o"
#define SCNo64			_scn64 "o"

#define SCNu8			_scn8  "u"
#define SCNu16			_scn16 "u"
#define SCNu32			_scn32 "u"
#define SCNu64			_scn64 "u"

#define SCNx8			_scn8  "x"
#define SCNx16			_scn16 "x"
#define SCNx32			_scn32 "x"
#define SCNx64			_scn64 "x"

#define INT8_MIN		INT8_C(-128)
#define INT8_MAX		INT8_C(127)
#define UINT8_MAX		UINT8_C(255)

#define INT16_MIN		INT16_C(-32768)
#define INT16_MAX		INT16_C(32767)
#define UINT16_MAX		UINT16_C(65535)

#define INT32_MIN		INT32_C(-2147483648)
#define INT32_MAX		INT32_C(2147483647)
#define UINT32_MAX		UINT32_C(4294967295)

#define INT64_MIN		INT64_C(-9223372036854775808)
#define INT64_MAX		INT64_C(9223372036854775807)
#define UINT64_MAX		UINT64_C(18446744073709551615)

#endif
