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

#ifndef _STDIO_H
#define _STDIO_H

#include <sys/types.h>
#include <sys/param.h>
#include <stdarg.h>

#define MAX_OPEN	NR_OPEN
#define BUFSIZ		1024
#define L_tmpnam	512

#define EOF		(-1)

#define	SEEK_SET	0
#define	SEEK_CUR	1
#define	SEEK_END	2

typedef struct __iobuf {
	int    _fd;
	int    _flag;
	int    _cnt;
	int    _bufsize;
	char * _buf;
	char * _ptr;
} FILE;

#define _IONBF		0x0001
#define _IOLBF		0x0002
#define _IOFBF		0x0003
#define _IOERR		0x0010
#define _IOEOF		0x0020

extern FILE * stdin;
extern FILE * stdout;
extern FILE * stderr;

extern FILE * fopen(const char *filename, const char *mode);
extern FILE * fdopen(int fd, const char *mode);
extern int    fgetc(FILE *stream);
extern char * fgets(char * buf, size_t n, FILE *stream);
extern int    fputc(int ch, FILE *stream);
extern int    fputs(const char *s, FILE *stream);
extern size_t fread(void * ptr, size_t size, size_t nobj, FILE *stream);
extern size_t fwrite(const void * ptr, size_t size, size_t nobj, FILE *stream);
extern int    fseek(FILE *stream, off_t off, int where);
extern int    fflush(FILE *stream);
extern int    fsetbuf(FILE *stream, int mode, char *buf, size_t size);
extern int    fclose(FILE *stream);
extern int    ungetc(int c, FILE *stream);

extern int printf(char *fmt, ...);
extern int fprintf(FILE *stream, const char *fmt, ...);
extern int sprintf(char *buf, const char *fmt, ...);
extern int snprintf(char *buf, size_t size, const char *fmt, ...);
extern int vsprintf(char *buf, const char *fmt, va_list arg);
extern int vsnprintf(char *buf, size_t size, const char *fmt, va_list ap);

static inline int rename(const char *old, const char *new)
{
	return 0;
}

static inline int remove(const char *path)
{
	return 0;
}

static inline int ftell(FILE *stream)
{
	return fseek(stream, 0, SEEK_CUR);
}

static inline int rewind(FILE *stream)
{
	return fseek(stream, 0, SEEK_SET);
}

static inline int fileno(FILE *stream)
{
	return stream->_fd;
}

static inline int feof(FILE *stream)
{
	return stream->_flag & _IOEOF;
}

static inline int ferror(FILE *stream)
{
	return stream->_flag & (_IOERR | _IOEOF);
}

static inline int clearerr(FILE *stream)
{
	return stream->_flag &= ~(_IOERR | _IOEOF);
}

static inline char *gets(char *buf)
{
	return fgets(buf, 1024, stdin);
}

static inline int getc(FILE *stream)
{
	return fgetc(stream);
}

static inline int getchar(void)
{
	return fgetc(stdin);
}

static inline int puts(const char *s)
{
	return fputs(s, stdout);
}
static inline int putc(int c, FILE *stream)
{
	return fputc(c, stream);
}

static inline int putchar(int c)
{
	return fputc(c, stdout);
}

static inline int sscanf(char *s, char *fmt,...)
{
	printf("sscanf error");
	return -1;
}

static inline int fscanf(FILE *stream, char *fmt,...)
{
	printf("fscanf error");
	return -1;
}

static inline int setvbuf(FILE *stream, char *buf, int mode ,size_t size)
{
	printf("setvbuf error");
	return -1;
}

static inline FILE *tmpfile(void)
{
	printf("tmp file error");
	return NULL;
}

static inline char * tmpnam(char *ptr)
{
	printf("tmpnam error");
	return NULL;
}

#endif
