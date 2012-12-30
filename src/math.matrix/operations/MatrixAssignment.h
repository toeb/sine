/**
 * Copyright (C) 2013 Tobias P. Becker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the  rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More information at: https://dslib.assembla.com/
 *
 */
#pragma once
#include <config.h>

#include <math.matrix/operations/MatrixIndexType.h>
#include <math.matrix/operations/MatrixRowCount.h>
#include <math.matrix/operations/MatrixColumnCount.h>
#include <math.matrix/operations/MatrixDimensionCheck.h>
#include <math.matrix/operations/MatrixCoefficientAccess.h>

namespace nspace {
  /**
   * \brief Matrix assign.
   *        the default implementation checks for dimension match and returns false if the dimensions do not match
   *        then every coefficient is copied in a boxed for loop
   */
  template<typename LHS, typename RHS>
  class OperationMatrixAssign {
public:

    /**
     * \brief Operations.
     *
     * \param [in,out]  lhs The left hand side.
     * \param rhs           The right hand side.
     *
     * \return  true if it succeeds, false if it fails.
     */
    static inline bool operation(LHS &  lhs, const RHS & rhs){
      if(!dimensionsMatch(lhs,rhs)) return false;
      indexTypeOfType(RHS) rowCount = rows(rhs);
      indexTypeOfType(RHS) colCount = cols(rhs);
      for(indexTypeOfType(RHS) i=0; i < rowCount; i++) {
        for(indexTypeOfType(RHS) j=0; j < colCount; j++) {
          coefficient(lhs,i,j) = coefficient(rhs,i,j);
        }
      }
      return true;
    }
  };

  /**
   * \brief Assign matrix. operation for assigning matrices
   *
   * \tparam  typename LHS  Type of the typename left hand side.
   * \tparam  typename RHS  Type of the typename right hand side.
   * \param [in,out]  lhs The left hand side.
   * \param rhs           The right hand side.
   *
   * \return  true if it succeeds, false if it fails.
   */
  template<typename LHS,typename RHS> inline bool assignMatrix(LHS & lhs, const RHS & rhs){
    return OperationMatrixAssign<LHS,RHS>::operation(lhs,rhs);
  }

/**
 * \brief A macro that specializes the OperationMatrixAssign for LHS and RHS types.
 *        be sure to return true if the assignement was successfull . else false is returned by default
 *        this only works for types that do not contains commas
 *
 * \param LHS             The left hand side matrix.
 * \param RHS             The right hand side matrix.
 * \param ASSIGNMENTCODE  The assignmentcode.
 */
#define BeginSpecializeMatrixAssign(LHS,RHS) class OperationMatrixAssign<LHS,RHS>{public: static inline bool operation(LHS & lhs, const RHS &rhs)
#define EndSpecializeMatrixAssign };

}
