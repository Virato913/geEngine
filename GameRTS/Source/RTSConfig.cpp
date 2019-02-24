#include "RTSConfig.h"

Vector2I GameOptions::s_Resolution = Vector2I(1920, 1080);
Vector2 GameOptions::s_MapMovementSpeed = Vector2(1024.0f, 1024.0f);

bool GameOptions::s_MapShowGrid = true;
Color GameOptions::s_MapGridColor = Color(255, 0, 0, 255);

bool GameOptions::s_Editor = false;
bool GameOptions::s_PathFinder = false;
bool GameOptions::s_ReachedGoal = false;
int32 GameOptions::s_Terrain = -1;
int32 GameOptions::s_PathState = 1;
int32 GameOptions::s_Walker = 1;
int32 GameOptions::s_BrushSize = 1;

const Vector2I
GameOptions::TILEHALFSIZE = Vector2I(TILESIZE_X >> 1, TILESIZE_Y >> 1);

const Vector2I
GameOptions::BITSHFT_TILESIZE = Vector2I(
  Math::countTrailingZeros(TILESIZE_X),
  Math::countTrailingZeros(TILESIZE_Y)
);

const Vector2I
GameOptions::BITSFHT_TILEHALFSIZE = Vector2I(GameOptions::BITSHFT_TILESIZE.x - 1,
                                             GameOptions::BITSHFT_TILESIZE.y - 1);

GameOptions&
g_gameOptions() {
  return GameOptions::instance();
}