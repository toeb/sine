#include "Rectangle.h"

using namespace std;
using namespace IBDS;

Rectangle::Rectangle( const Vector2D & dimension):
 _dimension(dimension){

}



void Rectangle::createGeometry(){
  deleteGeometry();
  Real x = _dimension[0]/2;
  Real y= _dimension[1]/2;
  
  addVertex(Vector3D(-x,-y,0));
  addVertex(Vector3D(-x,y,0));
  addVertex(Vector3D(x,y,0));
  addVertex(Vector3D(x,-y,0));

  addEdge(0,1);
  addEdge(1,2);
  addEdge(2,3);
  addEdge(3,0);
  
  addFace(0,1,2,3); //frontface
  addFace(3,2,1,0); //backface
}
void Rectangle::setDimension(const Vector2D & dim){
  _dimension=dim;

  deleteGeometry();
  createGeometry();

}
void Rectangle::setDimension(Real x,Real y){
  setDimension(Vector2D(x,y));

}
const Vector2D & Rectangle::getDimension()const{
  return _dimension;
}



 void Rectangle::getNormal(Vector3D &n_wcs)const{
   Matrix3x3 RT;
   getOrientation().getMatrix3x3T(RT);
   n_wcs.assign(RT.v[2]);
 }






