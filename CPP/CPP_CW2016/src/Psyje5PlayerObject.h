#pragma once
#include "Psyje5Object.h"

class Psyje5PlayerObject :
	public Psyje5Object
{
public:
	Psyje5PlayerObject(Psyje5Main* pEngine, int iMapX, int iMapY);
	~Psyje5PlayerObject(void);
	void Draw();
	void DoUpdate(int iCurrentTime);
	virtual int GetPsyje5ObjectKind() { return 1; }


private:
	Psyje5Main* m_pMainEngine;

	MovePos m_oMover;
	int m_iMapX;
	int m_iMapY;
	int m_iDir;
};

