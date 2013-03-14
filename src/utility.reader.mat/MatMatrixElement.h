#pragma once
#include <utility.reader.mat/MatElement.h>
namespace nspace{
  

struct MatMatrixElement : public MatElement{

enum Class{
  mxCELL_CLASS=1,
  mxSTRUCT_CLASS=2,
  mxOBJECT_CLASS=3,
  mxCHAR_CLASS=4,
  mxSPARSE_CLASS=5,
  mxDOUBLE_CLASS=6,
  mxSINGLE_CLASS=7,
  mxINT8_CLASS=8,
  mxUINT8_CLASS=9,
  mxINT16_CLASS=10,
  mxUINT16_CLASS=11,
  mxINT32_CLASS=12,
  mxUINT32_CLASS=13,
  mxINT64_CLASS=14,
  mxUINT64_CLASS=15
};
  bool doLoad()override final;

};

}