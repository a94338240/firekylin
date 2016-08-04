/*
 * Copyright (C) 1995, 1996 Nat Friedman <ndf@linux.mit.edu>.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <grp.h>

/*
 * If scaling is not dynamic, the buffers will be statically allocated, and
 * maximums must be chosen.  GR_MAX_LINE_LEN is the maximum number of
 * characters per line in the group file.  GR_MAX_MEMBERS is the maximum
 * number of members of any given group.
 */
#define GR_MAX_LINE_LEN 128

/* GR_MAX_MEMBERS = (GR_MAX_LINE_LEN-(24+3+6))/9 */
#define GR_MAX_MEMBERS 11

/*
 * This is the core group-file read function.  It behaves exactly like
 * getgrent() except that it is passed a file descriptor.  getgrent()
 * is just a wrapper for this function.
 */
struct group *__getgrent(int grp_fd)
{

	static char line_buff[GR_MAX_LINE_LEN];
	static char *members[GR_MAX_MEMBERS];
	static struct group group;
	char *ptr;
	char *field_begin;
	int member_num;
	char *endptr;
	int line_len;

	/* We use the restart label to handle malformatted lines */
	restart:

	/* Read the line into the static buffer */
	if ((line_len = read(grp_fd, line_buff, GR_MAX_LINE_LEN)) <= 0)
		return NULL;
	field_begin = strchr(line_buff, '\n');
	if (field_begin != NULL)
		lseek(grp_fd, (long) (1 + field_begin - (line_buff + line_len)),
		SEEK_CUR);
	else { /* The line is too long - skip it :-\ */

		do {
			if ((line_len = read(grp_fd, line_buff, GR_MAX_LINE_LEN))
					<= 0)
				return NULL;
		} while (!(field_begin = strchr(line_buff, '\n')));
		lseek(grp_fd, (long) ((field_begin - line_buff) - line_len + 1),
		SEEK_CUR);
		goto restart;
	}
	if (*line_buff == '#' || *line_buff == ' ' || *line_buff == '\n'
			|| *line_buff == '\t')
		goto restart;
	*field_begin = '\0';

	/* Now parse the line */
	group.gr_name = line_buff;
	ptr = strchr(line_buff, ':');
	if (ptr == NULL)
		goto restart;
	*ptr++ = '\0';

	group.gr_passwd = ptr;
	ptr = strchr(ptr, ':');
	if (ptr == NULL)
		goto restart;
	*ptr++ = '\0';

	field_begin = ptr;
	ptr = strchr(ptr, ':');
	if (ptr == NULL)
		goto restart;
	*ptr++ = '\0';

	group.gr_gid = (gid_t) strtoul(field_begin, &endptr, 10);
	if (*endptr != '\0')
		goto restart;

	member_num = 0;
	field_begin = ptr;

	while ((ptr = strchr(ptr, ',')) != NULL) {
		*ptr = '\0';
		ptr++;
		members[member_num] = field_begin;
		field_begin = ptr;
		member_num++;
	}
	if (*field_begin == '\0')
		members[member_num] = NULL;
	else {
		members[member_num] = field_begin;
		members[member_num + 1] = NULL;
	}
	group.gr_mem = members;
	return &group;
}

struct group *getgrgid(const gid_t gid)
{
	struct group *group;
	int grp_fd;

	if ((grp_fd = open(GRP_FILE, O_READ)) < 0)
		return NULL;

	while ((group = __getgrent(grp_fd)) != NULL)
		if (group->gr_gid == gid) {
			close(grp_fd);
			return group;
		}

	close(grp_fd);
	return NULL;
}

struct group *getgrnam(const char *name)
{
	int grp_fd;
	struct group *group;

	if (name == NULL) {
		errno = EINVAL;
		return NULL;
	}

	if ((grp_fd = open(GRP_FILE, O_READ)) < 0)
		return NULL;

	while ((group = __getgrent(grp_fd)) != NULL)
		if (!strcmp(group->gr_name, name)) {
			close(grp_fd);
			return group;
		}

	close(grp_fd);
	return NULL;
}
