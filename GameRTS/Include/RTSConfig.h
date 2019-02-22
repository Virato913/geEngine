#pragma once

//Define only if the map should be isometric
#define MAP_IS_ISOMETRIC

#ifdef MAP_IS_ISOMETRIC
//Tiles pixel size
# define TILESIZE_X 64
# define TILESIZE_Y 32
#else
//Tiles pixel size
# define TILESIZE_X 64
# define TILESIZE_Y 64
#endif

#include <geModule.h>
#include <geVector2I.h>
#include <geVector2.h>
#include <geColor.h>

using namespace geEngineSDK;

class GameOptions : public Module<GameOptions>
{
 public:
  //Application values
  static Vector2I s_Resolution;
  static Vector2 s_MapMovementSpeed;

  //World Values

  //Map Values
  static bool s_MapShowGrid;
  static Color s_MapGridColor;

  static bool s_Editor;
  static bool s_PathFinder;
  static int32 s_Terrain;
  static int32 s_PathState;

  static int32 s_BrushSize;

  //Global Constants
  static const Vector2I TILEHALFSIZE;
  static const Vector2I BITSFHT_TILEHALFSIZE;
  static const Vector2I BITSHFT_TILESIZE;
};

GameOptions&
g_gameOptions();
