#include "fn_string.h"

static size_t no_of_strings(const char *str, char c, char escape)
{
	size_t			i;
	size_t			count;
	unsigned char	no_of_escapes;

	no_of_escapes = 0;
	for (i = 0, count = 0; str[i]; ++i) {
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


/*
 * This helper function separates a string to an array of
 * strings. Last element of array will be NULL.
 * *str* is the string to be split
 * *delim* is the character that will separate the strings.
 * *escape* is an optional character that allows strings to include the delimiter. This is helpful for example splitting csv-files. See examples.
 * On success return a pointer to an array of strings.
 * if no *str* or *delim* is provided returns (void *)0;
 * Note. The resulting strings will not include the delimiter, i.e. delimiter is changed to '\0' character.
 * example 1.
 * fn_split("Split by space", 32, '\0')
 * returns {{"Split"},{"by"},{"space"}}
 * fn_split("Ignore \"quotes and split by\" space", 32, '"')
 * returns {{"Ignore"},{"quotes and split by"},{"space"}}
 */
char ** fn_split(const char *str, char delim, char escape)
{
	char			**arr;
	size_t 			  i;
	size_t			  word_start;
	size_t			  word_no;
	size_t 			  count;
	unsigned char	  no_of_escapes;

	if (!str || !delim) {
		return (void *)0;
	}

	count = no_of_strings(str, delim, escape);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr) {
		return (void *)0;
	}

	no_of_escapes = 0;
	for (i = 0, word_start = 0, word_no = 0; word_no < count; ++i) {
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
			safe_strlcpy(arr[word_no], &str[word_start], len);
			++word_no;
			word_start = i + 1;
		}
	}

	//TODO(): If uneven number of escapes, should return error?
	arr[word_no] = (void *)0;
	return arr;
}
