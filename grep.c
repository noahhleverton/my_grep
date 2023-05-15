#include <stdio.h>
#include <string.h>

#define RED "\x1b[31m" 
#define GREEN "\x1b[32m"
#define RESET_COLOUR "\x1b[0m"

FILE *filename;

int show_line_numbers = 1;
int ignore_case = 1;
int whole_word = 1;

/* Check for '-' arguments */
void check_options(char *option){
    if (strcmp(option, "-n") == 0)
        show_line_numbers = 0;
    if (strcmp(option , "-i") == 0)
        ignore_case = 0;
    if (strcmp(option, "-w") == 0)
        whole_word = 0;
}

/* Print lines containing search term */
void print_line(char *found, char line[], char search_term[]){

    /* Print string before search term, search term in red, rest of string */
    printf("%.*s%s%s",(int)(found - line), line, RED, search_term);
    printf("%s%s", RESET_COLOUR, found + strlen(search_term));

}

/* 
    An implementation of UNIX's grep command; prints out lines of input file containing the given search term
    Usage: ./grep "search term" filename -options
*/
int main(int argc, char *argv[]){

    /* Preliminary checks */
    if (argc < 3){
        printf("usage: ./grep \"search term\" filename -options\n");
        return 1;
    }

    if ((filename = fopen(argv[2], "r")) == NULL){
        printf("File not found\n");
        return 1;
    }

    if (argc == 4){
        check_options(argv[3]);
    }

    int line_counter = 1;
    char line[4096], *found;

    /* Search through file line by line until end */
    while (fgets(line, sizeof(line), filename) != NULL){

        /* Check if the search term is present in this line */
        if((found = strstr(line, argv[1])) != NULL){

            if (show_line_numbers == 0){
                printf("%s%d:%s ", GREEN, line_counter, RESET_COLOUR);
            }

            print_line(found, line, argv[1]);

            /* Print missing newline character if last line has search term */
            if (fgets(line, sizeof(line), filename) == NULL){
                printf("\n");
            }
        }

        line_counter ++;
    }

    fclose(filename);
    return 0;

}