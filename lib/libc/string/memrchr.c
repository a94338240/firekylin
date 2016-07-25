#include <string.h>

void* memrchr(const void *s, int c, size_t n)
{
	char* t = (char*) s;
	char* last = 0;

	for (int i = n; i; --i) {
		if (*t == c)
			last = t;
		++t;
	}
	return (void*) last;
}
