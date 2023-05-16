#include <stdio.h>
#include <string.h>

#define RED "\x1b[31m" 
#define GREEN "\x1b[32m"
#define RESET_COLOUR "\x1b[0m"

int main(void){
    char line[44] = "the black cat sits at the window in the sun\n";
    char search_term[4] = "the";
    char *current, *next;
    
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

    return 0;
}