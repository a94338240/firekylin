#include <math.h>

int isinf(double d)
{
	union {
		unsigned long long l;
		double d;
	} u;

	u.d = d;

	return (u.l == 0x7FF0000000000000ll ? 1 :
		u.l == 0xFFF0000000000000ll ? -1 : 0);
}
