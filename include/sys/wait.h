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

/*
 *    exit_code:	high byte	low byte
 *    	normal exit	  status	   0
 *    	signal exit	    0  		 signal
 *    	job control	  signal	  0177
 */

#ifndef _SYS_WAIT_H
#define _SYS_WAIT_H

#include <sys/types.h>

#define	WNOHANG		0x01	/* Not hang if no status, return immediately. */
#define WUNTRACED	0x02	/* Report status of stopped child process.    */

#define WIFEXITED(s)	(!((s)&0xFF))			/* normal exit 	*/
#define WIFSIGNALED(s)	(((unsigned int)(s)-1)&xFFFF) 	/* signal exit 	*/
#define WIFSTOPPED(s)	(((s)&0xFF)==0x7F)		/* job control	*/
#define WEXITSTATUS(s)	(((s) >> 8) & 0377)		/* exit status 	*/
#define WTERMSIG(s)	((s)&0x7F)			/* sig value 	*/
#define WSTOPSIG(s)	(((s)>>8)&0xFF)			/* stop signal 	*/

pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);

#endif
