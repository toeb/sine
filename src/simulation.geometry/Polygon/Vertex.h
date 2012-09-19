#pragma once

#include <simulation.geometry/polygon/Element.h>


namespace nspace{
struct Edge;
struct HalfEdge;
struct Vertex : public Element{
  Vertex():edge(0){}
  Vector3D p_ocs;
  Edge * edge;
  HalfEdge * getHalfEdgeTo(const Vertex * b)const;
};
}