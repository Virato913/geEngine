#pragma once

#include <gePrerequisitesUtil.h>
#include <geVector2I.h>

#include <SFML/Graphics.hpp>

using namespace geEngineSDK;

class RTSTiledMap;
class RTSMapGridWalker;

namespace RTSGame {
  class RTSUnitType;
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

  void setPathStart(float x, float y);

  void setPathEnd(float x, float y);
  
  void startPathFinding();

 private:
  RTSTiledMap* m_pTiledMap;
  Vector<RTSGame::RTSUnitType*> m_lstUnitTypes;
  //List<RTSUnit*> m_lstUnits;
  
  Vector<RTSMapGridWalker*> m_walkersList;
  //Vector<void*> m_walkersList;
  RTSMapGridWalker* m_activeWalker;
  //void* m_activeWalker;
  int8 m_activeWalkerIndex;

  sf::RenderTarget* m_pTarget;
};
