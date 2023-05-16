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
void print_line(char *current, char line[], char search_term[]){

    char *next;

    current = strstr(line, search_term);

    printf("%.*s",(int)(current - line), line);
    printf("%s%s%s", RED, search_term, RESET_COLOUR);

    while((next = strstr(current + strlen(search_term), search_term)) != NULL){

        /* Print string between current search term and next search term */
        printf("%.*s", (int)(next - current - strlen(search_term)), current + strlen(search_term)); 

        printf("%s%s%s", RED, search_term, RESET_COLOUR);
        current = next;
    }

    printf("%s", current + strlen(search_term));

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

    /* TODO: Change printing to highlight EVERY occurence of search_term in a line */

    /*  set current index as position after the last found search term

        while (line from index contains the search term) 
            print search term in red
            print string up to the next occurence*/

    fclose(filename);
    return 0;
}