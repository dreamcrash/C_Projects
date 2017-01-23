#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Draw.h"
#include "Drawing_command.h"
#include "Management_command.h"
#include "Command_parser.h"
#include "Graphic_interface.h"
#include "My_String.h"

/**
 * This function will verify if the point to be printed into the screen
 * is within the screen limits
 * 
 * @param draw  : The draw to be check
 * @param x     : The x coordinate of the point
 * @param y     : The y coordinate of the point
 * @return      : 1 if the point is within the limits and 0 otherwise
 */
int check_draw(Draw *draw, int x, int y){
    
    return x < draw->number_cols && 
           x >= 0                &&
           y < draw->number_rows &&
           y >= 0;
    
}


/**
 * This function will take the dimension (cols & rows) of a draw to be created
 * and check if those dimensions are within the max and min limits
 * and update those dimension accordingly.
 * 
 * @param cols  : The total of columns
 * @param rows  : The total of rows
 */
void check_adjust_boundaries(int *cols, int *rows){
    
    if(*cols < MIN_COLS) *cols = MIN_COLS;
    if(*cols > MAX_COLS) *cols = MAX_COLS;
    if(*rows < MIN_ROWS) *rows = MIN_ROWS;
    if(*rows > MAX_ROWS) *rows = MAX_ROWS;
}

/**
 * Creating and returning a draw object with dimension cols and rows.
 * If the dimensions are not within the limits, the dimension
 * will be adjust to a given default size
 * 
 * @param cols  : The total of columns of the draw
 * @param rows  : The total of rows of the draw
 * @return      : The created draw
 */    
Draw *new_draw (int cols, int rows){
    
    // Check for out of boundaries problems
    check_adjust_boundaries(&cols, &rows);
    
    char **screen = malloc(sizeof(screen) * rows);
    
    if(screen)
    {
        int no_nulls = 1;
        for(int c = 0; c < rows && no_nulls; c++)
        {
            // yep I know that chars are one byte
            screen[c] = malloc(sizeof(screen[c]) * (cols +1)); 
            if(!screen[c]) no_nulls = 0;
        }
        if(no_nulls){
            
            // Fill the screen with spaces
            for(int r = 0; r < rows; r++)
            {
                for(int c = 0; c < cols; c++)
                    screen[r][c] = ' ';
                screen[r][cols] = '\0';
            }
            
            Draw *draw = malloc(sizeof(*draw));
            
            if(draw){
                
                draw->number_cols       = cols;
                draw->number_rows       = rows;
                add_functions_to_draw(draw);
                draw->screen            = screen;
                draw->marker            = DEFAULT_CHAR;
                clean(draw);
                return draw;
            }
        }
    }
    // memory problems
    return NULL;
}


/**
 * This function will add to the draw the pointers to specific functions
 * 
 * @param draw : The draw
 */
void add_functions_to_draw(Draw *draw){
    
    draw->print             = printDraw;
    draw->check_draw_limits = check_draw;
}


/**
 * Function that will print the draw into the screen as ask the user for
 * commands to be performed in the draw
 * 
 * @param draw              : Draw to be printed    
 * @param command_parser    : Commands parser functions
 */

ERRORHANDLE draw_in_screen(Draw *draw, const Command_parser *command_parser){
  
    int drawing = KEEP_EXECUTION;
    
    while(drawing != EXIT)
    {
        draw->print(draw); // print the draw into the screen
        
        printf("Insert Command > ");
        // read commands from keyboard
        drawing = execute_commands(draw, command_parser);
        check_erros_msg(drawing);
    }
    
    return drawing;
}

/**
 * This function will free the memory occupied by a given draw
 * @param draw : The draw to be freed
 */
void free_draw(Draw **draw){
    
    Draw *tmp = *draw;
    
    for(int i = 0; i < tmp->number_rows; i++)
    {
        free(tmp->screen[i]);
        tmp->screen[i] = NULL;
    }
    free(tmp->screen);
    tmp->screen = NULL;
    tmp->print = NULL;
    tmp->check_draw_limits = NULL;
    free(*draw);
    *draw = NULL;
}
/* Function that starts a draw and creates the necessary 
 * structures
 */
ERRORHANDLE start_draw(int cols, int rows){
            
        Draw *draw = dim(cols, rows);
        
        if(draw)
        {
            Command_parser *command_parser  = load_command_parser();
            
            if(command_parser)
            {
                int result = draw_in_screen(draw, command_parser);
                free_draw(&draw);
                free_comand_parser(&command_parser);
                return result;
            }
            else{
                free_draw(&draw);
                return MEMORY_PROBLEMS;
            }
        }
        else
            return MEMORY_PROBLEMS;
   }

