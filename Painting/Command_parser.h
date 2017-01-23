
/* 
 * File:   Draw_command_parser.h
 * Author: Bruno Medeiros
 */

#ifndef DRAW_COMMAND_PARSER_H
#define DRAW_COMMAND_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif
#include "Draw.h"
#include "ERROS.h"
#define SAVE_NAME       "save"
#define POINT_NAME      "point"   
#define LINE_NAME       "line"
#define RECT_NAME       "rect"
#define POLYLINE_NAME   "polyLine"
#define CIRC_NAME       "circ"
#define ELLIPSE_NAME     "ellipse"
#define SAVE_FUNCTION   save_parser
#define POINT_FUNCTION  point_parser
#define LINE_FUNCTION   line_parser
#define RECT_FUNCTION   rect_parser

        
typedef ERRORHANDLE (*Function_parser_ptr) (Draw *d, char *arguments);
    
typedef struct COMMAND_PARSER{
    
    int total_commands_names;
    
    // just to insure that number of total_commands_names and functions are 
    // the same
    int total_commands_functions; 
    
    char **commands_names;
    // Array of function pointers to the parser functions
    Function_parser_ptr *parser_functions;
    
}Command_parser;




Command_parser *load_command_parser         ();
void free_comand_parser                     (Command_parser **parser);
ERRORHANDLE  execute_commands               (Draw *draw, const Command_parser *cp);
ERRORHANDLE save_parser                     (Draw *draw, char *arguments);
ERRORHANDLE point_parser                    (Draw *d, char *arguments);
ERRORHANDLE line_parser                     (Draw *d, char *arguments);
ERRORHANDLE rect_parser                     (Draw *d, char *arguments);
Function_parser_ptr give_function_command   (const Command_parser *command_parser, 
                                             const char *command_name);
                                            
#ifdef __cplusplus
}
#endif

#endif /* DRAW_COMMAND_PARSER_H */

