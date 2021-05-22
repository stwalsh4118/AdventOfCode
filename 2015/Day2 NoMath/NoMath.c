#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/utils.h"

#define ARRAYLENGTH(x) sizeof(x)/sizeof(x[0])
typedef struct {
    int length;
    int height;
    int width;
} BOX;



void extract_dimensions(char *raw_dim, int dimensions[]) {
    char * token = strtok(raw_dim,"x");
    int index = 0;
    while(token != NULL) {
        dimensions[index++] = atoi(token);
        token = strtok(NULL, "x");
    }
}

BOX *create_boxes(int num_boxes) {

    FILE* fp = fopen("boxes.txt", "r");

    BOX *boxes = (BOX*)malloc(num_boxes * sizeof(BOX));
    
    char * box;

    int index = 0;

    while(box=input_string(fp,10)) {
        
        if(strcmp(box,"") == 0) {
            break;
        }
        printf("%s\n",box);
        int dimensions[3];
        extract_dimensions(box, dimensions);

        boxes[index].length = dimensions[0];
        boxes[index].width = dimensions[1];
        boxes[index].height = dimensions[2];
        index++;
    }   

    fclose(fp);

    return boxes;
}

int calculate_surface_area(BOX box) {
    int HL = box.height*box.length;
    int HW = box.height*box.width;
    int LW = box.length*box.width;

    int surface_area = 2*(HL + HW + LW);
    
    if(HL <= HW && HL <= LW) {
        surface_area += HL;
    } else if (HW <= HL && HW <= LW) {
        surface_area += HW;
    } else {
        surface_area += LW;
    }

    return surface_area;
}

long calculate_total_paper(BOX *boxes, size_t num_boxes) {
    
    long total_paper = 0;

    for(int i = 0; i < num_boxes; i++) {
        total_paper += calculate_surface_area(boxes[i]);
    }

    return total_paper;

}

int main(int argc, char * argv[]) {

    BOX *boxes;

    FILE* fp = fopen("boxes.txt", "r");

    int num_boxes = count_lines(fp);
    fclose(fp);
    printf("%d\n",num_boxes);

    boxes = create_boxes(num_boxes);

    
    printf("total paper needed %ld", calculate_total_paper(boxes, num_boxes));
    return 0;
}