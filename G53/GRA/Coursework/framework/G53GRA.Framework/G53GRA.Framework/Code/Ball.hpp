//
//  Ball.hpp
//  G53GRA.Framework
//
//  Created by Jack Ellis on 03/04/2018.
//  Copyright © 2018 w.o.c.ward. All rights reserved.
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include <cmath>
#include "../Framework/Interface/DisplayableObject.h"
#include "../Framework/Interface/Animation.h"
#include "../Framework/Interface/Input.h"

class Ball : public DisplayableObject, public Animation, public Input
{
public:
    Ball(){};
    ~Ball(){};
    void Display();
    void Update(const double& deltaTime);
    void Bangle(float bX, float bY, float bZ);
    void HandleKey(unsigned char key, int state, int x, int y);
    void startFlying();
    void reset();
    void set();
    enum ballStates {preset, isSet, kicked, landed};

private:
    float length =          15.0f;  // Ball Length
    float width =           10.0f;  // Ball Width
    float bangles[3] =      {0.0f, 0.0f, 0.0f};  //flip, spin, yaw
    ballStates ballState =  preset;      // Has the ball been kicked?
    float gravity =         -9.8f;  // The value of acceleration in y due to gravity
    float speedOffBoot =    10.0f;
    float angleDegs;
    float angleRads;
    float speedAlong;
    float speedUp;
    float posOff[3] = {0.f,0.f,0.f};
    float banglesOff[3] = {0.f, 0.f, 0.f};
    GLint texID;        // For texturing
};

#endif /* Ball_hpp */
