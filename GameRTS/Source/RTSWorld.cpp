#include "RTSWorld.h"
#include "RTSTiledMap.h"

#include "RTSUnitType.h"
#include "RTSUnit.h"
#include "RTSDepthFirstSearchMapGridWalker.h"
#include "RTSBreadthFirstSearchMapGridWalker.h"
#include "RTSBestFirstSearchMapGridWalker.h"
#include "RTSDijkstraMapGridWalker.h"

RTSWorld::RTSWorld() {
  m_pTiledMap = nullptr;
  m_activeWalkerIndex = - 1;	//-1 = Invalid index
}

RTSWorld::~RTSWorld() {
  destroy();
}

bool
RTSWorld::init(sf::RenderTarget* pTarget) {
  GE_ASSERT(nullptr == m_pTiledMap && "World was already initialized");
  destroy();

  m_pTarget = pTarget;

  //Initialize the map (right now it's an empty map)
  m_pTiledMap = ge_new<RTSTiledMap>();
  GE_ASSERT(m_pTiledMap);
  m_pTiledMap->init(m_pTarget, Vector2I(256, 256));

  //Create the path finding classes and push them to the walker list
  m_walkersList.push_back(ge_new<RTSDepthFirstSearchMapGridWalker>(m_pTiledMap));
  m_walkersList.push_back(ge_new<RTSBreadthFirstSearchMapGridWalker>(m_pTiledMap));
  m_walkersList.push_back(ge_new<RTSBestFirstSearchMapGridWalker>(m_pTiledMap));
  m_walkersList.push_back(ge_new<RTSDijkstraMapGridWalker>(m_pTiledMap));

  //Init the walker objects

  for (SIZE_T it = 0; it < m_walkersList.size(); ++it) {
    m_walkersList[it]->init(m_pTarget);
  }

  //Set the first walker as the active walker
  setCurrentWalker(m_walkersList.size() > 0 ? 0 : -1);

  m_lstUnitTypes.push_back(ge_new<RTSGame::RTSUnitType>());
  m_lstUnitTypes.push_back(ge_new<RTSGame::RTSUnitType>());
  m_lstUnitTypes.push_back(ge_new<RTSGame::RTSUnitType>());

  for(uint32 i = 0; i < m_lstUnitTypes.size(); ++i) {
    m_lstUnitTypes[i]->loadAnimationData(m_pTarget, i + 1);
  }

  //m_lstUnits.push_back(ge_new<RTSGame::RTSUnit>(m_lstUnitTypes[0]->m_animationFrames,
  //                                              m_lstUnitTypes[0]->m_texture));

  return true;
}

void
RTSWorld::destroy() {
 //Destroy all the walkers
  while (m_walkersList.size() > 0) {
    if(m_walkersList.back())
    {
      ge_delete(m_walkersList.back());
    }
    m_walkersList.pop_back();
  }

  while(m_lstUnits.size()>0)
  {
    if(m_lstUnits.back())
    {
      ge_delete(m_lstUnits.back());
    }
    m_lstUnits.pop_back();
  }

  while(m_lstUnitTypes.size()>0)
  {
    if (m_lstUnitTypes.back())
    {
      ge_delete(m_lstUnitTypes.back());
    }
    m_lstUnitTypes.pop_back();
  }

  //As the last step, destroy the full map
  if (nullptr != m_pTiledMap) {
    ge_delete(m_pTiledMap);
    m_pTiledMap = nullptr;
  }
}

void
RTSWorld::update(float deltaTime) {
  setCurrentWalker(GameOptions::s_Walker);
  m_pTiledMap->update(deltaTime);
  if(!GameOptions::s_ReachedGoal)
  {
    if(m_activeWalker->update() != WALK_STATE::kStillLooking)
    {
      GameOptions::s_ReachedGoal = true;
    }
  }
  else
  {
    m_activeWalker->traceback();
  }
  for (auto it = m_lstUnits.begin();it!=m_lstUnits.end();++it)
  {
    (*it)->update(deltaTime);
  }
}

void
RTSWorld::render() {
  m_pTiledMap->render();
  if(GameOptions::s_PathFinder)
  {
    m_activeWalker->render();
  }
  m_pTiledMap->renderPathFinding();
  for(auto it = m_lstUnits.begin(); it != m_lstUnits.end(); ++it) {
    (*it)->draw();
  }
}

void
RTSWorld::updateResolutionData() {
  if (nullptr != m_pTiledMap) {
    Vector2I appResolution = g_gameOptions().s_Resolution;
    
    m_pTiledMap->setStart(0, 0);
    m_pTiledMap->setEnd(appResolution.x, appResolution.y - 175);
    
    //This ensures a clamp if necessary
    m_pTiledMap->moveCamera(0, 0);
  }
}

void
RTSWorld::setCurrentWalker(const int8 index) {
  //Revisamos que el walker exista (en modo de debug)
  GE_ASSERT(m_walkersList.size() > static_cast<SIZE_T>(index));

  m_activeWalker = m_walkersList[index];
  m_activeWalkerIndex = index;
}

void
RTSWorld::setPathStart(float x, float y)
{
  for(SIZE_T it = 0; it < m_walkersList.size(); ++it) {
    m_walkersList[it]->setStartPosition(x, y);
  }
  m_pTiledMap->setPathStart(x, y);
}

void
RTSWorld::setPathEnd(float x, float y)
{
  for(SIZE_T it = 0; it < m_walkersList.size(); ++it) {
    m_walkersList[it]->setEndPosition(x, y);
    m_walkersList[it]->setEndPosition(x, y);
  }
  m_pTiledMap->setPathEnd(x, y);
}

void RTSWorld::startPathFinding()
{
  m_activeWalker->reset();
}

void
RTSWorld::createUnit(UNIT_TYPE::E type, float x, float y) {
  RTSGame::RTSUnit* newUnit = m_lstUnitTypes[type]->createUnit(m_pTiledMap);
  newUnit->setPosition(x, y);
  m_lstUnits.push_back(newUnit);
}
