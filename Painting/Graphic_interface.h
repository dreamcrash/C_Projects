/* 
 * File:   Graphic_interface.h
 * Author: Bruno Medeiros.
 */

#ifndef GRAPHIC_INTERFACE_H
#define GRAPHIC_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif
#include "Draw_session.h"

void printXXnumbers                 (Draw *draw);
void printDraw                      (Draw *draw);
void print_char_x_times             (int number, char character);
void print_msg                      (char *string);
void clear_screen                   ();
void main_menu                      ();
void main_menu_graphic_msg          ();
void read_file_name_msg             ();
void are_you_sure                   ();
ERRORHANDLE menu_start_draw         ();
ERRORHANDLE menu_load_draw          ();


#ifdef __cplusplus
}
#endif

#endif /* GRAPHIC_INTERFACE_H */
