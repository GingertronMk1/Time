#include <stdio.h>

double volumeForRadius(double r);

int main() {
    printf("The volume of a sphere with radius 1 is %f\n", volumeForRadius(1));
    printf("The volume of a sphere with radius 4.657 is %f\n", volumeForRadius(4.657));
    printf("The volume of a sphere with radius -0.5 is %f\n", volumeForRadius(-0.5));
    printf("The volume of a sphere with radius 10 is %f\n", volumeForRadius(10));
    printf("The volume of a sphere with radius 42 is %f\n", volumeForRadius(42));

};

double vol(double r) {
   float pi = 3.14159265;
   double volume = (4*pi*r*r*r)/3;
   if(volume > 0) {                      //obviously negative radii and volumes aren't really a thing, so we do need to check for em
       return volume;
   } else {
       printf("Danger! Negative radii aren't a thing! Here's the answer anyway: ");
       return volume;
   };
};

