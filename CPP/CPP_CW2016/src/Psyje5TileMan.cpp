#include "header.h"
#include "Psyje5TileMan.h"


Psyje5TileMan::Psyje5TileMan(void)
	: TileManager(50,50)
{
}


Psyje5TileMan::~Psyje5TileMan()
{
}


void Psyje5TileMan::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const {
	switch (GetValue(iMapX, iMapY)) {
	case 0:
	case 1:
		pEngine->DrawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			pEngine->GetColour(GetValue(iMapX, iMapY)),
			pSurface);
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		pEngine->DrawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			pEngine->GetColour(0),
			pSurface);
		/*
		pEngine->DrawOval(
			iStartPositionScreenX + GetValue(iMapX, iMapY) * 2 + 5,
			iStartPositionScreenY + GetValue(iMapX, iMapY) * 2 + 5,
			iStartPositionScreenX + GetTileWidth() - GetValue(iMapX, iMapY) * 2 - 6,
			iStartPositionScreenY + GetTileHeight() - GetValue(iMapX, iMapY) * 2 - 6,
			pEngine->GetColour(GetValue(iMapX, iMapY)),
			pSurface);
			*/
		break;
	}
}