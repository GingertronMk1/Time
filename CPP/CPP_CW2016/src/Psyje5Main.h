#pragma once

#include "BaseEngine.h"
#include "TileManager.h"
#include "Psyje5TileMan.h"

class Psyje5Main :
	public BaseEngine
{
public:
	Psyje5Main(void);
	~Psyje5Main(void);

	virtual void SetupBackgroundBuffer();
	virtual int InitialiseObjects();
	virtual void DrawStrings();
	virtual void GameAction();
	virtual void MouseDown(int iButton, int iX, int iY);
	virtual void KeyDown(int iKeyCode);
	virtual void UndrawObjects();
	virtual void DrawObjects();

	// get reference to tileman
	Psyje5TileMan& GetTileManager() { return m_oTiles; }
private:
	Psyje5TileMan m_oTiles;
public:
	// defining states
	enum State { stateInit, stateMain, statePaused };

	int m_iPauseStarted;
private:
	State m_state;
};
