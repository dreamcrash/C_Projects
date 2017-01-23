#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ERROS.h"
#include "Graphic_interface.h"

/**
 * Function that checks the message handles errors
 * @param msg : An error handle message
 * 
 * This function could be improved performance wise by
 * hard-coded the messages to be printed
 */
void check_erros_msg(ERRORHANDLE msg){
    
    char *string = NULL;
   
    if(msg == OUT_OF_LIMITS){
        string = "Out of limits command! \n";
    }
    else if(msg == WRONG_PARSER){
        string = "The command format is not correct! \n";
    }
    else if(msg == COMMAND_NOT_FOUND){
        string = "This command does not exist! \n";
    }
    else if(msg == MEMORY_PROBLEMS) {
        string = "Memory problems! \n";
    }
    else{}
    
    // Print the error
    if(string)
    {
        int size_str  = strlen(string);
        print_char_x_times      (size_str, '-');
        print_msg               (string);
        print_char_x_times      (size_str, '-');
        getchar                 ();
    }
}

void check_success_msg(ERRORHANDLE msg){
    
    char *string = NULL;
    if(msg == EXIT){
        string = "You are exiting the program! \n";
    }
    
        // Print the error
    if(string)
    {
        int size_str  = strlen(string);
        print_char_x_times      (size_str, '-');
        print_msg               (string);
        print_char_x_times      (size_str, '-');
        getchar                 ();
    }
}