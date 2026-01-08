# What is it about
C lacks of string manipulation fucntions.
This repository is to make my life easier by having the string realted functions in one place.
Thought probably all of the functions have been implemented before I chose not to use other programmers functions. After all this is also a learning project.

# Information
As this is constantly evolving library this list is updated every now and then.
All of the functions are prefixed with *str_*.
There are some implementations of libc functions which I might delete later. These functions have bullet point:

"❓Since this is in libc, might delete this later."

# Contents
Below is listed the function name, it's prtotype and a brief explantion. More information about the functions can be found in str_lib.h

- STR_LEN
  - `size_t str_len(const char* restrict str);`
  - counts and returns the length of a *str*.
  - ❓Since this is in libc, might delete this later.
 
- STR_TRIM
  - `void str_trim(char *restrict str, const char *restrict chars);`
  - Trims both ends of *str* from *chars*.
  - Note. modifies the original string.

- STR_TRIM_FRONT
  - `void str_trim_front(char *restrict str, const char *restrict chars);`
  - Trims the front of *str* from *chars*.
  - Note. modifies the original string.

- STR_TRIM_BACK
  - `void str_trim_back(char *restrict str, const char *restrict chars);`
  - Trims the back of *str* from *chars*.
  - Note. modifies the original string.

- STR_REPLACE_ALL
  - `void str_replace_all(char *restrict str, char to_replace, char c);`
  - Replaces all occurences of characater *to_replace* with *c*.
  - Note. modifies the original string.

- STR_CPY
  - `size_t str_cpy(char *restrict dst, const char *retrict src);`
  - Tries to copy *stc* to *dst* and returns the number of characters copied excluding terminating '\0'.
  - Note. if *src* is longer than *dst* will cause UB.
  - ❓Since this is in libc, might delete this later.

- STR_NCPY
  - `size_t str_ncpy(char *restrict dst, const char *restrict src, size_t dsize);`
  - Copies at maximum *dsize - 1* characters from *src* to *dst*.
  - Returns the number of characters coied, exluding the terminating '\0'.
  - ❓Since this is in libc, might delete this later.

- STR_CLONE
  - `char *str_clone(const char *restrict src);`
  - Clones *src* and returns a pinter to newly allocated string.

- STR_CONTAINS
  - `int str_contains(const char *restrict test, const char *chars);`
  - Checks if *test* contains any of the *chars*.

- STR_IS_ANY_OF
  - `int str_is_any_of(const char test, const char *restrict char);`
  - Checks if *test* is any of the *chars*.

- STR_IS_ALL_OF
  - `int str_is_all_of(const char *restrict test, const char *restrict chars);`
  - Checks if *test* contains only *chars*.

- STR_TO_LOWER
  - `void str_to_lower(char *restrict str);`
  - Changes all the uppercase letters in *str* to lowercase letters.
  - Note. modifies the original string.

- STR_TO_UPPER
  - `void str_to_upper(char *restrict str);`
  - Changes all the lowercase letters in *str* to uppercase letters.
  - Note. modifies the original string.

- STR_SQUEEZE
  - `void str_squeeze(char *restrict str, const char *restict chars);`
  - Removes all the *chars* from *str*.
  - Note. modifies the original string.

- STR_SPLIT
  - `char **str_split(const char *restrict str, char delim);`
  - Separates *str* to an array of string by *delim*.
  - Does not include the *delim* to the new strings.

- STR_SPLIT_ESCAPE
  - `char **str_split_escape(const char *restrict str, char delim, char escape);`
  - Separates *str* to an array of strings by *delim* but allows the caller to 'escape' some of the *delim* chars by *escape*
  - This is useful for reading csv-files.
  - If the amount of *escapes* in the string is odd the result might not be expected.

- STR_SPLIT_INCLUSIVE
  - `char **str_split_inclusive(const char *restrict str, char delim);`
  - Separates *str* to an array of strings by *delim*.
  - Includes the *delim* to the new strings. 

- STR_WRAP
  - `char **str_wrap(const char *restrict str, size_t n);`
  - Separates *str* to an array of strings that are at maximum *n* characters long.
  - This is useful for wrapping long string to limited length lines.
  - If a word is longer than *n* force wraps the word on two lines.
