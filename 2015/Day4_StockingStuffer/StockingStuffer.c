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
    strcpy(msg,key);
    sprintf(result, "%d", num);
    //printf("The string for the num is %s\n", result);
    //printf("length of num string %d\n", strlen(result));
    strncat(msg,result,strlen(result));
    msg[strlen(msg)] = '\0';

    size_t len = strlen(msg);
    // printf("key and number %s and length %d\n", msg, len);
    char * leading_zeros;

    leading_zeros = md5(msg, len, num_zeros);
    char * all_zeros;
    if(num_zeros == 5) {
        all_zeros = "00000000000000000000";

    } else {
        all_zeros = "000000000000000000000000";

    }
    //printf("first five from hash %s\n", leading_zeros);

    if(strcmp(leading_zeros,all_zeros) == 0) {
        printf("all zeroes!");
        return true;
    }

    return false;
}

int find_correct_hash(char * key, int num_zeros) {
    int hash_number = 0;

    while(!check_hash(key, hash_number, num_zeros)) { 
        //printf("current hash number %d\n", hash_number);
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

    int correct_hash = find_correct_hash(key, 6);

    printf("correct hash %d\n", correct_hash);

    free(file_path);
    free(key);

    return 0;
}