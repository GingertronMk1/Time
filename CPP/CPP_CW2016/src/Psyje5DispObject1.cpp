#include "header.h"
#include "templates.h"
#include "Psyje5DispObject1.h"


Psyje5DispObject1::Psyje5DispObject1(BaseEngine* pEngine)
	: DisplayableObject(pEngine)
{
	m_iCurrentScreenX = m_iPreviousScreenX = 100;
	m_iCurrentScreenY = m_iPreviousScreenY = 100;
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	m_iDrawHeight = 50;
	m_iDrawWidth = 100;
	SetVisible(true);
}


Psyje5DispObject1::~Psyje5DispObject1()
{
}


void Psyje5DispObject1::Draw()
{
	for (int scale = 0; scale < m_iDrawWidth; scale += 5){
		GetEngine()->DrawScreenRectangle(
			m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth - (scale + 1),
			m_iCurrentScreenY + m_iDrawHeight - 1,
			0x000100 * scale
			);
	}
	StoreLastScreenPositionForUndraw();
}


void Psyje5DispObject1::DoUpdate(int iCurrentTime)
{
	// Moving the object about
	if (GetEngine()->IsKeyPressed(SDLK_UP))
		m_iCurrentScreenY -= 2;
	if (GetEngine()->IsKeyPressed(SDLK_DOWN))
		m_iCurrentScreenY += 2;
	if (GetEngine()->IsKeyPressed(SDLK_LEFT))
		m_iCurrentScreenX -= 2;
	if (GetEngine()->IsKeyPressed(SDLK_RIGHT))
		m_iCurrentScreenX += 2;

	// Making sure it doesn't fall off the edges
	// Starting side to side
	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= GetEngine()->GetScreenWidth() - m_iDrawWidth)
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - m_iDrawWidth;
	//Now top and bottom
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	if (m_iCurrentScreenY >= GetEngine()->GetScreenHeight() - m_iDrawHeight)
		m_iCurrentScreenY = GetEngine()->GetScreenHeight() - m_iDrawHeight;


	RedrawObjects();
}
