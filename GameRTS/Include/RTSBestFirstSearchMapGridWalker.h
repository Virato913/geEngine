#pragma once

#include "gePrerequisitesUtil.h"
#include "RTSMapGridWalker.h"

#include <SFML/Graphics.hpp>

using namespace geEngineSDK;
using namespace WALK_STATE;

//class RTSTiledMap;
class RTSMapTileNode;
class RTSTexture;

class RTSBestFirstSearchMapGridWalker : public RTSMapGridWalker
{
public:
  RTSBestFirstSearchMapGridWalker(void);
  RTSBestFirstSearchMapGridWalker(RTSTiledMap* pMap);
  virtual ~RTSBestFirstSearchMapGridWalker(void);

  virtual bool init(sf::RenderTarget* target);
  virtual void destroy();
  virtual WALK_STATE::E update();
  virtual void render();
  virtual void reset();
  //virtual bool weightedGraphSupported() { return false; }
  virtual void traceback();

protected:
  virtual void visitGridNode(int32 x, int32 y);

private:
  void priorityQueue(int32 x, int32 y);

  List<RTSMapTileNode*> m_Open;
  Vector<RTSMapTileNode*> m_Visited;
  RTSMapTileNode* m_Start;
  RTSMapTileNode* m_N;
  RTSMapTileNode* m_End;
  //Vector<RTSMapTileNode*> m_TileGrid;
  RTSMapTileNode** m_TileGrid;
  RTSTexture* m_Node;

  sf::RenderTarget* m_pTarget;
  sf::VertexArray m_FastestPath;
};
