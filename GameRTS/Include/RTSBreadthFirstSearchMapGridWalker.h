#pragma once

#include "gePrerequisitesUtil.h"
#include "RTSMapGridWalker.h"

#include <SFML/Graphics.hpp>

using namespace geEngineSDK;
using namespace WALK_STATE;

//class RTSTiledMap;
class RTSMapTileNode;
class RTSTexture;

class RTSBreadthFirstSearchMapGridWalker : public RTSMapGridWalker
{
 public:
  RTSBreadthFirstSearchMapGridWalker(void);
  RTSBreadthFirstSearchMapGridWalker(RTSTiledMap* pMap);
  virtual ~RTSBreadthFirstSearchMapGridWalker(void);

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
  template<typename T>
  bool existsInList(RTSMapTileNode* n, T list);
  void visitAdjacent(int32 _x, int32 _y, int32 x, int32 y);
  void reparentNode(RTSMapTileNode* n, RTSMapTileNode* parent);

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
