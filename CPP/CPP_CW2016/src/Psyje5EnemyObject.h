#pragma once
#include "Psyje5Object.h"
class Psyje5EnemyObject :
	public Psyje5Object
{
public:
	Psyje5EnemyObject(Psyje5Main* pEngine, int iMapX, int iMapY);
	~Psyje5EnemyObject(void);
	void Draw();
	void DoUpdate(int iCurrentTime);

private:
	Psyje5Main* m_pMainEngine;

	MovePos m_oMover;
	int m_iMapX;
	int m_iMapY;
	int m_iDir;
};

