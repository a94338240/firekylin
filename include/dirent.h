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

#ifndef _DIRENT_H
#define _DIRENT_H

#include <sys/types.h>

#define MAX_NAME_LEN	255
struct dirent{
	ino_t  d_ino;
	size_t d_reclen;
	char   d_name[MAX_NAME_LEN+1];
};

typedef struct {
	int    dd_fd;
} DIR;

DIR           *opendir(char *filename);
struct dirent *readdir(DIR *dir);
void           rewinddir(DIR *dir);
int            closedir(DIR *dir);

#endif
