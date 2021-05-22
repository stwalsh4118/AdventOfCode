#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../headers/utils.h"

void get_floor(char * instructions, int answer[]) {
    int floor = 0;
    char left_parenthesis = '(';
    bool has_entered_basement = false;
     
    //loop through input
    for(int i = 0; i < strlen(instructions); i++) {

        //if at the end of the instructions breadk from the loop
        if(!(has_entered_basement) && (floor==-1)) {
            answer[1] = i;
            has_entered_basement = true;
        }


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
    answer[0] = floor;

}


int main(int argc, char * argv[]) {
 
    printf("Input file path to instructions: ");

    char *file_path;
    file_path = input_string(stdin, 16);

    FILE *fp = fopen(file_path, "r");

    char *instructions;
    instructions = input_string(fp, 16);

    printf("\nInputted instructions: %s\n", instructions);

    int answer[2];
    get_floor(instructions, answer);

    printf("Floor ended on: %d\n", answer[0]);
    if(answer[1] != 0) {
        printf("Instruction basement was entered at: %d\n", answer[1]);
    } else {
        printf("Never entered the basement!\n");
    }

    free(instructions);
    return 0;
}
