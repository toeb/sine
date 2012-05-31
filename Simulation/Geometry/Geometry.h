#pragma once

#include <Simulation/Geometry/CoordinateSystem.h>
#include <vector>



namespace IBDS{

  class Axis{
  public:
    Axis(const Vector3D & normal){
      p.setZero();
      n.assign(normal);
    }
    Axis(){
      p.setZero();
      n.set(1,0,0);
    }
  Vector3D p;
  Vector3D n;
  inline Real projectOnAxis(const Vector3D & a) const{
   Vector3D diff;
    Real result;
    Vector3D::subtract(a, p,diff);
    Vector3D::dotProduct(n,diff,result);
    return result;
  
  }
};

  
struct Interval{
  // set the interval to the invalid values (+inf, -inf) 
  // which is useful for detrmining the max and min values 
  void setInvalid(){
    b = -DBL_MAX;
    a = DBL_MAX;
  }

  /**
   * \brief Sets the interval to (-inf,inf) .
   */
  void setUnbounded(){
    a = -DBL_MAX;
    b = DBL_MAX;
  }

  /**
   * \brief Extends interval to contain value.
   *
   * \author Tobi
   * \date 30.05.2012
   *
   * \param value The value.
   */
  inline void extendTo(Real value){
    if(value < a)a = value;
    if(value > b)b  =value;
  }
  Interval(Real low, Real high):a(low), b(high){
    
  }
  Interval(){
    setUnbounded();
  }
  bool overlaps(const Interval & other){
    if(other.b < a)return false;
    if(other.a > b)return false;
    return true;
  }
  bool disjoint(const Interval & other){
    return !overlaps(other);
  }
  bool subsetOf(const Interval & other){
    if(other.a <= a && other.b >= b)return true;
    return false;
  }

  Real a;
  Real b;
};
  
struct AABB{
  Vector3D min;
  Vector3D max;
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
    Vector3D::subtract(max,min,c);
    Vector3D::add(min,c,c);
  }
  bool isInside(const Vector3D & p)const{
    if(p[0] < min[0])return false;
    if(p[1] < min[1])return false;
    if(p[2] < min[2])return false;
    if(p[0] < max[0])return false;
    if(p[1] < max[1])return false;
    if(p[2] < max[2])return false;


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

enum Classification{
  UNCLASSIFIED=0,
  INSIDE=1,
  OUTSIDE=2,
  BOTH=3
};



class Geometry : public virtual CoordinateSystem{
public:
  virtual bool isInsideOCS(const Vector3D & p_ocs)const{return false;};
  virtual bool isInside(const Vector3D & p_wcs)const;
  virtual bool boundaryIntersects(const AABB & aabb_ocs){return false;} 
  

  
  virtual void projectOCS(const Axis & axis_ocs, Interval & result)const{}; 

  virtual void project(const Axis & axis_wcs, Interval & result)const;
  
  virtual void getBoundingBoxOCS(AABB & aabb_ocs)const;
  virtual void getBoundingBox(AABB & aabb_wcs)const;
  virtual Real calculateBoundingSphereRadius()const;

  virtual Classification classify(const AABB & aabb)const{return Classification::UNCLASSIFIED;};
  virtual Classification classify(const Vector3D & p, Real r)const{return Classification::UNCLASSIFIED;}
  virtual void fitInto(const AABB & aabb){};
};

}