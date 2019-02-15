#pragma once

#include <gePlatformUtility.h>
#include <geVector2.h>
#include <geVector2I.h>

#include "RTSConfig.h"

using namespace geEngineSDK;

class RTSMapTile
{
public:
  RTSMapTile();
  RTSMapTile(const int8 idType, const int8 cost);
  RTSMapTile(const RTSMapTile& copy);

  RTSMapTile&
    operator=(const RTSMapTile& rhs);

  FORCEINLINE uint8
    getType() const {
    return m_idType;
  }

  void
    setType(const int8 idType) {
    m_idType = idType;
  }

  FORCEINLINE int8
    getCost() const {
    return m_cost;
  }

  void
    setCost(const int8 cost) {
    m_cost = cost;
  }

private:
  uint8 m_idType;
  int8 m_cost;
};
