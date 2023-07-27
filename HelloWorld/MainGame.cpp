#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"

int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int DISPLAY_SCALE = 1;
const int ARRAY_SIZE = 10;
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
    int curr = 0;
    int arr[ARRAY_SIZE];
    int pressed = 0;
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
bool CheckOnPress();

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE ) {
    SetSequence(gameState.arr, ARRAY_SIZE);
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::StartAudioLoop("music");
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate(float elapsedTime) {
    Play::ClearDrawingBuffer(Play::cBlack);
    CreateSqrs();
    CheckOnPress();
    Play::DrawFontText("64px", "TRY TO GUESS THE SEQUENCE. REPEAT IT BY CLICKING ON THE SQUARES",
        { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 60 }, Play::CENTRE);
    if (gameState.curr == ARRAY_SIZE) {
        Play::DrawFontText("132px", "YOU DID IT!!!",
            { DISPLAY_WIDTH / 2, 30 }, Play::CENTRE);
    } else {
        Play::DrawFontText("132px", "SCORE: " + std::to_string(gameState.score),
        { DISPLAY_WIDTH / 2, 30 }, Play::CENTRE);
    }
    HandlePlayerControls();
	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// I guess that we can assign our 4 squares to sprites and after check if the sprite was clicked or not
void HandlePlayerControls() {
    if (Play::KeyPressed( VK_LBUTTON )) {
        gameState.curr++;
        Point2D mousePos = Play::GetMousePos();
        if (mousePos.x >= sqrR.tl.x && mousePos.x <= sqrR.br.x && mousePos.y >= sqrR.tl.y && mousePos.y <= sqrR.br.y) {
            //red
            gameState.pressed = 0;
            //Play::DrawDebugText({ 100,100 }, "RED", Play::cWhite, true);
        }
        else if (mousePos.x >= sqrY.tl.x && mousePos.x <= sqrY.br.x && mousePos.y >= sqrY.tl.y && mousePos.y <= sqrY.br.y) {
            //yellow
            gameState.pressed = 1;
            //Play::DrawDebugText({ 100,100 }, "YELLOW", Play::cWhite, true);
        }
        else if (mousePos.x >= sqrB.tl.x && mousePos.x <= sqrB.br.x && mousePos.y >= sqrB.tl.y && mousePos.y <= sqrB.br.y) {
            //blue
            gameState.pressed = 2;
            //Play::DrawDebugText({ 100,100 }, "BLUE", Play::cWhite, true);
        }
        else if (mousePos.x >= sqrG.tl.x && mousePos.x <= sqrG.br.x && mousePos.y >= sqrG.tl.y && mousePos.y <= sqrG.br.y) {
            //green
            gameState.pressed = 3;
            //Play::DrawDebugText({ 100,100 }, "GREEN", Play::cWhite, true);
        }
        if (CheckOnPress()) {
            gameState.score++;
        } else {
            gameState.score = 0;
            gameState.curr = 0;
        }
    }
    if (Play::KeyPressed( VK_SPACE )) {
        //ShowSeq();
        gameState.score = 888;
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

bool CheckOnPress() {
    if (gameState.arr[gameState.curr] == gameState.pressed) {
        return true;
    }
    else {
        return false;
    }
}
