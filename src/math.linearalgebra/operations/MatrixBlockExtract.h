#pragma once

#include <config.h>

namespace nspace{
template<typename BlockType, typename SourceType>
  class MatrixBlockExtract{
  public:
    static inline void operation(BlockType  & target, const SourceType & source, uint rowOffset, uint colOffset){
      if(target.rows()+rowOffset > source.rows()){
        ERROR("range exceed matrix dimension");
        return;
      }
      if(target.cols()+colOffset > source.cols()){
        ERROR("range exceed matrix dimension");
        return;
      }
      for(uint i=rowOffset; i < rowOffset+target.rows(); i++){
        for(uint j=colOffset; j < colOffset+target.cols(); j++){
          target(i,j) = source(i,j);
        }
      }
    }
  };
}