#pragma once
#include "DisplayableObject.h"
#include "MovePos.h"

class Psyje5Main;


class Psyje5Object :
	public DisplayableObject
{
public:
	Psyje5Object(Psyje5Main* pEngine, int iMapX, int iMapY);
	~Psyje5Object(void);
	void Draw();
	void DoUpdate(int iCurrentTime);
	int GetXDiffForDirection(int iDir){
		switch (iDir % 4){
		case 0: return 0;
		case 1: return 1;
		case 2: return 0;
		case 3: return -1;
		default: return 0;
		}
	}

	int GetYDiffForDirection(int iDir){
		switch (iDir % 4){
		case 0: return -1; // Up
		case 1: return 0; // Right
		case 2: return 1; // Down
		case 3: return 0; // Left
		default: return 0; // Can never happen
		}
	}
	virtual int GetPsyje5ObjectKind() { return 0; }

private:
	Psyje5Main* m_pMainEngine;

	MovePos m_oMover;
	int m_iMapX;
	int m_iMapY;
	int m_iDir;
public:
	bool IsVisible();
};

