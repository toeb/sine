#pragma once
#include <visualization/core/IRenderer.h>
#include <simulation/geometry/polygon/Polygon.h>

namespace nspace{

class PolygonRenderer : public IRenderer{
public:
  bool drawEdges;
  bool drawHalfEdges;
  bool drawVertices;
  bool drawNormals;
  bool drawFaces;
  bool drawLabels;
  
  

  Polygon & _polygon;
public:
  PolygonRenderer( Polygon & polygon);
  void render();    
};

}