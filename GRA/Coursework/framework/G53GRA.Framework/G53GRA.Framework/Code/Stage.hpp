//
//  Stage.hpp
//  G53GRA.Framework
//
//  Created by Jack Ellis on 03/04/2018.
//  Copyright © 2018 w.o.c.ward. All rights reserved.
//

#ifndef Stage_hpp
#define Stage_hpp

#include <stdio.h>
#include "../Framework/Interface/DisplayableObject.h"

class Stage : public DisplayableObject
{
public:
    Stage();
    ~Stage(){};
    void Display();
    void setTextures(GLuint* _texids);
    
private:
    void DrawStage();
    bool toTexture = false;
    GLuint* texids;
};

#endif /* Stage_hpp */
