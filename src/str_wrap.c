#include "str_lib.h"

static char *extract_line(const char *restrict str, size_t len)
{
	char *line;

	line = (char *)malloc(sizeof *line * len);
	if (!line) {
		return NULL;
	}

	line = memcpy(line, str, len);
	line[len - 1] = '\0';
	return line;
}

#include <stdio.h>
char **str_wrap(const char *restrict str, size_t n)
{
	char		**arr, **realloc_tmp;
	const char	cWhitespace[] = " \t\v\n";
	int			line_count, lineno;
	size_t		start, end, total_len;

	if (!str || !*str || n == 0 ) {
		return NULL;
	}

	total_len = str_len(str);
	line_count = (total_len + n) / n + 1;
	arr = (char **)malloc(sizeof *arr * (line_count + 1));
	if (!arr) {
		return NULL;
	}

	lineno = 0;
	start = 0;
	while ((end = start + n) < total_len) {

		if (str_is_any_of(str[end], cWhitespace)) {
			arr[lineno] = extract_line(&str[start], end - start + 1);
		}
		else {
			while (end > start && !str_is_any_of(str[end], cWhitespace)) {
				--end;
			}

			//NOTE(jyri): no whitespace was found, write part of the word and wrap.
			if (end == start) {
				arr[lineno] = extract_line(&str[start], n + 1);
				end = start + n - 1;
			}
			else {
				arr[lineno] = extract_line(&str[start], end - start + 1);
			}
		}

		if (!arr[lineno]) {
			goto clean_return;
		}

		if (lineno == line_count) {
			printf("%s\n", arr[lineno]);
		}
		
		++lineno;
		start = end + 1;

		if (lineno > line_count) {
			line_count *= 2;
			realloc_tmp = (char **)realloc(arr, sizeof *arr * line_count);
			if (!realloc_tmp) {
				goto clean_return;
			}
			arr = realloc_tmp;
		}
	}

	arr[lineno] = extract_line(&str[start], str_len(&str[start]) + 1);
	if (!arr[lineno]) {
		goto clean_return;
	}
	arr[++lineno] = NULL;
	return arr;

clean_return:
	for (int i = 0; arr[i] && i < line_count; ++i) {
		free(arr[i]);
	}
	free(arr);
	return NULL;
}
/*
void str_wrap_and_print(const char *restrict str, size_t n)
{
	char **arr;
	size_t len;

	if (!str || n == 0) {
		return;
	}

	arr = str_wrap(str, n);
	if (!arr) {
		return;
	}

	for (size_t i = 0; arr[i]; ++i) {
		len = str_len(arr[i]);	
		write(STDOUT_FILENO, arr[i], len);
		free(arr[i]);
	}
	free(arr);
}
*/
