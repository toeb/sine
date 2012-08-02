#pragma once

#include <Simulation/Geometry/Polygon/Element.h>
#include <Simulation/Geometry/Polygon/HalfEdge.h>
#include <Math/MathDefs.h>

namespace IBDS{

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