#include "header.h"
#include "templates.h"
#include "Psyje5TileMan.h"


Psyje5TileMan::Psyje5TileMan()
	: TileManager(60, 60)
{
}


Psyje5TileMan::~Psyje5TileMan()
{
}

void Psyje5TileMan::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	// Base class implementation just draws some grey tiles
	unsigned int iColour = 0x010000 * ((iMapX + iMapY + GetValue(iMapX, iMapY)) % 256);
	pEngine->DrawRectangle(
		iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileHeight() - 1,
		iColour,
		pSurface);
}
