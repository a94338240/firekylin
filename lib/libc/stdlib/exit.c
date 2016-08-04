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

#include <stdlib.h>
#include <sys/unistd.h>

typedef void (*atexit_func_t)(void);

atexit_func_t atexit_func_tab[32];
int atexit_func_num;

void exit(int exit_code)
{
	//atexit_func_t fn;
	//for (int i = 0; i < atexit_func_num; i++) {
	//	printf("\nexit3:comehere");
	//	fn = atexit_func_tab[i];
	//	(fn)();
	//}
	_exit(exit_code);
}
