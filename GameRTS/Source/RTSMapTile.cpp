#include "RTSMapTile.h"

RTSMapTile::RTSMapTile() {
  m_idType = 1;
  m_cost = 1;
}

RTSMapTile::RTSMapTile(const int8 idType, const int8 cost) {
  m_idType = idType;
  m_cost = cost;
}

RTSMapTile::RTSMapTile(const RTSMapTile& copy) {
  m_idType = copy.m_idType;
  m_cost = copy.m_cost;
}

RTSMapTile&
RTSMapTile::operator=(const RTSMapTile& rhs) {
  m_idType = rhs.m_idType;
  m_cost = rhs.m_cost;
  return *this;
}
