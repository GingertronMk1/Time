#pragma once
#include "TileManager.h"
class Psyje5TileMan :
	public TileManager
{
public:
	Psyje5TileMan();
	~Psyje5TileMan();
	void DrawTileAt(
		BaseEngine* pEngine, 
		SDL_Surface* pSurface, 
		int iMapX, int iMapY, 
		int iStartPositionScreenX, int iStartPositionScreenY) const;
};

