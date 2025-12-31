#include "str_lib.h"

static size_t no_of_strings_escape(const char *str, char c, char escape)
{
	size_t			i;
	size_t			count;
	unsigned char	no_of_escapes;

	no_of_escapes = 0;
	for (i = count = 0; str[i]; ++i) {
		if (str[i] == escape) {
			no_of_escapes ^= 1;
			continue ;
		}
		if (str[i] == c && no_of_escapes == 0) {
			++count;
		}
	}
	return count + 1;
}

static void clean_up(char **arr, size_t words)
{
	size_t i;

	for (i = 0; i < words; ++i) {
		free(arr[i]);
	}
	free(arr);
}

static size_t no_of_strings(const char *str, char c)
{
	size_t	i;
	size_t	count;

	for (i = count = 0; str[i]; ++i) {
		if (str[i] == c) {
			++count;
		}
	}
	return count + 1;
}

/*
 * Note. The resulting strings will not include the delimiter, i.e. delimiter is changed to '\0' character.
 * example 1.
 * fn_split("Split by space", 32, '\0')
 * returns {{"Split"},{"by"},{"space"}}
 * fn_split("Ignore \"quotes and split by\" space", 32, '"')
 * returns {{"Ignore"},{"quotes and split by"},{"space"}}
 */
char ** str_split_escape(const char *restrict str, char delim, char escape)
{
	char	**arr;
	size_t 	  i, word_start, word_no, count;
	char	  no_of_escapes;

	if (!str || !delim) {
		return (void *)0;
	}

	if (!escape) {
		return str_split(str, delim);
	}

	count = no_of_strings_escape(str, delim, escape);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr) {
		return (void *)0;
	}

	no_of_escapes = 0;
	for (i = word_start = word_no = 0; word_no < count; ++i) {
		if (str[i] && str[i] == escape) {
			no_of_escapes ^= 1;
			continue;
		}
		if ((str[i] == delim && no_of_escapes == 0) || str[i] == '\0') {
			size_t len = i - word_start + 1;
			arr[word_no] = (char *)malloc(sizeof(char) * len);
			if (!arr[word_no]) {
				clean_up(arr, word_no);
				return (void *)0;
			}
			str_cpy(arr[word_no], &str[word_start], len);
			++word_no;
			word_start = i + 1;
		}
	}

	//TODO(): If uneven number of escapes, should return error?
	arr[word_no] = (void *)0;
	return arr;
}

char **str_split(const char *restrict str, char delim)
{
	char	**arr;
	size_t 	  i, word_start, word_no, count;

	if (!str || !delim) {
		return (void *)0;
	}

	count = no_of_strings(str, delim);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr) {
		return (void *)0;
	}

	for (i =  word_start = word_no = 0; word_no < count; ++i) {
		if (str[i] == delim || str[i] == '\0') {
			size_t len = i - word_start + 1;
			arr[word_no] = (char *)malloc(sizeof(char) * len);
			if (!arr[word_no]) {
				clean_up(arr, word_no);
				return (void *)0;
			}
			str_cpy(arr[word_no], &str[word_start], len);
			++word_no;
			word_start = i + 1;
		}
	}

	arr[word_no] = (void *)0;
	return arr;
}

char **str_split_inclusive(const char *restrict str, char delim)
{
	char	**arr;
	size_t 	  i, word_start, word_no, count;

	if (!str || !delim) {
		return (void *)0;
	}

	count = no_of_strings(str, delim);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr) {
		return (void *)0;
	}

	for (i = word_start = word_no = 0; word_no < count; ++i) {
		if (str[i] == delim || str[i] == '\0') {
			size_t len = str[i] == '\0' ? i - word_start + 1 : i - word_start + 2;
			arr[word_no] = (char *)malloc(sizeof(char) * len);
			if (!arr[word_no]) {
				clean_up(arr, word_no);
				return (void *)0;
			}
			str_cpy(arr[word_no], &str[word_start], len);
			++word_no;
			word_start = i + 1;
		}
	}

	arr[word_no] = (void *)0;
	return arr;
}
