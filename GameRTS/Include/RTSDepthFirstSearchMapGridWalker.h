#pragma once

#include "gePrerequisitesUtil.h"
#include "RTSMapGridWalker.h"

#include <SFML/Graphics.hpp>

using namespace geEngineSDK;
using namespace WALK_STATE;

//class RTSTiledMap;
class RTSMapTileNode;
class RTSTexture;

class RTSDepthFirstSearchMapGridWalker : public RTSMapGridWalker
{
public:
  RTSDepthFirstSearchMapGridWalker(void);
  RTSDepthFirstSearchMapGridWalker(RTSTiledMap* pMap);
  virtual ~RTSDepthFirstSearchMapGridWalker(void);

  virtual bool init(sf::RenderTarget* target);
  virtual void destroy();
  virtual WALK_STATE::E update();
  virtual void render();
  virtual void reset();
  //virtual bool weightedGraphSupported() { return false; }

protected:
  virtual void visitGridNode(int32 x, int32 y);

private:
  List<RTSMapTileNode*> m_Open;
  Vector<RTSMapTileNode*> m_Visited;
  RTSMapTileNode* m_Start;
  RTSMapTileNode* m_N;
  RTSMapTileNode* m_End;
  Vector<RTSMapTileNode*> m_TileGrid;
  RTSTexture* m_Node;
};
