#pragma once
#include <utility.reader.mat/MatElement.h>
namespace nspace{
  
struct MatCompressedElement : public MatElement{
  bool doLoad()override final;
  typedef std::shared_ptr<MatElement> reflect_property(UncompressedElement);

  reflect_type(MatCompressedElement);
};

}