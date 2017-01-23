/* 
 * File:   DataTypes.h
 * Author: Bruno M. <brunom@di.uminho.pt>
 */

#ifndef DATATYPES_H
#define	DATATYPES_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define TRUE 1
#define FALSE 0
#define Bool   int 
#define STRING_SIZE 512
#define FILE_NAME_SIZE 50
#define INT_SIZE 6                             
#define INITIAL_YEAR 1980
#define FINAL_YEAR 2013
#define MAX_AUTHORS 32
#define LIST_NAME "lista.txt"
#define YEAR_TO_YEAR_NAME "datas3.txt"
#define YEAR "datas4.txt"
#define REPORT_D "D.txt"
#define REPORT_E "E.txt"
#define REPORT_G "G.txt"
#define HASH_SIZE 10007
#define TOP 10
    
    /**         AVL Autors 
                    Autor1 -----> AVL Autors
     *      Autor2
     
     
     
     */
    
    
    
    
        
    /** Social Network structure */
    typedef struct Social_Network{
        char *name;     // Author name
        int total;      // Total of coAuthors in the AVL of coAuthors
        int height;     // AVL height
        struct Social_Network *co_authors;  // Pointer to an AVL of coAuthors
        struct Social_Network *right;       // AVL RIGHT NODE
        struct Social_Network *left;        // AVL LEFT NODE
        
    }SocialNetworkT;
    /**
     * The social Network is represented as an AVL, where each AVL Node has 
     * a pointer to the right and left nodes, the total of coAuthors 
     * and a pointer to another AVL that will hold the coAuthors that 
     * have write articles with the node Author. 
     * 
     */
    

    /** The structure that will hold the statics of articles files.*/
    typedef struct Statistics
    {
          int entries;  // The # of entrances (articles) in a give file
        // The # of articles entrances rejected given a certain criteria
          int rejected; 
          int articles; // The # of articles (valid) accepted
          int revista;  // The # of magazine articles accepted
          int conferencia;   // The # of conference articles accepted
          int tmp_rejected;  // Used as an temporally variable
    }StatisticsS;
    
    
    /** Linked list that will hold the rejected articles */
    typedef struct Rejected
    {  
        int total_rejections;    // the total of rejected articles
        char *name;              // the name of the author
        struct Rejected *next;
        
    }RejectedS;
    
    

    /** This structure will hold information about a given year/articles */
    typedef struct YearArticles{
        
          int total_articles;   // total of articles in this year
          int accumulated;
        // Holds the size of the array of number authors per article
          int artPerAutSize; 
        // Array that will hold the number of Articles of 'x' number of authors
          int *artPerAut;    
    }YearArtS;
    
    /**
     The artPerAut will be an array that will hold the number of Articles of 
     * 'x' number of authors.
     * 'X' corresponds to the array position + 1, for example the following 
     * array: [1,4,5]
     *  Means that there is :
     *  > 1 article  with 1 author
     *  > 4 articles with 2 authors
     *  > 5 articles with 5 authors
     * ...
     */
    
    
    typedef struct PairsAuthors
    {
        struct Social_Network *author;
        struct Social_Network *coAuthor;
        struct PairsAuthors *next;
    }PairsAuthorsS;

    
    /** Structure that will hold all the information necessary to 
     * produce the reports **/
    typedef struct Reports
    {
        // Social Network of Authors
        struct Social_Network **redesocial;
        // The Statistics about the file read
        struct Statistics *statistics;
         // Information about the rejected articles
        struct Rejected *rejectedArticles;
         // A Hashtable of the years/articles. Where each position corresponds 
        // to an year (pointer to structure YearArticle
        struct YearArticles **hashtable;    
         /** Information about the files to be read **/
        struct File *files;      
         /** Linked list with the information about pairs of Authors 
          * that have write together **/
        struct PairsAuthors *pairs;                
          int maxNumberAuthorsFinded; 
        /** The final year maps to the last position 
         * of the Hashtable YearArticles **/
          int finalYear;
         /** The initial year maps to the initial position 
          * of the Hashtable YearArticles **/
          int initialYear;                  
    }ReportsS;
    
    
    typedef struct File
    {
        char *list;
        char *data3;
        char *data4;
        char *D_txt;
        char *E_txt;
        char *G_txt;
        char *directory;
    }FilesNames;
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* DATATYPES_H */

