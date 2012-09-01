#pragma once

#include <utility/xml/NamedChildParser.h>
#include <readers/urdf/structs/UrdfOrigin.h>
#include <readers/urdf/parsers/PrimitiveParsers.h>

namespace nspace{



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