#include "RTSDijkstraMapGridWalker.h"

#include "RTSTiledMap.h"
#include "RTSMapTileNode.h"
#include "RTSTexture.h"

RTSDijkstraMapGridWalker::RTSDijkstraMapGridWalker(void) :
  RTSMapGridWalker::RTSMapGridWalker() {
  m_N = ge_new<RTSMapTileNode>();
  m_Start = ge_new<RTSMapTileNode>();
  m_End = ge_new<RTSMapTileNode>();
  m_N = nullptr;
  //m_TileGrid.clear();
  m_TileGrid = nullptr;
  m_Node = ge_new<RTSTexture>();
  m_costText = ge_new<sf::Text>();
  m_arialFont = ge_new<sf::Font>();
  m_FastestPath = sf::VertexArray(sf::LineStrip);
  setStartPosition(0, 0);
  setEndPosition(0, 0);
}

RTSDijkstraMapGridWalker::RTSDijkstraMapGridWalker(RTSTiledMap* pMap) :
  RTSMapGridWalker::RTSMapGridWalker(pMap) {
  m_N = nullptr;
  //m_TileGrid.clear();
  m_TileGrid = nullptr;
  m_Node = ge_new<RTSTexture>();
  m_costText = ge_new<sf::Text>();
  m_arialFont = ge_new<sf::Font>();
  m_FastestPath = sf::VertexArray(sf::LineStrip);
  setStartPosition(0, 0);
  setEndPosition(0, 0);
}

RTSDijkstraMapGridWalker::~RTSDijkstraMapGridWalker() {
  destroy();
}

bool RTSDijkstraMapGridWalker::init(sf::RenderTarget* target) {
  m_pTarget = target;
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
      m_TileGrid[i][j].setCost(m_pTiledMap->getCost(i, j) + 1);
    }
  }
  m_Node->loadFromFile(target, "Textures/Node/circle.png");
  m_Node->setOrigin(m_Node->getWidth() / 2.0f, m_Node->getHeight() / 2.0f);
  m_arialFont->loadFromFile("Fonts/arial.ttf");
  m_costText->setFont(*m_arialFont);
  return true;
}

void RTSDijkstraMapGridWalker::destroy() {
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
    int32 mapaSize = m_pTiledMap->getMapSize().x;
    for(int32 i = 0; i < mapaSize; i++)
    {
      ge_delete(m_TileGrid[i]);
    }
    ge_delete(m_TileGrid);
  }
  m_Start = nullptr;
  m_End = nullptr;
  m_N = nullptr;
  if(m_Node)
    ge_delete(m_Node);
  if(m_costText)
    ge_delete(m_costText);
  if(m_arialFont)
    ge_delete(m_arialFont);
}

void RTSDijkstraMapGridWalker::render() {  
  int32 _x;
  int32 _y;
  for(int32 i = 0; i < m_Visited.size(); i++)
  {
    m_pTiledMap->getMapToScreenCoords(m_Visited[i]->m_x, m_Visited[i]->m_y, _x, _y);
    m_Node->setPosition(_x + TILESIZE_X / 2, _y + TILESIZE_Y / 2);
    m_Node->setScale(0.025f, 0.025f);
    m_Node->draw();
    m_costText->setPosition(_x, _y);
    m_costText->setString(toString(m_Visited[i]->m_cost).c_str());
    m_pTarget->draw(*m_costText);
  }
  m_pTarget->draw(m_FastestPath);
}

