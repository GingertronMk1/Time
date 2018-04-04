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
    glColor3f(0.0f,0.5f,0.0f);
     
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    
    glBindTexture(GL_TEXTURE_2D, texID);
    
    //printf("%d\n", texID);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(10.0f, 10.0f);
    glVertex3f(350, 0, 600);

    glTexCoord2f(10.0f, 0.0f);
    glVertex3f(350, 0, -600);
    
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-350, 0, -600);
    
    glTexCoord2f(0.0f, 10.0f);
    glVertex3f(-350, 0, 600);
    
    glEnd();
    
    glDisable(GL_COLOR_MATERIAL);
    
    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);
    glPopAttrib();
    glPopMatrix();
}
