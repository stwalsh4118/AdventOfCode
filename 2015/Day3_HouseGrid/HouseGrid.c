#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../headers/utils.h"

typedef struct {
    int x;
    int y;
} HOUSE;

bool is_house_visited(HOUSE * houses, HOUSE current_house, size_t num_houses) {

    for(int i = 0; i < num_houses; i++) {
        
        if((houses[i].x == current_house.x) && (houses[i].y == current_house.y)) {
            //printf("House already visited\n");
            return true;
        }
    }

    //printf("House not already visited\n");
    return false;
}

HOUSE *expand_house_array(HOUSE * houses, size_t * num_houses) {

    *num_houses = (*num_houses*2);
    // printf("max number of houses in an array: %zu\n", (SIZE_MAX / sizeof(houses[0])));
    //printf("expanding house array from %d to %d\n", *num_houses/2,*num_houses);
    // printf("size of house struct %d\n", sizeof(houses[0]));

    HOUSE * temp = realloc(houses, sizeof(houses[0])*(*num_houses+1));
    
    // printf("allocation finished\n");

    
    if(temp == NULL) {
        //printf("Failed to allocate, trying again");
        //return expand_house_array(houses, num_houses-10);
    } else {
        
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

    //printf("directions length %d\n", strlen(directions));
    //printf("at coordinate %d, %d on direction number %d current number of unique houses %d\n", current_house.x, current_house.y, 0, current_houses);

    for(int i = 0; i < strlen(directions); i++) {

        if(directions[i] == 0) {
            //break;

        } else if(directions[i] == v) {
            y_coordinate--;
            current_house.x = x_coordinate;
            current_house.y = y_coordinate;

            //printf("moving to coordinates %d, %d\n", x_coordinate, y_coordinate);

            if(!is_house_visited(houses, current_house, current_houses)) {
                current_houses++;
                if(current_houses >= num_houses) {
                    houses = expand_house_array(houses, &num_houses);
                }
                //printf("adding house at %d, %d\n", x_coordinate, y_coordinate);
                houses[current_houses-1].x = x_coordinate;
                houses[current_houses-1].y = y_coordinate;
            }
        
        } else if(directions[i] == left_arrow) {
            x_coordinate--;
            current_house.x = x_coordinate;
            current_house.y = y_coordinate;

            //printf("moving to coordinates %d, %d\n", x_coordinate, y_coordinate);

            if(!is_house_visited(houses, current_house, current_houses)) {
                current_houses++;
                if(current_houses >= num_houses) {
                    houses = expand_house_array(houses, &num_houses);
                }
                //printf("adding house at %d, %d\n", x_coordinate, y_coordinate);
                houses[current_houses-1].x = x_coordinate;
                houses[current_houses-1].y = y_coordinate;
            }
        
        } else if(directions[i] == right_arrow) {
            x_coordinate++;
            current_house.x = x_coordinate;
            current_house.y = y_coordinate;

            //printf("moving to coordinates %d, %d\n", x_coordinate, y_coordinate);

            if(!is_house_visited(houses, current_house, current_houses)) {
                current_houses++;
                if(current_houses >= num_houses) {
                    houses = expand_house_array(houses, &num_houses);
                }
                //printf("adding house at %d, %d\n", x_coordinate, y_coordinate);
                houses[current_houses-1].x = x_coordinate;
                houses[current_houses-1].y = y_coordinate;
            }
        
        } else {
            y_coordinate++;
            current_house.x = x_coordinate;
            current_house.y = y_coordinate;

            //printf("moving to coordinates %d, %d\n", x_coordinate, y_coordinate);

            if(!is_house_visited(houses, current_house, current_houses)) {
                current_houses++;
                if(current_houses >= num_houses) {
                    houses = expand_house_array(houses, &num_houses);
                }
                //printf("adding house at %d, %d\n", x_coordinate, y_coordinate);
                houses[current_houses-1].x = x_coordinate;
                houses[current_houses-1].y = y_coordinate;
            }
        }

        //printf("at coordinate %d, %d on direction number %d current number of unique houses %d\n", current_house.x, current_house.y, i+1, current_houses);

    }
    


    return current_houses;
}

int get_num_unique_houses_robo(char* directions, HOUSE * houses, size_t num_houses) {

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

    //printf("directions length %d\n", strlen(directions));
    //printf("at coordinate %d, %d on direction number %d current number of unique houses %d\n", current_house.x, current_house.y, 0, current_houses);

    for(int i = 0; i < strlen(directions); i++) {

        if(directions[i] == 0) {
            //break;

        } else if(directions[i] == v) {

            if(!robo_santa) {
                y_coordinate--;
                current_house.x = x_coordinate;
                current_house.y = y_coordinate;
                robo_santa = !robo_santa;
                //printf("Regular Santa ");
            } else {
                robo_y_coordinate--;
                current_house.x = robo_x_coordinate;
                current_house.y = robo_y_coordinate;
                robo_santa = !robo_santa;
                //printf("Robo Santa ");
            }
            

            //printf("moving to coordinates %d, %d\n", current_house.x, current_house.y);

            if(!is_house_visited(houses, current_house, current_houses)) {
                current_houses++;
                if(current_houses >= num_houses) {
                    houses = expand_house_array(houses, &num_houses);
                }
                //printf("adding house at %d, %d\n", current_house.x, current_house.y);
                houses[current_houses-1].x = current_house.x;
                houses[current_houses-1].y = current_house.y;
            }
        
        } else if(directions[i] == left_arrow) {
            if(!robo_santa) {
                x_coordinate--;
                current_house.x = x_coordinate;
                current_house.y = y_coordinate;
                robo_santa = !robo_santa;
                //printf("Regular Santa ");

            } else {
                robo_x_coordinate--;
                current_house.x = robo_x_coordinate;
                current_house.y = robo_y_coordinate;
                robo_santa = !robo_santa;
                //printf("Robo Santa ");

            }

            //printf("moving to coordinates %d, %d\n", current_house.x, current_house.y);

            if(!is_house_visited(houses, current_house, current_houses)) {
                current_houses++;
                if(current_houses >= num_houses) {
                    houses = expand_house_array(houses, &num_houses);
                }
                //printf("adding house at %d, %d\n", current_house.x, current_house.y);
                houses[current_houses-1].x = current_house.x;
                houses[current_houses-1].y = current_house.y;
            }
        
        } else if(directions[i] == right_arrow) {
            if(!robo_santa) {
                x_coordinate++;
                current_house.x = x_coordinate;
                current_house.y = y_coordinate;
                robo_santa = !robo_santa;
                //printf("Regular Santa ");

            } else {
                robo_x_coordinate++;
                current_house.x = robo_x_coordinate;
                current_house.y = robo_y_coordinate;
                robo_santa = !robo_santa;
                //printf("Robo Santa ");

            }

            //printf("moving to coordinates %d, %d\n", current_house.x, current_house.y);

            if(!is_house_visited(houses, current_house, current_houses)) {
                current_houses++;
                if(current_houses >= num_houses) {
                    houses = expand_house_array(houses, &num_houses);
                }
                //printf("adding house at %d, %d\n", current_house.x, current_house.y);
                houses[current_houses-1].x = current_house.x;
                houses[current_houses-1].y = current_house.y;
            }
        
        } else {
            if(!robo_santa) {
                y_coordinate++;
                current_house.x = x_coordinate;
                current_house.y = y_coordinate;
                robo_santa = !robo_santa;
                //printf("Regular Santa ");

            } else {
                robo_y_coordinate++;
                current_house.x = robo_x_coordinate;
                current_house.y = robo_y_coordinate;
                robo_santa = !robo_santa;
                //printf("Robo Santa ");

            }

            //printf("moving to coordinates %d, %d\n", current_house.x, current_house.y);

            if(!is_house_visited(houses, current_house, current_houses)) {
                current_houses++;
                if(current_houses >= num_houses) {
                    houses = expand_house_array(houses, &num_houses);
                }
                //printf("adding house at %d, %d\n", current_house.x, current_house.y);
                houses[current_houses-1].x = current_house.x;
                houses[current_houses-1].y = current_house.y;
            }
        }

        //printf("at coordinate %d, %d on direction number %d current number of unique houses %d\n", current_house.x, current_house.y, i+1, current_houses);

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

    return 0;
}