#pragma once
namespace mbslib{


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