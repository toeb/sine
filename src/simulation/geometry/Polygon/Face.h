#pragma once

#include <simulation/geometry/polygon/Element.h>
#include <simulation/geometry/polygon/HalfEdge.h>
#include <math/definitions.h>

namespace nspace{

struct Face: public Element{
  Face():first(0),valid(false){}
  bool valid;
  Vector3D n_ocs;
  int vertexCount;
  HalfEdge * first;
  void getCenter(Vector3D & c)const;
  void getVertices(std::vector<Vertex *> & vertices)const;
};

}