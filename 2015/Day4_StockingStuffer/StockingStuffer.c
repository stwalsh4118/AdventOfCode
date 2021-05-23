#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include  "../../headers/MD5.h"
#include "../../headers/utils.h"

bool check_hash(char * key, int num, int num_zeros) {

    char result[50];
    char msg[20];
    
    //copy our key into a different string 
    strcpy(msg,key);

    //turn our hash number into a string
    sprintf(result, "%d", num);

    //concatenate our key and hash number together so we can get the md5 hash of it
    strncat(msg,result,strlen(result));

    //add a string terminal to the end of our key + hash number string
    msg[strlen(msg)] = '\0';

    size_t len = strlen(msg);
    char * leading_zeros;

    //get the md5 hash of our key + number string and return the X leading digits depending on the number of leading zeros we want 
    leading_zeros = md5(msg, len, num_zeros);
    char * all_zeros;

    //depending on how many leading zeros we get the amount of zeros to check the hash against
    if(num_zeros == 5) {
        all_zeros = "00000000000000000000";

    } else {
        all_zeros = "000000000000000000000000";
    }

    //if the amount of leading zeros in the hash is same as the amount of zeros we want return true
    if(strcmp(leading_zeros,all_zeros) == 0) {
        free(leading_zeros);
        return true;
    }

    //if the amount of leading zeros in the hash is not the same as the amount of zeros we want return false
    free(leading_zeros);
    return false;
}

int find_correct_hash(char * key, int num_zeros) {
    int hash_number = 0;

    //while we havent found the has with the amount of leading zeros that we want
    while(!check_hash(key, hash_number, num_zeros)) { 

        //go to the next hash number and check again
        hash_number++;
    }

    return hash_number;
}

int main(int argc, char * argv[]) {
    printf("Input file path to key: ");

    char *file_path;
    file_path = input_string(stdin, 16);

    FILE *fp = fopen(file_path, "r");

    char *key;
    key = input_string(fp, 16);

    printf("%s\n", key);
    int correct_hash_five_zeros = find_correct_hash(key, 5);
    int correct_hash_six_zeros = find_correct_hash(key, 6);

    printf("correct hash with 5 leading zeros %d\n",correct_hash_five_zeros);
    printf("correct hash with 6 leading zeros %d\n", correct_hash_six_zeros);

    free(file_path);
    free(key);

    return 0;
}