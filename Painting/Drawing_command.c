#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Drawing_command.h"
#include "Draw.h"
#include "ERROS.h"


/** Swap Variables */
void swap(int *x1, int *x2){
    int aux = *x1;
    *x1 = *x2;
    *x2 = aux;
}

/**
 * Swap the coordinates of two points;
 * @param x1    : Coordinate x of the point 1
 * @param y1    : Coordinate y of the point 1
 * @param x2    : Coordinate x of the point 2
 * @param y2    : Coordinate y of the point 2
 */
void swapPoints(int *x1, int *y1, int *x2, int *y2){
    swap(x1,x2);
    swap(y1,y2);
}



/**
 * Find the biggest and smallest numbers between two
 * number pass as parameter
 * @param v1    : The first number to be tested
 * @param v2    : The second number to be tested
 * @param min   : Will hold the smallest number
 * @param max   : Will hold the biggest number
 */
void maxAndMin(int v1, int v2, int *min, int *max){
    
    if (v1 > v2){
        *max = v1;
        *min = v2;
    }
    else{
        *max = v2;
        *min = v1;
    }
}

/**
 * Cleans a draw. In another words, this function will fill up 
 * the draw with spaces
 * @param The draw to be clean
 */
void clean(Draw *d){
    int rows = d->number_rows;
    int cols = d->number_cols;
    
    for(int r = 0; r < rows; r++)
        for(int c = 0; c < cols; c++)
            d->screen[r][c] = ' ';
}

/**
 * Printing a point into the screen.
 * @param d : The draw where it will be printed the point
 * @param x : The coordinate x of the point
 * @param y : The coordinate y of the point
 */
void point(Draw *d, int x, int y){
    
     d->screen[y][x] = d->marker;
}


/**
 * This function receives two points a draws a line between
 * them.
 * @param d     : The draw where the line will be print
 * @param x1    : The coordinate x of the first point
 * @param y1    : The coordinate y of the first point
 * @param x2    : The coordinate x of the second point
 * @param y2    : the coordinate y of the second point
 */
void line (Draw *d, int x1, int y1, int x2, int y2){
    
    /** Based on the equation y = mx + b */

    float m, b;
    
    /** m = (x2 - x1) / (y2 - y1) **/ 
    m = ((abs( x2 - x1)) *  1.0) / ((abs( y2 - y1)) * 1.0);
    if(m <= 1.0 )/* Drawing Lines with m <= 1 */
    {   
        if(y1 > y2) /** Vertical lines **/
        {
             /** After the swaps y1 < y2 and the value of x is not important **/
            swapPoints(&x1, &y1, &x2, &y2);  
        }
        
        m = ((x2 - x1) * 1.0) / ((y2 - y1) * 1.0);
        b = x1 - (y1 * m); /** b = x - (y * m) **/
        
        /* It will draw a line according with the equation y = mx + b **/
        for(int i = y1; i <= y2; i++)
        {
            point(d, m * i + b, i);
        }
        
    }
    else /* Drawing Lines with m > 1 */
    {
        if(x1 > x2 || ( y1 ==  y2 &&  x1 > x2)) /** Drawing horizontal lines **/
        {
            /* After the swaps x1 < x2 and y is not relevant */
            swapPoints(&x1,&y1, &x2,&y2);       
        }
         
        m = ((y2-y1)*1.0)/((x2-x1)*1.0);
        b = y1 - (x1 * m); /*y = mx + b*/
        if(y1 == y2) /** If it is a horizontal line then the slope is 0 
                      * and the b will be equal to y1 **/
        {
            m = 0;
            b = y1;
        }
        /* It will draw a line according with the equation y = mx + b **/
        for(int j = x1; j <= x2; j++)
        {
            point(d, j, m * j + b);
        }
    }
}

/**
 * This function will receive two points and print a rectangle
 * that passes through those points.
 * 
 * @param d     : The draw where the rectangle will be drawn
 * @param x1    : Coordinate x of the point 1
 * @param y1    : Coordinate y of the point 1
 * @param x2    : Coordinate x of the point 2;
 * @param y2    : Coordinate y of the point 2
 */
