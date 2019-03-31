#pragma once

#include "RTSUnitType.h"

namespace RTSGame {
  namespace STATE {
    enum E {
      kATTACK = 0,
      kDIE,
      kIDLE,
      kRUN,
      kNUM_STATES
    };
  }
  
  namespace DIRECTION {
    enum E {
      kN = 0,
      kNW,
      kW,
      kSW,
      kS,
      kSE,
      kE,
      kNE,
      kNUM_DIRECTIONS
    };
  }

  class RTSUnit {
   public:
     RTSUnit(const Vector<Animation> animationFrames,
             RTSTexture* texture,
             RTSTiledMap* tiledMap) :
       m_animationFrames(animationFrames) {
       m_texture = texture;
       m_pTiledMap = tiledMap;
       m_state = STATE::kIDLE;
       m_direction = DIRECTION::kN;
       m_texture->setPosition(100, 100);
       m_frameCount = 0;
       m_elapsedTime = 0;
     }

     ~RTSUnit();

     void
     update(float deltaTime);
     void
     draw();
     void
     setPosition(float x, float y);

   private:
     Vector<Animation> m_animationFrames;
     RTSTexture* m_texture;
     RTSTiledMap* m_pTiledMap;
     STATE::E m_state;
     DIRECTION::E m_direction;
     int32 m_frameCount;
     float m_elapsedTime;
     Vector2 m_position;
 };
}