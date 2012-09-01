#pragma once
#include <utility/xml/ElementParser.h>
#include <readers/urdf/structs/MassConfiguration.h>
#include <readers/urdf/parsers/MassParser.h>
#include <readers/urdf/parsers/InertiaParser.h>

namespace nspace{


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