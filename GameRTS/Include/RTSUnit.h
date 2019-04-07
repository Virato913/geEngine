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
   private:
     class SelectedCircle {
      public:
       SelectedCircle(sf::RenderTarget* target);
       ~SelectedCircle();

       void
       setOrigin(float x, float y);

       void
       setPosition(float x, float y);

       void
       draw();

      private:
       sf::CircleShape m_shape;
       sf::RenderTarget* m_pTarget;
     };

   public:
     RTSUnit(const Vector<Animation> animationFrames,
             RTSTexture* texture,
             RTSTiledMap* tiledMap,
             sf::RenderTarget* target);

     ~RTSUnit();

     void
     update(float deltaTime);
     void
     draw();
     void
     setPosition(float x, float y);
     void
     makeSelected(const bool isSelected);
     Vector2
     getPosition();
     void
     getPosition(float& x, float& y);

   private:
     Vector<Animation> m_animationFrames;
     RTSTexture* m_texture;
     RTSTiledMap* m_pTiledMap;
     STATE::E m_state;
     DIRECTION::E m_direction;
     int32 m_frameCount;
     float m_elapsedTime;
     Vector2 m_position;
     bool m_bSelected;
     SelectedCircle m_circle;
 };
}