#pragma once
#include <Simulation/Geometry/Polygon/Element.h>
#include <Simulation/Geometry/Polygon/Vertex.h>
#include <Simulation/Geometry/Polygon/HalfEdge.h>
namespace IBDS{
 
struct Edge: public Element{
  HalfEdge * getUnconnectedHalfEdge()const;
  void getDirection(Vector3D & dir);
  bool isInFrontOf(const Edge * edge)const;
  bool isInBackOf(const Edge * edge)const;
  bool sharesVertex(const Edge * edge)const;
  HalfEdge * getHalfEdgeTo(const Vertex * v)const;
  Vertex *A;
  Vertex *B;
  HalfEdge * forward;
  HalfEdge * backward;
};

}