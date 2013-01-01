#pragma once

#include <config.h>

namespace nspace{
    /**
   * \brief Matrix trait for defining that a type is a scalar matrix type
   *        default implementation defines matrix type as non-scalar
   */
  template<typename MatrixType>
  class MatrixTraitIsScalar{
  public:
    static const bool isScalar = false;
  };

/**
 * \brief A macro that defines define matrix scalar trait for a type.
 *
 * \param ISSCALAR  whether or not type is scalar.
 * \param TYPE      the type.
 */
#define DefineMatrixScalarTraits(ISSCALAR,TYPE) template<> class MatrixTraitIsScalar<TYPE>{public: static const bool isScalar = ISSCALAR;};

/**
 * \brief A macro that defines defines scalar trait
 *
 * \param TYPE  The type.
 */
#define DefineScalarTrait(TYPE) DefineMatrixScalarTraits(true,TYPE)

/**
 * \brief A macro that defines defines is scalar trait to false for type.
 *
 * \param TYPE  The type.
 */
#define DefineMatrixTrait(TYPE) DefineMatrixScalarTraits(false,TYPE)

  /**
   * \brief Query if type is a scalar matrix.
   *
   * \tparam  typename MatrixType Type of the matrix .
   *
   * \return  true if scalar matrix, false if not.
   */
  template<typename MatrixType> inline bool isScalarMatrix(){return MatrixTraitIsScalar<typename MatrixType>::isScalar;}

  /**
   * \brief Query if 'matrix' is scalar a matrix.
   *
   * \tparam  typename MatrixType Type of the matrix.
   * \param matrix  The matrix.
   *
   * \return  true if matrix is scalar matrix, false if not.
   */
  template<typename MatrixType> inline bool isScalarMatrix(const MatrixType & matrix){return isScalarMatrix<typename MatrixType>();}



  
}