#pragma once
#include <visualization/core/IRenderer.h>
#include <simulation/geometry/polygon/Polygon.h>
#include <visualization/core/Color.h>
namespace nspace{

class PolygonRenderer : public IRenderer{
public:
  Color faceColor;
  Color forwardHalfEdgeColor;
  Color backwardHalfEdgeColor;
  Color vertexColor;
  Color normalColor;
  Color labelColor;
  Color edgeColor;

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