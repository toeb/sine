#pragma once
#include <simulation/access/MatrixValue.h>
namespace nspace{

template<typename Derived>
class TypedMatrixValue : public MatrixValue{
private:
  Derived & _matrix;
public:

  TypedMatrixValue(Derived & mat):_matrix(mat){
    
  }


  virtual int rows() const
  {
    return _matrix.rows();
  }

  virtual int cols() const
  {
    return _matrix.cols();
  }

  virtual Real & value( int i, int j ) 
  {
    return  _matrix(i,j);
  }

  virtual const Real value( int i, int j ) const
  {
   return _matrix(i,j);
  }

};
}
