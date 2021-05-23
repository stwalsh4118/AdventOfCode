#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/utils.h"

//box struct that holds the length width and height of the box
typedef struct {
    int length;
    int height;
    int width;
} BOX;



void extract_dimensions(char *raw_dim, int dimensions[]) {
    //split the dimensions string that we got from the file at the x
    char * token = strtok(raw_dim,"x");
    int index = 0;

    //keep splitting until we get to the end of the dimensions
    while(token != NULL) {

        //convert the string version of the dimension into an int then store it in the dimensions array to use later
        dimensions[index++] = atoi(token);
        token = strtok(NULL, "x");
    }
}

BOX *create_boxes(int num_boxes, FILE* fp) {


    //allocate memory for each set of dimensions in the file 
    BOX *boxes = (BOX*)malloc(num_boxes * sizeof(BOX));
    
    char * box;

    int index = 0;

    //while there are still boxes to be read from the file
    while(box=input_string(fp,10)) {
        
        if(strcmp(box,"") == 0) {
            break;
        }

        printf("%s\n",box);
        int dimensions[3];

        //change the string representation of the dimensions into ints that we can use
        extract_dimensions(box, dimensions);

        //store the dimensions in their respective box object
        boxes[index].length = dimensions[0];
        boxes[index].width = dimensions[1];
        boxes[index].height = dimensions[2];
        index++;

        free(box);
    }   

    fclose(fp);

    return boxes;
}

int calculate_surface_area(BOX box) {
    int HL = box.height*box.length;
    int HW = box.height*box.width;
    int LW = box.length*box.width;

    //calculate the surface area of the box
    int surface_area = 2*(HL + HW + LW);
    

    //calculate the smallest side of the box to find out the amount of slack we need
    if(HL <= HW && HL <= LW) {
        surface_area += HL;
    } else if (HW <= HL && HW <= LW) {
        surface_area += HW;
    } else {
        surface_area += LW;
    }

    return surface_area;
}

int caluclate_volume(BOX box) {
    //calculate the volume of the box is cubic feet
    return box.height*box.width*box.length;
}

int calculate_smallest_perimeter(BOX box) {
    int HL = box.height + box.length;
    int HW = box.height + box.width;
    int LW = box.length + box.width;

    //check for the smallest side then return its perimeter
    if(HL <= HW && HL <= LW) {
        return 2*HL;
    } else if (HW <= HL && HW <= LW) {
        return 2*HW;
    } else {
        return 2*LW;
    }
}

long calculate_total_paper(BOX *boxes, size_t num_boxes) {
    
    long total_paper = 0;
    
    //loop through all the boxes adding up their surface areas + slack needed
    for(int i = 0; i < num_boxes; i++) {
        total_paper += calculate_surface_area(boxes[i]);
    }

    return total_paper;

}

long calculate_total_ribbon(BOX *boxes, size_t num_boxes) {

    long total_ribbon = 0;

    //loop through all the boxes adding up the perimeter of their smallest side and their volume
    for(int i = 0; i < num_boxes; i++) {
        total_ribbon += (calculate_smallest_perimeter(boxes[i]) + caluclate_volume(boxes[i]));
    }

    return total_ribbon;
}

int main(int argc, char * argv[]) {

    printf("Input file path to box dimensions: ");

    char *file_path;
    file_path = input_string(stdin, 16);

    FILE *fp = fopen(file_path, "r");

    BOX *boxes;

    int num_boxes = count_lines(fp);
    fclose(fp);
    printf("%d\n",num_boxes);

    fp = fopen(file_path, "r");

    boxes = create_boxes(num_boxes, fp);

    fclose(fp);
    
    printf("total paper needed %ld\n", calculate_total_paper(boxes, num_boxes));
    printf("total ribbon needed %ld\n", calculate_total_ribbon(boxes, num_boxes));

    free(boxes);
    return 0;
}