#include <stdio.h>

void clockAdder(int b, int d);

int main() {
    clockAdder(1245,345);
    clockAdder(1045,345);
    clockAdder(800,435);
    clockAdder(2300,300);

};

void clockAdder(int b, int d) {
    int bHours = b/100;                 //splitting start time into hours and minutes
    int bMinutes = b%100;
    int dHours = d/100;                 //splitting duration into hours and minutes
    int dMinutes = d%100;
    int fHours = bHours + dHours;       //adding hours
    int fMinutes = bMinutes + dMinutes; //adding minutes
    if(fMinutes >= 60) {                 //if the end minutes is more than 60, convert those 60 minutes into an hour
        fMinutes = fMinutes - 60;
        fHours = fHours + 1;
    };
    if(fHours >= 24) {                   //if the end hours is more than 24, convert those 24 hours into a day, essentially
        fHours = fHours - 24;
    };
    int fTime = (fHours*100) + fMinutes;    //the opposite process to what happens at the beginning of the function
    if(500 < fTime && fTime <= 1200) {
        printf("Start time is %d. Duration is %d. End time is %d in the morning.\n", b, d, fTime);
    } else if(1200 < fTime && fTime <= 1700) {
        printf("Start time is %d. Duration is %d. End time is %d in the afternoon.\n", b, d, fTime);
    } else if(1700 < fTime && fTime <= 2100) {
        printf("Start time is %d. Duration is %d. End time is %d in the evening.\n", b, d, fTime);
    } else if(2100 < fTime||fTime <= 500) {
        printf("Start time is %d. Duration is %d. End time is %d at night.\n", b, d, fTime);
    };
};
