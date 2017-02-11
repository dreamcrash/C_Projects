/* 
 * File:   Draw_command.h
 * Author: Bruno Medeiros
 */

#ifndef DRAW_COMMAND_H
#define DRAW_COMMAND_H
#include "Draw_session.h"
#include "ERROS.h"




void swap               (int *x1, int *x2);
void swapPoints         (int *x1, int *y1, int *x2, int *y2); 
void maxAndMin          (int v1, int v2, int *min, int *max);
void clean              (Draw *d);
void point              (Draw *d, int x, int y);
void line               (Draw *d, int x1, int y1, int x2, int y2);
void rect               (Draw *d, int x1, int y1, int x2, int y2);
void polyLine           (Draw *d, int *points, int numberPoints);
void circ               (Draw *d, int x, int y, int r);
void ellipse            (Draw *d, int x1, int y1, int x2, int y2, int rm);


#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* DRAW_COMMAND_H */