WALK_STATE::E RTSDijkstraMapGridWalker::update() {
  if(m_Open.size() > 0)
  {
    m_N = m_Open.front();
    m_Open.pop_front();
    m_N->setVisited(true);
    m_Visited.push_back(m_N);
    if(m_N->Equals(*m_End))
    {
      //return kReachedGoal;
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

void RTSDijkstraMapGridWalker::visitGridNode(int32 x, int32 y)
{
  //if((m_pTiledMap->getCost(x, y) != 3000 && !m_TileGrid[x + m_pTiledMap->getMapSize().y * y]->getVisited()) &&
  //   !m_TileGrid[x + m_pTiledMap->getMapSize().y * y]->m_parent)
  //{
  //  m_Open.push_front(m_TileGrid[x + m_pTiledMap->getMapSize().y * y]);
  //  m_TileGrid[x + m_pTiledMap->getMapSize().y * y]->m_parent = m_N;
  //  m_Open.unique();
  //}
  if((m_pTiledMap->getType(x, y) != TERRAIN_TYPE::kObstacle && !m_TileGrid[x][y].getVisited()) &&
     !m_TileGrid[x][y].m_parent)
  {
    priorityQueue(x, y);
  }
}

template<typename T>
bool RTSDijkstraMapGridWalker::existsInList(RTSMapTileNode* n, T list)
{
  for(auto it = list.begin(); it != list.end(); it++)
  {
    if(n->Equals(*(*it)))
    {
      return true;
    }
  }
  return false;
}

int32 RTSDijkstraMapGridWalker::visitAdjacent(int32 _x, int32 _y, int32 x, int32 y)
{
  if(existsInList(&m_TileGrid[x][y], m_Visited))
  {
    int32 currentCost = m_TileGrid[_x][_y].m_cost;
    int32 parentCost = m_TileGrid[_x][_y].m_parent->m_cost;
    int32 adjacentCost = m_TileGrid[x][y].m_cost;
    if(currentCost - adjacentCost > 0)
    {
      if((currentCost - adjacentCost) > (currentCost - parentCost))
      {
        return currentCost - adjacentCost;
      }
      return -1;
    }
    return -1;
  }
  return -1;
}

void RTSDijkstraMapGridWalker::reparentNode(RTSMapTileNode* n, RTSMapTileNode* parent)
{
  n->setParent(parent);
}

void RTSDijkstraMapGridWalker::traceback()
{
  m_FastestPath.clear();
  int32 tempX = 0;
  int32 tempY = 0;
  if(m_Visited.size() > 0)
  {
    RTSMapTileNode* n = m_End;
    Vector2I mapSize = m_pTiledMap->getMapSize();
    int32 x, y;
    int32 cost = 3000;
    int32 lcost = 0;
    int32 lx;
    int32 ly;
    while(n->m_parent)
    {
      lx = n->m_parent->m_x;
      ly = n->m_parent->m_y;

      x = n->m_x + 1;
      y = n->m_y;
      
      if(n->m_x < (mapSize.x - 1))
      {
        cost = visitAdjacent(n->m_x, n->m_y, x, y);
        if(cost > 0 && cost > lcost)
        {
          lcost = cost;
          lx = x;
          ly = y;
        }
      }
      
      x = n->m_x + 1;
      y = n->m_y + 1;
      if(n->m_x < (mapSize.x - 1) && n->m_y < (mapSize.y - 1))
      {
        cost = visitAdjacent(n->m_x, n->m_y, x, y);
        if(cost > 0 && cost > lcost)
        {
          lcost = cost;
          lx = x;
          ly = y;
        }
      }
      
      x = n->m_x;
      y = n->m_y + 1;
      if(n->m_y < (mapSize.y - 1))
      {
        cost = visitAdjacent(n->m_x, n->m_y, x, y);
        if(cost > 0 && cost > lcost)
        {
          lcost = cost;
          lx = x;
          ly = y;
        }
      }
      
      x = n->m_x - 1;
      y = n->m_y + 1;
      if(n->m_x > 0 && n->m_y < (mapSize.y - 1))
      {
        cost = visitAdjacent(n->m_x, n->m_y, x, y);
        if(cost > 0 && cost > lcost)
        {
          lcost = cost;
          lx = x;
          ly = y;
        }
      }
      
      x = n->m_x - 1;
      y = n->m_y;
      if(n->m_x > 0)
      {
        cost = visitAdjacent(n->m_x, n->m_y, x, y);
        if(cost > 0 && cost >> lcost)
        {
          lcost = cost;
          lx = x;
          ly = y;
        }
      }
      
      x = n->m_x - 1;
      y = n->m_y - 1;
      if(n->m_x > 0 && n->m_y > 0)
      {
        cost = visitAdjacent(n->m_x, n->m_y, x, y);
        if(cost > 0 && cost > lcost)
        {
          lcost = cost;
          lx = x;
          ly = y;
        }
      }
      
      x = n->m_x;
      y = n->m_y - 1;
      if(n->m_y > 0)
      {
        cost = visitAdjacent(n->m_x, n->m_y, x, y);
        if(cost > 0 && cost > lcost)
        {
          lcost = cost;
          lx = x;
          ly = y;
        }
      }
      
      x = n->m_x + 1;
      y = n->m_y - 1;
      if(n->m_x < (mapSize.x - 1) && n->m_y>0)
      {
        cost = visitAdjacent(n->m_x, n->m_y, x, y);
        if(cost > 0 && cost > lcost)
        {
          lcost = cost;
          lx = x;
          ly = y;
        }
      }

      m_pTiledMap->getMapToScreenCoords(n->m_x, n->m_y, tempX, tempY);
      m_FastestPath.append(sf::Vertex(sf::Vector2f(tempX + TILESIZE_X / 2, tempY + TILESIZE_Y / 2)));

      reparentNode(n, &m_TileGrid[lx][ly]);

      n = n->m_parent;
    }
    n = m_Visited.front();
    m_pTiledMap->getMapToScreenCoords(n->m_x, n->m_y, tempX, tempY);
    m_FastestPath.append(sf::Vertex(sf::Vector2f(tempX + TILESIZE_X / 2, tempY + TILESIZE_Y / 2)));
  }
}

void RTSDijkstraMapGridWalker::priorityQueue(int32 x, int32 y)
{
  for(auto it = m_Open.begin(); it != m_Open.end(); it++)
  {
    if((*it)->m_x == x && (*it)->m_y == y)
    {
      return;
    }
    if(m_N->m_cost < (*it)->m_cost)
    {
      m_Open.insert(it, &m_TileGrid[x][y]);
      RTSMapTileNode* n = &m_TileGrid[x][y];
      int32 cost = n->m_cost;
      m_TileGrid[x][y].m_parent = m_N;
      while(n->m_parent!=nullptr)
      {
        cost += n->m_parent->m_cost;
        n = n->m_parent;
      }
      m_TileGrid[x][y].m_parent = m_N;
      m_TileGrid[x][y].m_cost = cost;
      m_Open.unique();
      return;
    }
  }
  m_Open.push_back(&m_TileGrid[x][y]);
  m_TileGrid[x][y].m_parent = m_N;
  RTSMapTileNode* n = &m_TileGrid[x][y];
  int32 cost = n->m_cost;
  m_TileGrid[x][y].m_parent = m_N;
  while(n->m_parent != nullptr)
  {
    cost += n->m_parent->m_cost;
    n = n->m_parent;
  }
  m_TileGrid[x][y].m_parent = m_N;
  m_TileGrid[x][y].m_cost = cost;
  m_Open.unique();
}

void RTSDijkstraMapGridWalker::reset()
{
  if(m_Open.size() > 0)
  {
    m_Open.clear();
  }
  if(m_Visited.size() > 0)
  {
    m_Visited.clear();
  }

  m_FastestPath.clear();

  m_N = nullptr;

  //int32 mapSize = m_pTiledMap->getMapSize().x * m_pTiledMap->getMapSize().y;
  //m_TileGrid.resize(mapSize);
  for(int32 i = 0; i < m_pTiledMap->getMapSize().x; i++)
  {
    for(int32 j = 0; j < m_pTiledMap->getMapSize().y; j++)
    {
      m_TileGrid[i][j].setVisited(false);
      if(m_TileGrid[i][j].m_parent)
      {
        m_TileGrid[i][j].m_parent = nullptr;
      }
      m_TileGrid[i][j].setCost(m_pTiledMap->getCost(i, j) + 1);
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
