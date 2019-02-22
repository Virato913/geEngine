#pragma once

#include <gePlatformUtility.h>
#include <geVector2.h>
#include <geVector2I.h>

#include "RTSConfig.h"

using namespace geEngineSDK;

class RTSMapTileNode
{
public:
  RTSMapTileNode();
  RTSMapTileNode(const int32 cost);
  RTSMapTileNode(const int32 x, const int32 y, RTSMapTileNode* parent, const bool visited, const int32 cost);
  RTSMapTileNode(const RTSMapTileNode& copy);

  RTSMapTileNode&
    operator=(const RTSMapTileNode& rhs);

  bool operator==(const RTSMapTileNode& rhs);
  bool operator<(const RTSMapTileNode& rhs);
  bool operator>(const RTSMapTileNode& rhs);

  void setParent(RTSMapTileNode* parent)
  {
    m_parent = parent;
  }

  void setVisited(const bool visited)
  {
    m_visited = visited;
  }

  bool getVisited() const 
  {
    return m_visited;
  }

  FORCEINLINE int32
    getCost() const {
    return m_cost;
  }

  void
    setCost(const int32 cost) {
    m_cost = cost;
  }

  bool Equals(const RTSMapTileNode& rhs)
  {
    return ((m_x == rhs.m_x) && (m_y == rhs.m_y));
  }

  int32 m_cost;
  int32 m_x;
  int32 m_y;
  bool m_visited;
  RTSMapTileNode* m_parent;
};
