#include "str_lib.h"

char *str_clone(const char *restrict src)
{
	char	*clone;
	size_t	 len;

	if (!src) {
		return NULL;
	}

	len = str_len(src) + 1;
	clone = (char *)malloc(sizeof(char) * len);
	if (!clone) {
		return NULL;
	}

	memcpy(clone, src, len);
	
	return (clone);
}
