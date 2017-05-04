#include "header.h"
#include "BaseEngine.h"
#include "Psyje5Object.h"
#include "Psyje5EnemyObject.h"
#include "Psyje5PlayerObject.h"
#include "Psyje5FriendObject.h"
#include "Psyje5Main.h"
#include "JPGImage.h"
#include "TileManager.h"

#define BLACK 0
#define WHITE 0xffffff
#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff


Psyje5Main::Psyje5Main(void)
	: BaseEngine(50)
	, m_state(stateInit)
	, m_iHiScore(0)
	, m_iScore(0)
	, m_iTilesDone(0)
	, m_Level(1)
	, m_bInsideDraw(false)
{
}


Psyje5Main::~Psyje5Main()
{
}

void Psyje5Main::SetupBackgroundBuffer() {
	int xVal = 15;
	int yVal = 11;

	int rectWidth = GetScreenWidth() / xVal;
	int rectHeight = this->GetScreenHeight() / yVal;
	ImageData im;

	switch (m_state) {
	case stateInit:
		FillBackground(GREEN);
		//DrawBackgroundSquares(RED, BLUE);
		im.LoadImage("splash.jpg");
		im.RenderImageWithMask(this->GetBackground(), 0, 0, 0, 0, im.GetWidth(), im.GetHeight());
		{
			char* data[] =
			{

				"bbbbbbbbbbbbbbb",
				"baaaaaaaaaaaaab",
				"bababababababab",
				"baaaaaaaaaaaaab",
				"bababababababab",
				"baaaaaaaaaaaaab",
				"bababababababab",
				"baaaaaaaaaaaaab",
				"bababababababab",
				"baaaaaaaaaaaaab",
				"bbbbbbbbbbbbbbb"
			};
			m_oTiles.SetSize(xVal, yVal);
			
			for (int x = 0; x < xVal; x++)
				for (int y = 0; y < yVal; y++)
					m_oTiles.SetValue(x, y, data[y][x] - 'a');

			for (int y = 0; y < yVal; y++) {
				for (int x = 0; x < xVal; x++)
					printf("%d", m_oTiles.GetValue(x, y));
				printf("\n");
			}

			m_oTiles.SetBaseTilesPositionOnScreen(25, 40);
		}
		return;

		case stateMain:
			FillBackground(BLACK);
			DrawBackgroundSquares(RED, BLACK);
			// Tile based stuff
			m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 14, 10);
			
			break;
			
		case statePaused:
			DrawBackgroundSquares(BLUE, BLACK);
			Redraw(true);
			m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 14, 10);
			break;
		case stateFailed:
			FillBackground(RED);
			DrawBackgroundSquares(BLACK, RED);
			break;
		case stateWon:
			// Draw an image loaded from a file.
			// Load the image file into an image object - at the normal size
			// Create a second image from the first, by halving the size
			//im.ShrinkFrom(&im2, 2);

			// Note: image loaded only once, above, and now we will draw it nine times
			// Also note: don't try to use the 'WithMask' version with a jpg - the mask needs a solid colour
			/*
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					im.RenderImageWithMask(this->GetBackground(),
					0, 0,
					i * 100, j * 100 + 300,
					im.GetWidth(), im.GetHeight());
			*/
			FillBackground(RED);
			DrawBackgroundSquares(BLACK, RED);
			Redraw(true);
			/**/
			break;
	}
}


int Psyje5Main::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	int i_ComputerObjects = 1;			// UPDATE THIS ONE TO INCREASE/DECREASE HOW MANY COMPUTER OBJECTS THERE ARE

	i_ComputerObjects += 2;				// For the array

	
	CreateObjectArray(i_ComputerObjects);		// Make an array to put our objects in (it's 2 larger than the number of computer objects so we can have the player object and the NULL at the end
	StoreObjectInArray(0, new Psyje5PlayerObject(this, 1, 1));	// The first object is the player
	StoreObjectInArray(1, new Psyje5FriendObject(this, 13, 9));
	for (int i = 2; i <= i_ComputerObjects; i++){				// The remainder (bar 1) are the 'AI' objects
		int compX = (rand() % 13) + 1;		// random no between 1 and 13
		int compY = (rand() % 9) + 1;		// random no between 1 and 9
		if (compX % 2 == 0 && compX % 2 == 0)
			compY += 1;
		
		printf("Computer object %d starts at %d, %d\n", i - 1, compX, compY);
		StoreObjectInArray(i, new Psyje5EnemyObject(this, compX, compY));
	}
	StoreObjectInArray(i_ComputerObjects, NULL);				// The last one is a NULL pointer so we know where the array ends

	return 0;
}

