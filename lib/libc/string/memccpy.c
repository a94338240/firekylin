#include <string.h>

void *memccpy(void *dst, const void *src, int c, size_t count)
{
	char *a = dst;
	char *b = src;

	while (count--) {
		*a++ = *b;
		if (*b == c) {
			return (void *) a;
		}
		b++;
	}
	return 0;
}
