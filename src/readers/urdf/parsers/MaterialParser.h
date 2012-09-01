#pragma once
namespace mbslib{
class MaterialParser : public NamedElementParser{
public:
  MaterialParser():NamedElementParser("material"){
    
  }
protected:
  virtual bool parseNamedElement(XMLElement * materialNode){
    return true;
  }
};
}