#pragma once
#include <simulation.access/MatrixValue.h>
namespace nspace{
  template<typename Derived>
  class TypedMatrixValue : public MatrixValue{
    REFLECTABLE_OBJECT(TypedMatrixValue);
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
    Derived & value(){return _matrix;}

    const Derived & value()const{
      return _matrix;
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
