#pragma once
#include <config.h>
#include <core/Serialization.h>
#include <core/reflection/Type.h>
#ifndef MATRIX_CLASSES
#define MATRIX_CLASSES 2
#endif
#if MATRIX_CLASSES ==1 

#elif MATRIX_CLASSES == 2
#include <math.matrix.dslib/types.h>

namespace nspace{
typedef nspace::math::dslib::Vector2D   Vector2D;
typedef nspace::math::dslib::Vector3D   Vector3D;
typedef nspace::math::dslib::Matrix3x3  Matrix3x3;
typedef nspace::math::dslib::Matrix2x2  Matrix2x2;
typedef nspace::math::dslib::Matrix4x4  Matrix4x4;
typedef nspace::math::dslib::Matrix4x3  Matrix4x3;
typedef nspace::math::dslib::Matrix3x4  Matrix3x4;
typedef nspace::math::dslib::Quaternion Quaternion;
typedef nspace::math::dslib::VectorND   VectorND;
typedef nspace::math::dslib::MatrixNxM  MatrixNxM;

META(nspace::math::dslib::Vector2D  );
META(nspace::math::dslib::Vector3D  );
META(nspace::math::dslib::Matrix3x3 );
META(nspace::math::dslib::Matrix2x2 );
META(nspace::math::dslib::Matrix4x4 );
META(nspace::math::dslib::Matrix4x3 );
META(nspace::math::dslib::Matrix3x4 );
META(nspace::math::dslib::Quaternion);
//META(nspace::math::dslib::VectorND  );
META(nspace::math::dslib::MatrixNxM );

}
#elif MATRIX_CLASSES == 3
#include <math.matrix.dslib/types.h>
#include <math.matrix.eigen/types.h>

namespace nspace{
  typedef nspace::math::eigen::Vector2D   Vector2D;
  typedef nspace::math::eigen::Vector3D   Vector3D;
  typedef nspace::math::eigen::Matrix3x3  Matrix3x3;
  typedef nspace::math::eigen::Matrix2x2  Matrix2x2;
  typedef nspace::math::eigen::Matrix4x4  Matrix4x4;
  typedef nspace::math::eigen::Matrix4x3  Matrix4x3;
  typedef nspace::math::eigen::Matrix3x4  Matrix3x4;
  typedef nspace::math::dslib::Quaternion Quaternion;
  typedef nspace::math::eigen::VectorND   VectorND;
  typedef nspace::math::eigen::MatrixNxM  MatrixNxM;
}
#endif

namespace nspace{
  
SERIALIZERS(Vector3D, 
  stream<<(*value)(0) <<" "<< (*value)(1)<<" " << (*value)(2),
  stream >> (*value)(0) >> (*value)(1) >> (*value)(2) 
  )
SERIALIZERS(Vector2D, stream<<(*value)(0) <<" "<< (*value)(1), stream >> (*value)(0) >> (*value)(1) )
  
  namespace math{



    namespace operators{
      inline Vector3D operator ^ (const Vector3D & a, const Vector3D & b){
        Vector3D result;
        shorthands::matrix::crossProduct(result, a,b);
        return result;
      }
    
    }
  }
}

