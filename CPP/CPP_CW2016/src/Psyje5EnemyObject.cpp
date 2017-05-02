#include "header.h"
#include "Psyje5EnemyObject.h"
#include "Psyje5Main.h"


Psyje5EnemyObject::Psyje5EnemyObject(Psyje5Main* pEngine, int iMapX, int iMapY)
	: Psyje5Object(pEngine, iMapX, iMapY)
	, m_pMainEngine(pEngine)
	, m_iMapX(iMapX)
	, m_iMapY(iMapY)
	, m_iDir(0)
{
// The same as for 'Psyje5Object'
}


Psyje5EnemyObject::~Psyje5EnemyObject(void)
{
}

void Psyje5EnemyObject::Draw() {
	if (!IsVisible())
		return;

	int iTick = m_pMainEngine->GetModifiedTime() / 20;
	int iFrame = iTick % 30;
	int iSize = 10 + iFrame;
	if (iFrame > 15)
		iSize = 10 + (30 - iFrame);

	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - iSize, m_iCurrentScreenY - iSize,
		m_iCurrentScreenX + iSize - 1, m_iCurrentScreenY + iSize - 1,
		0x00ffff);

	StoreLastScreenPositionForUndraw();

};

void Psyje5EnemyObject::DoUpdate(int iCurrentTime) {
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;

	DisplayableObject* pObject;
	for (int iObjectId = 0;
		(pObject = m_pMainEngine->GetDisplayableObject(iObjectId)) != NULL; iObjectId++) {
		if (pObject == this)
			continue;
		int iXDiff = pObject->GetXCentre() - m_iCurrentScreenX;
		int iYDiff = pObject->GetYCentre() - m_iCurrentScreenY;

		int iTick = iCurrentTime / 20;
		int iFrame = iTick % 30;
		int iSize = 10 + iFrame;
		if (iFrame > 15)
			iSize = 10 + (30 - iFrame);
		int iSizeOther = iSize;

		// Old Mate Pythagorus
		if (((iXDiff*iXDiff) + (iYDiff*iYDiff)) < ((iSizeOther + iSize)*(iSizeOther + iSize))) {
			if (iObjectId == 0) {
				m_pMainEngine->GameOver();
			}
			else {
				m_iMapX = 1 + rand() % 13;
				m_iMapY = 1 + (rand() % 2) * 8;
				m_iDir = 1;
				m_oMover.Setup(
					m_iMapX * 50 + 25 + 25, //m_iCurrentScreenX,
					m_iMapY * 50 + 25 + 40, //m_iCurrentScreenY,
					m_iMapX * 50 + 25 + 25,
					m_iMapY * 50 + 25 + 40,
					iCurrentTime,
					iCurrentTime + 400 + rand() % 200);
				m_oMover.Calculate(iCurrentTime);
				m_iCurrentScreenX = m_oMover.GetX();
				m_iCurrentScreenY = m_oMover.GetY();
				RedrawObjects();
			}
			return;
		}

	}

	// If movement has finished
	if (m_oMover.HasMovementFinished(iCurrentTime))
	{
		
		Psyje5TileMan& tm = m_pMainEngine->GetTileManager();
		
		// Handle any tile that we just moved onto
		switch (tm.GetValue(m_iMapX, m_iMapY))
		{
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			if (rand() % 10 == 0) {
				tm.UpdateTile(m_pMainEngine, m_iMapX, m_iMapY, 0);
				m_pMainEngine->TileUpdate(-1);
			}
			break;
		}
		
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
		case 2: // Pellet
		case 3: // Pellet
		case 4: // Pellet
		case 5: // Pellet
		case 6: // Pellet
		case 7: // Pellet
		case 8: // Pellet
			// Allow move - set up new movement now
			m_iMapX += GetXDiffForDirection(m_iDir);
			m_iMapY += GetYDiffForDirection(m_iDir);

			m_oMover.Setup(
				m_iCurrentScreenX,
				m_iCurrentScreenY,
				m_iMapX * 50 + 25 + 25,
				m_iMapY * 50 + 25 + 40,
				iCurrentTime,
				iCurrentTime + 400 - (5 * m_pMainEngine->GetLevel()));
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