#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../../headers/utils.h"

typedef struct {
    char one;
    char two;
    int index;
}PAIR;

bool has_x_vowels(char * word, int x) {
    char a = 'a';
    char e = 'e';
    char i = 'i';
    char o = 'o';
    char u = 'u';
    int num_vowels = 0;

    //loop through all of the characters in the word
    for(int j = 0; j < strlen(word); j++) {

        //if the current character is a vowel, add to the number of vowels in the word
        if((word[j] == a) || (word[j] == e) || (word[j] == i) || (word[j] == o) || (word[j] == u)) {
            num_vowels++;
        }
    }

    //if the number of vowels in the word is greater or equal to the number specified then we return true
    if(num_vowels >= x) {
        return true;
    }

    //if the number of vowels in the word is less than the number specified then we return false
    return false;

}

bool has_double_letter(char * word) {


    //loop through all of the charcters in the word
    for(int i = 0; i < strlen(word)-1; i++) {

        //if the current character and the next character are the same then there is a double letter and we return true
        if(word[i] == word[i+1]) {
            
            return true;
        }
    }

    //if we make it through the word without finding a double letter we return false
    return false;
}

bool has_forbidden_pair(char * word) {

    char * ab = "ab";
    char * cd = "cd";
    char * pq = "pq";
    char * xy = "xy";


    //loop through all of the characters in the word
    for(int i = 0; i < strlen(word)-1; i++) {

        //if the current character and the next character equal one of the forbidden pairs of letters then we return true
        if(((word[i] == ab[0]) && (word[i+1] == ab[1])) || ((word[i] == cd[0]) && (word[i+1] == cd[1])) || ((word[i] == pq[0]) && (word[i+1] == pq[1])) || ((word[i] == xy[0]) && (word[i+1] == xy[1]))) {
    
            return true;
        }
    }

    //if we make it through the word without finding a pair of forbidden letters we return false
    return false;
}

bool has_repeat_with_one_inbetween(char * word) {


    //loop through all of the characters in the word
    for(int i = 0; i < strlen(word)-2; i++) {

        //if the current character and the next next character are the same then there is a pair of the same character with one in between and we return true
        if(word[i] == word[i+2]) {
            return true;
        }
    }

    //if we make it through the word without finding a pair of the same character with one character inbetween we return false
    return false;
}

bool has_repeating_pair_no_overlap(char * word) {

    //loop through all of the characters in the word
    for(int i = 0; i < strlen(word)-3; i++) {

        //loop through all of the characters after the current character + 2, this is so we dont check overlapping pairs
        for(int j = i+2; j < strlen(word)-1; j++) {

            //if the current pair we are checking against equals our base pair then we return true
            if((word[i] == word[j]) && (word[i+1] == word[j+1])) {
                return true;
            }
        }
    }

    //if we make it through the word without finding a repeated non overlapping pair we return false
    return false;

}

int check_words(FILE* fp) {
    int number_nice_words = 0;
    char * word;

    //loop through all of the words, reading them in from the file one at a time
    while(word = input_string(fp,10)) {

        //if the current word is empty that means we reached the end of the file and we break from the loop
        if(strcmp(word,"") == 0) {
            break;
        }
        
        //check the word for all of the conditions, if the word passes all of them add to the nice words list
        if(has_double_letter(word) && !has_forbidden_pair(word) && has_x_vowels(word,3)) {
            number_nice_words++;
        }

        free(word);
    }
    
    //return the total number of nice words in the list
    return number_nice_words;
}

int check_words_part_two_electric_boogaloo(FILE* fp) {
    int number_nice_words = 0;
    char * word;


    //same as above, but different conditions
    while(word = input_string(fp,10)) {

        if(strcmp(word,"") == 0) {
            break;
        }

        if(has_repeat_with_one_inbetween(word) && has_repeating_pair_no_overlap(word)) {
            number_nice_words++;
        }

        free(word);
    }

    return number_nice_words;
}

int main(int argc, char * argv[]) {

    printf("Input file path to words list: ");

    char *file_path;
    file_path = input_string(stdin, 16);

    FILE *fp = fopen(file_path, "r");   
    int num_nice_words = check_words(fp);
    fclose(fp);


    fp = fopen(file_path, "r");
    int num_nice_words_part_two_electric_boogaloo = check_words_part_two_electric_boogaloo(fp);

    printf("Number of nice words in the list %d\n", num_nice_words);
    printf("Number of nice words part two electric boogaloo in the list %d\n", num_nice_words_part_two_electric_boogaloo);
    
    fclose(fp);
    free(file_path);
    return 0;
}