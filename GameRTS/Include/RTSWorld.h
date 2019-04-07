#pragma once

#include <gePrerequisitesUtil.h>
#include <geVector2I.h>

#include <SFML/Graphics.hpp>

using namespace geEngineSDK;

class RTSTiledMap;
class RTSMapGridWalker;

namespace RTSGame {
  class RTSUnitType;
  class RTSUnit;
}

namespace UNIT_TYPE {
  enum E {
    kArcher = 0,
    kCastilianKnight,
    kCrossbow,
    kNumTypes
  };
}

class RTSWorld
{
 public:
  RTSWorld();
  ~RTSWorld();

 public:
  bool
  init(sf::RenderTarget* pTarget);

  void
  destroy();

  void
  update(float deltaTime);

  void
  render();

  RTSTiledMap*
  getTiledMap() {
    return m_pTiledMap;
  }

  void
  updateResolutionData();

  void
  setCurrentWalker(const int8 index);

  void
  setPathStart(float x, float y);

  void
  setPathEnd(float x, float y);
  
  void
  startPathFinding();

  void
  createUnit(UNIT_TYPE::E type, float x, float y);

  Vector<RTSGame::RTSUnit*>
  getUnits();

 private:
  RTSTiledMap* m_pTiledMap;
  Vector<RTSGame::RTSUnitType*> m_lstUnitTypes;
  Vector<RTSGame::RTSUnit*> m_lstUnits;
  
  Vector<RTSMapGridWalker*> m_walkersList;
  //Vector<void*> m_walkersList;
  RTSMapGridWalker* m_activeWalker;
  //void* m_activeWalker;
  int8 m_activeWalkerIndex;

  sf::RenderTarget* m_pTarget;
};
