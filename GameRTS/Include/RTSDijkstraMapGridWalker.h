#pragma once

#include "gePrerequisitesUtil.h"
#include "RTSMapGridWalker.h"

#include <SFML/Graphics.hpp>

using namespace geEngineSDK;
using namespace WALK_STATE;

//class RTSTiledMap;
class RTSMapTileNode;
class RTSTexture;

class RTSDijkstraMapGridWalker : public RTSMapGridWalker
{
public:
  RTSDijkstraMapGridWalker(void);
  RTSDijkstraMapGridWalker(RTSTiledMap* pMap);
  virtual ~RTSDijkstraMapGridWalker(void);

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
  int32 visitAdjacent(int32 _x, int32 _y, int32 x, int32 y);
  void reparentNode(RTSMapTileNode* n, RTSMapTileNode* parent);
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
  sf::Font* m_arialFont;
  sf::Text* m_costText;
};
