/* 
 * File:   Board.h
 * Author: Bruno Medeiros.
 */

#ifndef BOARD_H
#define BOARD_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "Draw.h"
       
typedef struct DRAW_SESSION{
    
    struct DRAW *draw;
    
    // Method to print the draw
    void (*print)(struct DRAW *draw); 
        
    // Function to check if the draws is out of the screen 
    int (*check_draw_limits) (struct DRAW *draw, int x, int y);
    
    struct COMMAND_PARSER *command_parser;
   
}Draw_session;
     
#include "Command_parser.h"
#include "ERROS.h"
struct Command_parser;  

Draw_session *new_session                   (int cols, int rows);
Draw_session *new_session_with_load_draw    (Draw *draw);
void free_session                           (Draw_session **draw);
void add_functions_to_session               (Draw_session *draw);
ERRORHANDLE draw_in_screen                  (Draw_session *draw);
ERRORHANDLE start_session                   (int cols, int rows);
ERRORHANDLE to_draw                         (Draw_session *draw);


#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
