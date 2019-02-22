#pragma once

#include "gePrerequisitesUtil.h"
#include "RTSMapGridWalker.h"

using namespace geEngineSDK;
using namespace WALK_STATE;

//class RTSTiledMap;
class RTSMapTileNode;
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
  //virtual bool weightedGraphSupported() { return false; }

 protected:
  virtual void visitGridNode(int32 x, int32 y);

 private:
  Queue<RTSMapTileNode*> m_Open;
  RTSMapTileNode* m_Start;
  RTSMapTileNode* m_N;
  RTSMapTileNode* m_End;
  Vector<RTSMapTileNode*> m_TileGrid;
};
