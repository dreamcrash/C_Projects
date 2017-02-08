/* 
 * File:   Board.h
 * Author: Bruno Medeiros.
 */

#ifndef BOARD_H
#define BOARD_H

#ifdef __cplusplus
extern "C" {
#endif
    
#define MAX_ROWS 1000
#define MAX_COLS 1000
#define MIN_COLS 80
#define MIN_ROWS 25
#define DEFAULT_CHAR '.'

    
typedef struct DRAW{
    
    char **screen;      //holds the image that will be printed into the screen
    int number_cols;
    int number_rows;
    // Current character that will be print using the commands
    char marker;       
        
    // Method to print the draw
    void (*print)(struct DRAW *draw); 
        
    // Function to check if the draws is out of the screen 
    int (*check_draw_limits) (struct DRAW *draw, int x, int y);
   
}Draw;
     
#include "Command_parser.h"  
struct Command_parser;  
    
int check_draw                      (Draw *draw, int x, int y);
void check_adjust_boundaries        (int *cols, int *rows);
Draw *new_draw                      (int cols, int rows);
void add_functions_to_draw          (Draw *draw);
ERRORHANDLE draw_in_screen          (Draw *draw, const Command_parser *cp);
void free_draw                      (Draw **draw);
void check_erros_msg                (ERRORHANDLE msg);
ERRORHANDLE start_draw              (int cols, int rows);
ERRORHANDLE to_draw                 (Draw *draw);


#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */

