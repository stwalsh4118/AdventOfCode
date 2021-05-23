#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../headers/utils.h"

int * parse_command(char * command) {

    int * commands = (int *) malloc(5 * sizeof(int));

    char * token = strtok(command, " ");

    int command_index = 0;

    //check for one of the 3 command types: turn off, turn on, and toggle
    if(strcmp(token, "turn") == 0) {
        token = strtok(NULL, " ");
        if(strcmp(token,"on") == 0) {
            commands[0] = 1;
        } else {
            commands[0] = 2;
        }
    } else {
        commands[0] = 3;
    }

    //first x coordinate
    token = strtok(NULL, ",");
    commands[1] = atoi(token);

    //first y coordinate
    token = strtok(NULL, " ");
    commands[2] = atoi(token);

    // "through"
    token = strtok(NULL, " ");

    //second x coordinate
    token = strtok(NULL, ",");
    commands[3] = atoi(token);
    //second y coordinate
    token = strtok(NULL, " ");
    commands[4] = atoi(token);

    return commands; 

}

int count_lights(bool lights[1000][1000]) {
    int lit_lights = 0;

    for(int i = 0; i < 1000; i++) {
        for(int j = 0; j < 1000; j++) {
            if(lights[i][j]) {
                lit_lights++;
            }
        }
    }
    return lit_lights;
}

void turn_on_lights(bool lights[1000][1000], int x1, int y1, int x2, int y2) {

    for(int i = x1; i <= x2; i++) {
        for(int j = y1; j <= y2; j++) {
            lights[i][j] = true;
        }
    }

}

void turn_off_lights(bool lights[1000][1000], int x1, int y1, int x2, int y2) {
    for(int i = x1; i <= x2; i++) {
        for(int j = y1; j <= y2; j++) {
            lights[i][j] = false;
        }
    }
}

void toggle_lights(bool lights[1000][1000], int x1, int y1, int x2, int y2) {
    for(int i = x1; i <= x2; i++) {
        for(int j = y1; j <= y2; j++) {
            lights[i][j] = !lights[i][j];
        }
    }
}

int do_commands(FILE* fp) {

    char * command;
    int * parsed_command;

    bool lights[1000][1000];
    
    for(int i = 0; i < 1000; i++) {
        for(int j = 0; j < 1000; j++) {
            lights[i][j] = false;
        }
    }

    while(command = input_string(fp,10)) {

        if(strcmp(command, "") == 0) {
            break;
        }


        parsed_command = parse_command(command);

        if(parsed_command[0] == 1) {
            printf("turn on lights\n");
            turn_on_lights(lights, parsed_command[1], parsed_command[2], parsed_command[3], parsed_command[4]);
        } else if(parsed_command[0] == 2) {
            printf("turn off lights\n");
            turn_off_lights(lights, parsed_command[1], parsed_command[2], parsed_command[3], parsed_command[4]);
        } else {
            printf("toggle lights\n");
            toggle_lights(lights, parsed_command[1], parsed_command[2], parsed_command[3], parsed_command[4]);
        }

        free(parsed_command);
        free(command);
    }

    printf("lights on %d\n",count_lights(lights));


    return 0;
}

int main(int argc, char * argv[]) {

    printf("Input file path to command list: ");

    char *file_path;
    file_path = input_string(stdin, 16);

    FILE *fp = fopen(file_path, "r");

    do_commands(fp);

    fclose(fp);
    free(file_path);
    return 0;
}