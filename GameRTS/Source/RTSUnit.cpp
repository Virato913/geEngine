#include "RTSUnit.h"
#include "RTSTiledMap.h"

namespace RTSGame {
  RTSUnit::RTSUnit(const Vector<Animation> animationFrames,
                   RTSTexture* texture,
                   RTSTiledMap* tiledMap,
                   sf::RenderTarget* target) :
    m_animationFrames(animationFrames),
    m_bSelected(false),
    m_circle(target) {
    m_texture = texture;
    m_pTiledMap = tiledMap;
    m_state = STATE::kIDLE;
    m_direction = DIRECTION::kN;
    m_texture->setPosition(100, 100);
    m_frameCount = 0;
    m_elapsedTime = 0;
  }

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

    x += TILESIZE_X / 2;
    y += TILESIZE_Y / 2;

    m_texture->setPosition(x - (currentFrame.w / 2),
                           y - (currentFrame.h));
    if(m_bSelected) {
      m_circle.setPosition(x,
                           y);
      m_circle.draw();
    }
    m_texture->draw();
  }

  void
  RTSUnit::setPosition(float x, float y) {
    m_position.x = x;
    m_position.y = y;
  }

  void
  RTSUnit::makeSelected(const bool isSelected) {
    m_bSelected = isSelected;
  }

  geEngineSDK::Vector2
  RTSUnit::getPosition() {
    return m_position;
  }

  void
  RTSUnit::getPosition(float& x, float& y) {
    x = m_position.x;
    y = m_position.y;
  }

  RTSUnit::SelectedCircle::SelectedCircle(sf::RenderTarget* target) :
    m_shape(TILESIZE_X / 2),
    m_pTarget(target) {
#ifdef MAP_IS_ISOMETRIC
    m_shape.setScale(sf::Vector2f(1, 0.5f));
    //m_shape.setScale(sf::Vector2f(m_shape.getScale().x / 4,
    //                              m_shape.getScale().y / 4));
    m_shape.scale(0.5, 1);
#else
    //m_shape.setScale(1 / 2, 1 / 2);
#endif // MAP_IS_ISOMETRIC
    m_shape.setOutlineThickness(1);
    m_shape.setFillColor(sf::Color::Transparent);
    int x = m_shape.getLocalBounds().width / 2;
    int y = m_shape.getLocalBounds().height / 2;
    m_shape.setOrigin(x, y);
  }

  RTSUnit::SelectedCircle::~SelectedCircle() {

  }

  void
  RTSUnit::SelectedCircle::setOrigin(float x, float y) {

  }

  void
  RTSUnit::SelectedCircle::setPosition(float x, float y) {
    m_shape.setPosition(x, y);
  }

  void
  RTSUnit::SelectedCircle::draw() {
    m_pTarget->draw(m_shape);
  }
}
