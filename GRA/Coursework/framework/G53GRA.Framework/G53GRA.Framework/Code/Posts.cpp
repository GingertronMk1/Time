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
    glTranslatef(pos[0], pos[1], pos[2]);
    DrawSet();
    glPopAttrib();
    glPopMatrix();
}

void Posts::DrawSet()
{
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    
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
    
    DrawPost(distApart);
    DrawPost(-distApart);
    DrawCrossBar();
     
    glPopAttrib();
    glPopMatrix();
}

void Posts::DrawPost(float x)
{
    glPushMatrix();
    glTranslatef(x, height/2, 0.f);     // Translate up by half height as we'll draw the cube out from origin
    glScalef(width, height, width);     // Scale properly
    DrawCube();
    glPopMatrix();
}

void Posts::DrawCrossBar()
{
    glPushMatrix();
    glTranslatef(0.f, crossHeight, 0.f);
    glScalef(2*(distApart+1), width, width);
    DrawCube();
    glPopMatrix();
}

void Posts::DrawCube()
{
    glPushMatrix();
    
    
    glBegin(GL_QUADS);
    
    // draw the front face
    
    // set the normal of the front face
    glNormal3f(0.0f, 0.0f, 1.0f);
    
    // set coordinates for the vertices
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    
    // draw the back face
    
    // set the normal of the back face
    glNormal3f(0.0f, 0.0f, -1.0f);
    
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    
    // draw the left face

    // set the normal of the left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    
    // set coordinates for the vertices
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    
    // draw the right face

    // set the normal of the right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    
    // set coordinates for the vertices
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    
    // draw the top face
    
    // set the normal of the top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    
    // set coordinates for the vertices
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    
    // draw the bottom face
    
    // set the normal of the bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    
    // set coordinates for the vertices
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
   
    glEnd();
    glPopMatrix();
}
