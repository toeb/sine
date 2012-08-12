#pragma once
#include <common/Config.h>

namespace nspace{


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


  

  template<typename T,typename Mat>
  class MatrixSum{
  public:
    static inline void operation(T & result, const Mat & mat){
      result =0;
      for(int i=0; i < mat.rows(); i++){
        for(int j=0; j < mat.cols(); j++){
          result = result + mat(i,j);
        }
      }
    }
  };

  template<typename OutputMat, typename InputMat>
  class MatrixPad{
  public: 
    static inline void operation(OutputMat & out, const InputMat & input, uint rowsTop, uint rowsBottom, uint colsLeft, uint colsRight){
      out.resize(input.rows()+rowsTop+rowsBottom,input.cols()+colsLeft+colsRight,true);
      for(int i=0; i< input.rows(); i++){
        for(int j=0; j < input.cols(); j++){
          out(i+rowsTop,j+colsLeft) = input(i,j);
        }
      }
    }
  };



  template< typename OutputMatrix, typename InputMatrix, typename KernelMatrix,typename T>
  class MatrixConvolution{
  public:
    static inline void operation(OutputMatrix & r, const InputMatrix & g, const KernelMatrix & kernel  ){
      uint fx = kernel.cols();
      uint fy = kernel.rows();
      uint rx = g.cols()-fx+1;
      uint ry = g.rows()-fy+1;

      KernelMatrix window;
      window.resize(fy,fx);
      r.resize(ry,rx);
      for(int i=0; i < ry; i++){
        for(int j=0; j < rx; j++){
          T sum=0.0;
          for(int l = 0; l < fy; l++){
            for(int k =0; k < fx; k++){
              sum = sum + g(i+l,j+k)*kernel(l,k);
            }
          }
          r(i,j)=sum;

        }
      }

    }
  };
}