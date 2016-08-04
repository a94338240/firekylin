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

#include <firekylin/kernel.h>
#include <firekylin/driver.h>

extern void tty_init(void);
extern void mem_init(void);
extern void rd_init(void);
extern void hd_init(void);

struct char_device  *char_table[DEV_CHAR_MAX + 1];
struct block_device *blk_table[DEV_BLK_MAX + 1];

void dev_init(void)
{
	/* init char dev */
	tty_init();
	mem_init();

	/* init block dev */
	rd_init();
	hd_init();
}
