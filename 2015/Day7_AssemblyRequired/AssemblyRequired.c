#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "../../headers/utils.h"

typedef struct {
    int signal;
    char * identifier;
} WIRE;

typedef struct {
    char * input1;
    char * input2;
    char * output;
    char * operator;
} COMMAND;

COMMAND *expand_command_array(COMMAND * commands, size_t * num_commands) {

    *num_commands = (*num_commands*2);

    //make house array bigger so we can store more houses
    COMMAND * temp = realloc(commands, sizeof(commands[0])*(*num_commands+1));
    

    
    if(temp == NULL) {

        //this is where i would put code to deal with the reallocation failing but i kinda dont know what to put
    } else {

        //if allocation was successful, set the pointer for the house array to the new expanded array
        commands = temp;
    }

    return commands;
}

WIRE *expand_wires_array(WIRE * wires, size_t * num_wires) {

    *num_wires = (*num_wires*2);

    //make house array bigger so we can store more houses
    WIRE * temp = realloc(wires, sizeof(wires[0])*(*num_wires+1));
    
    printf("expanding wires array \n");
    
    if(temp == NULL) {

        //this is where i would put code to deal with the reallocation failing but i kinda dont know what to put
    } else {

        //if allocation was successful, set the pointer for the house array to the new expanded array
        wires = temp;
    }

    return wires;
}

bool is_string_number(char * string) {
    int length = strlen (string);
    for (int i=0;i<length; i++) {
        if (!isdigit(string[i]))
        {
            return false;
        }
    }

    return true;
}

COMMAND *parse_command(char * command) {
    
    COMMAND * cmd = (COMMAND *) malloc (sizeof(COMMAND));
    cmd->operator = strdup("");
    char command_pieces[10][10];
    char * token;

    //printf("parsing\n");

    token = strtok(command, " ");
    int index = 0;
    while(token != NULL) {
        //printf("token %s\n", token);
        strcpy(command_pieces[index], token);
        token = strtok(NULL, " ");
        index++;
    }

    for(int i = 0; i < index; i++) {
        //printf("%s\n", command_pieces[i]);
        if(strcmp(command_pieces[i], "AND") == 0) {
            
            cmd->operator = strdup("AND");
            cmd->input1 = strdup(command_pieces[i-1]);
            cmd->input2 = strdup(command_pieces[i+1]);
            cmd->output = strdup(command_pieces[i+3]);

        } else if(strcmp(command_pieces[i], "OR") == 0) {
            cmd->operator = strdup("OR");
            cmd->input1 = strdup(command_pieces[i-1]);
            cmd->input2 = strdup(command_pieces[i+1]);
            cmd->output = strdup(command_pieces[i+3]);
        } else if(strcmp(command_pieces[i], "LSHIFT") == 0) {
            cmd->operator = strdup("LSHIFT");
            cmd->input1 = strdup(command_pieces[i-1]);
            cmd->input2 = strdup(command_pieces[i+1]);
            cmd->output = strdup(command_pieces[i+3]);
        } else if(strcmp(command_pieces[i], "RSHIFT") == 0) {
            cmd->operator = strdup("RSHIFT");
            cmd->input1 = strdup(command_pieces[i-1]);
            cmd->input2 = strdup(command_pieces[i+1]);
            cmd->output = strdup(command_pieces[i+3]);
        } else if(strcmp(command_pieces[i], "NOT") == 0) {
            cmd->operator = strdup("NOT");
            cmd->input1 = strdup(command_pieces[i+1]);
            cmd->input2 = strdup("");
            cmd->output = strdup(command_pieces[i+3]);
        }
    }

    if(!(*cmd->operator)) {
        cmd->operator = strdup("DIRECT");
        cmd->input1 = strdup(command_pieces[0]);
        cmd->input2 = strdup("");
        cmd->output = strdup(command_pieces[2]);
    }

    
    //printf("what %s\n", parsed_command.output);


    return cmd;
}

