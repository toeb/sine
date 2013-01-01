#pragma once
#include <config.h>
namespace nspace{

  /**
   * \brief Matrix type selector.  this class allows to choose what type to return when to input types are involved
   *        the default implementation will always choose the first type
   *        this class may be specialized e.g. scalar vs matrix selection
   */
  template<typename A, typename B>
  class MatrixTypeSelector{
  public:
    typedef A Type;
  };

/**
 * \brief A macro that defines return type for an operation with two types
 *        e.g. returnType(int,double) should return double
 *
 * \param A The void to process.
 * \param B The void to process.
 */
#define returnType(A,B) MatrixTypeSelector<A,B>::Type

/**
 * \brief A macro that specializes the return type for an operation of two types.
 *
 * \param TYPEA       The typea.
 * \param TYPEB       The typeb.
 * \param RESULTTYPE  The resulttype.
 */
#define SpecializeTypeSelector(TYPEA, TYPEB, RESULTTYPE) template<> class MatrixTypeSelector<TYPEA,TYPEB> {public: typedef RESULTTYPE Type;};
#define SpecializeTypeSelectorPartially(TYPEA,TYPEB, RESULTTYPE) class MatrixTypeSelector<TYPEA,TYPEB> {public: typedef typename RESULTTYPE Type;};

  
template<typename MatrixType> SpecializeTypeSelectorPartially(MatrixType, double, MatrixType);
template<typename MatrixType> SpecializeTypeSelectorPartially(double , MatrixType, MatrixType);

}