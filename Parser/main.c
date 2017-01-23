/* 
 * File:   main.c
 * Author: Bruno M. <brunom@di.uminho.pt>
 */

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "ManipulateData.h"
#include "SaveDBLP.h"
#include "printStdio.h"
#include "ReadDBLP.h"
#include "Debug.h"
#include "DataTypes.h"



int main(int argc, char **argv) 
{
    
    // Prepare Reports structure 
     ReportsS *reports = create_reports();
     
     if(reports)
     {
        // Read the names of the file that will be open
        save_file_names(reports->files , (argc > 1) ? argv[1] : ""); 

        // Read the list of conferences
        read_list_conferences(reports);                            
        generated_reports(reports);

        free_Reports(reports);
     }
     else
         printf("Memory Problems \n");
     
     /* printReport(&reports); */   
     return (EXIT_SUCCESS);
}

