#include "RTSBreadthFirstSearchMapGridWalker.h"

RTSBreadthFirstSearchMapGridWalker::RTSBreadthFirstSearchMapGridWalker(void) {
  m_N = nullptr;
  m_TileGrid = nullptr;
  setStartPosition(0, 0);
  setEndPosition(0, 0);
}

RTSBreadthFirstSearchMapGridWalker::RTSBreadthFirstSearchMapGridWalker(RTSTiledMap* pMap) {
  m_N = nullptr;
  m_TileGrid = nullptr;
  setStartPosition(0, 0);
  setEndPosition(0, 0);
}

RTSBreadthFirstSearchMapGridWalker::~RTSBreadthFirstSearchMapGridWalker() {
  destroy();
}

bool RTSBreadthFirstSearchMapGridWalker::init() {
  return true;
}
