#include "RTSBestFirstSearchMapGridWalker.h"

#include "RTSTiledMap.h"
#include "RTSMapTileNode.h"
#include "RTSTexture.h"

RTSBestFirstSearchMapGridWalker::RTSBestFirstSearchMapGridWalker(void) :
  RTSMapGridWalker::RTSMapGridWalker() {
  m_N = ge_new<RTSMapTileNode>();
  m_Start = ge_new<RTSMapTileNode>();
  m_End = ge_new<RTSMapTileNode>();
  m_N = nullptr;
  //m_TileGrid.clear();
  m_TileGrid = nullptr;
  m_Node = ge_new<RTSTexture>();
  setStartPosition(0, 0);
  setEndPosition(0, 0);
}

RTSBestFirstSearchMapGridWalker::RTSBestFirstSearchMapGridWalker(RTSTiledMap* pMap) :
  RTSMapGridWalker::RTSMapGridWalker(pMap) {
  m_N = nullptr;
  //m_TileGrid.clear();
  m_TileGrid = nullptr;
  m_Node = ge_new<RTSTexture>();
  setStartPosition(0, 0);
  setEndPosition(0, 0);
}

RTSBestFirstSearchMapGridWalker::~RTSBestFirstSearchMapGridWalker() {
  destroy();
}

bool RTSBestFirstSearchMapGridWalker::init(sf::RenderTarget* target) {
  if(/*m_TileGrid.size() > 0*/m_TileGrid)
  {
    destroy();
  }
  //m_TileGrid.resize(mapSize);
  m_TileGrid = new RTSMapTileNode*[m_pTiledMap->getMapSize().x];
  for(int32 i = 0; i < m_pTiledMap->getMapSize().x; i++)
  {
    m_TileGrid[i] = new RTSMapTileNode[m_pTiledMap->getMapSize().y];
    for(int32 j = 0; j < m_pTiledMap->getMapSize().y; j++)
    {
      //m_TileGrid[i + m_pTiledMap->getMapSize().y * j] = ge_new<RTSMapTileNode>();
      //m_TileGrid[i + m_pTiledMap->getMapSize().y * j]->setVisited(false);
      //m_TileGrid[i + m_pTiledMap->getMapSize().y * j]->m_x = i;
      //m_TileGrid[i + m_pTiledMap->getMapSize().y * j]->m_y = j;
      m_TileGrid[i][j].setVisited(false);
      m_TileGrid[i][j].m_x = i;
      m_TileGrid[i][j].m_y = j;
      m_TileGrid[i][j].setCost(m_pTiledMap->getCost(i, j));
    }
  }
  m_Node->loadFromFile(target, "Textures/Node/circle.png");
  m_Node->setOrigin(m_Node->getWidth() / 2.0f, m_Node->getHeight() / 2.0f);
  return true;
}

void RTSBestFirstSearchMapGridWalker::destroy() {
  if(m_Open.size() > 0)
  {
    m_Open.clear();
  }
  if(m_Visited.size() > 0)
  {
    m_Visited.clear();
  }
  //if(m_TileGrid.size() > 0)
  //{
  //  for(int32 i = 0; i < m_TileGrid.size(); i++)
  //  {
  //    ge_delete<RTSMapTileNode>(m_TileGrid[i]);
  //  }
  //  m_TileGrid.clear();
  //}
  if(m_TileGrid)
  {
    int32 mapaSize = m_pTiledMap->getMapSize().x*m_pTiledMap->getMapSize().y;
    for(int32 i = 0; i < mapaSize; i++)
    {
      ge_delete(m_TileGrid[i]);
    }
    ge_delete(m_TileGrid);
  }
  ge_delete(m_N);
  ge_delete(m_Start);
  ge_delete(m_End);
  ge_delete(m_Node);
  m_N = nullptr;
}

void RTSBestFirstSearchMapGridWalker::render() {
  int32 _x;
  int32 _y;
  for(int32 i = 0; i < m_Visited.size(); i++)
  {
    m_pTiledMap->getMapToScreenCoords(m_Visited[i]->m_x, m_Visited[i]->m_y, _x, _y);
    m_Node->setPosition(_x + TILESIZE_X / 2, _y + TILESIZE_Y / 2);
    m_Node->setScale(0.025f, 0.025f);
    m_Node->draw();
  }
}

WALK_STATE::E RTSBestFirstSearchMapGridWalker::update() {
  if(m_Open.size() > 0)
  {
    m_N = m_Open.front();
    m_Open.pop_front();
    m_N->setVisited(true);
    m_Visited.push_back(m_N);
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

void RTSBestFirstSearchMapGridWalker::visitGridNode(int32 x, int32 y)
{
  //if((m_pTiledMap->getCost(x, y) != 3000 && !m_TileGrid[x + m_pTiledMap->getMapSize().y * y]->getVisited()) &&
  //   !m_TileGrid[x + m_pTiledMap->getMapSize().y * y]->m_parent)
  //{
  //  m_Open.push_front(m_TileGrid[x + m_pTiledMap->getMapSize().y * y]);
  //  m_TileGrid[x + m_pTiledMap->getMapSize().y * y]->m_parent = m_N;
  //  m_Open.unique();
  //}
  if((m_pTiledMap->getCost(x, y) != 3 && !m_TileGrid[x][y].getVisited()) &&
     !m_TileGrid[x][y].m_parent)
  {
    priorityQueue(x, y);
  }
}

void RTSBestFirstSearchMapGridWalker::priorityQueue(int32 x, int32 y)
{
  Vector2I node = Vector2I(x, y);
  Vector2I end = Vector2I(m_End->m_x, m_End->m_y);
  uint32 distance = node.manhattanDist(end);
  for(auto it = m_Open.begin(); it != m_Open.end(); it++)
  {
    if((*it)->m_x == x && (*it)->m_y == y)
    {
      return;
    }
    node.x = (*it)->m_x;
    node.y = (*it)->m_y;
    if(distance < node.manhattanDist(end))
    {
      m_Open.insert(it, &m_TileGrid[x][y]);
      m_TileGrid[x][y].m_parent = m_N;
      m_Open.unique();
      return;
    }
  }
  m_Open.push_back(&m_TileGrid[x][y]);
  m_TileGrid[x][y].m_parent = m_N;
  m_Open.unique();
}

void RTSBestFirstSearchMapGridWalker::reset()
{
  if(m_Open.size() > 0)
  {
    m_Open.clear();
  }
  if(m_Visited.size() > 0)
  {
    m_Visited.clear();
  }

  m_N = nullptr;

  //int32 mapSize = m_pTiledMap->getMapSize().x * m_pTiledMap->getMapSize().y;
  //m_TileGrid.resize(mapSize);
  for(int32 i = 0; i < m_pTiledMap->getMapSize().x; i++)
  {
    for(int32 j = 0; j < m_pTiledMap->getMapSize().y; j++)
    {
      m_TileGrid[i][j].setVisited(false);
    }
  }

  int32 x, y;
  getStartPosition(x, y);
  //m_Start = m_TileGrid[x + m_pTiledMap->getMapSize().y * y];
  m_Start = &m_TileGrid[x][y];
  m_Start->setVisited(true);

  getEndPosition(x, y);
  //m_End = m_TileGrid[x + m_pTiledMap->getMapSize().y * y];
  m_End = &m_TileGrid[x][y];

  m_Open.push_front(m_Start);
}
