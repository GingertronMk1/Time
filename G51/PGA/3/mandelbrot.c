#include <stdio.h>

void mandelbrot();

int main() {
    mandelbrot();
};

void mandelbrot(){
    for(int rows = 0; rows < 53; rows++){
        for(int columns = 0; columns < 80; columns++){
            int it = 4096;
            double r = 0;
            double i = 0; 
            double r2 = 0; 
            double i2 = 0;
            double x = (columns-40)*(1.5/40);
            double y = (rows-26.5)/26.5;
            do {
                double tmp = r2 - i2 + x;
                i = 2 * r * i + y;
                r = tmp;
                r2 = r*r; i2 = i*i;
            } while((r2 + i2) <= 4.0 && --it);
            if(it == 0){
                printf(" ");
            } else {
                printf("*");
            };
        };
        printf("\n");
    };
};

