/* 
 * File:   Draw.h
 * Author: Bruno Medeiros
 *
 * Created on 10 de February de 2017, 19:19
 */

#ifndef DRAW_H
#define DRAW_H

#ifdef __cplusplus
extern "C" {
#endif
    
#define MAX_ROWS 1000
#define MAX_COLS 1000
#define MIN_COLS 80
#define MIN_ROWS 25
#define DEFAULT_CHAR '.'

typedef struct DRAW{
    
    //holds the image that will 
    // be printed into the screen
    char **screen;      
    int number_cols;
    int number_rows;
    
    // Current character that will 
    // be print using the commands
    char marker;   
}Draw;


void free_draw                          (Draw *draw);
Draw *new_draw                          (int cols, int rows);
int check_draw                          (Draw *draw, int x, int y);
void check_adjust_boundaries            (int *cols, int *rows);
char **create_screen_draw               (int cols, int rows);
void free_screen                        (char **screen, int rows);


#ifdef __cplusplus
}
#endif

#endif /* DRAW_H */

