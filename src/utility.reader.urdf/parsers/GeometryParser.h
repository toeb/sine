#pragma once
#include <utility.xml/NamedElementParser.h>
namespace nspace{

class GeometryParser:public NamedElementParser{
public:
  GeometryParser():NamedElementParser("geometry"){
    
  }
protected:
  virtual bool parseNamedElement(XMLElement * geometryNode){
    return true;
  }
};
}