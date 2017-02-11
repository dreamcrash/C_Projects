#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Graphic_interface.h"
#include "Draw_session.h"
#include "ERROS.h"
#include "My_String.h"
#include "Management_command.h"

/**
 * Function that will print in the bottom of the draw the 'xx' coordinates.
 * @param draw : The draw to be check
 */
void printXXnumbers(Draw *draw){
    int d = 0;
    int cols = draw->number_cols;
    
    int levels = (log(cols) / log(10));     // How many digits the number have
    int rep = pow(10,levels);               // the number of times we need 
                                            // to print the same digit    
    int chunck = round(cols/10+0.5);

    printf("    ");
    for(int m = 0; m <= levels; m++, rep /= 10,  chunck *= 10)
    {
        for(int v = 0, l = 0; v <= chunck; v++,l++)
        {
            if(l == 10) l = 0;
            
            for(int n = 0;n < rep;n++,d++)
                if(d <= cols)
                    printf("%d",l);
            
        } 
        d = 0;
        printf("\n    ");
    }
}


/**
 * Prints the draw into the screen 
 * 
 * @param draw : The draw that will be printed into the screen
 */
void printDraw(Draw *draw){
    
    const int num_cols  = draw->number_cols;
    const int num_rows  = draw->number_rows;
    char **screen       = draw->screen;
    
    //draw upper
    printf("   _");
    for(int r = 0; r < num_cols; r++)
    {
        printf("_");
    }
    printf("_\n");
    
    // draw sides
    for(int r = num_rows - 1; r >= 0; r--)
    {
        printf("%3d|",r);
        for(int c = 0; c < num_cols ; c++)
        {
            printf("%c",screen[r][c]);
        }
        printf("|\n");
    }
    printf("   |");
    
    // draw bottom
    for(int r = 0; r < num_cols; r++)
    {
        printf("_");
    }
    printf("|\n");
    printXXnumbers(draw);
}

/**
 * This function will print the "character" "number" of times in the screen
 * 
 * @param number    : The number of times that the character will be printed 
 * @param character : The character that will be print into the screen
 */
void print_char_x_times(int number, char character){
    
    for(int i = 0; i < number; i++)
        printf("%c",character);
    printf("\n");
}
/**
 * Prints a string into the screen
 * @param string : String to be printed
 */
void print_msg(char *string){
        printf("%s", string);
}

void clear_screen(){

    int i = 0;
    while((i++) < 100) 
        printf("\n");
}

/**
 * Main Menu
 */
void main_menu (){
    
    
    int option = 0;
    int result = 0;
    
    do{
        clear_screen();
        main_menu_graphic_msg();
        printf("\n\tChoose your option: ");
        
        size_t buffer_size = 128;
        char *str = read_strings_stdin(&buffer_size);
        result = sscanf(str, "%d", &option);
        free(str);
        
        if(result)
        {
            switch (option)// Read the option  
            { 
                // Exit
                case 0: result = EXIT;
                        break;
                
                // Creating a new draw
                case 1: result = menu_start_draw();
                        break;
                        
                // Loading a draw from a file and starts a draw
                case 2: result = menu_load_draw();
                        break;
                        
             
                default : puts("\n\t\t\t\t\tOption not valid!\n");
                        getchar();
                        break;    
            }
        }
        else
        {
            result = WRONG_PARSER;
        }
        
        check_erros_msg     (result);
        check_success_msg   (result);
        getchar();
    
    }while(result != EXIT);
}

void main_menu_graphic_msg(){
    
    printf("\n\t\t\t");
    print_char_x_times (50,'*');
    printf("\t\t\t*\t\t\t\t\t\t *\n\t\t\t*\t\t   Lets draw!\t\t\t *\n");
    printf("\t\t\t*\t\t\t\t\t\t *\n\t\t\t");
    print_char_x_times (50,'*'); 
    printf("\t\t\t*\t\t\t\t\t\t *\n");
    printf("\t\t\t* 1 - Create a new draw\t\t\t\t *\n");
    printf("\t\t\t* 2 - Load draw\t\t\t\t         *\n");
    printf("\t\t\t* 3 - Drawing from the last saved section\t *\n");
    printf("\t\t\t* 4 - Program made by\t\t\t\t *\n");
    printf("\t\t\t* 5 - Help menu \t\t\t\t *\n");
    printf("\t\t\t*\t\t\t\t\t\t *\n");
    printf("\t\t\t* 0 - Exit the application \t\t\t *\n");
    printf("\t\t\t*\t\t\t\t\t\t *\n\t\t\t");
    print_char_x_times (50,'*');   
}

void read_file_name_msg(){
    printf("Insert the file name : \n");
}

void are_you_sure(){
    printf("Are you sure? The current draw will be lost !!! (y/Y for yes) \n");
}

ERRORHANDLE menu_start_draw(){
    
    int cols = 0, rows = 0;
    printf("Insert the dimensions (rows, cols) : ");
    
    size_t buffer_size = 128;
    char *str = read_strings_stdin(&buffer_size);

    int result = sscanf(str, "%d %d", &cols, &rows);
    free(str);
    
    if(result == 2)
    {
        // Check the boundaries just to print to the user
        // the dim function adjusts the dimension internally
        int tmp_cols = cols, tmp_rows = rows; 
        check_adjust_boundaries(&cols, &rows);
        
        // If the dimension had to be adjusted
        if(tmp_cols != cols && tmp_rows != rows){
            printf("The dimension are not within the limits !\n");
            printf("Automatically adjust to [ %d | %d ]\n ",cols, rows);
            getchar();
        }
        return start_session(cols, rows);
    }
    return WRONG_PARSER;
}
/**
 * Loading a draw before having creating a any draw.
 * @return 
 */
ERRORHANDLE menu_load_draw (){
    
    read_file_name_msg();
    
    size_t string_size = 0;
    
    // Reading the user command as a string
    char *file_name = read_strings_stdin(&string_size); 
     
    Draw *draw = LoadMFT(file_name);
     
    Draw_session *session = new_session_with_load_draw(draw);
    
    free(file_name);
    
    return draw ? to_draw(session) : MEMORY_PROBLEMS;
}