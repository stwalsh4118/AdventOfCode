#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

char * input_string(FILE* fp, size_t initial_size) {

    char *output_string;
    int next_char;
    size_t output_length = 0;

    //allocate inital memory with inital size
    output_string = realloc(NULL, sizeof(*output_string)*initial_size);

    //return of realloc fails
    if(!output_string) return output_string;


    //while not at end of file or not at new line
    while((EOF != (next_char = fgetc(fp))) && (next_char != '\n')) {

        //add character to string
        output_string[output_length++]=next_char;

        //if string array is full
        if(output_length == initial_size) {
            
            //reallocate string with more memory
            output_string = realloc(output_string, sizeof(*output_string)*(initial_size+=16));

            //if allocation fails return
            if(!output_string) return output_string;
        }   
    }


    //put string terminator at the end of the array/string
    output_string[output_length++] = '\0';


    //reallocate the memory one last time to the size of the string, then return it
    return realloc(output_string, sizeof(*output_string) * output_length);

}