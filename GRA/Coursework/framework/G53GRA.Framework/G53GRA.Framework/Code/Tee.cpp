//
//  Tee.cpp
//  G53GRA.Framework
//
//  Created by Jack Ellis on 04/04/2018.
//  Copyright © 2018 w.o.c.ward. All rights reserved.
//

#include "Tee.hpp"
#include <cmath>

Tee::Tee(const std::string& filename) : Tee()
{
    texID = Scene::GetTexture(filename);
}

void Tee::Display()
{
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, texID);
    glNormal3f(0.0f, 1.0f, 0.0f);

    glColor3f(2.33f, 1.71f,.46f);
    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(radius, height, radius);
    int slices = 12;
    for (int i = 0; i < slices; i++)
    {
        float cTheta = (2*i*M_PI)/slices;       // Current theta
        float nTheta = (2*(i+1)*M_PI)/slices;   // Next theta
        float cSin = sin(cTheta);
        float nSin = sin(nTheta);
        float cCos = cos(cTheta);
        float nCos = cos(nTheta);
        glBegin(GL_QUADS);
        glNormal3f(nSin, 0, nCos);
        glTexCoord2f(0.2f,0.0f);
        glVertex3f(nSin, 0, nCos);
        glTexCoord2f(0.2f,1.0f);
        glVertex3f(nSin, 1, nCos);
        glNormal3f(cSin, 0, cCos);
        glTexCoord2f(0.0f,1.0f);
        glVertex3f(cSin, 1, cCos);
        glTexCoord2f(0.0f,0.0f);
        glVertex3f(cSin, 0, cCos);
        glEnd();
        glBegin(GL_TRIANGLES);
        glNormal3f(0.0f,1.0f,0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0, 1, 0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(cSin, 1, cCos);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(nSin, 1, nCos);
        glEnd();
    }
    
    glDisable(GL_COLOR_MATERIAL);
    
    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);
    
    glPopAttrib();
    glPopMatrix();
}
