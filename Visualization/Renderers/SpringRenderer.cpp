#include "SpringRenderer.h"

#include <Visualization/MiniGL.h>
#include <iostream>
using namespace IBDS;
using namespace std;

SpringRenderer::SpringRenderer(DampedSpring & spring):_spring(spring){
  _maxForceAmount = 0.0001;
}


void SpringRenderer::render(){
  _spring.calculateSpringAndDampeningForce();
  
  const Connector & cA = _spring.getConnectorA();
  const Connector & cB = _spring.getConnectorB();

  const Vector3D  & a_wcs = cA.getCachedWorldPosition();
  const Vector3D  & b_wcs = cB.getCachedWorldPosition();
  float color[4];
  const Vector3D & f=_spring.getSpringForce();
  Real amount = f.length();
  if(amount > _maxForceAmount)_maxForceAmount = amount;
  MiniGL::valueToColor(amount,color,0,_maxForceAmount);  
  MiniGL::drawVector(a_wcs,b_wcs,1,color);
  
  //cout << amount << " " << color[0] << " " <<color[1] << " " << color[2] << endl;

}