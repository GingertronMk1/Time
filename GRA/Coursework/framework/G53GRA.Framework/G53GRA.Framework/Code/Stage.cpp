//
//  Stage.cpp
//  G53GRA.Framework
//
//  Created by Jack Ellis on 03/04/2018.
//  Copyright © 2018 w.o.c.ward. All rights reserved.
//

#include "Stage.hpp"


Stage::Stage()
{
}

void Stage::Display()
{
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    
    // Position objects in world space
    glTranslatef(pos[0], pos[1], pos[2]);               // Position
    glScalef(scale[0], scale[1], scale[2]);             // Scale
    glScalef(1000.f, 1000.f, 1000.f);
    glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
    glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)
    glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)
    
    DrawStage();

    glPopAttrib();
    glPopMatrix();
}

void Stage::setTextures(GLuint* _texids)
{
    texids = _texids;                       // Store texture references in pointer array
    toTexture = true;                       // Assume all loaded correctly
    for (int i = 0; i < 6; i++)             // Check if any textures failed to load (NULL)
        if (texids[i] == NULL) toTexture = false;   // If one texture failed, do not display any
}

void Stage::DrawStage()
{
    glDisable(GL_LIGHTING);                 // Disable lighting just for skybox
    glColor4f(1.f, 1.f, 1.f, 1.f);          // White canvas on which to draw skybox
    if (toTexture) glEnable(GL_TEXTURE_2D); // Enable 2D texturing
    
    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[0]); // skybox_left.bmp
    glBegin(GL_QUADS);
    // LEFT SIDE
    if (toTexture) glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
    glVertex3f(-1.f, 1.f, -1.f);
    if (toTexture) glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
    glVertex3f(-1.f, 1.f, 1.f);
    if (toTexture) glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
    glVertex3f(-1.f, -1.f, 1.f);
    if (toTexture) glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
    glVertex3f(-1.f, -1.f, -1.f);
    glEnd();
    
    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[1]); // skybox_right.bmp
    glBegin(GL_QUADS);
    // RIGHT SIDE
    if (toTexture) glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
    glVertex3f(1.f, 1.f, 1.f);
    if (toTexture) glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
    glVertex3f(1.f, 1.f, -1.f);
    if (toTexture) glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
    glVertex3f(1.f, -1.f, -1.f);
    if (toTexture) glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
    glVertex3f(1.f, -1.f, 1.f);
    glEnd();
    
    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[2]); // skybox_front.bmp
    glBegin(GL_QUADS);
    //  FAR SIDE
    if (toTexture) glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
    glVertex3f(1.f, 1.f, -1.f);
    if (toTexture) glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
    glVertex3f(-1.f, 1.f, -1.f);
    if (toTexture) glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
    glVertex3f(-1.f, -1.f, -1.f);
    if (toTexture) glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
    glVertex3f(1.f, -1.f, -1.f);
    glEnd();
    
    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[3]); // skybox_back.bmp
    glBegin(GL_QUADS);
    // NEAR SIDE
    if (toTexture) glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
    glVertex3f(-1.f, 1.f, 1.f);
    if (toTexture) glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
    glVertex3f(1.f, 1.f, 1.f);
    if (toTexture) glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
    glVertex3f(1.f, -1.f, 1.f);
    if (toTexture) glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
    glVertex3f(-1.f, -1.f, 1.f);
    glEnd();
    
    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[4]); // skybox_down.bmp
    glBegin(GL_QUADS);
    // BOTTOM SIDE
    if (toTexture) glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
    glVertex3f(-1.f, -1.f, 1.f);
    if (toTexture) glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
    glVertex3f(1.f, -1.f, 1.f);
    if (toTexture) glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
    glVertex3f(1.f, -1.f, -1.f);
    if (toTexture) glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
    glVertex3f(-1.f, -1.f, -1.f);
    glEnd();
    
    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[5]); // skybox_up.bmp
    glBegin(GL_QUADS);
    // TOP SIDE
    if (toTexture) glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
    glVertex3f(1.f, 1.f, 1.f);
    if (toTexture) glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
    glVertex3f(-1.f, 1.f, 1.f);
    if (toTexture) glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
    glVertex3f(-1.f, 1.f, -1.f);
    if (toTexture) glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
    glVertex3f(1.f, 1.f, -1.f);
    glEnd();
    
    if (toTexture) glDisable(GL_TEXTURE_2D);    // Disable texturing until reenabled
    glEnable(GL_LIGHTING);                      // Reenable lighting after drawing skybox
}
