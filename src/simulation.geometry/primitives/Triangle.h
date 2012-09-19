#pragma once

#include <simulation/geometry/polygon/Polygon.h>
namespace nspace{
  
class Triangle : public Polygon{
public:
protected:
  void createGeometry(){
    addVertex(Vector3D(-1,-1,0));
    addVertex(Vector3D(+1,-1,0));
    addVertex(Vector3D(0,1,0));
    
    addEdge(0,1);
    addEdge(1,2);
    addEdge(2,0);
    
    addFace(0,1,2);
    addFace(2,1,0);
  }
};

}