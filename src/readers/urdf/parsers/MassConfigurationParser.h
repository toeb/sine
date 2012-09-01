#pragma once
#include <urdfreader/parsers/general/ElementParser.h>
#include <urdfreader/parsers/urdf/structs/MassConfiguration.h>
#include <urdfreader/parsers/urdf/MassParser.h>
#include <urdfreader/parsers/urdf/InertiaParser.h>

namespace mbslib{


class MassConfigurationParser : public ElementParser{
public:
  MassConfiguration massConfiguration;
  bool parse(XMLElement* element){
    //create mass and inertia parser
    MassParser mass;
    InertiaParser inertia;
    
    //parse children of current element to find mass and inertia nodes
    if(mass.parse(element)) massConfiguration.mass()=mass.mass;
    if(inertia.parse(element)) massConfiguration.inertia() = inertia.inertia;
    return true;
  }
};
}