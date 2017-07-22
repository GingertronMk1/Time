#include "header.h"
#include "templates.h"
#include "Psyje5Engine.h"
#include "Psyje5DispObject1.h"
#include "Psyje5DispObject2.h"
#include "Psyje5TileMan.h"

Psyje5Engine::Psyje5Engine() 
	: BaseEngine(9)
{
}


Psyje5Engine::~Psyje5Engine()
{
}


void Psyje5Engine::SetupBackgroundBuffer()
{
	FillBackground(0);
	int tilesAcross = 40;
	int tilesUp = 30;
	int tileWidth = GetScreenWidth() / tilesAcross;
	int tileHeight = this->GetScreenHeight() / tilesUp;
	m_oTiles.SetSize(tilesAcross, tilesUp);
	for (int x = 0; x < tilesAcross; x++)
		for (int y = 0; y < tilesUp; y++)
			m_oTiles.SetValue(x, y, rand() % 31);

	m_oTiles.SetBaseTilesPositionOnScreen(0, 0);
	m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 14, 10);

	for (int iX = 0; iX < GetScreenWidth(); iX++) {
		for (int iY = 0; iY < this->GetScreenHeight(); iY += 10) {
			switch (iX % 20) {
			case 0: DrawBackgroundRectangle(iX, iY, iX + 5, iY + 5, 0xFFF000); break;
			case 10: DrawBackgroundRectangle(iX, iY, iX + 5, iY + 5, 0x000FFF); break;
			}
		}
	}
}


void Psyje5Engine::MouseDown(int iButton, int iX, int iY)
{
	printf("%d %d\n", iX, iY);
	if (iButton == SDL_BUTTON_LEFT) {
		DrawRectangle(iX - 10, iY - 10, iX + 10, iY + 10, 0xFF0000);
		Redraw(false);
	}
	else if (iButton == SDL_BUTTON_RIGHT) {
		Redraw(true);
	}
}


int Psyje5Engine::InitialiseObjects()
{
	DrawableObjectsChanged();	// We're going to change the array - don't use it without a reload
	DestroyOldObjects();		// Get rid of anything that's hanging around
	CreateObjectArray(3);		// Make an array that's 1 bigger than necessary
	StoreObjectInArray(0, new Psyje5DispObject1(this));
	StoreObjectInArray(1, new Psyje5DispObject2(this));
	StoreObjectInArray(2, NULL);	// This is why we made it bigger
	return 0;
}

void Psyje5Engine::DrawStrings(){

}

void Psyje5Engine::DrawStringsUnderneath()
{
	char buf[128];
	sprintf(buf, "Numbers are fun! Here's several: %d", rand()%50);
	DrawScreenString(0, 0, buf, 0x00ffff, NULL);
}


#if 1
void Psyje5Engine::UnDrawStrings()
{
	CopyBackgroundPixels(0, 0, GetScreenWidth(), 200);
}
#endif