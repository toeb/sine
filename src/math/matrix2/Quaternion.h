
#pragma once
#include <common/Config.h>
#include <math/definitions.h>


namespace nspace
{
  namespace matrix2{
  template<typename T>
  class StaticVector<T,4>{
  public:

    Real & x(){return _data[0];}
    const Real & x()const{return _data[0];}
    Real & y(){return _data[1];}
    const Real & y()const{return _data[1];}
    Real & z(){return _data[2];}
    const Real & z()const{return _data[2];}
    Real & w(){return _data[3];}
    const Real & w()const{return _data[3];}
  };

  template<typename T>
  class StaticVector<T,3>{
  public:
  
    StaticVector(const T& x,const T& y, const T& z){
      _data[0]=x;
      _data[1]=y;
      _data[2]=z;
    }
  };

  template<typename T>
  class QuaternionOperations{
  public:

    inline static void fromAngularVelocity(StaticVector<T,4> & qDot, const Vector3D & omega, const StaticVector<T,4> & orientation){
        
      qDot.w()=0;
      qDot.x()=omega(0);
      qDot.y()=omega(1);
      qDot.z()=omega(2);  
      qDot = 0.5*qDot*orientation;
    }
    inline static void  toAngularVelocity(Vector3D & result,const StaticVector<T,4>& qDot, const StaticVector<T,4> & orientation){
      Quaternion conj = orientation.conjugate();
      Quaternion omegaTilde = 2*conj*qDot;
      result(0)=omegaTilde.x();
      result(1)=omegaTilde.y();
      result(2)=omegaTilde.z();
    }
    inline static void matrixQ(Matrix4x3 & result, const StaticVector<T,4> & q){      
      result(0,0) =-q(1); 
      result(0,1) =-q(2);
      result(0,2) =-q(3);  
      result(1,0) = q(0); 
      result(1,1) =-q(3);
      result(1,2) = q(2);
      result(2,0) = q(3); 
      result(2,1) = q(0);
      result(2,2) =-q(1);
      result(3,0) =-q(2); 
      result(3,1) = q(1);
      result(3,2) = q(0);      
    }
  
  static inline void conjugate(StaticVector<T,4> & q_conj, const StaticVector<T,4> & q){

  }
  static inline void toRotationMatrix(Matrix3x3 & R, const StaticVector<T,4> & q){

  }
  static inline void fromRotationMatrix(StaticVector<T,4> & q, const Matrix3x3 & R){

  }
  static inline void fromAxisAngle(StaticVector<T,4> & q, const Vector3D &axis, const Real angle){

  }
  static inline void multiply(const Matrix4x3 & a, const Vector3D & v, StaticVector<T,4> & result){
    result.w()=0;
    result.x()=0;
    result.y()=0;
    result.z()=0;
    for(int i=0; i < 3; i++){
      result.w() += v(i)*a(0,i);
      result.x() += v(i)*a(1,i);
      result.y() += v(i)*a(2,i);
      result.z() += v(i)*a(3,i);
    }
  }

};
  }
}


