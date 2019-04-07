#pragma once

#include "RTSTexture.h"
#include "RTSWorld.h"

using namespace geEngineSDK;

namespace sf{
  class RenderWindow;
  class RenderTarget;
  class Font;
  template<typename T>
  class Vector2;
}

class RTSApplication
{
  class SelectionSquare {
   public:
    SelectionSquare(sf::RenderTarget* target);
    ~SelectionSquare();

    void
    draw();

    void
    setRenderTarget(sf::RenderTarget* target);

    void
    setOrigin(float x, float y);

    void
    setFirstPos(int32 x, int32 y);

    void
    setSecondPos(int32 x, int32 y);

    bool
    isWithin(int32 x, int32 y);

   private:
    
    sf::Vector2<int>* m_FirstPos;
    sf::Vector2<int>* m_SecondPos;

    sf::RenderTarget* m_pTarget;
    sf::RectangleShape* m_shape;
  };

 public:
  RTSApplication();
  virtual ~RTSApplication();

  int32
  run();

  sf::RenderWindow*
  getRenderWindow() {
    return m_window;
  }

  RTSWorld*
  getWorld() {
    return &m_gameWorld;
  }

  float getFPS() const {
    return m_framesPerSecond;
  }

 protected:

 private:
   void
   initSystems();

   void
   initGUI();

   void
   destroySystems();

   void
   gameLoop();

   void
   postInit();

   void
   postDestroy();

   void
   updateFrame();
   
   void
   renderFrame();

 private:
   sf::RenderWindow* m_window;
   sf::Font* m_arialFont;
   RTSWorld m_gameWorld;

   float m_fpsTimer;
   float m_fpsCounter;
   float m_framesPerSecond;

   SelectionSquare m_square;
};
