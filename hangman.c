#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "hangman.h"


// TASK 1
int is_word_guessed(const char secret[], const char letters_guessed[]) {
    int secretLen = strlen(secret);
    int lettersGuessedLen = strlen(letters_guessed);
    int foundLetterFlag = 0;
    
    for (int i = 0; i < secretLen; i++) { 
        foundLetterFlag = 0;
        for (int j = 0; j < lettersGuessedLen; j++) { 
            if (secret[i] == letters_guessed[j]) {
                foundLetterFlag = 1;
                break;
            }
        }
        if (!foundLetterFlag) {
            return 0;
        }
    }
    return 1;
}


// TASK 2
void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]) {
    int secretLen = strlen(secret);
    int lettersGuessedLen = strlen(letters_guessed);
    int foundLetterFlag = 0;

    for (int i = 0; i < secretLen; i++) {
        foundLetterFlag = 0; 

        for (int j = 0; j < lettersGuessedLen; j++) {
            if (secret[i] == letters_guessed[j]) {
                foundLetterFlag = 1;
                break; 
            }
        }

        if (foundLetterFlag) {
            guessed_word[i] = secret[i];
        } else {
            guessed_word[i] = '_';
        }
    }
    guessed_word[secretLen] = '\0';
}


int get_word(char secret[]){
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        long int random = (rand() % size) + 1;
        fseek(fp, random, SEEK_SET);
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);
    return 0;
}


// TASK 4
void hangman(const char secret[]) {
    int secretLen = strlen(secret);
    int guesses_left = 8;             
    char letters_guessed[255] = "";   
    int letters_count = 0;

    printf("Welcome to the game Hangman!\n");
    printf("I am thinking of a word that is %d letters long.\n", secretLen);
    printf("-------------\n");

   
    while (guesses_left > 0 && !is_word_guessed(secret, letters_guessed)) {
        printf("You have %d guesses left.\n", guesses_left);
        
        
        char current_progress[255];
        get_guessed_word(secret, letters_guessed, current_progress);
        
      
        printf("Current word: ");
        for (int i = 0; current_progress[i] != '\0'; i++) {
            printf("%c ", current_progress[i]);
        }
        printf("\n");

     
        printf("Please guess a letter: ");
        char guess;
        scanf(" %c", &guess); 

        
        int already_guessed = 0;
        for (int i = 0; i < letters_count; i++) {
            if (letters_guessed[i] == guess) {
                already_guessed = 1;
                break;
            }
        }

        if (already_guessed) {
            printf("Oops! You've already guessed that letter.\n");
        } else {
           
            letters_guessed[letters_count] = guess;
            letters_count++;
            letters_guessed[letters_count] = '\0';

            
            int in_word = 0;
            for (int i = 0; i < secretLen; i++) {
                if (secret[i] == guess) {
                    in_word = 1;
                    break;
                }
            }

            if (in_word) {
                printf("Good guess!\n");
            } else {
                printf("Oops! That letter is not in my word.\n");
                guesses_left--; 
            }
        }
        printf("-------------\n");
    }

    
    if (is_word_guessed(secret, letters_guessed)) {
        printf("Congratulations, you won! The word was indeed: %s\n", secret);
    } else {
        printf("Sorry, you ran out of guesses. The word was: %s\n", secret);
    }
}