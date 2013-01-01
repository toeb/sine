#pragma once
#include <math.matrix/operations/MatrixTraits.h>

namespace nspace{
/**
 * \brief A convenience macro that calls OPERATION for all default scalar types. (double,float,int,unsigned int, short ....unsigned char)
 *
 * \param OPERATION The operation.
 */
#define FOR_ALL_DEFAULT_SCALAR_TYPES(OPERATION) OPERATION(double); OPERATION(float); OPERATION(int); OPERATION(unsigned int); OPERATION(short); OPERATION(unsigned short); OPERATION(char) ; OPERATION(unsigned char);

  /**
   * \brief Define Scalar Matrix Trait fro default scalars
   *
   */
  FOR_ALL_DEFAULT_SCALAR_TYPES(DefineScalarTrait);

}