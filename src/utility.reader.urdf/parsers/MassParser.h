#pragma once
#include <utility.xml/NamedChildParser.h>
#include <math/core.h>


namespace nspace{

class MassParser : public NamedChildParser{
public:
  MassParser():NamedChildParser("mass"){}
  Real mass;
protected:
  bool parseChild(XMLElement * massElement){   
    return massElement->QueryDoubleAttribute("value",&mass)==0;
  }  
};
}