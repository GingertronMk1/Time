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
	, m_iTimer(0)
	, m_iHiScore(0)
	, m_iScore(0)
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

	switch (m_state) {
	case stateInit:
		FillBackground(GREEN);
		DrawBackgroundSquares(RED, BLUE);

			{
				char* data[] = {
					"bbbbbbbbbbbbbbb",
					"baeaeadadaeaeab",
					"babcbcbcbcbibeb",
					"badadgdadhdadhb",
					"bgbcbcbcbibcbeb",
					"badadadadadadab",
					"bfbcbibcbcbcbeb",
					"bahadadhdadadab",
					"bfbcbcbibcbibeb",
					"badadadadadadab",
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
		case stateOver:
			FillBackground(RED);
			DrawBackgroundSquares(BLACK, RED);
			break;
	}
}


int Psyje5Main::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	int i_ComputerObjects = 2;			// UPDATE THIS ONE TO INCREASE/DECREASE HOW MANY COMPUTER OBJECTS THERE ARE

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
	switch (m_state) {
	case stateInit:	
		CopyBackgroundPixels(0, 0, GetScreenWidth(), GetScreenHeight());
		DrawScreenString(100, 200, "You are red.", BLACK, NULL);
		DrawScreenString(100, 240, "Avoid Blue for as long as you can.", BLACK, NULL);
		DrawScreenString(100, 280, "Green boosts your score.", BLACK, NULL);
		DrawScreenString(100, 320, "Space begins the game.", BLACK, NULL);
		break;

	case stateMain:
		CopyBackgroundPixels(0, 0, GetScreenWidth(), 100);
		char buf[128];
		sprintf(buf, "Your score so far: %d", m_iScore);
		m_iTimer++;
		m_iScore = m_iTimer / 10;
		DrawScreenString(250, 10, buf, WHITE, NULL);
		break;

	case statePaused:
		CopyBackgroundPixels(0, 280, GetScreenWidth(), 40);
		sprintf(buf, "Your score so far: %d", m_iScore);
		DrawScreenString(250, 10, buf, WHITE, NULL);
		DrawScreenString(100, 300, "Paused. SPACE continues, ESC quits.", WHITE, NULL);
		break;

	case stateOver:
		CopyBackgroundPixels(0, 0, GetScreenWidth(), GetScreenHeight());
		sprintf(buf, "Final Score: %d", m_iScore);
		DrawScreenString(250, 10, buf, WHITE, NULL);
		sprintf(buf, "Reigning High Score: %d", m_iHiScore);
		DrawScreenString(250, 50, buf, WHITE, NULL);

		DrawScreenString(100, 200, "Game Over.", WHITE, NULL);
		DrawScreenString(100, 250, "SPACE twice restarts.", WHITE, NULL);
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
	case statePaused: break;
	case stateMain: UpdateAllObjects(GetModifiedTime()); break;
	case stateOver: break;
	}
}

void Psyje5Main::MouseDown(int iButton, int iX, int iY){
}

void Psyje5Main::KeyDown(int iKeyCode) {
	switch (iKeyCode){
	case SDLK_ESCAPE:
		switch (m_state) {
		case stateInit: 
			SetExitWithCode(0);
			break;
		case stateMain: 
			break;
		case statePaused:
			m_state = stateOver;
			SetupBackgroundBuffer();
			Redraw(true);
			break;
		case stateOver:
			SetExitWithCode(0);
			break;
		};
		break;
	case SDLK_SPACE: // pause
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
		case stateOver:
			InitialiseObjects();
			m_state = stateInit;
			if (m_iScore > m_iHiScore)
				m_iHiScore = m_iScore;
			m_iTimer = m_iScore = 0;
			SetupBackgroundBuffer();
			break;
		}
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
	m_state = stateOver;
	SetupBackgroundBuffer();
	Redraw(true);
}

void Psyje5Main::DrawBackgroundSquares(int iColour1, int iColour2)
{
	int totalWidth = GetScreenWidth();
	int totalHeight = this->GetScreenHeight();
	int movementThing = m_iTimer % totalWidth;
	printf("%d\n", movementThing);

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
	case stateOver: return 3; break;
	}
}


void Psyje5Main::ScoreUpdate(int iScoreUpdate)
{
	m_iTimer += iScoreUpdate;
}
