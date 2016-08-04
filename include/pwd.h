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

#ifndef _PWD_H
#define _PWD_H

#include <sys/types.h>
#include <stdio.h>

struct passwd {
	char *pw_name; 		/* Username.  		*/
	char *pw_passwd; 	/* Password.  		*/
	uid_t pw_uid; 		/* User ID.  		*/
	gid_t pw_gid; 		/* Group ID.  		*/
	char *pw_gecos; 	/* Real name.  		*/
	char *pw_dir; 		/* Home directory.  	*/
	char *pw_shell; 	/* Shell program.  	*/
};

extern struct passwd *getpwuid(uid_t uid);
extern struct passwd *getpwnam(const char *name);
extern struct passwd *getpwent(void);
extern void setpwent(void);
extern void endpwent(void);
extern int  putpwent(const struct passwd *p, FILE *stream);

#endif
