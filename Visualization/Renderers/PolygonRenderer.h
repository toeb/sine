#pragma once
#include <Visualization/IRenderer.h>
#include <Simulation/Geometry/Polygon/Polygon.h>

namespace IBDS{

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