#include "SpringRenderer.h"

#include <Visualization/MiniGL.h>
#include <iostream>
using namespace IBDS;

SpringRenderer::SpringRenderer(const DampedSpring & spring):_spring(spring){
  _maxForceAmount = 0;
}

float hat(Real value){
  if(value < 0)return 0;
  if(value > 2)return 0;
  if(value < 1)return value;
  if(value >= 1)return 2-value;
}
void valueToColor(Real value, float * color, Real min=0, Real max=10){
  if(max < min)return;
  if(value > max)value = max;
  if(value < min)value = min;
  value = value -min;
  Real d = max - min;
  value = value / d; //value element of [0,1]
  float r=0;
  float g=0;
  float b=0;
  if(value < 0.5){
    b = hat(value*4);
  }
  if(value > 0.25 && value < 0.75){
    g = hat((value-0.25)*4);
  }
  if(value > 0.5){
    r = hat((value-0.5)*4);
  }
  color[0] = r;
  color[1]=  g;
  color[2] = b;
  color[3] = 1;//alpha

  //std::cout << value << " " << r << " " << g << " " << b << std::endl;
}
void SpringRenderer::render(){
  const Connector & cA = _spring.getConnectorA();
  const Connector & cB = _spring.getConnectorB();
  Vector3D  a_wcs ;
  Vector3D  b_wcs;
  cA.calculateWorldPosition(a_wcs);
  cB.calculateWorldPosition(b_wcs);


  float color[4];
  Vector3D f;
  _spring.calculateSpringForce(f);
  Real amount = f.length();
  if(amount > _maxForceAmount)_maxForceAmount = amount;
  valueToColor(amount,color,0,_maxForceAmount);
  
  MiniGL::drawVector(a_wcs,b_wcs,4,color);
}