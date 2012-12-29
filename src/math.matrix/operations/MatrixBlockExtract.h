#pragma once

#include <config.h>

namespace nspace{
  template<typename BlockType, typename SourceType>
  class MatrixBlockExtract{
  public:
    static inline void operation(BlockType  & target, const SourceType & source, uint rowOffset, uint colOffset){
      if(target.rows()+rowOffset > source.rows()){
        /*ERROR("range exceed matrix dimension");*/
        return;
      }
      if(target.cols()+colOffset > source.cols()){
        /*      ERROR("range exceed matrix dimension");*/
        return;
      }
      for(uint i=0; i < target.rows(); i++){
        for(uint j=0; j < target.cols(); j++){
          target(i,j) = source(i+rowOffset,j+colOffset);
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
}
