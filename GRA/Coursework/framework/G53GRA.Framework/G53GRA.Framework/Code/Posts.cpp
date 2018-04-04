//
//  Posts.cpp
//  G53GRA.Framework
//
//  Created by Jack Ellis on 02/04/2018.
//  Copyright © 2018 w.o.c.ward. All rights reserved.
//

#include "Posts.hpp"

void Posts::Display()
{
    glPushMatrix();
    DrawSet(pos[0], pos[1], pos[2]);
    glPopMatrix();
}

void Posts::DrawSet(float x, float y, float z)
{
    glPushMatrix();
    glColor3f(255.0f,255.0f,255.0f);
    DrawPost(x+(distApart/2), y, z);
    DrawPost(x-(distApart/2), y, z);
    DrawCrossBar(x, y+crossHeight, z);
    glPopMatrix();
}

void Posts::DrawPost(float x, float y, float z)
{
    float diam = width/2;           //It's not a circle but same idea
    float hHeight = height/2;
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glTranslatef(x,y+hHeight,z);
    glScalef(diam, hHeight, diam);
    DrawCube();
    glPopAttrib();
    glPopMatrix();
}

void Posts::DrawCrossBar(float x, float y, float z)
{
    float diam = width/2;           //It's not a circle but same idea
    float halfWidth = 1+(distApart/2);
    
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glTranslatef(x, y, z);
    glScalef(halfWidth, diam, diam);
    DrawCube();
    glPopAttrib();
    glPopMatrix();
}

void Posts::DrawCube()
{
    glPushMatrix();
    // NEAR SIDE
    glBegin(GL_QUADS);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);
    glEnd();
    // FAR SIDE
    glBegin(GL_QUADS);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glEnd();
    // BOTTOM SIDE
    glBegin(GL_QUADS);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);
    glEnd();
    // TOP SIDE
    glBegin(GL_QUADS);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);
    glEnd();
    // LEFT SIDE
    glBegin(GL_QUADS);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glEnd();
    // RIGHT SIDE
    glBegin(GL_QUADS);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glEnd();
    glPopMatrix();
}
