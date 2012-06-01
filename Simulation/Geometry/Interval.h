#pragma once


namespace IBDS{
  
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
}