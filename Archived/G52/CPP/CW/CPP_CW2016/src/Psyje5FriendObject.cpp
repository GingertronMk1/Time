#include "header.h"
#include "Psyje5FriendObject.h"
#include "Psyje5Main.h"


Psyje5FriendObject::Psyje5FriendObject(Psyje5Main* pEngine, int iMapX, int iMapY)
	: Psyje5Object(pEngine, iMapX, iMapY)
	, m_pMainEngine(pEngine)
	, m_iMapX(iMapX)
	, m_iMapY(iMapY)
	, m_iDir(0)
{
	// The same as for 'Psyje5Object'
}


Psyje5FriendObject::~Psyje5FriendObject(void)
{
}

void Psyje5FriendObject::Draw() {
	if (!IsVisible())
		return;

	int iTick = m_pMainEngine->GetModifiedTime() / 20;
	int iFrame = iTick % 30;
	int iSize = 10;

	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - iSize, m_iCurrentScreenY - iSize,
		m_iCurrentScreenX + iSize - 1, m_iCurrentScreenY + iSize - 1,
		0x00ff00);

	StoreLastScreenPositionForUndraw();

};

void Psyje5FriendObject::DoUpdate(int iCurrentTime) {
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;

	DisplayableObject* pObject;
	Psyje5Object* pPsyje5Object;
	for (int iObjectId = 0;
		(pObject = m_pMainEngine->GetDisplayableObject(iObjectId)) != NULL; iObjectId++) {
		if (pObject == this)
			continue;
		// dynamically cast to a Psyje5Object so we can
		// use functions from that class to ID each object
		pPsyje5Object = dynamic_cast<Psyje5Object*>(pObject);			
		int pPsyje5ObjectKind = pPsyje5Object->GetPsyje5ObjectKind();

		int iXDiff = pObject->GetXCentre() - m_iCurrentScreenX;
		int iYDiff = pObject->GetYCentre() - m_iCurrentScreenY;

		int iSize = 10;

		int iTick, iFrame, iSizeOther;

		switch (pPsyje5ObjectKind) {
		case 1:			iSizeOther = 20;			// Player object has a constant size of 20
			break;
		case 2:
			iTick = iCurrentTime / 20;
			iFrame = iTick % 30;
			iSizeOther = 10 + iFrame;
			if (iFrame > 15)
				iSizeOther = 10 + (30 - iFrame);	// Enemy objects pulsate
			break;
		case 3:
			iSizeOther = 10;						// Friend object has a constant size of 10
			break;									// We're unlikely to encounter another friend
		}

		// Old Mate Pythagorus
		if (((iXDiff*iXDiff) + (iYDiff*iYDiff)) < ((iSizeOther + iSize)*(iSizeOther + iSize))) {
			if (pPsyje5ObjectKind == 1) {
				m_pMainEngine->ScoreUpdate(1000);
			}
				m_iMapX = 1 + rand() % 13;
				m_iMapY = 1 + (rand() % 2) * 8;
				m_iDir = 1;
				m_oMover.Setup(
					m_iMapX * 50 + 25 + 25, //m_iCurrentScreenX,
					m_iMapY * 50 + 25 + 40, //m_iCurrentScreenY,
					m_iMapX * 50 + 25 + 25,
					m_iMapY * 50 + 25 + 40,
					iCurrentTime,
					iCurrentTime + 400);
				m_oMover.Calculate(iCurrentTime);
				m_iCurrentScreenX = m_oMover.GetX();
				m_iCurrentScreenY = m_oMover.GetY();
				RedrawObjects();
			return;
		}

	}

	// If movement has finished
	if (m_oMover.HasMovementFinished(iCurrentTime))
	{
		Psyje5TileMan& tm = m_pMainEngine->GetTileManager();


		// Set off a new movement
		switch (rand() % 10)
		{
		case 0: // Increase dir by 1
			m_iDir = (m_iDir + 1) % 4;
			break;
		case 1: // Reduce dir by 1
			m_iDir = (m_iDir + 3) % 4;
			break;
		}

		switch (tm.GetValue(
			m_iMapX + GetXDiffForDirection(m_iDir),
			m_iMapY + GetYDiffForDirection(m_iDir)))
		{
		case 0: // Passageway
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			// Allow move - set up new movement now
			m_iMapX += GetXDiffForDirection(m_iDir);
			m_iMapY += GetYDiffForDirection(m_iDir);

			m_oMover.Setup(
				m_iCurrentScreenX,
				m_iCurrentScreenY,
				m_iMapX * 50 + 25 + 25,
				m_iMapY * 50 + 25 + 40,
				iCurrentTime,
				iCurrentTime + 500);
			break;
		case 1: // Wall
			m_iDir = rand() % 4; // Rotate randomly
			break;
		}
	}

	if (!m_oMover.HasMovementFinished(iCurrentTime))
	{
		m_oMover.Calculate(iCurrentTime);
		m_iCurrentScreenX = m_oMover.GetX();
		m_iCurrentScreenY = m_oMover.GetY();
	}

	RedrawObjects();


}