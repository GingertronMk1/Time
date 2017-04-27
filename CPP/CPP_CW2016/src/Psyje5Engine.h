#pragma once
#include "BaseEngine.h"
#include "Psyje5TileMan.h"
class Psyje5Engine :
	public BaseEngine
{
public:
	Psyje5Engine();
	~Psyje5Engine();
	virtual void SetupBackgroundBuffer();
	virtual void MouseDown(int iButton, int iX, int iY);
	virtual int InitialiseObjects();

private:
	Psyje5TileMan m_oTiles;
public:
	void DrawStrings();
	void DrawStringsUnderneath();
	void UnDrawStrings();
};

