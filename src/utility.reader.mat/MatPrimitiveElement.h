#pragma once
#include <utility.reader.mat/MatElement.h>
namespace nspace{
  
template<typename T>
struct MatPrimitiveElement : public MatElement{
  bool doLoad()override final{
    return false;
  }

  typedef std::vector<T> reflect_property(Array);
  reflect_type(MatPrimitiveElement<T>)
};
}