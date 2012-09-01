#pragma once

#include <urdfreader/parsers/general/NamedChildParser.h>
#include <urdfreader/parsers/urdf/structs/Origin.h>
#include <urdfreader/parsers/urdf/PrimitiveParsers.h>

namespace mbslib{



class OriginParser : public NamedChildParser{

public:
  OriginParser():NamedChildParser("origin"){
    
  }
  Origin origin;
protected:
  bool parseChild(tinyxml2::XMLElement * originElement){    
    if(!parseVector(origin.xyz, originElement->Attribute("xyz")))return false;
    if(!parseVector(origin.rpy, originElement->Attribute("rpy")))return false;
    return true;
  }

};
}