void Psyje5Main::DrawStrings() {
	char buf[128];
	switch (m_state) {
	case stateInit:	
		/*
		CopyBackgroundPixels(0, 0, GetScreenWidth(), GetScreenHeight());
		DrawScreenString(100, 200, "You are red.", BLACK, NULL);
		DrawScreenString(100, 240, "Avoid Blue for as long as you can.", BLACK, NULL);
		DrawScreenString(100, 280, "Green boosts your score.", BLACK, NULL);
		DrawScreenString(100, 320, "Space begins the game.", BLACK, NULL);
		*/
		break;

	case stateMain:
		DrawGameInfo(CurrentState());
		break;

	case statePaused:
		DrawGameInfo(CurrentState());
		DrawScreenString(200, 10, buf, WHITE, NULL);
		DrawScreenString(100, 300, "Paused. SPACE continues, ESC quits.", WHITE, NULL);
		break;

	case stateFailed:
		DrawGameInfo(CurrentState());
		DrawScreenString(100, 200, "Game Over.", WHITE, NULL);
		DrawScreenString(100, 250, "SPACE twice restarts.", WHITE, NULL);
		DrawScreenString(100, 300, "ESC exits.", WHITE, NULL);
		DestroyOldObjects();
		break;
	case stateWon:
		DrawGameInfo(CurrentState());
		DrawScreenString(100, 250, "SPACE twice for next level.", WHITE, NULL);
		DrawScreenString(100, 300, "ESC exits.", WHITE, NULL);
		DestroyOldObjects();
		break;
	}
}

void Psyje5Main::GameAction() {
	if (!IsTimeToAct())
		return;

	SetTimeToAct(1);
	switch (m_state){
	case stateInit:
	case stateFailed:
	case stateWon:
	case statePaused: break;
	case stateMain: UpdateAllObjects(GetModifiedTime()); break;
	}
}

void Psyje5Main::MouseDown(int iButton, int iX, int iY){
}

void Psyje5Main::KeyDown(int iKeyCode) {
	switch (iKeyCode){
	case SDLK_ESCAPE:
		switch (m_state) {
		case stateMain: 
			break;
		case statePaused:
			m_state = stateFailed;
			SetupBackgroundBuffer();
			Redraw(true);
			break;
		case stateInit:
		case stateWon:
		case stateFailed:
			SetExitWithCode(0);
			break;
		};
		break;
	case SDLK_SPACE:
		switch (m_state){
		case stateInit:
			m_state = stateMain;
			SetupBackgroundBuffer();
			Redraw(true);
			break;
		case stateMain:
			m_state = statePaused;
			m_iPauseStarted = GetTime();
			SetupBackgroundBuffer();
			Redraw(true);
			break;
		case statePaused:
			m_state = stateMain;
			IncreaseTimeOffset(m_iPauseStarted - GetTime());
			SetupBackgroundBuffer();
			Redraw(true);
			break;
		case stateFailed:
			InitialiseObjects();
			m_state = stateInit;
			m_iScore = 0;
			if (m_iScore > m_iHiScore)
				m_iHiScore = m_iScore;
			SetupBackgroundBuffer();
			break;
		case stateWon:
			InitialiseObjects();
			m_state = stateInit;
			m_iTilesDone = 0;
			SetupBackgroundBuffer();
			m_Level++;
		}
		break;
	case SDLK_RETURN: // DEBUG GET TO NEXT LEVEL
		GameWon();
		break;
	}
}

void Psyje5Main::UndrawObjects()
{
	if (m_state != stateInit) // Not in initialise state
		BaseEngine::UndrawObjects();
}

void Psyje5Main::DrawObjects()
{
	if (m_state != stateInit) // Not in initialise state
		BaseEngine::DrawObjects();
}

void Psyje5Main::GameOver() {
	m_state = stateFailed;
	SetupBackgroundBuffer();
	Redraw(true);
}

void Psyje5Main::GameWon()
{
	m_state = stateWon;
	SetupBackgroundBuffer();
	Redraw(true);
}

void Psyje5Main::DrawBackgroundSquares(int iColour1, int iColour2)
{
	int totalWidth = GetScreenWidth();
	int totalHeight = this->GetScreenHeight();

	for (int iX = 0; iX < totalWidth; iX++) {
		for (int iY = 0; iY < totalHeight; iY += 10) {
			switch (abs(iX - iY) % 20) {
			case 0: DrawBackgroundRectangle(iX, iY, iX + 10, iY + 10, iColour1); break;
			case 10: DrawBackgroundRectangle(iX, iY, iX + 10, iY + 10, iColour2); break;
			}

		}
	}
}


int Psyje5Main::CurrentState()
{
	switch (m_state){
	case stateInit: return 0; break;
	case stateMain: return 1; break;
	case statePaused: return 2; break;
	case stateFailed: return 3; break;
	case stateWon: return 4; break;
	}
}


void Psyje5Main::ScoreUpdate(int iScoreUpdate)
{
	m_iScore += iScoreUpdate;
}


void Psyje5Main::TileUpdate(int iTaken)
{
	m_iTilesDone += iTaken;
	this->ScoreUpdate(100 * iTaken);
	if (m_iTilesDone == 93)
		GameWon();
}

