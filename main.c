#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "hangman.h"

int main () {
    
    srand(time(NULL));

    char secret[255];
    
   
    if (get_word(secret)) {
        printf("Error loading word\n");
        return 1;
    }

   
    hangman(secret);

    return 0;
}