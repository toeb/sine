#pragma once
#include <common/Config.h>

namespace nspace{

//   template<typename OutputMatrix, typename MatrixFactorA, typename MatrixFactorB,typename Operation>
//   class MatrixElementWise{
// 
//   };

template<typename OutputMatrix, typename MatrixFactorA, typename MatrixFactorB>
class MatrixMultiplyElementWise{
public:
  static inline void operation(OutputMatrix & c, const MatrixFactorA & a, const MatrixFactorB &  b){
    if(a.rows()!=b.rows()||a.cols()!=b.cols())return;
    c.resize(a.rows(), a.cols(),false);
    for(int i=0; i < a.rows();i++){
      for(int j=0; j < a.cols();j++){
        c(i,j)=a(i,j)*b(i,j);
      }
    }
  }
};

  template<typename OutputMatrix, typename InputMatrix>
  class MatrixExtractBlock{
  public:
    static inline void operation(OutputMatrix & result, const InputMatrix & original, uint startRow, uint startCol, uint rows, uint cols){
      result.resize(rows,cols,false);
      if(original.rows()<rows+startRow)return;
      if(original.cols()<cols+startCol)return;
      for(int i=0; i < rows;i++ ){
        for(int j=0; j < cols; j++){
          result(i,j) = original(i+startRow,j+startCol);
        }
      }
    }
  };


  template<typename FilteredMatrix, typename InputMatrix, typename FilterFunction, typename FilterFunctionArgument>
  class MatrixFilter{
  public:
    static inline void operation(FilteredMatrix & result, const InputMatrix & g, FilterFunction f, uint filterWidth, uint filterHeight){
      uint gx = g.cols();
      uint gy = g.rows();
      uint fx2 = filterWidth/2;
      uint fy2 = filterHeight/2;
      uint rx = gx-filterWidth+1;
      uint ry = gy-filterHeight+1;
      FilterFunctionArgument current;
      result.resize(ry,rx,false);
      current.resize(filterHeight,filterWidth,false);
      for(int i= 0; i < ry; i++){
        for(int j=0; j < rx; j++){
          g.block(current,i,j);
         // MatrixExtractBlock<FilterFunctionArgument, InputMatrix>::operation(current,g,i,j,filterHeight,filterWidth);
          f(result(i,j),current);
        }
      }
    }
  };
  template< typename OutputMatrix, typename InputMatrix, typename FilterMatrix,typename T>
  class MatrixConvolution{
  public:
    static inline void operation(OutputMatrix & r, const InputMatrix & g, const FilterMatrix & f  ){
      uint fx = f.cols();
      uint fy = f.rows();
      MatrixFilter<OutputMatrix,InputMatrix,std::function<void (T & , FilterMatrix&) >,FilterMatrix>::operation(
        OutputMatrix, g, [&f](T & val, FilterMatrix & window){
        MatrixMultiplyElementWise<FilterMatrix,FilterMatrix,FilterMatrix>::operation(window,window,f);

      },fx,fy);
    }
  };
}