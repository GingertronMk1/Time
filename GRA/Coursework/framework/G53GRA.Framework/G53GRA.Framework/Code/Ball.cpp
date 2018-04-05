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
    float slices = 12;  // Needs to be a multiple of 4
    glPushMatrix();     //Remember how everything else
    
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glTranslatef(pos[0], pos[1], pos[2]);   //Set position (due to the way the ball will be rendered we have to move it back in z by the value of its current length
    glRotatef(static_cast<GLint>(bangles[0]), 1.0f, 0.0f, 0.0f);    //Set rotation in x
    glRotatef(static_cast<GLint>(bangles[1]), 0.0f, 1.0f, 0.0f);    //Set rotation in y
    glRotatef(static_cast<GLint>(bangles[2]), 0.0f, 0.0f, 1.0f);    //Set rotation in z
    
    glTranslatef(0, 0, -length);
    glScalef(width, width, length);     //Set scale
    
    for (float i = 0; i < (slices*2); i++)
    {
        float cTheta = (2*i*M_PI)/slices;       // Current theta
        float nTheta = (2*(i+1)*M_PI)/slices;   // Next theta
        float cSin = sin(cTheta);               // The sine of current theta
        float nSin = sin(nTheta);               // The sine of next theta
        float cCos = cos(cTheta);               // The cosine of current theta
        float nCos = cos(nTheta);               // The cosine of next theta
        
        int percentage = 100*(i/(slices));      // What percentage of the way around are we?

        if (percentage%25 == 8)                 // So the green stripes are on the diagonals properly
        {
            
            
            float mat_colour[]  = { 0.f, 1.f, 0.f, 1.f };
            float mat_ambient[] = { 0.f, 1.f, 0.f, 1.f };
            float mat_spec[]    = { 0.f, 1.f, 0.f, 0.1f };
            
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance looks
        }
        else
        {
            float mat_colour[]
            = { 1.f, 1.f, 1.f, 1.f };
            float mat_ambient[]
            = { 1.f, 1.f, 1.f, 1.f };
            float mat_spec[]
            = { 1.f, 1.f, 1.f, 1.f };
            
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance looks
        }
        
        // For each value of theta we go front to back, and back to front, along the ball
        // meeting in the middle.
        for (float j = 0; j < slices; j++)
        {
            float jSlices = j/slices;
            float incJSlices = (j+1)/slices;
            
            float p1 = sqrt(jSlices*(2-jSlices));
            float p2 = sqrt(incJSlices*(2-incJSlices));
             
            glBegin(GL_QUADS);
            glNormal3f(cSin*p1, cCos*p1, jSlices);
            glVertex3f(cSin*p1, cCos*p1, jSlices);
            
            glNormal3f(cSin*p2, cCos*p2, incJSlices);
            glVertex3f(cSin*p2, cCos*p2, incJSlices);
            
            glNormal3f(nSin*p2, nCos*p2, incJSlices);
            glVertex3f(nSin*p2, nCos*p2, incJSlices);
            
            glNormal3f(nSin*p1, nCos*p1, jSlices);
            glVertex3f(nSin*p1, nCos*p1, jSlices);
            glEnd();
            
            glBegin(GL_QUADS);
            glNormal3f(nSin*p1, nCos*p1, 2-jSlices);
            glVertex3f(nSin*p1, nCos*p1, 2-jSlices);
            
            glNormal3f(nSin*p2, nCos*p2, 2-incJSlices);
            glVertex3f(nSin*p2, nCos*p2, 2-incJSlices);
            
            glNormal3f(cSin*p2, cCos*p2, 2-incJSlices);
            glVertex3f(cSin*p2, cCos*p2, 2-incJSlices);
            
            glNormal3f(cSin*p1, cCos*p1, 2-jSlices);
            glVertex3f(cSin*p1, cCos*p1, 2-jSlices);
            glEnd();
        }
         /**/
        
    }
    
    glPopAttrib();
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
            bangles[0] -= 10;
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
#if 1
    printf("Kickable\n");
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
#endif
    
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
