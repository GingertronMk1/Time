#include <stdio.h>

void rectPrinter();

int main() {
    rectPrinter();
};

void rectPrinter(){
    int width;
    int height;
    printf("Please enter the width and height for your rectangle (separated by a comma, e.g. 7,6): ");
    scanf("%d,%d", &width, &height);
    if(0 > width || width > 80 || 0 > height || height > 80){
        printf("Error: invalid values!\n");
    } else {
        for (int y = 1; y <= height; y++){
            for (int x = 1; x <= width; x++){
                printf("*");
            };
            printf("\n");
        }
    };
};

