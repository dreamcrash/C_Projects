#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h> //"To use tolower in C99,"
#include "My_String.h"

/**
 * Will read a string from the stdin regardless of the string size;
 * 
 * @param str_size  : Variable to save the string size
 * @return The pointer to the string read from the stdin
 */
char *read_strings_stdin(size_t *str_size){

    FILE* fp = stdin;
    size_t buffer_size = 25;
    size_t char_read = 0;
    int ch;
    
    
    // Initial size;
    char *str = realloc(NULL, sizeof(*str) * buffer_size);
    
    if(str)
    {
        while(EOF!= (ch = fgetc(fp)) && ch != '\n'){
            str[char_read++] = ch;
            
            // Check the buffer size
            if(char_read == buffer_size)
            {
                buffer_size *= 2;
                str = realloc(str, sizeof(*str) * (buffer_size));
                
                if(!str)return str; // memory problems
            }
        }
        str[char_read++]='\0';
        *str_size = char_read;
        return realloc(str, sizeof(*str) * char_read);
    }
    
    *str_size = 0;
    // Reading problems
    return NULL; 
}


/**
 * Makes an entire string tolower
 * @param string    : String to be modified
 * @return          : The modified string
 */
char *string_to_lower(char *string){
        char *tmp_ptr = string;
            
       // Lower all the char in the string
         for ( ; *tmp_ptr; ++tmp_ptr) 
                *tmp_ptr = tolower(*tmp_ptr);
    return string;
}

/**
 * Will check if the string is not empty (only space characters)
 * @param string    : String to be check
 * @return          : 1 if the string is not empty, 0 otherwise
 */
int is_not_empty_string(char *string){
    
    char *tmp_ptr = string;
    
    for(;*tmp_ptr && *tmp_ptr == ' '; ++tmp_ptr);
    
    return *tmp_ptr != '\0';
}
