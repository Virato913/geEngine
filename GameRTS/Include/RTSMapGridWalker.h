#pragma once

#include "gePrerequisitesUtil.h"
#include "geVector2I.h"

#include <SFML/Graphics.hpp>

using namespace geEngineSDK;

class RTSTiledMap;
//class RTSTexture;

namespace WALK_STATE {
  enum E {
    kStillLooking = 0,
    kReachedGoal,
    kUnableToReachGoal,
    kNumStates
  };
}

class RTSMapGridWalker
{
 public:
  RTSMapGridWalker(void);
  RTSMapGridWalker(RTSTiledMap* pMap) { m_pTiledMap = pMap; }
  virtual ~RTSMapGridWalker(void);

  virtual bool init(sf::RenderTarget* render) { return false; }
  virtual void destroy() = 0;
  virtual WALK_STATE::E update() = 0;
  virtual void render() = 0;
  virtual void reset() = 0;
  virtual bool weightedGraphSupported() { return false; }
  virtual bool heuristicsSupported() { return false; }
  virtual void traceback() = 0;
  void setTiledMap(RTSTiledMap* pMap) { m_pTiledMap = pMap; }
  RTSTiledMap* getMapGrid() { return m_pTiledMap; }
  void setStartPosition(const int32 x, const int32 y) { m_StartX = x; m_StartY = y; }
  void setEndPosition(const int32 x, const int32 y) { m_EndX = x; m_EndY = y; }
  void getStartPosition(int32& x, int32& y) { x = m_StartX; y = m_StartY; }
  void getEndPosition(int32& x, int32& y) { x = m_EndX; y = m_EndY; }

 protected:
  virtual void visitGridNode(int32 x, int32 y) = 0;

 protected:
  RTSTiledMap* m_pTiledMap;
  int32 m_StartX, m_StartY;
  int32 m_EndX, m_EndY;
};
