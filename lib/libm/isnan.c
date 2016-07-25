#include <math.h>

int isnan(double d)
{
	union {
		unsigned long long l;
		double d;
	} u;
	u.d = d;
	return (u.l == 0x7FF8000000000000ll || u.l == 0x7FF0000000000000ll
			|| u.l == 0xFFF8000000000000ll);
}
