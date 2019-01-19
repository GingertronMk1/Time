//
//  Turf.cpp
//  G53GRA.Framework
//
//  Created by Jack Ellis on 02/04/2018.
//  Copyright © 2018 w.o.c.ward. All rights reserved.
//

#include "Turf.hpp"

/*
Turf::Turf()
{
    //Display();
}
 */

Turf::Turf(const std::string& filename) : Turf()
{
    texID = Scene::GetTexture(filename);
}

void Turf::Display()
{
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glTranslatef(pos[0], pos[1], pos[2]);
    glColor3f(1.0f,1.0f,1.0f);
    glScalef(width, 1.f, length);
     
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    
    glBindTexture(GL_TEXTURE_2D, texID);
    
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(1.f, 1.f);
    glVertex3f(0.5f, 0, 0.5f);

    glTexCoord2f(1.f, 0.f);
    glVertex3f(0.5f, 0, -0.5f);
    
    glTexCoord2f(0.f, 0.f);
    glVertex3f(-0.5f, 0, -0.5f);
    
    glTexCoord2f(0.f, 1.f);
    glVertex3f(-0.5f, 0, 0.5f);
    
    glEnd();
    
    glDisable(GL_COLOR_MATERIAL);
    
    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);
    glPopAttrib();
    glPopMatrix();
}
