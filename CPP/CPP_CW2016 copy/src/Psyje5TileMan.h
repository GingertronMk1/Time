#pragma once

#include "TileManager.h"

class Psyje5TileMan :
	public TileManager
{
public:
	Psyje5TileMan(void);
	~Psyje5TileMan(void);

	void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;
};

