#pragma once
#include <config.h>
#include <math.matrix/operations/MatrixCoefficientAccess.h>
#include <math.matrix/operations/MatrixRowCount.h>
#include <math.matrix/operations/MatrixColumnCount.h>

namespace nspace{

  /**
   * \brief Adds. lhs1:= rhs1+rhs2.
   *
   * \param [in,out]  lhs The left hand side.
   * \param rhs1          The first right hand side.
   * \param rhs2          The second right hand side.
   */
  template<typename LHS, typename RHS1, typename RHS2> void add(LHS & lhs, const RHS1 & rhs1, const RHS2 & rhs2);

  /**
   * \brief Adds rhs1 + rhs2 and returns the resulting matrix
   *
   * \param rhs1  The first right hand side.
   * \param rhs2  The second right hand side.
   *
   * \return  the resulting matrix.
   */
  template<typename T>  T add(const T & rhs1, const T& rhs2);


  /**
   * \brief Matrix addition .
   */
  template<typename Sum, typename Summand1, typename Summand2>
  class MatrixAddition{
  public:

    /**
     * \brief Operation adds the a and b into sum.  this is done recursively if need be until scalars are reached
     *
     * \param [in,out]  sum Number of.
     * \param a             The const Summand1 &amp; to process.
     * \param b             The const Summand2 &amp; to process.
     */
    static inline void operation(Sum & sum, const Summand1 & a, const Summand2 & b){
      auto rowCount = rows(a);
      auto colCount = cols(a);
      // recursion anchor. //@TODO is scalar test
      if(rowCount==1 && colCount==1) {
        coefficient(sum,0,0)=coefficient(a,0,0)+coefficient(b,0,0);
      }
      for(int i=0; i < rowCount; i++){
        for(int j=0; j < colCount; j++){
          add(coefficient(sum,i,j),coefficient(a,i,j),coefficient(b,i,j));
        }
      }
    }
  };

  //Implementation
  template<typename LHS, typename RHS1, typename RHS2>
  void add(LHS & lhs, const RHS1 & rhs1, const RHS2 & rhs2){
    MatrixAddition<LHS,RHS1,RHS2>::operation(lhs,rhs1,rhs2);
  }
  
  template<typename T>
  T add(const T & rhs1, const T& rhs2){
    T lhs;
    resize(lhs,rhs1);
    add(lhs,rhs1,rhs2);
    return lhs;
  }
  








}