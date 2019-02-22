#include "RTSMapTileNode.h"

RTSMapTileNode::RTSMapTileNode() {
  m_cost = 1;
  m_x = m_y = 0;
  m_visited = false;
  m_parent = nullptr;
}

RTSMapTileNode::RTSMapTileNode(const int32 cost) {
  m_cost = cost;
  m_x = m_y = 0;
  m_visited = false;
  m_parent = nullptr;
}

RTSMapTileNode::RTSMapTileNode( const int32 x, const int32 y, RTSMapTileNode* parent, const bool visited, const int32 cost)
{
  m_x = x;
  m_y = y;
  m_parent = parent;
  m_visited = visited;
  m_cost = cost;
}

RTSMapTileNode::RTSMapTileNode(const RTSMapTileNode& copy) {
  m_cost = copy.m_cost;
  m_x = copy.m_x;
  m_y = copy.m_y;
  m_visited = copy.m_visited;
  m_parent = copy.m_parent;
}

RTSMapTileNode&
RTSMapTileNode::operator=(const RTSMapTileNode& rhs) {
  m_cost = rhs.m_cost;
  m_x = rhs.m_x;
  m_y = rhs.m_y;
  m_visited = rhs.m_visited;
  m_parent = rhs.m_parent;
  return *this;
}

bool RTSMapTileNode::operator==(const RTSMapTileNode& rhs)
{
  return this->Equals(rhs);
}

bool RTSMapTileNode::operator<(const RTSMapTileNode& rhs)
{
  return m_cost < rhs.m_cost;
}

bool RTSMapTileNode::operator>(const RTSMapTileNode& rhs)
{
  return m_cost > rhs.m_cost;
}
