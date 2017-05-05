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
	// The same as for 'Psyje5Object'
}


Psyje5PlayerObject::~Psyje5PlayerObject()
{
}

void Psyje5PlayerObject::Draw() {
	if (!IsVisible())
		return;

	int iTick = m_pMainEngine->GetModifiedTime() / 20;
	int iFrame = iTick % 30;
	int iSize = 20;
	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - iSize, m_iCurrentScreenY - iSize,
		m_iCurrentScreenX + iSize - 1, m_iCurrentScreenY + iSize - 1,
		0xff0000);

	m_pMainEngine->DrawScreenString(m_iCurrentScreenX - 10,
									m_iCurrentScreenY - 12, 
									"P", 0x00ffff, NULL);


	StoreLastScreenPositionForUndraw();
};

void Psyje5PlayerObject::DoUpdate(int iCurrentTime) {

	// Allow some control over the object by the player
	if (m_pMainEngine->IsKeyPressed(SDLK_w))	// UP
		m_iDir = 0;
	if (m_pMainEngine->IsKeyPressed(SDLK_d))	// RIGHT
		m_iDir = 1;
	if (m_pMainEngine->IsKeyPressed(SDLK_s))	// DOWN
		m_iDir = 2;
	if (m_pMainEngine->IsKeyPressed(SDLK_a))	// LEFT
		m_iDir = 3;
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;

	if (m_oMover.HasMovementFinished(iCurrentTime))
	{
		Psyje5TileMan& tm = m_pMainEngine->GetTileManager();

		if (tm.GetValue(m_iMapX, m_iMapY) != 7) {
			tm.UpdateTile(m_pMainEngine, m_iMapX, m_iMapY, 7);
			m_pMainEngine->TileUpdate(1);
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
				iCurrentTime + 600);
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