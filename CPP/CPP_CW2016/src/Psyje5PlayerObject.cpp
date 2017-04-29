#include "header.h"
#include "Psyje5Main.h"
#include "Psyje5PlayerObject.h"


Psyje5PlayerObject::Psyje5PlayerObject(Psyje5Main* pEngine, int iMapX, int iMapY)
	: Psyje5Object(pEngine, iMapX, iMapY)
	, m_pMainEngine(pEngine)
	, m_iMapX(iMapX)
	, m_iMapY(iMapY)
	, m_iDir(0)
{
	m_iStartDrawPosX = -25;
	m_iStartDrawPosY = -25;

	m_iDrawWidth = 50;
	m_iDrawHeight = 50;

	m_iPreviousScreenX = m_iCurrentScreenX = iMapX * 50 + 25 + 25;
	m_iPreviousScreenY = m_iCurrentScreenY = iMapY * 50 + 25 + 40;

	SetVisible(true);
}


Psyje5PlayerObject::~Psyje5PlayerObject()
{
}

void Psyje5PlayerObject::Draw() {
	if (!IsVisible() || m_pMainEngine->CurrentState() == 2)
		return;

	int iTick = m_pMainEngine->GetModifiedTime() / 20;
	int iFrame = iTick % 30;
	int iSize = 20;
	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - iSize, m_iCurrentScreenY - iSize,
		m_iCurrentScreenX + iSize - 1, m_iCurrentScreenY + iSize - 1,
		0xff0000);

	StoreLastScreenPositionForUndraw();
};

void Psyje5PlayerObject::DoUpdate(int iCurrentTime) {

	// Allow some control over the object by the player
	if (m_pMainEngine->IsKeyPressed(SDLK_UP))
		m_iDir = 0;
	if (m_pMainEngine->IsKeyPressed(SDLK_RIGHT))
		m_iDir = 1;
	if (m_pMainEngine->IsKeyPressed(SDLK_DOWN))
		m_iDir = 2;
	if (m_pMainEngine->IsKeyPressed(SDLK_LEFT))
		m_iDir = 3;
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;

	DisplayableObject* pObject;
	for (int iObjectId = 0; (pObject = m_pMainEngine->GetDisplayableObject(iObjectId)) != NULL; iObjectId++) {
		if (pObject == this)
			continue;
		int iXDiff = pObject->GetXCentre() - m_iCurrentScreenX;		// get the centre of the object we're looking at in X
		int iYDiff = pObject->GetYCentre() - m_iCurrentScreenY;		// same in Y

		int iTick = iCurrentTime / 20;
		int iFrame = iTick % 30;
		int iSize = 10 + iFrame;
		if (iFrame > 15)
			iSize = 10 + (30 - iFrame);
		int iSizeOther = iSize;

		// Old Mate Pythagorus
		
		if (((iXDiff*iXDiff) + (iYDiff*iYDiff)) < ((iSizeOther + iSize)*(iSizeOther + iSize))) {		// if the difference between the centres of us and the other thing are bigger less than the radii:
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
			printf("Player Collision\n");
			
			m_pMainEngine->GameOver();
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
			tm.UpdateTile(m_pMainEngine, m_iMapX, m_iMapY,
				tm.GetValue(m_iMapX, m_iMapY) + 1);
			break;
		case 8:
			tm.UpdateTile(m_pMainEngine, m_iMapX, m_iMapY, 0);
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
				iCurrentTime + 400 + rand() % 200);
			break;
		case 1: // Wall
			switch (m_iDir) {
			case 0: m_iDir = 2; break;
			case 1: m_iDir = 3; break;
			case 2: m_iDir = 0; break;
			case 3: m_iDir = 1; break;
			}
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