/* 
 * File:   My_String.h
 * Author: Bruno Medeiros.
 */

#ifndef MY_STRING_H
#define MY_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

char *read_strings_stdin                    (size_t *str_size);
char *string_to_lower                       (char *string);
int is_not_empty_string                     (char *string);
int read_string_formated                    (const char *fmt, ...);


#ifdef __cplusplus
}
#endif

#endif /* MY_STRING_H */

