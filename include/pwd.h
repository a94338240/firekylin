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