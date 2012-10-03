#pragma once
#include <visualization/Renderer.h>
#include <simulation.geometry/polygon/Polygon.h>
#include <visualization/Color.h>
#include <visualization.opengl/GlTexture.h>
#include <core.hub/CompositeHubObject.h>
#include <core.initialization/Initializable.h>
namespace nspace{

  class PolygonRenderer : public virtual Renderer, public virtual CompositeHubObject, public virtual Initializable{
    TYPED_OBJECT(PolygonRenderer);
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
  protected:
  
  };

}