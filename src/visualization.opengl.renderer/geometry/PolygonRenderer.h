#pragma once
#include <visualization/IRenderer.h>
#include <simulation.geometry/polygon/Polygon.h>
#include <visualization/Color.h>
#include <visualization.opengl/GlTexture.h>
namespace nspace{

class PolygonRenderer : public IRenderer{
public:
  Texture texture;
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
  bool initializeObject();
  void render();    
};

}