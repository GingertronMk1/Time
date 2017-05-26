#pragma once
#include "Psyje5Object.h"
#include "MovePos.h"

class Psyje5Main;


class Psyje5FriendObject :
	public Psyje5Object
{
public:
	Psyje5FriendObject(Psyje5Main* pEngine, int iMapX, int iMapY);
	~Psyje5FriendObject(void);
	void Draw();
	void DoUpdate(int iCurrentTime);
	int GetPsyje5ObjectKind() { return 3; }

private:
	Psyje5Main* m_pMainEngine;

	MovePos m_oMover;
	int m_iMapX;
	int m_iMapY;
	int m_iDir;
	};