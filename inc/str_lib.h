#ifndef STR_LIB_H 
# define STR_LIB_H

#include <stdlib.h>
#include <string.h>

/* STR_LEN
 * Calculates the lenght of the *str*.
 * Returns the length of str or 0 if no *str* is present.
 */
size_t str_len(const char* restrict str);

/* STR_TRIM
 * Remove all the *chars* from the beginning and end of *str*.
 * Important! This function modifies the *str* in place.
 */
void str_trim(char *restrict str, const char* restrict chars);

/* STR_TRIM_FRONT
 * Remove all the *chars* from the beginning of *str*.
 * Important! This function modifies the *str* in place.
 */
void str_trim_front(char *restrict str, const char *restrict chars);

/* STR_TRIM_BACK
 * Remove all the *chars* from the back of hte *str*.
 * Important! This function modifies the *str* in place.
 */
void str_trim_back(char *restrict str, const char *restrict chars);

/* STR_REPLACE ALL
 * Replace every occurence of *to_replace* with *c* in *str*
 * Note. It is callers responsibility to make sure *c* and *to_replace* are printable chars.
 * Important! This function modifies the *str* in place.
 */
void str_replace_all(char *restrict str, char to_replace, char c);

/* STR_CPY
 * Tries to copy *src* to *dst* and add a terminating to the end of *dst* '\0'
 * Returns the number of characters copied, excluding the terminating '\0'.
 * Important! If *src* is longer than *dst* will cause UB.
 */
size_t str_cpy(char *restrict dst, const char *restrict src);

/* STR_NCPY
 * Copies max. *dsize* - 1 chars from *src* to *dst*.
 * Guarantees to '\0'-terminate the *dst* (hence max. dsize - 1).
 * Returns the number of characters copied, exluding the terminating '\0'.
 * Note. It is users responsiblity to make sure the size of *dst* is large enough.
 */
size_t str_ncpy(char *restrict dst, const char *restrict src, size_t dsize);

/* STR_CLONE
 * Clones the *src* to a newly allocated memory
 * On success returns a pointer to the clone.
 * On failure returns NULL.
 */
char *str_clone(const char* restrict src);

/* STR_CONTAINS
 * Checks if string *test* contains any of the characters in *chars*.
 * Returns 1 if any of the *chars* is found in *test* and 0 if not.
 * Note. If *test* points to NULL returns -1.
 * Note. If *test* is valid and *chars* is empty returns 1 (i.e. always true when compared to nothing).
 */
int str_contains(const char *restrict test, const char *restrict chars);

/* STR_IS_ANY_OF
 * Checks if a character *test* is any of the character in *chars*.
 * Returns 1 if test matches any of the *chars*, and 0 if not.
 * Note. If *test* is null-character returns -1.
 * Note. If *test* is valid and *chars* is empty returns 1 (i.e. always true when compared to nothing).
 */
int str_is_any_of(const char test, const char *restrict chars);

/* STR_IS_ALL_OFF
 * Check if all the characters in *test* are one of *chars*
 * Returns 1 if true, and 0 if not.
 * Note. If *test* is empty returns -1.
 * Note. If *test* is valid and *chars* is empty returs 1 (i.e. always true when compared to nothing).
 */
int str_is_all_of(const char *restrict test, const char *restrict chars);

/* STR_TO_LOWER
 * Change all capital characters of *str* to lower characters.
 * Important! This function modifies the *str* in place.
 */
void str_to_lower(char *restrict str);

/* STR_TO_UPPER
 * Change all lower characters of *str* to capital characters.
 * Important! This function modifies the *str* in place.
 */
void str_to_upper(char *restrict str);

/* STR_SQUEEZE
 * Removes all the characters fomr *str* presented in *chars*
 * Important! This function modifies *str* in place.
 */
void str_squeeze(char *restrict str, const char *restrict chars);

/* STR_SPLIT
 * Separates *str* to an array of strings by *delim*.
 * Delimiting character is excluded from the resulting strings
 * Last element of array will be NULL.
 * If no *str* or *delim* is provided return NULL 
 */
char **str_split(const char *restrict str, char delim);

/* STR_SPLIT_ESCAPE
 * Similar to str_split but allows escapes of delimiter.
 * Escaping is useful for example splitting csv-information.
 * Notice that the escaping characters are included in the resulting strings.
 * 	- str_trim can be used to strip them of if necessary.
 * If *str* and *delim* are valid but *escape* is not provided, calls str_split(str, delim)
 * example 1. escape has no effect
 * 		fn_split_escape("Split by space", ' ', '"')
 * 		returns {{"Split"}{"by"}{"space"}}
 * example 2. escape used for csv type string
 * 		fn_split_escape("str1,\"str2,has,commas\",str3", ',', '"')
 * 		returns {{"str1"}{"\"str2,has,commas\""}{"str3"}}
 */
char **str_split_escape(const char *restrict str, char delim, char escape);

/* STR_SPLIT_INCLUSIVE
 * Same as str_split but delimiting character is included in the resulting strings.
 */
char **str_split_inclusive(const char *restrict str, char delim);

/* STR_WRAP
 * Wraps *str* to around *n* length of strings.
 * If the nth chracacter of a string is not whitespace, finds the previous whitespace character and starts the next string with the word that had the nth character.
 * if word in *str* is longer than *n* forces the wrapping inside that word.
 * On success returns a heap allocated array of strings (lines).
 * On failure returns NULL.
 * Notice that the function does not check if *str* contains newline (\n) characters itself. 
 * example 1. str_wrap("This is line that should be wrapped by every 10th character", 10);
 * 		                         ^          ^          ^          ^          ^     
 * 		^ represent every 10th character
 * 		Since most of the ^'s are inside words the returned string has this kind of presentation
 * 		This is line that should be wrapped by every 10th character
 * 		       ^         ^         ^          ^          ^         ^    
 * 		returns {{"This is},{"line that"}{"should be"}{"wrapped by"}{"every 10th"}{"character"}} 
 */
char **str_wrap(const char *restrict str, size_t n);

/* STR_WRAP_AND_PRINT
 * Uses str_wrap to wrap the string by around *n* characters, prints the lines and frees the memory.
 */
//void str_wrap_and_print(const char *restrict str, size_t n);

#endif
