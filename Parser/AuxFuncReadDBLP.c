#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ReadDBLP.h"
#include "ManipulateData.h"
#include "AuxFuncReadDBLP.h"
#include "DataTypes.h"



/**
 * Makes an entire string tolower
 * @param string    : String to be modified
 * @return          : The modified string
 */
char *str_toLower(char *string){
        char *tmp_ptr = string;
            
       // Lower all the char in the string
         for ( ; *tmp_ptr; ++tmp_ptr) 
                *tmp_ptr = tolower(*tmp_ptr);
    return string;
}

/** Remove all the consecutive symbol from a string */
void bypass_symbol(char **article, char symbol){
    while(*(*article) == symbol) (*article)++;
}


Bool parser_int(char **article, int *number){
    
     char input_string[INT_SIZE];
     /** Take out spaces */ 
     bypass_symbol(article, ' ');                                                         
     if(sscanf (*article, "%[0-9]", input_string) > 0)
     {
         /** skips the characters read it by sscanf */
         *article += strlen(input_string);
         *number = atoi(input_string);
         return TRUE;
     }
     
     return FALSE;
}


/** Read the authors */
Bool parser_authors(char **article,   int *autors, size_t *size){
    
    char str[STRING_SIZE];
    char ch;
    size_t strSize;
    
    bypass_symbol(article, ' ');
     
    *autors = 0;
    *size = 0;
    
    ch = **article;
    
    
    /** Read a string until ',' or ':' is reach. 
     * When ':' is found the cycle terminates */
    while(ch != ':' && sscanf (*article,"%[^,|:]s", str) > 0)       
    {
        strSize = strlen(str) + 1;
        *article += strSize;   // updating the actual position on the string
        *size += strSize;
        ch = *(*article-1);  // take the terminal character
        (*autors)++;         //increment the number of authors found */
    }
    
    return !(*autors == 0); /** Check if any author was read. */
}

/** Function to validate the title */
Bool is_title_valid(char **article){
    
    char title [STRING_SIZE];
    char ch = ' ';
    
    if(sscanf (*article, "%[^.]s", title) != 0) /** If the Title is not missing */
    {
        str_toLower(title);       /** turn lower all characters in the title */
        /** skips the characters read it by sscanf */
        *article += strlen(title) + 1;  
        ch = *(*article-1);       
    }
    /** If the final symbol read it is not '.' then the format is wrong. 
     * Otherwise, we  must check if on the title there is any forbidden words. 
     */
    
    return (ch != '.') ? FALSE : !exist_word(title);
}

/** Read the article name & Acronym */
Bool parser_magazine_info(char **article){
    
    char revista[STRING_SIZE];
    bypass_symbol(article, ' ');
    
    /** read magazines name's */
    /** Read all the string until '(' is reach */
    if(sscanf (*article, "%[^(]s", revista) > 0)                                        
    {
        /** skip the character read it by sscanf */
        *article += strlen(revista) + 1;    
        
        /** Read Acronym & check if it starts with the '(' symbol */
        if(*(*article-1) == '(' && sscanf (*article, "%[^)]s", revista) > 0)
        {
             /** skips the characters read it by sscanf */
             *article += strlen(revista) + 1;  
             
             /** check if Acronym ends with ')' */
             return (*(*article-1) == ')');                                             
        }
    }
    return FALSE;
}

/** Read the article volume */
Bool parser_num_magazine(char **article, int *number){
    
    char ch,chF;
     
    bypass_symbol(article, ' ');
    ch = **article;
    (*article)++;
    
    if(ch == '(' && parser_int(article,number)) /** read volume */
    {  
       ch = **article;
       bypass_symbol(article, ' ');
       (*article)++;
       chF = **article;
       (*article)++;
       return (ch == ')' && chF == ':'); 
    }
    return FALSE;
}

/** Read the number of pages */
Bool parser_num_pages(char **article, int *num_pag){
    
      int pag_inc, pag_end;
   
     /** Read initial page */
    if(parser_int(article, &pag_inc))                                             
    {
        bypass_symbol(article, ' '); 
        
        if(**article == '-')
        {
           (*article)++; 
           bypass_symbol(article, ' '); 
           if(parser_int(article, &pag_end))    /** Read final page */                                   
           {
                /** Calculate the number of pages */
               *num_pag = pag_end - pag_inc + 1;                               
               return TRUE;
           } 
        } 
        
    }
    return FALSE;   
}

/** Read the article year */
Bool parser_year(char **article,   int *year){    
    
    bypass_symbol(article, ' ');
    
    if(**article == '(')
    {
       (*article)++;
       bypass_symbol(article, ' ');
       
       if(parser_int(article, year))       /** read year */
       { 
         bypass_symbol(article, ' ');
         return (**article == ')');
       }
    }
     
    return FALSE;
}

/** Read the conference name & Acronym */
Bool parser_conference_info(char **article) {
    
    char revista[STRING_SIZE];
    bypass_symbol(article, ' ');
    
    if (sscanf (*article, "%[^:|\n]s", revista) > 0)
    {
         *article += strlen(revista)-4;
         return isdigit(*(*article));
    }
    return FALSE;
}
