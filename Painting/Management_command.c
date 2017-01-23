#include <stdio.h>
#include <stdlib.h>
#include "Draw.h"
#include "Management_command.h"

/**
 * This function will return a draw with the given dimensions.
 * 
 * @param lines     : The number of lines of the draw
 * @param columns   : The number of columns of the draw
 * @return  A draw with the dimension passing as arguments
 */
Draw *dim(int lines, int columns){
    return new_draw (lines, columns);
}

/**
 * This command will change the current marker for a new one.
 * 
 * @param draw          : The current draw
 * @param new_marker    : The new marker to draw
 */
void set_marker(Draw *draw, char new_marker){
    draw->marker = new_marker;
}

/**
 * Function that will take a draw and merge with a draw
 * loaded from a file
 * 
 * @param file_name : The file where the draw to be merger is saved
 * @param draw      : The current draw
 * @return          : Will return FILE_ERROR if the function could not
 * read the file, FILE_WRONG_DIM if the draw to be load is bigger then
 * the current draw, FILE_SUCESSES otherwise
 */
FILE_ERRORHANDLE merge(char *file_name, Draw *draw){
  
    Draw *tmp_draw = LoadMFT(file_name);
    
    // If draw as successfully loaded and have smaller dimension than the 
    // current draw
    if(tmp_draw){
        if(tmp_draw->number_rows <= draw->number_rows && 
                tmp_draw->number_cols <= draw->number_cols)
        {
            // Copying the draw
            for(int i = 0;i < tmp_draw->number_rows;i++)
                for(int j = 0;j< tmp_draw->number_cols;j++)
                    if(tmp_draw->screen[i][j]!=0) // if not space
                        draw->screen[i][j] = tmp_draw->screen[i][j];
          
                free(tmp_draw);
                return FILE_SUCCESS;
        }
        else
            return FILE_WRONG_DIM;
    }
    else 
        return FILE_ERROR;
}



/**
 * Saves a draw alow with some data into a file 
 * @param data  : Information about the draw to be save
 * @return      : Will return FILE_ERROR if the function could 
 * not read the file FILE_SUCESSES otherwise
 */
FILE_ERRORHANDLE saveMFT(SaveDraw *data){
    
  FILE *fp; 

  fp = fopen(data->text[FILE_NAME],"w");
  if(!fp)
  {
      return FILE_ERROR;
  }
  else
  { 
        int rows = data->draw->number_rows;
        int cols = data->draw->number_cols;
        char **screen = data->draw->screen;
        
        fprintf(fp,"Id:%s\n",data->text[ID]);
	fprintf(fp,"Comment:%s\n",data->text[COMMENT]);
	fprintf(fp,"Author:%s\n",data->text[AUTHOR]);
        fprintf(fp,"Rows = %d  Columns = %d\n",rows, cols);
        
        
        for(int r = rows - 1; r >= 0; r--)
        {
            for(int c = 0; c < cols ; c++)
            {
                fprintf(fp,"%c",screen[r][c]);
            }
            fprintf(fp,"\n");
        }
            	
            
	fclose(fp);
	return FILE_SUCCESS;
    }
}  

/*LOAD Draw from file */
Draw *LoadMFT(char *filename){
    
  FILE *fp;

  fp = fopen(filename,"r");
  if(!fp)
  {
      return NULL;
  }
  else
  {
        char line[FILE_BUFFER];
        int j;
        int erro = 0;
        int rows, cols;
        
        /* --- Reading matrix dimension  --- */
	if(fgets(filename,FILE_BUFFER,fp) != NULL && 
                fscanf(fp,"%*[^=]=%d %*[^=]=%d",&rows,&cols) > 0)
        {
            Draw *draw = new_draw(rows, cols);

            fgets(line, FILE_BUFFER,fp); /* Cleans the rest of line */

            // While there is still lines to be read
            for(int i = draw->number_rows - 1; (i>=0)&&(!erro); i--)
            {
                j = 1;
                // While there is still columns to read
                while((j <= draw->number_cols && (!erro))) 
                {
                    if(!fscanf(fp,"%c",&(draw->screen[i][j]))) erro = 1;
                    else j++;
                }

                while(fgetc(fp)!='\n'); // Reads the rest of the line
            }
            fclose(fp);
        
            if(erro)
            {
                free_draw(&draw);
                return NULL;
            }
            else
            {
                return draw;
            }
        }
        else
        { 
             fclose(fp);
             return NULL;
        }
  }
}