int is_wire_active(WIRE * wires, char * id, size_t * num_wires) {
    
    for(int i = 0; i < *num_wires; i++) {
        if(strcmp(wires[i].identifier, id) == 0) {
            return wires[i].signal;
        }
    }

    return  -1;
}

COMMAND * extract_commands(FILE* fp, size_t * total_commands) {
    COMMAND * commands = (COMMAND *) malloc (sizeof(COMMAND));
    size_t num_commands = 1;
    size_t current_command = 0;
    char * command;

    while(command = input_string(fp, 10)) {

        if(strcmp(command, "") == 0) {
            break;
        }

        if(current_command >= num_commands) {
            commands = expand_command_array(commands, &num_commands);
            printf("expanding commands array from %d to %d\n", num_commands, num_commands*2);
        }

        //printf("%s\n",command);
        commands[current_command] = *(parse_command(command));
        //printf("what\n");
        //printf("%s\n", cmd->output);

        printf("input 1 %s input 2 %s operator %s output %s \n", commands[current_command].input1, commands[current_command].input2, commands[current_command].operator, commands[current_command].output);
       //printf("input 1 %s input 2 %s operator %s output %s\n", cmd->input1, cmd->input2, cmd->operator, cmd->output);


        current_command++;
        //printf("what2\n");
    }

    *total_commands = current_command;

    return commands;
}

int bitwise_AND(int input1, int input2) {
    return input1 & input2;
}

int bitwise_OR(int input1, int input2) {
    return input1 | input2;
}

int bitwise_LSHIFT(int input1, int input2) {
    return input1 << input2;
}

int bitwise_RSHIFT(int input1, int input2) {
    return input1 >> input2;
}

int bitwise_NOT(int input1) {
    return ~input1;
}

int find_signal_at_target(char * target, COMMAND * commands, WIRE * wires, size_t * num_wires, size_t * wires_size) {
    
    int index = 0;
    int signal = 0;
    while(strcmp(commands[index].output, target) != 0) {
        //printf("current output %s\n", commands[index].output);
        index++;
    }

    printf("target wanted %s has inputs %s and %s and operator to it %s\n", commands[index].output, commands[index].input1, commands[index].input2, commands[index].operator);

    int check_wire = is_wire_active(wires, commands[index].output, num_wires);

    if(check_wire != -1) {
        return check_wire;
    } else {
        if(*num_wires >= *wires_size) {
            wires = expand_wires_array(wires, wires_size);
        }

        wires[*num_wires].identifier = strdup(commands[index].output);
        wires[*num_wires].signal = 0;

        *num_wires++;
    }

    if(strcmp(commands[index].operator, "DIRECT") == 0) {

        printf("found direct connection\n");
        if(is_string_number(commands[index].input1)) {
            printf("value found at root %d\n", atoi(commands[index].input1));
            return atoi(commands[index].input1);
        } else {
            signal = find_signal_at_target(commands[index].input1, commands, wires, num_wires, wires_size);
            printf("current target %s\n", commands[index].input1);
        }

    }

    

    return signal;

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

    COMMAND * commands;
    WIRE * wires = (WIRE *) malloc (sizeof(WIRE));
    wires[0].signal = -1;
    wires[0].identifier = strdup("init");
    size_t num_wires = 1;
    size_t wires_size = 1;
    size_t num_commands;
    commands = extract_commands(fp, &num_commands);

    printf("number of commands %d\n", num_commands);

    //printf("input 1 %s input 2 %s operator %s output %s\n", commands[3].input1, commands[3].input2, commands[3].operator, commands[3].output);

    int x = 5;
    int y = 5;

    printf("%d\n", bitwise_AND(x,y));

    int d = find_signal_at_target("a", commands, wires, &num_wires, &wires_size);

    printf("%d\n", d);


    printf("deez nuts\n");

    return 0;
}