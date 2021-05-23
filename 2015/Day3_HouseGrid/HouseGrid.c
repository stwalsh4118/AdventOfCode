#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../headers/utils.h"

//struct to hold x and y values for the houses
typedef struct {
    int x;
    int y;
} HOUSE;

bool is_house_visited(HOUSE * houses, HOUSE current_house, size_t num_houses) {

    //loop through all of the current visited houses to see if the current house has been visited
    for(int i = 0; i < num_houses; i++) {
        
        //if the current house is one of the visited houses
        if((houses[i].x == current_house.x) && (houses[i].y == current_house.y)) {
            return true;
        }
    }

    return false;
}

HOUSE *expand_house_array(HOUSE * houses, size_t * num_houses) {

    *num_houses = (*num_houses*2);

    //make house array bigger so we can store more houses
    HOUSE * temp = realloc(houses, sizeof(houses[0])*(*num_houses+1));
    

    
    if(temp == NULL) {

        //this is where i would put code to deal with the reallocation failing but i kinda dont know what to put
    } else {

        //if allocation was successful, set the pointer for the house array to the new expanded array
        houses = temp;
    }

    return houses;
}

int get_num_unique_houses(char* directions, HOUSE * houses, size_t num_houses) {

    char v = 'v';
    char left_arrow = '<';
    char right_arrow = '>';
    size_t current_houses = 1;
    HOUSE current_house = {0,0};
    int x_coordinate = 0;
    int y_coordinate = 0;


    //loop through all of the directions
    for(int i = 0; i < strlen(directions); i++) {

        if(directions[i] == 0) {
            //break;

        //if the directions is "v" (which means down)
        } else if(directions[i] == v) {

            //move the coordinates downwards
            y_coordinate--;

            //set the current house coordinates
            current_house.x = x_coordinate;
            current_house.y = y_coordinate;

            //if the house at the current coordinates has not been visited before            
            if(!is_house_visited(houses, current_house, current_houses)) {

                //increase the number of unique visited houses
                current_houses++;

                //if there are more unique visited houses than what we can hold in our array, expand the array
                if(current_houses >= num_houses) {
                    houses = expand_house_array(houses, &num_houses);
                }

                //add the current house to the visited houses array
                houses[current_houses-1].x = x_coordinate;
                houses[current_houses-1].y = y_coordinate;
            }
        
        //if the directions is "<" (which means left)
        //the rest is the same as above
        } else if(directions[i] == left_arrow) {
            x_coordinate--;
            current_house.x = x_coordinate;
            current_house.y = y_coordinate;


            if(!is_house_visited(houses, current_house, current_houses)) {
                current_houses++;
                if(current_houses >= num_houses) {
                    houses = expand_house_array(houses, &num_houses);
                }
                houses[current_houses-1].x = x_coordinate;
                houses[current_houses-1].y = y_coordinate;
            }
        
        //if the directions is ">" (which means right)
        //the rest is the same as above
        } else if(directions[i] == right_arrow) {
            x_coordinate++;
            current_house.x = x_coordinate;
            current_house.y = y_coordinate;


            if(!is_house_visited(houses, current_house, current_houses)) {
                current_houses++;
                if(current_houses >= num_houses) {
                    houses = expand_house_array(houses, &num_houses);
                }
                houses[current_houses-1].x = x_coordinate;
                houses[current_houses-1].y = y_coordinate;
            }
        
        //if the directions is anything else (which due to the constraints of the input means up since thats the only other symbol that should be in the directions)
        //the rest is the same as above
        } else {
            y_coordinate++;
            current_house.x = x_coordinate;
            current_house.y = y_coordinate;


            if(!is_house_visited(houses, current_house, current_houses)) {
                current_houses++;
                if(current_houses >= num_houses) {
                    houses = expand_house_array(houses, &num_houses);
                }
                houses[current_houses-1].x = x_coordinate;
                houses[current_houses-1].y = y_coordinate;
            }
        }


    }
    


    return current_houses;
}

