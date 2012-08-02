#pragma once

#include <simulation/geometry/Interval.h>
#include <simulation/geometry/Axis.h>
#include <simulation/geometry/BoundingVolumes/BoundingVolume.h>
namespace nspace{
  
class BoundingBox : public BoundingVolume{
public:
  Vector3D min;
  Vector3D max;

  BoundingBox():BoundingVolume(CoordinateSystem::identity()){

  }
  BoundingBox(const CoordinateSystem & parentCoordinates):BoundingVolume(parentCoordinates){

  }

  
  void updateBoundingVolume(){
    
  }

  Real getWidth()const{
    return max[0]-min[0];
  }
  Real getHeight()const{
    return max[1]-min[1];
  }
  Real getDepth()const{
    return max[2]-min[2];
  }
  void getCenter(Vector3D & c)const{
    //todo ist das richtig
    Vector3D::subtract(max,min,c);
    Vector3D::add(min,c,c);
  }
  bool isInside(const Vector3D & p)const{
    // todo ist das richtig?
    if(p[0] < min[0])return false;
    if(p[1] < min[1])return false;
    if(p[2] < min[2])return false;
    if(p[0] > max[0])return false;
    if(p[1] > max[1])return false;
    if(p[2] > max[2])return false;


    return true;
  }
  void projectOCS(const Axis & axis_ocs, Interval & interval)const{
    interval.setInvalid();
    for(int i=0; i < 8; i++){
      Vector3D corner;

      if((i/4)%2)corner[0] = min[0];
      else corner[0] = max[0];

      if((i/2)%2)corner[1] = min[1];
      else corner[1] = max[1];

      if((i/1)%2)corner[2] = min[2];
      else corner[2] = max[2];

      Real val = axis_ocs.projectOnAxis(corner);
      if(interval.a>val)interval.a = val;
      if(interval.b<val)interval.b = val;

    }
  }
};
  
}