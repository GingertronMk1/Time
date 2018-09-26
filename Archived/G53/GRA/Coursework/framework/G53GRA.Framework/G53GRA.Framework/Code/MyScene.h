#pragma once

#include "../Framework/Engine/Scene.h"
#include "Turf.hpp"
#include "Posts.hpp"
#include "Ball.hpp"
#include "Sun.hpp"
#include "Stage.hpp"
#include "Tee.hpp"

class MyScene :
	public Scene
{
public:
	MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	~MyScene() {};

private:
	void Initialise();
	void Projection();

};
