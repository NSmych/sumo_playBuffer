#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"

int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int DISPLAY_SCALE = 1;

enum Colors {
    RED = 0,
    YELLOW,
    BLUE,
    GREEN
};

struct GameState {
	int score = 0;
    Colors colors = RED;
};

GameState gameState;

void HandlePlayerControls();
void UpdateSqrs();
void UpdateCircles();

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE ) {
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();
	Play::StartAudioLoop("music");
	//Play::CreateGameObject(TYPE_AGENT8, { 115, 0 }, 50, "agent8");
    //int id_fan = Play::CreateGameObject(TYPE_FAN, { 1140, 217 }, 0, "fan");
    //Play::GetGameObject(id_fan).velocity = { 0, 3 };
    //Play::GetGameObject(id_fan).animSpeed = 1.0f;
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime ) {
    Play::ClearDrawingBuffer(Play::cBlack);
    UpdateSqrs();
    UpdateCircles();
    Play::DrawFontText("64px", "REMEMBER THE COLOURS ORDER. REPEAT THE SEQUENCE BY CLICKING ON THE SQUARES",
        { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 30 }, Play::CENTRE);
    Play::DrawFontText("132px", "SCORE: " + std::to_string(gameState.score),
        { DISPLAY_WIDTH / 2, 50 }, Play::CENTRE);
	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

void HandlePlayerControls() {
    if (Play::GetMouseButton(Play::LEFT)) {
        Point2D mousePos = Play::GetMousePos();
    }
    if (Play::KeyPressed(VK_SPACE)) {
    //RESTART GAME
    }
}

// Gets called once when the player quits the game
int MainGameExit( void ) {
	Play::DestroyManager();
	return PLAY_OK;
}

Point2D getBottomRight(Point2D topLeft, int length) {
    return { topLeft.x + length, topLeft.y + length };
}

void UpdateSqrs() {
    int margin = 10;
    int h = 200;
    Point2D mid = { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 };
    
    Point2D red = {mid.x - margin - h, mid.y - margin - h};
    Point2D yellow = { mid.x + margin, mid.y - margin - h };
    Point2D blue = { mid.x - margin - h, mid.y + margin };
    Point2D green = { mid.x + margin, mid.y + margin };
    
    Play::DrawRect(red, getBottomRight(red, h), Play::cRed, true);
    Play::DrawRect(yellow, getBottomRight(yellow, h), Play::cYellow, true);
    Play::DrawRect(blue, getBottomRight(blue, h), Play::cBlue, true);
    Play::DrawRect(green, getBottomRight(green, h), Play::cGreen, true);
}

void UpdateCircles() {

}
