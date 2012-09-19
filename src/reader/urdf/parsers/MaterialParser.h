#pragma once
#include <utility/xml/NamedElementParser.h>

namespace nspace{
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