int get_num_unique_houses_robo(char* directions, HOUSE * houses, size_t num_houses) {

    //all of this is the same as above except every time we read in a direction we switch between changing regular santa's coordinates and robo santa's coordinates
    //it still checks if the current house that the santa we're focusing on is at has been visited before and adds them like normal

    char v = 'v';
    char left_arrow = '<';
    char right_arrow = '>';
    size_t current_houses = 1;
    HOUSE current_house = {0,0};
    int x_coordinate = 0;
    int y_coordinate = 0;
    int robo_x_coordinate = 0;
    int robo_y_coordinate = 0;
    bool robo_santa = false;


    for(int i = 0; i < strlen(directions); i++) {

        if(directions[i] == 0) {

        } else if(directions[i] == v) {

            if(!robo_santa) {
                y_coordinate--;
                current_house.x = x_coordinate;
                current_house.y = y_coordinate;
                robo_santa = !robo_santa;
            } else {
                robo_y_coordinate--;
                current_house.x = robo_x_coordinate;
                current_house.y = robo_y_coordinate;
                robo_santa = !robo_santa;
            }
            


            if(!is_house_visited(houses, current_house, current_houses)) {
                current_houses++;
                if(current_houses >= num_houses) {
                    houses = expand_house_array(houses, &num_houses);
                }
                houses[current_houses-1].x = current_house.x;
                houses[current_houses-1].y = current_house.y;
            }
        
        } else if(directions[i] == left_arrow) {
            if(!robo_santa) {
                x_coordinate--;
                current_house.x = x_coordinate;
                current_house.y = y_coordinate;
                robo_santa = !robo_santa;

            } else {
                robo_x_coordinate--;
                current_house.x = robo_x_coordinate;
                current_house.y = robo_y_coordinate;
                robo_santa = !robo_santa;

            }


            if(!is_house_visited(houses, current_house, current_houses)) {
                current_houses++;
                if(current_houses >= num_houses) {
                    houses = expand_house_array(houses, &num_houses);
                }
                houses[current_houses-1].x = current_house.x;
                houses[current_houses-1].y = current_house.y;
            }
        
        } else if(directions[i] == right_arrow) {
            if(!robo_santa) {
                x_coordinate++;
                current_house.x = x_coordinate;
                current_house.y = y_coordinate;
                robo_santa = !robo_santa;

            } else {
                robo_x_coordinate++;
                current_house.x = robo_x_coordinate;
                current_house.y = robo_y_coordinate;
                robo_santa = !robo_santa;

            }


            if(!is_house_visited(houses, current_house, current_houses)) {
                current_houses++;
                if(current_houses >= num_houses) {
                    houses = expand_house_array(houses, &num_houses);
                }
                houses[current_houses-1].x = current_house.x;
                houses[current_houses-1].y = current_house.y;
            }
        
        } else {
            if(!robo_santa) {
                y_coordinate++;
                current_house.x = x_coordinate;
                current_house.y = y_coordinate;
                robo_santa = !robo_santa;

            } else {
                robo_y_coordinate++;
                current_house.x = robo_x_coordinate;
                current_house.y = robo_y_coordinate;
                robo_santa = !robo_santa;

            }


            if(!is_house_visited(houses, current_house, current_houses)) {
                current_houses++;
                if(current_houses >= num_houses) {
                    houses = expand_house_array(houses, &num_houses);
                }
                houses[current_houses-1].x = current_house.x;
                houses[current_houses-1].y = current_house.y;
            }
        }


    }
    


    return current_houses;
}


int main(int argc, char * argv[]) {

    printf("Input file path to directions: ");

    char *file_path;
    file_path = input_string(stdin, 16);

    FILE *fp = fopen(file_path, "r");

    char *directions;
    directions = input_string(fp, 16);

    printf("%s\n", directions);

    HOUSE * houses = (HOUSE*) malloc(sizeof(HOUSE));
    HOUSE origin = {0,0};
    houses[0] = origin;

    int num_unique_houses = get_num_unique_houses(directions, houses, 1);

    HOUSE * houses_robo = (HOUSE*) malloc(sizeof(HOUSE));
    HOUSE origin_robo = {0,0};
    houses_robo[0] = origin_robo;

    int num_unique_houses_robo = get_num_unique_houses_robo(directions, houses_robo, 1);

    printf("num unique houses %d\n", num_unique_houses);
    printf("num unique houses with robo %d\n", num_unique_houses_robo);


    free(file_path);
    free(directions);
    free(houses);
    free(houses_robo);

    return 0;
}