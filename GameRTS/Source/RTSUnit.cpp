#include "RTSUnit.h"
#include "RTSTiledMap.h"

namespace RTSGame {
  RTSUnit::~RTSUnit() {

  }

  void
  RTSUnit::update(float deltaTime) {
    m_elapsedTime += deltaTime;
  }

  void
  RTSUnit::draw() {
    float frameTime = m_animationFrames[m_state].duration / m_animationFrames[m_state].numFrames;
    AnimationFrame& currentFrame = m_animationFrames[m_state].frames[m_direction][m_frameCount];
    m_texture->setSrcRect(currentFrame.x, currentFrame.y, currentFrame.w, currentFrame.h);
    if(m_elapsedTime > frameTime) {
      m_frameCount = (++m_frameCount) % m_animationFrames[m_state].numFrames;
      m_elapsedTime = 0.0f;
    }
    int x = 0;
    int y = 0;
    m_pTiledMap->getMapToScreenCoords(m_position.x, m_position.y, x, y);
    m_texture->setPosition(x + (TILESIZE_X / 4),
                           y - (currentFrame.h / 2));
    m_texture->draw();
  }

  void
  RTSUnit::setPosition(float x, float y) {
    m_position.x = x;
    m_position.y = y;
  }
}
