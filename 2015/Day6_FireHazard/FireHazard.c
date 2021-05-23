#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../headers/utils.h"

int * parse_command(char * command) {

    //allocate memory for the parsed commands so we can return this 
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

    //loop through all of the lights and count them if they are on
    for(int i = 0; i < 1000; i++) {
        for(int j = 0; j < 1000; j++) {
            if(lights[i][j]) {
                lit_lights++;
            }
        }
    }
    return lit_lights;
}

long count_brightness(int ** brightness) {
    long total_brightness = 0;

    //loop through all of the lights and add up their brightness values
    for(int i = 0; i < 1000; i++) {
        for(int j = 0; j < 1000; j++) {
            total_brightness += brightness[i][j];
        }
    }

    return total_brightness;
}

void turn_on_lights(bool lights[1000][1000], int x1, int y1, int x2, int y2) {


    //turn on the lights within the given range
    for(int i = x1; i <= x2; i++) {
        for(int j = y1; j <= y2; j++) {
            lights[i][j] = true;
        }
    }

}

void turn_off_lights(bool lights[1000][1000], int x1, int y1, int x2, int y2) {

    //turn off the lights within the given range
    for(int i = x1; i <= x2; i++) {
        for(int j = y1; j <= y2; j++) {
            lights[i][j] = false;
        }
    }
}

void toggle_lights(bool lights[1000][1000], int x1, int y1, int x2, int y2) {

    //toggle the lighs within the given range
    for(int i = x1; i <= x2; i++) {
        for(int j = y1; j <= y2; j++) {
            lights[i][j] = !lights[i][j];
        }
    }
}

void turn_up_lights(int ** brightness, int x1, int y1, int x2, int y2) {

    //turn up the brightness of the lights by one within the given range
    for(int i = x1; i <= x2; i++) {
        for(int j = y1; j <= y2; j++) {
            brightness[i][j]++;
        }
    }

}

void turn_down_lights(int ** brightness, int x1, int y1, int x2, int y2) {

    //turn down the brightness of the lights by one within the given range (as long as they aren't 0)
    for(int i = x1; i <= x2; i++) {
        for(int j = y1; j <= y2; j++) {
            if(brightness[i][j] != 0) {
                brightness[i][j]--;
            }
        }
    }
}

void turn_up_twice(int ** brightness, int x1, int y1, int x2, int y2) {

    //turn up the brightness of the lights by two within the given range
    for(int i = x1; i <= x2; i++) {
        for(int j = y1; j <= y2; j++) {
            brightness[i][j]+=2;
        }
    }
}

int do_commands_bool(FILE* fp) {


    char * command;
    int * parsed_command;

    bool lights[1000][1000];
    

    //initialize the lights array to all falses to start "off"
    for(int i = 0; i < 1000; i++) {
        for(int j = 0; j < 1000; j++) {
            lights[i][j] = false;
        }
    }



    
    //loop through all of the commands
    while(command = input_string(fp,10)) {

        //if the command is an empty string that means we hit the end of the file and we should break from the loop
        if(strcmp(command, "") == 0) {
            break;
        }


        //parse the command into its seperate parts
        parsed_command = parse_command(command);


        //if the command contains "turn on"
        if(parsed_command[0] == 1) {
            turn_on_lights(lights, parsed_command[1], parsed_command[2], parsed_command[3], parsed_command[4]);

        // if the command contains "turn off"
        } else if(parsed_command[0] == 2) {
            turn_off_lights(lights, parsed_command[1], parsed_command[2], parsed_command[3], parsed_command[4]);

        // if the command contains "toggle"
        } else {
            toggle_lights(lights, parsed_command[1], parsed_command[2], parsed_command[3], parsed_command[4]);
        }


        //free the memory that was allocated
        free(parsed_command);
        free(command);
    }


    printf("lights on %d\n",count_lights(lights));


    return 0;
}

int do_commands_int(FILE* fp) {



    char * command;
    int * parsed_command;

    //allocate memory to hold the pointers to the "rows"
    int ** brightness = (int **) malloc (1000 * sizeof(int*));

    //allocate memory for each "row" and add it to the array of arrays
    for(int i = 0; i < 1000; i++) {
        brightness[i] = (int *) malloc (1000* sizeof(int));
    }
    
    //initialize all values within the array to 0 
    for(int i = 0; i < 1000; i++) {
        for(int j = 0; j < 1000; j++) {
            brightness[i][j] = 0;
        }
    }

    //rest is same as above
    while(command = input_string(fp,10)) {

        if(strcmp(command, "") == 0) {
            break;
        }

        parsed_command = parse_command(command);

        if(parsed_command[0] == 1) {
            turn_up_lights(brightness, parsed_command[1], parsed_command[2], parsed_command[3], parsed_command[4]);
        } else if(parsed_command[0] == 2) {
            turn_down_lights(brightness, parsed_command[1], parsed_command[2], parsed_command[3], parsed_command[4]);
        } else {
            turn_up_twice(brightness, parsed_command[1], parsed_command[2], parsed_command[3], parsed_command[4]);
        }
        


        free(parsed_command);
        free(command); 

    }

    printf("total brightness %d\n",count_brightness(brightness));
    free(brightness);

    return 0;
}

int main(int argc, char * argv[]) {

    printf("Input file path to command list: ");

    char *file_path;
    file_path = input_string(stdin, 16);

    printf("file path %s\n",file_path);
    FILE *fp = fopen(file_path, "r");

    if(fp != NULL) {
        printf("file opened correctly\n");
    }

    do_commands_bool(fp);

    fclose(fp);
    fp = fopen(file_path, "r");

    do_commands_int(fp);

    fclose(fp);
    free(file_path);
    return 0;
}