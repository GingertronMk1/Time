//
//  Sun.hpp
//  G53GRA.Framework
//
//  Created by Jack Ellis on 03/04/2018.
//  Copyright © 2018 w.o.c.ward. All rights reserved.
//

#ifndef Sun_hpp
#define Sun_hpp

#include <stdio.h>
#include "../Framework/Interface/DisplayableObject.h"

class Sun : public DisplayableObject
{
public:
    Sun(){};
    ~Sun(){};
    void Display();
};

#endif /* Sun_hpp */
