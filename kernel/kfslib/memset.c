#include "../include/kfsdef.h"

void*   memset(void *b, size_t c, size_t len)
{
	size_t			i;
	uint8_t         *s;

	s = b;
	i = 0;
	while (len > 0)
	{
		s[i] = c;
		len--;
		i++;
	}
	return (b);
}