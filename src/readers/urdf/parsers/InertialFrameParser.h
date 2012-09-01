#pragma once


#include <utility/xml/NamedChildParser.h>
#include <readers/urdf/parsers/MassConfigurationParser.h>
#include <readers/urdf/parsers/OriginParser.h>

namespace nspace{

class InertialFrameParser : public NamedChildParser{
public:
  InertialFrameParser():NamedChildParser("inertial"){}
  MassConfiguration massConfiguration;
  Origin origin;
protected:
  virtual bool parseChild(XMLElement * inertialElement){
    //create massconfig and origin parser
    MassConfigurationParser mass;
    OriginParser originParser;
    //parse children of inertial element
    originParser.parse(inertialElement);
    mass.parse(inertialElement);
    //set mass config and coordinates
    massConfiguration=mass.massConfiguration;
    origin = originParser.origin;
    return true;
  }
};
}