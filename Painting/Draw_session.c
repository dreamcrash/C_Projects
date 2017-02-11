#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Draw_session.h"
#include "Drawing_command.h"
#include "Management_command.h"
#include "Command_parser.h"
#include "Graphic_interface.h"
#include "My_String.h"

/**
 * Will create a section.
 * @param cols  The number of columns that the draw will have
 * @param rows  The number of rows that the draw will have
 * @return 
 */
Draw_session *new_session(int cols, int rows){
    
    Draw_session *session = malloc(sizeof(*session));
    
    if(session)
    {
        session->draw = new_draw (cols, rows);
        
        if(session->draw)
        {
            add_functions_to_session(session);
            session->command_parser  = load_command_parser();
            
            if(session->command_parser)
            {
                return session;
            }
            free_draw(session->draw);
        }
        
        free(session);
    } 
    // Memory Problems
    return NULL;      
}

/**
 * Creating a session but using a already made draw
 * @param draw  : The draw that will be used
 * @return  A new session with a before hand made draw
 */
Draw_session *new_session_with_load_draw(Draw *draw){
        
    Draw_session *session = malloc(sizeof(*session));
    
    if(session)
    {
        session->draw = draw;
        
        if(session->draw)
        {
            add_functions_to_session(session);
            session->command_parser  = load_command_parser();
            
            if(session->command_parser)
            {
                return session;
            }
            free_draw(session->draw);
        }
        
        free(session);
    } 
    // Memory Problems
    return NULL;
}
/**
 * This function will free the memory occupied by a given draw
 * @param draw : The draw to be freed
 */
void free_session(Draw_session **draw){
    
    Draw_session *tmp = *draw;
    
    free_draw(tmp->draw);
    free_comand_parser(&tmp->command_parser);
    tmp->print = NULL;
    tmp->check_draw_limits = NULL;
    
    free(*draw);
    *draw = NULL;
}









/**
 * This function will add to the draw the pointers to specific functions
 * 
 * @param draw : The current session
 */
void add_functions_to_session(Draw_session *session){
    
    session->print             = printDraw;
    session->check_draw_limits = check_draw;
}


/**
 * Function that will print the draw into the screen as ask the user for
 * commands to be performed in the draw
 * 
 * @param session              : Working session    
 */

ERRORHANDLE draw_in_screen(Draw_session *session){
  
    int drawing = KEEP_EXECUTION;
    
    Draw *draw = session->draw;
    
    while(drawing != EXIT)
    {
        session->print(draw); // print the draw into the screen
        
        printf("Insert Command > ");
        // read commands from keyboard
        drawing = execute_commands(session);
        check_erros_msg(drawing);
    }
    
    return drawing;
}

/* Function that starts a session and creates the necessary 
 * structures
 */
ERRORHANDLE start_session(int cols, int rows){
            
        Draw_session *session = new_session(cols, rows);
        return (session) ? to_draw(session) : MEMORY_PROBLEMS;
 }


/**
 * Performing the actually draw
 * @param draw : The empty draw
 * @return 
 */
ERRORHANDLE to_draw(Draw_session *session){
    
    int result = draw_in_screen(session);
    free_session(&session);
    return result;    
} 