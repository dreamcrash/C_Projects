#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Draw.h"
#include "Command_parser.h"
#include "Drawing_command.h"
#include "Management_command.h"
#include "ERROS.h"
#include "My_String.h"


/**
 * This function will load the command names and corresponding pointers
 * to their functions
 * 
 * @return A command parser structure
 */
Command_parser *load_command_parser(){
    
    Command_parser *parser = malloc(sizeof(*parser));
    
    if(parser){
        const char *array_names[] = {
            SET_MARKER,
            MERGE_NAME,
            SAVE_NAME,
            POINT_NAME,
            LINE_NAME,
            RECT_NAME,
            POLYLINE_NAME,
            CIRC_NAME,
            ELLIPSE_NAME,
            NULL
        };
        
        // Count total of commands
        int total_commands_name = 0;
        for(int i = 0; array_names[i]; i++, total_commands_name++);
        parser->total_commands_names = total_commands_name;
        
        parser->commands_names = malloc(sizeof(parser->commands_names) 
                * total_commands_name);
        
        // Copy command names
        if(parser->commands_names)
        {
            int no_null = 1;
            
            // Copy name by name
            for(int i = 0; i < total_commands_name && no_null; i++)
            {
                parser->commands_names[i] = malloc(sizeof(strlen(array_names[i]))
                                                +1);
                if(parser->commands_names[i]){
                    strcpy(parser->commands_names[i], array_names[i]);
                }
                else{
                    no_null = 0;
                }
            }
            
            // If no memory problems with the names than copy functions pointers
            if(no_null)
            {
                const Function_parser_ptr parser_functions[] = {
                    SET_MARKER_FUNCTION,
                    MERGE_FUNCTION,
                    SAVE_FUNCTION,
                    POINT_FUNCTION,
                    LINE_FUNCTION, 
                    RECT_FUNCTION,
                    NULL
                };
                
                int total_commands_functions = 0;
                for(int i = 0; parser_functions[i]; i++, 
                        total_commands_functions++);
                
                parser->total_commands_functions = total_commands_functions;

                parser->parser_functions = malloc(sizeof(parser->parser_functions) 
                                            * total_commands_functions);
                
                if(parser->parser_functions)
                {
                    for(int i = 0; i < total_commands_functions; i++)
                    {
                        parser->parser_functions[i] = parser_functions[i];
                    }
                    return parser; 
                }
            }
        }
    }
   
    // Memory problems
    return NULL;
}

/**
 * Makes a deep free of the Command_parser structure
 * @param parser The Structure to be freed
 */
void free_comand_parser(Command_parser **parser){
    
    Command_parser *ptr_parser = *parser;
    int total_commands_names = ptr_parser->total_commands_names;
    
    // Free array of string (names of commands)
    for(int i = 0; i < total_commands_names && ptr_parser->commands_names[i]; 
            i++)
    {
        free(ptr_parser->commands_names[i]);
        ptr_parser->commands_names[i] = NULL;
    }
    free(ptr_parser->commands_names);
    ptr_parser->commands_names = NULL;
  
    // Free functions pointer array
    free(ptr_parser->parser_functions);
    ptr_parser->parser_functions = NULL;
    
    free(*parser);
    *parser = NULL;
}

/**
 * This function will read a command from the user, parser that command
 * and executed it.
 * 
 * @param draw              : The draw where the command will be executed in
 * @param command_parser    : The grammar to parser the commands
 * 
 * @return This function will return: 
 *          > EXIT if the user inserted the command;
 *          > MEMORY_PROBLEMS in case of memory problems;
 *          > WRONG_PARSER if the user inserted an invalid command
 *          > OUT_OF_LIMITS if the user inserted commands that draws out of the
 * limits of the draw;
 *          > COMMAND_NOT_FOUND if the command does not exist
 *          > KEEP_EXECUTION otherwise.
 * 
 */

