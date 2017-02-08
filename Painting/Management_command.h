/* 
 * File:   Management_command.h
 * Author: Bruno Medeiros
 */

#ifndef MANAGEMENT_COMMAND_H
#define MANAGEMENT_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif
   
#define FILE_BUFFER 128
    
/** 
 * Structure used to save information about a draw that 
 * will be saved on file 
 */
typedef struct SAVEDDRAW
{
    char **text;                 /* 0 -> draw id;
                                  * 1 -> comment
                                  * 2 -> Author
                                  * 3 -> File name
                                  */ 
    Draw *draw;
 }SaveDraw;

#define ID 0 
#define COMMENT 1
#define AUTHOR 2
#define FILE_NAME 3
 
Draw *dim                   (int lines, int columns);    
void set_marker             (Draw *draw, char new_marker);
ERRORHANDLE merge           (char *file_name, Draw *draw);
ERRORHANDLE saveMFT         (SaveDraw *data);
Draw *LoadMFT               (char *filename);


#ifdef __cplusplus
}
#endif

#endif /* MANAGEMENT_COMMAND_H */

