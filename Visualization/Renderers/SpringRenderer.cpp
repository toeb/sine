#include "SpringRenderer.h"

#include <Visualization/MiniGL.h>
#include <iostream>
using namespace IBDS;
using namespace std;

SpringRenderer::SpringRenderer(const DampedSpring & spring):_spring(spring){
  _maxForceAmount = 0.0001;
}


void SpringRenderer::render(){
  const Connector & cA = _spring.getConnectorA();
  const Connector & cB = _spring.getConnectorB();
  const Vector3D  & a_wcs = cA.getWorldPosition();
  const Vector3D  & b_wcs = cB.getWorldPosition();
  float color[4];
  Vector3D f;
  _spring.calculateSpringForce(f);
  Real amount = f.length();
  if(amount > _maxForceAmount)_maxForceAmount = amount;
  MiniGL::valueToColor(amount,color,0,_maxForceAmount);  
  MiniGL::drawVector(a_wcs,b_wcs,4,color);
  
  cout << amount << " " << color[0] << " " <<color[1] << " " << color[2] << endl;

}