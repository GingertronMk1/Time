#pragma once

#include "DisplayableObject.h"

class Psyje5DispObject2 :
	public DisplayableObject
{
public:
	Psyje5DispObject2(BaseEngine* pEngine);
	~Psyje5DispObject2(void);
	void Draw();
	void DoUpdate(int iCurrentTime);
protected:
	int m_iDirectionLeft;		// Are we moving left?
	int m_iDirectionUp;			// Are we moving up?

};
