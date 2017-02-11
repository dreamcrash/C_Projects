#include <stdio.h>
#include <stdlib.h>
#include "Draw.h"
#include "Drawing_command.h"


void free_draw(Draw *draw){
    free_screen(draw->screen, draw->number_rows);
    free(draw);
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
    
    char **screen = create_screen_draw(cols, rows);
    
    if(screen)
    {
        Draw *draw = malloc(sizeof(*draw));
        
        if(draw)
        {
            draw->number_cols       = cols;
            draw->number_rows       = rows;
            draw->screen            = screen;
            draw->marker            = DEFAULT_CHAR;
            clean(draw);
            return draw;
        }
    }
    // memory problems
    return NULL;
}


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
 * Creates the matrix where the draw will be save
 * @param cols  : the number of columns of the draw 
 * @param rows  : the number of rows of the draw
 * @return      : The newly created matrix 
 */
char **create_screen_draw(int cols, int rows){
    
     char **screen = malloc(sizeof(screen) * rows);
    
     if(screen)
     {
        int no_nulls = 1;
        for(int c = 0; c < rows && no_nulls; c++)
        {
            // yep I know that chars are one byte
            screen[c] = malloc(sizeof(screen[c]) * (cols + 1)); 
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
        }
        return screen;
     }
     return NULL; // Memory problems
 }

/**
 * This function will free the memory allocated to the matrix
 * that holds the draw.
 * 
 * @param screen    : The matrix to be freed
 * @param rows      : The number of rows
 */
void free_screen(char **screen, int rows){
    
    for(int i = 0; i < rows; i++)
    {
        free(screen[i]);
    }
    free(screen);
}