ERRORHANDLE execute_commands(Draw *draw, const Command_parser *command_parser){
    
    size_t string_size = 0;
    
    // Reading the user command as a string
    char *command = read_strings_stdin(&string_size); 
    char *command_name = malloc(sizeof(*command_name) * string_size);
    
    if(command && command_name)
    {   
        // Read the command name
        int result = sscanf(command, "%s", command_name);
        int msg_to_return = KEEP_EXECUTION;
        
        if(result)
        {
            // Lower all the char in the string
            command_name = string_to_lower(command_name);
            
            if(strcmp(command_name, "exit") == 0)
            {
                msg_to_return = EXIT;
            }
            else{
                // Search for the function that will execute the command
                Function_parser_ptr command_function = 
                        give_function_command (command_parser, command_name);
                
                if(command_function){
                    
                    // Jump in the string into the argument position
                    char *command_arguments = command + strlen(command_name);
                    
                    msg_to_return = command_function(draw, command_arguments);
                }
                else{
                    msg_to_return = COMMAND_NOT_FOUND;
                }
            }
        }
        else
            msg_to_return = WRONG_PARSER;
        
        // execute command
        free(command);
        free(command_name);
        
        return msg_to_return;
    }
    else{
        return MEMORY_PROBLEMS;
    }
    
    return EXIT;
}

/**
 * Changes to the current draw marker
 * 
 * @param draw      : Current draw
 * @param arguments : ...
 * @return WRONG_PARSER if the user insert bad strings and SUCCESS otherwise
 */
ERRORHANDLE set_marker_parser               (Draw *draw, char *arguments){
        
    char new_marker;
    int result = sscanf(arguments, " %c", &new_marker);
    
    // Check if the number of arguments are correct
    if(result == 1)
    {
        set_marker(draw, new_marker);
        return SUCCESS;
    }
    else
        return WRONG_PARSER;
}


/**
 * Loads a previously save draw and merge it with the current one
 * 
 * @param draw      : Current draw
 * @param arguments : ...
 * @return  It will return:  
 *  > MEMORY_PROBLEMS if there is memory allocation;
 *  > WRONG_PARSER  if the user insert bad strings; 
 *  > FILE_ERROR if the function could not read the file; 
 *  > FILE_WRONG_DIM if the draw to be load is bigger then
 * the current draw; 
 *  >SUCCESS otherwise
 */
ERRORHANDLE merge_parser                    (Draw *draw, char *arguments){
    
    size_t string_size = strlen(arguments);
    
    char *file_name = malloc(string_size + 1);
    
    if(file_name){
        
        int result = sscanf(arguments, " %s", file_name);
        
        if(result == 1)
        {
            ERRORHANDLE merge_result = merge(file_name, draw);
            free(file_name);
            return merge_result;
        }
        else
        {
            free(file_name);
            return WRONG_PARSER;
        }
    }
    else
        return MEMORY_PROBLEMS;
    
    return SUCCESS;
}



/**
 * Saves the current draw in a file
 * @param draw          : Current draw
 * @param arguments     : ...
 * @return  MEMORY_PROBLEMS if there was memory problems, WRONG_PARSER
 * if the user insert bad strings and SUCCESS otherwise
 */
ERRORHANDLE save_parser (Draw *draw, char *arguments){
    
    SaveDraw *save_draw = malloc(sizeof(*save_draw));
    
    if(save_draw)
    {
        static const char *msg[] = 
                    {   "Insert Id > ", 
                        "Insert Comment > ", 
                        "Insert Author > ",
                        "Insert File Name >",
                        NULL
                    };

        int total_msg = 0; 
        int no_empty_string = 1;
        
        // Get total of messages
        for(int i = 0; msg[i]; i++, total_msg++);
        
        save_draw->text = malloc(sizeof(save_draw->text) * total_msg);
        
        if(save_draw->text)
        {
            size_t buffer_size = FILE_BUFFER;
            // Ask the user for information about the draw
            for(int i = 0; i < total_msg && no_empty_string; i++)
            {
                printf("%s",msg[i]);
                
                save_draw->text[i] = read_strings_stdin(&buffer_size);

                if(!save_draw->text[i]) return MEMORY_PROBLEMS;
                
                no_empty_string = is_not_empty_string(save_draw->text[i]);
            }
            if(no_empty_string)
            {
                save_draw->draw = draw;
                
                // Save the draw on the file
                ERRORHANDLE result = saveMFT(save_draw);
                
                // Free the draw information structure
                for(int i = 0; i < total_msg ; i++)
                {
                    free(save_draw->text[i]);
                }
                free(save_draw->text);
                save_draw->text = NULL;
                free(save_draw);
                save_draw = NULL;
                
                return result;
            }
            else
            {
                free(save_draw);
                return WRONG_PARSER;
            }
        }
    }
    return MEMORY_PROBLEMS;
}


