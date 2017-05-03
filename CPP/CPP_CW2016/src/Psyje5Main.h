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
	void GameWon();
	void DrawGameInfo(int m_CurrentState);
	void TileUpdate(int iTaken);
	void ScoreUpdate(int iScoreUpdate);
	void DrawBackgroundSquares(int iColour1, int iColour2);
	int CurrentState();
	int GetLevel() { return m_Level; }

	// get reference to tileman
	Psyje5TileMan& GetTileManager() { return m_oTiles; }
private:
	Psyje5TileMan m_oTiles;
public:
	// defining states
	enum State { stateInit, stateMain, statePaused, stateFailed, stateWon };

	int m_iPauseStarted;
private:
	State m_state;
public:
	int m_iHiScore;
	int m_iScore;
	int m_iTilesDone;
	int m_Level;
	void GameRender(void);
private:
	bool m_bInsideDraw;
public:
	void AnimatedBG();
};

