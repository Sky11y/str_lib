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
	
	return clone;
}

char *str_slice(const char *restrict src, int start, int end)
{
	char	*slice;
	int		len;

	if (!src || start < 0 || end < -1) {
		return NULL;
	}

	if (end == -1) {
		len = str_len(src);
	}
	else {
		len = end - start;
	}

	if (len < 1) {
		return NULL;
	}

	slice = (char *)malloc(sizeof(char) * (len + 1));
	if (!slice) {
		return NULL;
	}

	memcpy(slice, &src[start], len);
	slice[len] = '\0';

	return slice;
}
