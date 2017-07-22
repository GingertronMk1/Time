#pragma once

#include "DisplayableObject.h"

class Psyje5DispObject1 :
	public DisplayableObject
{
public:
	Psyje5DispObject1(BaseEngine* pEngine);
	~Psyje5DispObject1(void);
	void Draw();
	void DoUpdate(int iCurrentTime);
};
