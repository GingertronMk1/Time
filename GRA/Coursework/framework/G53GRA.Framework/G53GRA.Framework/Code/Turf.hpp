//
//  Turf.hpp
//  G53GRA.Framework
//
//  Created by Jack Ellis on 02/04/2018.
//  Copyright © 2018 w.o.c.ward. All rights reserved.
//

#ifndef Turf_hpp
#define Turf_hpp

#include <stdio.h>
#include "../Framework/Interface/DisplayableObject.h"

class Turf : public DisplayableObject
{
public:
    Turf(){};
    ~Turf(){};
    Turf(const std::string& filename);
    void Display();
    
private:
    GLint texID;
};

#endif /* Turf_hpp */