/** Drawing commands **/

/**
 * This function will take a draw, read a string extract the coordinates of the
 * point to be draw. The point will only be drawn if the string format 
 * is correct and point is not located outside the draw limits.
 * 
 * @param draw      : The draw where a point will be drawn
 * @param arguments : A string that should contain the coordinates of the 
 * point to be drawn
 * @return          : Returns SUCCESS if the point was draw; OUT_OF_LIMITS if 
 * the coordinates are out of the draw limits; 3 : If the string does not 
 * contain the coordinates.
 */

ERRORHANDLE point_parser        (Draw *draw, char *arguments){
    
    int x, y;
    int result = sscanf(arguments, "%d %d", &x, &y);
    
    // Check if the number of arguments are correct
    if(result == 2){
        // Check limits
        if(draw->check_draw_limits(draw, x, y))
        {
            point(draw, x, y); // Draw the point
            return SUCCESS;
        }
        else
            return OUT_OF_LIMITS;
    }
    else
        return WRONG_PARSER;
}

/**
 * This function will take a draw, read a string extract the coordinates of the
 * line to be draw. The line will only be drawn if the string format 
 * is correct and point is not located outside the draw limits.
 * 
 * @param draw      : The draw where a line will be drawn
 * @param arguments : A string that should contain the coordinates of the 
 * line to be drawn
 * @return          : Returns SUCCESS if the point was draw; OUT_OF_LIMITS if 
 * the coordinates are out of the draw limits; 3 : If the string does not 
 * contain the coordinates.
 */

ERRORHANDLE line_parser         (Draw *draw, char *arguments){
    
    int x1, y1, x2, y2;
    int result = sscanf(arguments, "%d %d %d %d", &x1, &y1, &x2, &y2);
    
    
    // Check if the number of arguments are correct
    if(result == 4){
        // Check limits
        if(draw->check_draw_limits(draw, x1, y1) && 
                draw->check_draw_limits(draw, x2, y2))
        {
            line(draw, x1, y1, x2, y2); // Draw the line
            return SUCCESS;
        }
        else
            return OUT_OF_LIMITS;
    }
    else
        return WRONG_PARSER;
}

/**
 * This function will take a draw, read a string extract the coordinates of the
 * rectangle to be draw. The rectangle will only be drawn if the string format 
 * is correct and point is not located outside the draw limits.
 * 
 * @param draw      : The draw where a rectangle will be drawn
 * @param arguments : A string that should contain the coordinates of the 
 * rectangle to be drawn
 * @return          : Returns SUCCESS if the point was draw; OUT_OF_LIMITS if 
 * the coordinates are out of the draw limits; 3 : If the string does not 
 * contain the coordinates.
 */

ERRORHANDLE rect_parser          (Draw *draw, char *arguments){
        
    int x1, y1, x2, y2;
    int result = sscanf(arguments, "%d %d %d %d", &x1, &y1, &x2, &y2);
    
    // Check if the number of arguments are correct
    if(result == 4){
        // Check limits
        if(draw->check_draw_limits(draw, x1, y1) && 
                draw->check_draw_limits(draw, x2, y2))
        {
            rect(draw, x1, y1, x2, y2); // Draw the line
            return SUCCESS;
        }
        else
            return OUT_OF_LIMITS;
    }
    else
        return WRONG_PARSER;
}

/**
 * This function given a command parser and a name will return the memory
 * address of the function corresponding to the requested command
 * 
 * @param command_parser    : The list of commands
 * @param command_name      : The name of the command
 * @return A pointer to the function or NULL if the function does not exists
 */
Function_parser_ptr give_function_command(const Command_parser *command_parser, 
        const char *command_name){
    
        int not_find = 1;
        int total_commands = command_parser->total_commands_names;
        int command_pos = -1;
        char **command_names = command_parser->commands_names;
              
        for(int i = 0; i < total_commands && not_find; i++)
        {
            if(strcmp(command_names[i], command_name) == 0)
            {
                command_pos = i;    // Command position
                not_find =  0;      // exit loop
            }
        }
        
        // Command not found it
        if(command_pos == -1 || command_pos > command_parser->total_commands_functions) 
        {
            return NULL;
        }
        else{
            return command_parser->parser_functions[command_pos];
        }
}