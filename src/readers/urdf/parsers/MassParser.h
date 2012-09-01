#pragma once
#include <urdfreader/parsers/general/NamedChildParser.h>
#include <simulation/math/types.h>


namespace mbslib{

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