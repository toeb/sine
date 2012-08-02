#pragma once

#include <Simulation/Geometry/Polygon/Polygon.h>
namespace nspace{


class Pyramid : public Polygon{
public:
protected:
  void createGeometry(){
    addVertex(Vector3D(-0.5,-0.5,-0.5));
    addVertex(Vector3D(-0.5,-0.5,0.5));
    addVertex(Vector3D(0.5,-0.5,0.5));
    addVertex(Vector3D(0.5,-0.5,-0.5));
    addVertex(Vector3D(0,0.5,0));
    

    addEdge(0,1);
    addEdge(1,2);
    addEdge(2,3);
    addEdge(3,0);
    
    addEdge(0,4);
    addEdge(1,4);
    addEdge(2,4);
    addEdge(3,4);

    
    addFace(3,2,1,0);
    
    addFace(0,1,4);
    addFace(1,2,4);
    addFace(2,3,4);
    addFace(3,0,4);
  }
};
}