#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"

int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int DISPLAY_SCALE = 1;
const int ARRAY_SIZE = 30;
int H = 200;
int MARGIN = 10;
Point2D S_MID = { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 + 25 };

enum Colors {
    RED = 0,
    YELLOW,
    BLUE,
    GREEN
};

struct GameState {
	int score = 0;
    Colors colors = RED;
    int max = 4;
};
GameState gameState;

struct Sqr {
    Point2D tl = { S_MID.x - MARGIN - H, S_MID.y - MARGIN - H };
    Point2D br = { tl.x + H, tl.y + H };
    Play::Colour pix = Play::cRed;
    bool fill = true;
};
Sqr sqrR, sqrY, sqrB, sqrG;

void modifyStructValues(Sqr& s, Point2D topLeft, Play::Colour c, bool fillWithColor) {
    s.tl = topLeft;
    s.br = { topLeft.x + H, topLeft.y + H };
    s.pix = c;
    s.fill = fillWithColor;
}

void SetSequence();
void HandlePlayerControls();
void SetSequence(int arr[], int size);
void CreateSqrs();
//void UpdateSqrs();

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE ) {
    int arr[ARRAY_SIZE];
    SetSequence(arr, ARRAY_SIZE);
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::StartAudioLoop("music");
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime ) {
    Play::ClearDrawingBuffer(Play::cBlack);
    CreateSqrs();
    Play::DrawFontText("64px", "REMEMBER THE COLOURS ORDER. REPEAT THE SEQUENCE BY CLICKING ON THE SQUARES",
        { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 60 }, Play::CENTRE);
    Play::DrawFontText("132px", "SCORE: " + std::to_string(gameState.score),
        { DISPLAY_WIDTH / 2, 30 }, Play::CENTRE);
    HandlePlayerControls();
	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

void HandlePlayerControls() {
    if (Play::KeyPressed( VK_LBUTTON )) {
        Point2D mousePos = Play::GetMousePos();
        gameState.score++;
    }
    if (Play::KeyPressed(VK_SPACE)) {
        gameState.score = 0;
    }
}

// Gets called once when the player quits the game
int MainGameExit( void ) {
	Play::DestroyManager();
	return PLAY_OK;
}

void SetSequence(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = Play::RandomRollRange(0, 3);
    }
}

void CreateSqrs() {
    Point2D redP = { S_MID.x - MARGIN - H, S_MID.y - MARGIN - H };
    Point2D yellowP = { S_MID.x + MARGIN, S_MID.y - MARGIN - H };
    Point2D blueP = { S_MID.x - MARGIN - H, S_MID.y + MARGIN };
    Point2D greenP = { S_MID.x + MARGIN, S_MID.y + MARGIN };

    modifyStructValues(sqrR, redP, Play::cRed, true);
    modifyStructValues(sqrY, yellowP, Play::cYellow, true);
    modifyStructValues(sqrB, blueP, Play::cBlue, true);
    modifyStructValues(sqrG, greenP, Play::cGreen, true);

    Play::DrawRect(sqrR.tl, sqrR.br, sqrR.pix, sqrR.fill);
    Play::DrawRect(sqrY.tl, sqrY.br, sqrY.pix, sqrY.fill);
    Play::DrawRect(sqrB.tl, sqrB.br, sqrB.pix, sqrB.fill);
    Play::DrawRect(sqrG.tl, sqrG.br, sqrG.pix, sqrG.fill);
}


