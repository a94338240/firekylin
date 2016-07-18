/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MODE_VIEW	1
#define MODE_INSERT	2
#define MODE_REPLACE	3

#define COLS		80
#define LINES		25
#define MAX_CHARS 	80
#define MAX_LINES	300

int cur_x, cur_y;
int top;
int lines;
int fd;

struct line {
	long cnt;
	char data[MAX_CHARS];
};
struct line buf[MAX_LINES];

void read_file()
{
	char ch;
	int i = 0;
	while (read(fd, &ch, 1)) {
		buf[i].data[buf[i].cnt++] = ch;
		if (ch == '\n')
			i++;
	}
	lines = ++i;
}

void draw_win()
{
	int i;

	printf("\033[1;1H");
	for (int i = 0; i < 8 * 24; i++)
		printf("          ");
	printf("\033[1;1P");
	for (i = 0; i < lines; i++)
		write(0, buf[i].data, buf[i].cnt);
	while (i++ < 24)
		printf("\033[%d;1H~\n", i);
	printf("\033[1;1H");
}

void insert(char ch)
{
	struct line *line = &(buf[top + cur_y]);
	for (int i = line->cnt; i > cur_x; i--)
		line->data[i + 1] = line->data[i];
	line->data[cur_x++] = ch;
	line->cnt++;
	printf("\033[1;%dH", cur_y);
	write(0, line->data, line->cnt);
	printf("\033[%d;%dH", cur_x, cur_y);
}

void save()
{
	lseek(fd, 0, 0);
	for (int i = 0; i < lines; i++)
		write(fd, buf[i].data, buf[i].cnt);
	close(fd);
}

int main(int argc, char **argv)
{
	cur_x = 0;
	cur_y = 0;
	top = 0;

	char ch;

	if (argc >= 2)
		fd = open(argv[1], O_CREAT | O_RDWR);
	else
		fd = open("default.vi", O_CREAT | O_RDWR);
	if (fd < 0) {
		printf("%s", strerror(errno));
		exit(0);
	}
	memset(buf, 0, sizeof(buf));

	read_file();
	printf("\033[0;0E");
	draw_win();

	cur_x = 0;
	cur_y = 0;
	top = 0;
	int mode = MODE_VIEW;
	while (1) {
		read(0, &ch, 1);
		//printf("\0330;24P:%c",ch);
		switch (mode) {
		case MODE_VIEW:
			switch (ch) {
			case 'h':
				if (cur_x > 0) {
					cur_x--;
					printf("\033%d;%dP", cur_x, cur_y);
				}
				break;
			case 'j':
				if (cur_y > 0) {
					cur_y--;
					if (cur_x > buf[cur_y + top].cnt)
						cur_x = buf[cur_y + top].cnt;
					printf("\033[%d;%dH", cur_x, cur_y);
					break;
				}
				if (top > 0) {
					top--;
					draw_win();
					break;
				}
				break;
			case 'k':
				if (cur_y + top >= lines)
					break;
				if (cur_y < 24) {
					cur_y++;
					if (cur_x > buf[cur_y + top].cnt)
						cur_x = buf[cur_y + top].cnt;
					printf("\033[%d;%dH", cur_x, cur_y);
					break;
				} else {
					top++;
					draw_win();
					break;
				}
				break;
			case 'l':
				if (cur_x < buf[cur_y + top].cnt) {
					cur_x++;
					printf("\033%d;%dP", cur_x, cur_y);
				}
				break;
			case 'i':
				mode = MODE_INSERT;
				break;
			case 'q':
				save();
				printf("\033[e");
				printf("\033[25;1H\n");
				exit(0);
			}
			break;
		case MODE_INSERT:
			if (ch == '\033') {
				mode = MODE_VIEW;
				break;
			}
			insert(ch);
			break;
		}
	}
}
