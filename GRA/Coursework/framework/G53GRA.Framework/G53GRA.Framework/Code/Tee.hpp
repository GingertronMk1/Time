//
//  Tee.hpp
//  G53GRA.Framework
//
//  Created by Jack Ellis on 04/04/2018.
//  Copyright © 2018 w.o.c.ward. All rights reserved.
//

#ifndef Tee_hpp
#define Tee_hpp

#include <stdio.h>
#include "../Framework/Interface/DisplayableObject.h"

class Tee : public DisplayableObject
{
public:
    Tee(){};
    ~Tee(){};
    Tee(const std::string& filename);
    void Display();
    
private:
    float height = 15;
    float radius = 5;
    GLint texID;
};

#endif /* Tee_hpp */
