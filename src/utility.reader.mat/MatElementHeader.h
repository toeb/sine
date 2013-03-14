#pragma once
#include <core.reflection.h>
#include <memory>
#include <utility.reader.mat/MatUtilities.h>

namespace nspace{
  
struct MatFile;
struct ElementHeader{  
  enum Type{
    miINT8=1,
    miUINT8=2,
    miINT16=3,
    miUINT16=4,
    miINT32=5,
    miUINT32=6,
    miSINGLE=7,
    miDOUBLE=9,
    miINT64=12,
    miUINT64=13,
    miMATRIX=14,
    miCOMPRESSED=15,
    miUTF8=16,
    miUTF16=17,
    miUTF32=18,
    miUnknown=9999
  };
  Type type;
  uint32 byteSize;  

  ElementHeader(){}
  ElementHeader(std::shared_ptr<MatFile> owner):_Owner(owner){}
  typedef std::shared_ptr<MatFile> basic_property(Owner);
 
  friend std::ostream & operator<<(std::ostream & out, const ElementHeader & header){
    out << header.byteSize << "B "<<header.type;
    return out;
  }
  reflect_type(ElementHeader)
};
}