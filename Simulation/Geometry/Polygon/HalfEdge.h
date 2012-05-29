#pragma once
#include <Simulation/Geometry/Polygon/Element.h>

namespace IBDS{
struct Edge;
struct Face;
struct Vertex;
struct HalfEdge :public Element{
  HalfEdge():next(0),edge(0),face(0){}
  HalfEdge* next;
  Edge * edge;
  Face * face;


  bool isForwardHalfEdge()const;
  bool isFirstHalfEdgeOfFace()const;
  HalfEdge * getPrevious()const;

  Vertex * getEndVertex()const;
  Vertex * getStartVertex()const;
  HalfEdge * getReverseHalfEdge()const;
  HalfEdge * getNextHalfEdgeOf(const Vertex * v)const;
};

}