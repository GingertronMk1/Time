//
//  Ball.cpp
//  G53GRA.Framework
//
//  Created by Jack Ellis on 03/04/2018.
//  Copyright © 2018 w.o.c.ward. All rights reserved.
//

#include "Ball.hpp"
#include <cmath>

void Ball::Display()
{
    width = length * (2.0f/3.0f);
    glPushMatrix();     //Remember how everything else looks

    glColor3f(1.0f,1.0f,1.0f);      //Set colour
    glTranslatef(pos[0], pos[1], pos[2]);   //Set position
    glRotatef(static_cast<GLint>(bangles[0]), 1.0f, 0.0f, 0.0f);    //Set rotation in x
    glRotatef(static_cast<GLint>(bangles[1]), 0.0f, 1.0f, 0.0f);    //Set rotation in y
    glRotatef(static_cast<GLint>(bangles[2]), 0.0f, 0.0f, 1.0f);    //Set rotation in z

    glScalef(width, width, length);     //Set scale
    glutSolidSphere(1, static_cast<GLint>(12), static_cast<GLint>(12));        //Draw a ball
    
    glPopMatrix();
}

void Ball::Update(const double& deltaTime)
{
    if (isKicked == 1) {
        if (pos[1] <= 0)
        {
            isKicked = 2;
        }
        else
        {
            speedUp += gravity/100;
            //printf("speedUp: %f\n", speedUp);
            pos[2] += speedAlong;
            pos[1] += speedUp;
            bangles[0] -= 5;
            if (bangles[0] > 180.0f) {bangles[0] = bangles[0] - 180.0f;}    //doesnt' need to be 360 as ball has order-2 rotational symmetry
        }
    }
}

void Ball::Bangle(float bX, float bY, float bZ)
{
    bangles[0] = bX;
    bangles[1] = bY;
    bangles[2] = bZ;
}

void Ball::HandleKey(unsigned char key, int state, int x, int y)
{
    if(state == 1)  // Only on the downstroke
    {
        if(isKicked == 0)
        {
            switch (key)
            {
                case ' ':   startFlying();
                            break;
                case 'q':
                case 'Q':   bangles[0] -= 2;
                            printf("angle: %f\n", bangles[0]);
                            break;
                case 'a':
                case 'A':   bangles [0] += 2;
                            printf("angle: %f\n", bangles[0]);
                default:    break;

            }
        } else if(isKicked == 2) {
            switch (key)
            {
                case 'r':
                case 'R':   reset();
                default:    break;
            }
        }
    }
}

void Ball::startFlying()
{
    for (int i = 0; i < 3; i++)
    {
        origPos[i] = pos[i];
        origBangles[i] = bangles[i];
        printf("pos[%d]: %f, bangles[%d]: %f\n", i, origPos[i], i, origBangles[i]);

    }
    angleDegs = abs(bangles[0]);
    angleRads = angleDegs*(M_PI/180.0f);
    speedAlong = speedOffBoot*cos(angleRads);
    speedUp = speedOffBoot*sin(angleRads);
    isKicked = 1;   // Get update() going

}

void Ball::reset()
{
    printf("Resetting...\n");
    speedUp = 0;
    speedAlong = 0;
    for (int i = 0; i < 3; i++)
    {
        pos[i] = origPos[i];
        bangles[i] = origBangles[i];
        printf("pos[%d]: %f, bangles[%d]: %f\n", i, pos[i], i, bangles[i]);
    }
    isKicked = 0;       // Reset fully
}
