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
	virtual void GameOver();

	// get reference to tileman
	Psyje5TileMan& GetTileManager() { return m_oTiles; }
private:
	Psyje5TileMan m_oTiles;
public:
	// defining states
	enum State { stateInit, stateMain, statePaused, stateOver };

	int m_iPauseStarted;
private:
	State m_state;
public:
	int m_iTimer;
	int m_iHiScore;
	void DrawBackgroundSquares(int iColour1, int iColour2);
	int CurrentState();
	void ScoreUpdate(int iScoreUpdate);
	int m_iScore;
};

