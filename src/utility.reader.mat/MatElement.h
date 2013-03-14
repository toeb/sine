#pragma once
#include <utility.reader.mat/MatElementHeader.h>
namespace nspace{  
struct MatElement{
  bool load(ElementHeader header, std::shared_ptr<char> data);

  reflect_type(MatElement); 
  typedef std::shared_ptr<char> reflect_property(RawData);
  typedef ElementHeader reflect_property(Header);
protected:  
  virtual bool doLoad()=0;
};
}