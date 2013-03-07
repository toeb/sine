#pragma once

#include <utility.reader.h>
#include <utility.reader.mesh/IMeshBuilder.h>

namespace nspace{
  


  class MeshReader : public Reader{
    reflect_type(MeshReader);
    reflect_superclasses(Reader);

    typedef IMeshBuilder* reflect_property(Builder);
    
  public:
    MeshReader():_Builder(0){}
  protected:
    IMeshBuilder & builder(){return *getBuilder();}
    bool doRead(){
      if(!getBuilder())return false;
      return readMesh(*getBuilder());
    } 
    virtual bool readMesh(IMeshBuilder & meshBuilder)=0;
  };
}