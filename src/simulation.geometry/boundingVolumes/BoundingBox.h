#pragma once
#include <math/core.h>
#include <simulation.geometry/Interval.h>
#include <simulation.geometry/Axis.h>
#include <simulation.geometry/boundingVolumes/BoundingVolume.h>
namespace nspace{
  
class BoundingBox : public BoundingVolume{
private:
  Vector3D _min;
  Vector3D _max;
public:
  Vector3D & minValue(){
    return _min;
  }
  Vector3D & maxValue(){
    return _max;
  }
  const Vector3D & minValue()const{
    return _min;
  }
  const Vector3D & maxValue()const{
    return _max;
  }
    
  template<typename T>
  inline void extendBy(const T & vector){
     if(vector(0)<_min(0)) _min(0) = vector(0);
     if(vector(0)>_max(0)) _max(0) = vector(0);
     
     if(vector(1)<_min(1)) _min(1) = vector(1);
     if(vector(1)>_max(1)) _max(1) = vector(1);
     
     if(vector(2)<_min(2)) _min(2) = vector(2);
     if(vector(2)>_max(2)) _max(2) = vector(2);
  }


  BoundingBox():BoundingVolume(CoordinateSystem::identity()){

  }
  BoundingBox(const CoordinateSystem & parentCoordinates):BoundingVolume(parentCoordinates){

  }

  
  void updateBoundingVolume(){
    
  }

  Real getWidth()const{
    return _max(0) - _min(0);
  }
  Real getHeight()const{
    return _max(1)-_min(1);
  }
  Real getDepth()const{
    return _max(2)-_min(2);
  }
  void getCenter(Vector3D & c)const{
    //todo ist das richtig?
    //Vector3D::subtract(_max,_min,c);
    //Vector3D::add(_min,c,c);
    c=(_max-_min)*0.5;
  }
  bool isInside(const Vector3D & p)const{
    // todo ist das richtig?
    if(p(0) < _min(0))return false;
    if(p(1) < _min(1))return false;
    if(p(2) < _min(2))return false;
    if(p(0) > _max(0))return false;
    if(p(1) > _max(1))return false;
    if(p(2) > _max(2))return false;


    return true;
  }
  void projectOCS(const Axis & axis_ocs, Interval & interval)const{
    interval.setInvalid();
    for(int i=0; i < 8; i++){
      Vector3D corner;

      if((i/4)%2)corner(0) = _min(0);
      else corner(0) = _max(0);

      if((i/2)%2)corner(1) = _min(1);
      else corner(1) = _max(1);

      if((i/1)%2)corner(2) = _min(2);
      else corner(2) = _max(2);

      Real val = axis_ocs.projectOnAxis(corner);
      if(interval.a>val)interval.a = val;
      if(interval.b<val)interval.b = val;

    }
  }
};
  
}