void Psyje5Main::DrawGameInfo(int m_CurrentState)
{
	char buf[128];
	CopyBackgroundPixels(0, 0, GetScreenWidth(), 100);
	if (m_CurrentState == 1 || m_CurrentState == 2 || m_CurrentState == 4) {
		sprintf(buf, "Your score so far: %d", m_iScore);
		DrawScreenString(20, 10, buf, WHITE, NULL);

	}
	else if (m_CurrentState == 3) {
		sprintf(buf, "Final Score: %d", m_iScore);
		DrawScreenString(20, 10, buf, WHITE, NULL);
		sprintf(buf, "Reigning High Score: %d", m_iHiScore);
		DrawScreenString(20, 50, buf, WHITE, NULL);
		if (m_iScore > m_iHiScore) {
			DrawScreenString(20, 90, "New High Score! Well Done!", WHITE, NULL);
		}
		else {
			DrawScreenString(20, 90, "Better Luck Next Time", WHITE, NULL);
		}
	}
	sprintf(buf, "Level %d", m_Level);
	DrawScreenString(400, 10, buf, WHITE, NULL);
	sprintf(buf, "Tiles taken: %d", m_iTilesDone);
	DrawScreenString(550, 10, buf, WHITE, NULL);
}


void Psyje5Main::GameRender(void)
{
	if (!m_bNeedsRedraw)
		return;

	// Just drawn so no more redraw needed
	m_bNeedsRedraw = false;
	// Note: the redraw flags must only be set early in this method, not at the end, since the drawing/moving of the moving objects may
	// potentially flag a win/lose condition and a state change, which will set the redraw flag again to force a full draw after the 
	// state changes.

	if (m_bWholeScreenUpdate)
	{
		// Drawn whole screen now, so no need to draw it again. See note above about the importance of not resetting this after DrawChangingObjects()
		m_bWholeScreenUpdate = false;

		// Lock surface if needed
		if (SDL_MUSTLOCK(m_pActualScreen))
		{
			m_bInsideDraw = true;
			if (SDL_LockSurface(m_pActualScreen) < 0)
				return;
		}

		// Draw the screen as it should appear now.
		// First draw the background
		CopyAllBackgroundBuffer();
		// Draw the text for the user
		DrawStrings(); // Single function in case people want to use that instead
		DrawStringsUnderneath();	// Draw the string underneath the other objects here
		// Then draw the changing objects
		DrawObjects();
		// Another option for where to put the draw strings code - if you want it on top of the moving objects
		DrawStringsOnTop();

		// Unlock if needed
		if (SDL_MUSTLOCK(m_pActualScreen))
			SDL_UnlockSurface(m_pActualScreen);
		m_bInsideDraw = false;

		SDL_UpdateTexture(m_pSDL2Texture, NULL, m_pActualScreen->pixels, m_pActualScreen->pitch);
		//SDL_RenderClear( m_pSDL2Renderer );
		SDL_RenderCopy(m_pSDL2Renderer, m_pSDL2Texture, NULL, NULL);
		SDL_RenderPresent(m_pSDL2Renderer);

		//SDL_UpdateRect(m_pActualScreen, 0, 0, m_iScreenWidth, m_iScreenHeight);    
	}
	else
	{
		// Here we assume that the background buffer has already been set up

		// Lock surface if needed
		if (SDL_MUSTLOCK(m_pActualScreen))
		{
			m_bInsideDraw = true;
			if (SDL_LockSurface(m_pActualScreen) < 0)
				return;
		}

		// Remove objects from their old positions
		UndrawObjects();
		// Remove the old strings be re-drawing the background
		UnDrawStrings();

		// THIS IS THE ANIMATED BACKGROUND
		AnimatedBG(BLACK, RED);
		// THIS IS THE ANIMATED BACKGROUND


		// Draw the text for the user
		DrawStrings(); // Single function in case people want to use that instead
		DrawStringsUnderneath();	// Draw the string underneath the other objects here
		// Draw objects at their new positions
		DrawObjects();
		// Another option for where to put the draw strings code - if you want it on top of the moving objects
		DrawStringsOnTop();

		// Unlock if needed
		if (SDL_MUSTLOCK(m_pActualScreen))
			SDL_UnlockSurface(m_pActualScreen);
		m_bInsideDraw = false;

		// Copy the screen display into the window and display it
		SDL_UpdateTexture(m_pSDL2Texture, NULL, m_pActualScreen->pixels, m_pActualScreen->pitch);
		SDL_RenderCopy(m_pSDL2Renderer, m_pSDL2Texture, NULL, NULL);
		SDL_RenderPresent(m_pSDL2Renderer);
	}
}


void Psyje5Main::AnimatedBG(int iColour1, int iColour2)
{
	CopyBackgroundPixels(0, 0, this->GetScreenWidth(), this->GetScreenHeight());
	FillBackground(BLACK);
	switch ((m_iScore/100) % 2) {
	case 0: DrawBackgroundSquares(iColour1, iColour2); break;
	case 1: DrawBackgroundSquares(iColour2, iColour1); break;
	};
	// Tile based stuff
	m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 14, 10);
}
