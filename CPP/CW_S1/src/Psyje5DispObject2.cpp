#include "header.h"
#include "templates.h"
#include "Psyje5DispObject2.h"


Psyje5DispObject2::Psyje5DispObject2(BaseEngine* pEngine)
	: DisplayableObject(pEngine)
{
	m_iCurrentScreenX = m_iPreviousScreenX = 200;
	m_iCurrentScreenY = m_iPreviousScreenY = 200;
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	m_iDrawHeight = 100;
	m_iDrawWidth = 50;
	SetVisible(true);
	m_iDirectionUp = 1;
	m_iDirectionLeft = 1;
}


Psyje5DispObject2::~Psyje5DispObject2()
{
}


void Psyje5DispObject2::Draw()
{
	for (int scale = 0; scale < m_iDrawWidth; scale+=10){
		GetEngine()->DrawScreenTriangle(
			m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth - 1,
			m_iCurrentScreenY + m_iDrawHeight - 1,
			m_iCurrentScreenX + m_iDrawWidth - (scale + 1),
			m_iCurrentScreenY + m_iDrawHeight - 1,
			0x010000 * scale
			);
	}
	StoreLastScreenPositionForUndraw();
}


void Psyje5DispObject2::DoUpdate(int iCurrentTime)
{
	// Moving the object about
	if (m_iDirectionUp) {
		m_iCurrentScreenY -= GetEngine()->GetScreenHeight()/200;
	} else {
		m_iCurrentScreenY += GetEngine()->GetScreenHeight()/200;
	}
	if (m_iDirectionLeft) {
		m_iCurrentScreenX -= GetEngine()->GetScreenWidth()/200;
	} else {
		m_iCurrentScreenX += GetEngine()->GetScreenWidth()/200;
	}

	// Making sure it doesn't fall off the edges
	// Starting side to side
	if (m_iCurrentScreenX < 0) {		// Falling off the left
		m_iCurrentScreenX = 0;
		m_iDirectionLeft = 0;
	}
	if (m_iCurrentScreenX >= GetEngine()->GetScreenWidth() - m_iDrawWidth) {	// Falling off the right
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - m_iDrawWidth;
		m_iDirectionLeft = 1;

	}
	//Now top and bottom
	if (m_iCurrentScreenY < 0) {
		m_iCurrentScreenY = 0;
		m_iDirectionUp = 0;
	}
	if (m_iCurrentScreenY >= GetEngine()->GetScreenHeight() - m_iDrawHeight) {
		m_iCurrentScreenY = GetEngine()->GetScreenHeight() - m_iDrawHeight;
		m_iDirectionUp = 1;
	}


	RedrawObjects();
}