void rect(Draw *d, int x1, int y1, int x2, int y2){

    /**
     * (x1,y2)                      (x2,y2)
     * 
     * (x1,y1)                      (x2,y1)
     * Basically we can draw for lines to make a Rectangle.
     */
    
    /**
     * We could improve this function by drawing directly the
     * rectangle without reusing the line function.
     */
    
    line(d,x1,y1,x1,y2); /** Left   line **/
    line(d,x1,y2,x2,y2); /** Upper  line **/
    line(d,x2,y2,x2,y1); /** Right  line **/
    line(d,x2,y1,x1,y1); /** Bottom line **/                               
}

/**
 *  This command draws a line by joining the points whose coordinates were given. 
 *  This allows you to abbreviate some strokes.
 * 
 * @param d             : Current draw
 * @param points        : Array with the points
 * @param array_size    : The size of the array of points
 */
void polyLine(Draw *d, int *points, int array_size){
     
     /** Dim should be an even number and bigger than 4 */
     
     /* PolyLine x1,y1, x2,y2, ..., xn,yn
      * line(x1,y1,x2,y2), line(x2,y2,x3,y3), line(xn-1,yn-1,xn,yn)
      */
     
     for(int i = 0; i < array_size - 2; i += 2)
     {
         line(d, points[i], points[i+1], points[i+2], points[i+3]);
     }
     
 }

/**
 * Draws a circle
 * @param d : Current draw
 * @param x : x coordinate of the center of the circle
 * @param y : y coordinate of the center of the circle
 * @param r : radius of the circle
 */
void circ(Draw *d, int x, int y, int r){
    
    /** This circle-drawing algorithm uses 4-way symmetry. */
    int r2 = r * r;
    point(d, x, y + r);
    point(d, x, y - r);
     
    for (int i = 1; i <= r; i++){
        
        int j = (int) (sqrt(r2 - i*i) + 0.5);
        point(d, x + i, y + j);
        point(d, x + i, y - j);
        point(d, x - i, y + j);
        point(d, x - i, y - j);
    }
}

/**
 * This command lets you trace an ellipse with focus at x1, y1 and x2, y2 
 * respectively and with a radius smaller than rmin.
 * 
 * @param draw  : Current draw
 * @param x1    : Coordinate x of the first point of focus
 * @param y1    : Coordinate y of the first point of focus
 * @param x2    : Coordinate x2 of the second point of focus
 * @param y2    : Coordinate y2 of the second point of focus
 * @param rm    : radius
 */
 void ellipse (Draw *draw, int x1, int y1, int x2, int y2, int rm){
     
     int j;
     float n, ni;
     int minR, minC, maxR,maxC;
     int rm2 = rm * rm;
     float rm2F = rm2 +0.0;
     
     int y2minusy1div2 = ((y2-y1)/2);   /** With this aux variables in save the **/
     int auxX = ((x2-x1)/2)+x1;         /** the number of total instructions **/
     int auxY = y2minusy1div2 + y1;
     
     float d = sqrt(rm2+(y2minusy1div2 * y2minusy1div2));
     float twoD2 = 2*d*2*d+0.0;
     
     maxAndMin(x1,x2,&minC,&maxC);  // Gets the highest and lowest 'x' coordinate
     maxAndMin(y1,y2,&minR,&maxR);  // Gets the highest and lowest 'y' coordinate
    
     // Calculates the inferior and superior limit need to calculate the ellipse
     minC = (minC - rm < 0) ? 0 : minC - rm2;
     minR = (minR - rm < 0) ? 0 : minR - rm2;
     maxC = (maxC + rm > draw->number_cols) ? draw->number_cols : maxC + rm2;
     maxR = (maxR + rm > draw->number_rows) ? draw->number_rows : maxR + rm2;
     
     if(x1 == x2)
     {
         for (int i = minC; i < maxC; i++)
         {
             ni = (i-auxX) * (i-auxX) / rm2F;
             for (int j = minR; j <= maxR;j++)
             {
                 n = ni + ((j-auxY) * (j-auxY)/ twoD2);
                 
                 if (n>=1.0 && n<=1.25)
                     point(draw,j,i);
             }
         }
     }
     
     if (y1==y2)
     {
        for (int i = minC; i < maxC; i++)
         {
             ni = (i-auxX) * (i-auxX) / twoD2;
             for (j = minR; j <= maxR;j++)
             {
                n = ni+(((j-auxY)*(j-auxY))/rm2F);
                if (n>=1.0 && n<=1.25)  point(draw,j,i);
             }
         }
     }
}

