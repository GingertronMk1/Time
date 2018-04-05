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
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    DrawSet(pos[0], pos[1], pos[2]);
    glPopAttrib();
    glPopMatrix();
}

void Posts::DrawSet(float x, float y, float z)
{
    glPushMatrix();
    
    float mat_colour[]                      //
    = { 1.f, 1.f, 1.f, 1.f };               //
    float mat_ambient[]                     //
    = { 1.f, 1.f, 1.f, 1.f };               //
    float mat_spec[]                        //
    = { 0.f, 0.f, 0.f, 1.f };               //
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance looks
    
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
    glNormal3f(0.f,0.f,-1.f);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);
    glEnd();
    // FAR SIDE
    glBegin(GL_QUADS);
    glNormal3f(0.f, 0.f, 1.f);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glEnd();
    // BOTTOM SIDE
    glBegin(GL_QUADS);
    glNormal3f(0.f,-1.f,0.f);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);
    glEnd();
    // TOP SIDE
    glBegin(GL_QUADS);
    glNormal3f(0.f,1.f,0.f);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);
    glEnd();
    // LEFT SIDE
    glBegin(GL_QUADS);
    glNormal3f(-1.f, 0.f, 0.f);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glEnd();
    // RIGHT SIDE
    glBegin(GL_QUADS);
    glNormal3f(1.f,0.f,0.f);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glEnd();
    glPopMatrix();
}
