#include "Hexahedron.h"

using namespace IBDS;
using namespace std;

Hexahedron::Hexahedron(Real x, Real y , Real z):_xExtent(x),_yExtent(y),_zExtent(z){

}

void Hexahedron::createGeometry(){
  deleteGeometry();
  Real x = _xExtent/2;
  Real y = _yExtent/2;
  Real z = _zExtent/2;  
  
  addVertex(Vector3D(-x,-y,-z));
  addVertex(Vector3D(-x,-y,z));
  addVertex(Vector3D(-x,y,z));
  addVertex(Vector3D(-x,y,-z));
  addVertex(Vector3D(x,-y,-z));
  addVertex(Vector3D(x,-y,z));
  addVertex(Vector3D(x,y,z));
  addVertex(Vector3D(x,y,-z));
  
  addEdge(1,0);
  addEdge(2,1);
  addEdge(3,2);
  addEdge(0,3);
  
  addEdge(7,4);
  addEdge(6,7);
  addEdge(5,6);
  addEdge(4,5);
  
  addEdge(0,4);
  addEdge(1,5);
  addEdge(2,6);
  addEdge(3,7);

  addFace(0,1,2,3);
  addFace(7,6,5,4);
  addFace(1,5,6,2);
  addFace(0,3,7,4);
  addFace(2,6,7,3);
  addFace(0,4,5,1);


}





Real Hexahedron::getXExtent()const{return _xExtent;};
Real Hexahedron::getYExtent()const{return _yExtent;};
Real Hexahedron::getZExtent()const{return _zExtent;};
