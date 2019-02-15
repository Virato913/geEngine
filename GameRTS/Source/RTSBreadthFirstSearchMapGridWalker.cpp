#include "RTSBreadthFirstSearchMapGridWalker.h"

RTSBreadthFirstSearchMapGridWalker::RTSBreadthFirstSearchMapGridWalker(void) :
RTSMapGridWalker::RTSMapGridWalker() {
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
    m_TileGrid.clear();
  if(!m_pTiledMap)
    return false;
  m_pTiledMap->getMapGrid(m_TileGrid);
  return true;
}

void RTSBreadthFirstSearchMapGridWalker::destroy() {
  if(m_TileGrid.size() > 0)
    m_TileGrid.clear();
  m_N = nullptr;
}

void RTSBreadthFirstSearchMapGridWalker::render() {

}

WALK_STATE::E RTSBreadthFirstSearchMapGridWalker::update() {
  if(m_Open.size() > 0)
  {
    m_N = m_Open.front();
    m_Open.pop();

    if(m_N == m_End)
    {
      return kReachedGoal;
    }

    int32 x, y;

    return kStillLooking;
  }
  return kUnableToReachGoal;
}

void RTSBreadthFirstSearchMapGridWalker::visitGridNode(int32 x, int32 y)
{

}

void RTSBreadthFirstSearchMapGridWalker::reset()
{
  while(m_Open.size()>0)
  {
    m_Open.pop();
  }

  m_N = nullptr;

  m_Open.push(m_Start);
}
