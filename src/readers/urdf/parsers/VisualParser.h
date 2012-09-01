#pragma once
#include <urdfreader/parsers/general/NamedElementParser.h>
#include <urdfreader/parsers/urdf/OriginParser.h>
#include <urdfreader/parsers/urdf/GeometryParser.h>
#include <urdfreader/parsers/urdf/MaterialParser.h>

namespace mbslib{
class VisualParser : public NamedElementParser{
public:
  VisualParser():NamedElementParser("visual"){}
  OriginParser origin;
  GeometryParser geometry;
  MaterialParser material;
protected:
  virtual bool parseNamedElement(XMLElement * visualElement){
    origin.parse(visualElement);
    geometry.parseChildrenOf(visualElement);
    material.parseChildrenOf(visualElement);
    return true;
  }
};

}