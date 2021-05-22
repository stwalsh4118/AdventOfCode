#include <stdio.h>
#include <string.h>
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

int get_floor(char * instructions) {
    int floor = 0;
    char left_parenthesis = '(';
     
    //loop through input
    for(int i = 0; i < strlen(instructions); i++) {

        //if at the end of the instructions break from the loop
        if(instructions[i] == 0) {
            break;

        //if current character is a left_parenthesis go up a floor
        } else if(instructions[i] == left_parenthesis) {
            floor++;
        
        //else if current character is a right_parenthesis go down a floor
        } else {
            floor--;
        }
    }

    //return the floor number we end up at
    return floor;

}


int main(int argc, char * argv[]) {
 
    printf("Input file path to instructions: ");

    char *file_path;
    file_path = input_string(stdin, 16);

    FILE *fp = fopen(file_path, "r");

    char *instructions;
    instructions = input_string(fp, 16);

    printf("\nInputted instructions: %s\n", instructions);

    int floors = get_floor(instructions);

    printf("Floor ended on: %d\n", floors);
    

    free(instructions);
    return 0;
}
