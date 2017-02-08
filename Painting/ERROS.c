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
    
    char *str = NULL;
    
    switch(msg)
    {
        // I could but all the msg inside a array, but IMO in this manner
        // is more explicity
        
        case OUT_OF_LIMITS      : str = "Out of limits command! \n";
                                  break;
                                  
        case WRONG_PARSER       : str = "The command format is not correct! \n";
                                  break;
                                  
        case COMMAND_NOT_FOUND  : str = "This command does not exist! \n";
                                  break;
                                  
        case MEMORY_PROBLEMS    : str = "Memory problems! \n";
                                  break;
                
        case FILE_ERROR         : str = "ERROR reading the file! \n";
                                  break;
        
        case FILE_WRONG_DIM     : str = "The Draw has wrong dimensions! \n";
                                  break;
    }
    
    // Print the error
    if(str)
    {
        int size_str  = strlen(str);
        print_char_x_times      (size_str, '-');
        print_msg               (str);
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