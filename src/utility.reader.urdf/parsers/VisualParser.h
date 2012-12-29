#pragma once
#include <utility.xml/NamedElementParser.h>
#include <utility.reader.urdf/parsers/OriginParser.h>
#include <utility.reader.urdf/parsers/GeometryParser.h>
#include <utility.reader.urdf/parsers/MaterialParser.h>

namespace nspace{
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