//
//  Sun.cpp
//  G53GRA.Framework
//
//  Created by Jack Ellis on 03/04/2018.
//  Copyright © 2018 w.o.c.ward. All rights reserved.
//

#include "Sun.hpp"

void Sun::Display()
{
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glTranslatef(pos[0], pos[1], pos[2]);
    glColor3f(2.33f, 1.71f,.46f);
    glutSolidSphere(10, static_cast<GLint>(12), static_cast<GLint>(12));
    glPopAttrib();
    glPopMatrix();
}

