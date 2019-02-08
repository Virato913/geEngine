#pragma once

#include "gePrerequisitesUtil.h"
#include "RTSMapGridWalker.h"
#include "RTSTiledMap.h"

using namespace geEngineSDK;

class RTSTexture;

class RTSBreadthFirstSearchMapGridWalker : public RTSMapGridWalker
{
 public:
  RTSBreadthFirstSearchMapGridWalker(void);
  RTSBreadthFirstSearchMapGridWalker(RTSTiledMap* pMap);
  virtual ~RTSBreadthFirstSearchMapGridWalker(void);

  virtual bool init();
  virtual void destroy();
  virtual WALK_STATE::E update();
  virtual void render();
  virtual void reset();
  virtual bool weightedGraphSupported() { return false; }

 protected:
  virtual void visitGridNode(int32 x, int32 y);

 private:
  queue<RTSTiledMap::MapTile*> m_Open;
  RTSTiledMap::MapTile* m_Start;
  RTSTiledMap::MapTile* m_N;
  RTSTiledMap::MapTile* m_End;
  RTSTiledMap::MapTile** m_TileGrid;
};
