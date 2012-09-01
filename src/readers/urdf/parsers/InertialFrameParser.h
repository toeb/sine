#pragma once


#include <urdfreader/parsers/general/NamedChildParser.h>
#include <urdfreader/parsers/urdf/MassConfigurationParser.h>
#include <urdfreader/parsers/urdf/OriginParser.h>

namespace mbslib{

class InertialFrameParser : public NamedChildParser{
public:
  InertialFrameParser(){name() ="inertial";}
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