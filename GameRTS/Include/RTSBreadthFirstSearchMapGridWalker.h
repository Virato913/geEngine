#pragma once

#include "gePrerequisitesUtil.h"
#include "RTSMapGridWalker.h"

using namespace geEngineSDK;
using namespace WALK_STATE;

//class RTSTiledMap;
//class RTSMapTile;
//class RTSTexture;

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
  queue<RTSMapTile*> m_Open;
  RTSMapTile* m_Start;
  RTSMapTile* m_N;
  RTSMapTile* m_End;
  Vector<RTSMapTile> m_TileGrid;
};
