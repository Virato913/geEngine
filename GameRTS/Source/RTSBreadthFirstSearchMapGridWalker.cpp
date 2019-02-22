#include "RTSBreadthFirstSearchMapGridWalker.h"

#include "RTSTiledMap.h"
#include "RTSMapTileNode.h"

RTSBreadthFirstSearchMapGridWalker::RTSBreadthFirstSearchMapGridWalker(void) :
  RTSMapGridWalker::RTSMapGridWalker() {
  m_N = ge_new<RTSMapTileNode>();
  m_Start = ge_new<RTSMapTileNode>();
  m_End = ge_new<RTSMapTileNode>();
  m_N = nullptr;
  m_TileGrid.clear();
  setStartPosition(0, 0);
  setEndPosition(0, 0);
}

RTSBreadthFirstSearchMapGridWalker::RTSBreadthFirstSearchMapGridWalker(RTSTiledMap* pMap) :
  RTSMapGridWalker::RTSMapGridWalker(pMap) {
  m_N = nullptr;
  m_TileGrid.clear();
  setStartPosition(0, 0);
  setEndPosition(0, 0);
}

RTSBreadthFirstSearchMapGridWalker::~RTSBreadthFirstSearchMapGridWalker() {
  destroy();
}

bool RTSBreadthFirstSearchMapGridWalker::init() {
  if(m_TileGrid.size() > 0)
  {
    destroy();
  }
  int32 mapSize = m_pTiledMap->getMapSize().x * m_pTiledMap->getMapSize().y;
  m_TileGrid.resize(mapSize);
  for(int32 i = 0; i < m_pTiledMap->getMapSize().x; i++)
  {
    for(int32 j = 0; j < m_pTiledMap->getMapSize().y; j++)
    {
      m_TileGrid[i + i * j] = ge_new<RTSMapTileNode>();
      m_TileGrid[i + i * j]->setVisited(false);
      m_TileGrid[i + i * j]->m_x = i;
      m_TileGrid[i + i * j]->m_y = j;
    }
  }
  return true;
}

void RTSBreadthFirstSearchMapGridWalker::destroy() {
  if(m_TileGrid.size() > 0)
  {
    for(int32 i = 0; i < m_TileGrid.size(); i++)
    {
      ge_delete<RTSMapTileNode>(m_TileGrid[i]);
    }
    m_TileGrid.clear();
  }
  ge_delete<RTSMapTileNode>(m_N);
  m_N = nullptr;
}

void RTSBreadthFirstSearchMapGridWalker::render() {

}

WALK_STATE::E RTSBreadthFirstSearchMapGridWalker::update() {
  if(m_Open.size() > 0)
  {
    m_N = m_Open.front();
    m_Open.pop();
    m_N->setVisited(true);
    if(m_N->Equals(*m_End))
    {
      return kReachedGoal;
    }
    Vector2I mapSize = m_pTiledMap->getMapSize();
    int32 x, y;

    x = m_N->m_x + 1;
    y = m_N->m_y;
    if(m_N->m_x < (mapSize.x - 1))
    {
      visitGridNode(x, y);
    }

    x = m_N->m_x + 1;
    y = m_N->m_y + 1;
    if(m_N->m_x < (mapSize.x - 1) && m_N->m_y < (mapSize.y - 1))
    {
      visitGridNode(x, y);
    }

    x = m_N->m_x;
    y = m_N->m_y + 1;
    if(m_N->m_y < (mapSize.y - 1))
    {
      visitGridNode(x, y);
    }

    x = m_N->m_x - 1;
    y = m_N->m_y + 1;
    if(m_N->m_x > 0 && m_N->m_y < (mapSize.y - 1))
    {
      visitGridNode(x, y);
    }

    x = m_N->m_x - 1;
    y = m_N->m_y;
    if(m_N->m_x > 0)
    {
      visitGridNode(x, y);
    }

    x = m_N->m_x - 1;
    y = m_N->m_y - 1;
    if(m_N->m_x > 0 && m_N->m_y > 0)
    {
      visitGridNode(x, y);
    }

    x = m_N->m_x;
    y = m_N->m_y - 1;
    if(m_N->m_y > 0)
    {
      visitGridNode(x, y);
    }

    x = m_N->m_x + 1;
    y = m_N->m_y - 1;
    if(m_N->m_x < (mapSize.x - 1) && m_N->m_y>0)
    {
      visitGridNode(x, y);
    }

    return kStillLooking;
  }
  return kUnableToReachGoal;
}

void RTSBreadthFirstSearchMapGridWalker::visitGridNode(int32 x, int32 y)
{
  if(m_pTiledMap->getCost(x, y) == 3000 || m_TileGrid[x + x * y]->getVisited())
  {
    return;
  }
  m_Open.push(m_TileGrid[x + x * y]);
  m_TileGrid[x + x * y]->m_parent = m_N;
}

void RTSBreadthFirstSearchMapGridWalker::reset()
{
  while(m_Open.size()>0)
  {
    m_Open.pop();
  }

  m_N = nullptr;

  int32 mapSize = m_pTiledMap->getMapSize().x * m_pTiledMap->getMapSize().y;
  m_TileGrid.resize(mapSize);
  for(int32 i = 0; i < m_pTiledMap->getMapSize().x; i++)
  {
    for(int32 j = 0; j < m_pTiledMap->getMapSize().y; j++)
    {
      m_TileGrid[i + i * j]->setVisited(false);
    }
  }

  int32 x, y;
  getStartPosition(x, y);
  m_Start = m_TileGrid[x + x * y];
  m_Start->setVisited(true);

  getEndPosition(x, y);
  m_End = m_TileGrid[x + x * y];

  m_Open.push(m_Start);
}
