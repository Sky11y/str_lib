#include "str_lib.h"

size_t str_len(const char* restrict str)
{
	size_t len = 0;

	if (!str) {
		return 0;
	}
	
	while (str[len]) {
		++len;
	}
	return len;
}

void str_trim(char *restrict str, const char* restrict chars)
{
	size_t i = 0;
	size_t j = str_len(str);

	if (i == j) {
		return ;
	}

	while (i < j && str_is_any_of(str[i], chars) == 1) {
		++i;
	}

	//contains only *chars*. Return empty string.
	if (i == j) {
		str[0] = '\0';
		return ;
	}

	while (j > i && str_is_any_of(str[j - 1], chars) == 1) {
		--j;
	}

	memmove(str, &str[i], j - i);
	str[j - i] = '\0';
}

void str_trim_front(char *restrict str, const char *restrict chars)
{
	size_t i = 0;
	size_t len;

	if (!str) {
		return ;
	}

	while (str[i] && str_is_any_of(str[i], chars) == 1) {
		++i;
	}

	if (str[i] == '\0') {
		str[0] = '\0';
		return ;
	}

	len = str_len(str) - i;
	memmove(str, &str[i], len);
	str[len] = '\0';
}

void str_trim_back(char *restrict str, const char *restrict chars)
{
	size_t i = str_len(str);

	if (i == 0) {
		return ;
	}

	while (i > 0 && str_is_any_of(str[i - 1], chars) == 1) {
		--i;
	}

	str[i] = '\0';
}

void str_replace_all(char *restrict str, char to_replace, char c)
{
	size_t i = 0;

	if (!str) {
		return ;
	}

	while(str[i]) {
		if (str[i] == to_replace) {
			str[i] = c;
		}
		i++;
	}
}

size_t str_cpy(char *restrict dst, const char *restrict src)
{
	size_t i;

	if (!dst || !src) {
		return 0;
	}

	for (i = 0; src[i]; ++i) {
		dst[i] = src[i];
	}

	dst[i] = '\0';
	return i;
}

size_t str_ncpy(char *restrict dst, const char *restrict src, size_t dsize)
{
	size_t src_len = 0;
	size_t i;

	if (!dst || !src || dsize == 0) {
		return 0;
	}

	while (src[src_len] && src_len < dsize - 1) {
		++src_len;
	}

	for (i = 0; i < src_len; ++i) {
		dst[i] = src[i];
	}

	dst[src_len] = '\0';
	return src_len;
}

int str_contains(const char *restrict test, const char *restrict chars)
{
	size_t i;

	if (!test) {
		return -1;
	}

	if (!chars) {
		return 1;
	}

	for (i = 0; test[i]; ++i) {
		if (str_is_any_of(test[i], chars) == 1) {
			return 1;
		}
	}
	return 0;
}

int str_is_any_of(const char test, const char *restrict chars)
{ 
	size_t i;

	if (!test) {
		return -1;
	}

	if (!chars) {
		return 1;
	}

	for (i = 0; chars[i]; ++i) {
		if (test == chars[i]) {
			return 1;
		}
	}
	return 0;
}

int str_is_all_of(const char *restrict test, const char *restrict chars)
{
	size_t i;
	
	if (!test) {
		return -1;
	}

	if (!chars) {
		return 1;
	}

	for (i = 0; test[i]; ++i) {
		if (str_is_any_of(test[i], chars) == 0) {
			return 0;
		}
	}
	return 1;
}

void str_to_lower(char *restrict str)
{
	size_t i;

	if (!str) {
		return ;
	}
	
	for (i = 0; str[i]; ++i) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] += 32;
		}
	}
}

void str_to_upper(char *restrict str)
{
	size_t i;

	if (!str) {
		return ;
	}
	
	for (i = 0; str[i]; ++i) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			str[i] -= 32;
		}
	}
}

void str_squeeze(char *restrict str, const char *restrict chars)
{
	size_t i;
	size_t j;
	size_t k;

	if (!str) {
		return ;
	}

	for (i = j = 0; str[i]; ++i) {
		for (k = 0; chars[k] && str[i] != chars[k]; ++k) {
			;
		}
		if (!chars[k]) {
			str[j++] = str[i];
		}
	}
	str[j] = '\0';
}

void str_free_arr(char **arr)
{
	size_t i = 0;
	
	while (arr[i]) {
		free(arr[i]);
		++i;
	}
	free(arr);
}
