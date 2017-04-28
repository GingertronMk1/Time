#include "header.h"
#include "BaseEngine.h"
#include "Psyje5Object.h"
#include "Psyje5Main.h"
#include "JPGImage.h"
#include "TileManager.h"


Psyje5Main::Psyje5Main(void)
	: BaseEngine(50)
	, m_state(stateInit)
{
}


Psyje5Main::~Psyje5Main()
{
}

void Psyje5Main::SetupBackgroundBuffer() {
	switch (m_state) {
		case stateInit:
			FillBackground(0xffff00);
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
			int xVal = 15;
			int yVal = 11;
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
			FillBackground(0);
			m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 14, 10);
			break;

		case statePaused:
			FillBackground(0);
			m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 14, 10);
			break;
	}
}


int Psyje5Main::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	int i_NumberOfObjects = 2;

	// Creates an array one element larger than the number of objects that you want.
	CreateObjectArray(i_NumberOfObjects + 1);

	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	for (int i = 0; i < i_NumberOfObjects; i++){
		StoreObjectInArray(i, new Psyje5Object(this, i, i));
	}

	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
	StoreObjectInArray(i_NumberOfObjects, NULL);

	// NOTE: We also need to destroy the objects, but the method at the 
	// top of this function will destroy all objects pointed at by the 
	// array elements so we can ignore that here.

	return 0;
}

void Psyje5Main::DrawStrings() {
	switch (m_state) {
	case stateInit:	
		CopyBackgroundPixels(0, 280, GetScreenWidth(), 40);
		DrawScreenString(100, 300, "Waiting for Space key", 0x0, NULL);
		break;

	case stateMain:
		CopyBackgroundPixels(0, 0, GetScreenWidth(), 30);
		DrawScreenString(250, 10, "Running", 0xffffff, NULL);
		break;

	case statePaused:
		CopyBackgroundPixels(0, 280, GetScreenWidth(), 40);
		DrawScreenString(200, 300, "Paused. Space continues", 0xffffff, NULL);
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
	}
}

void Psyje5Main::MouseDown(int iButton, int iX, int iY){
}

void Psyje5Main::KeyDown(int iKeyCode) {
	switch (iKeyCode){
	case SDLK_ESCAPE:	// quit
		SetExitWithCode(0);
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
