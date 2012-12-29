#pragma once
#include <simulation.geometry/polygon/Element.h>
#include <simulation.geometry/polygon/Vertex.h>
#include <simulation.geometry/polygon/HalfEdge.h>
namespace nspace{
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