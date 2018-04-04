//
//  Posts.hpp
//  G53GRA.Framework
//
//  Created by Jack Ellis on 02/04/2018.
//  Copyright © 2018 w.o.c.ward. All rights reserved.
//

#ifndef Posts_hpp
#define Posts_hpp

#include <stdio.h>
#include "../Framework/Interface/DisplayableObject.h"

class Posts : public DisplayableObject
{
public:
    Posts(){};
    ~Posts(){};
    void Display();
    void DrawSet(float x, float y, float z);
    void DrawPost(float x, float y, float z);
    void DrawCrossBar(float x, float y, float z);
    void DrawCube();
    
private:
    float width = 5;            //Width of each post
    float height = 400;         //Height of each post
    float distApart = 100;      //Distance posts are apart
    float crossHeight = 100;    //Height of crossbar
};

#endif /* Posts_hpp */
