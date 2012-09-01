#pragma once

#include <urdfreader/parsers/general/NamedElementParser.h>
#include <urdfreader/ModelBuilderHolder.h>
#include <simulation/kinematics/CoordinateSystem.h>
#include <urdfreader/parsers/general/CompositeChildParser.h>
#include <urdfreader/parsers/urdf/OriginParser.h>

namespace mbslib{
  
class RootLinkParser : public NamedElementParser, public ModelBuilderHolder{
private:
  CoordinateSystem _coordinates;
  CompositeChildParser _compositeChildParser;
public:
  RootLinkParser(IModelBuilder & builder):NamedElementParser("root"),ModelBuilderHolder(builder){    

  }
protected:
  bool parseNamedElement(tinyxml2::XMLElement * root){
    const char * linkText = root->Attribute("link");
    if(!linkText)return false;
    std::string linkString = linkText;
    
    const char * typeText = root->Attribute("type");
    if(!typeText)return false;
    std::string typeString = typeText;


    Node * rootNode = model().nodes()(linkString);
    if(!rootNode){
      ERROR("Could not find Node by name of " << linkString);
      return false;
    }

    OriginParser origin;
    origin.parse(root);

    model().set("origin",origin.origin);
    model().set("basetype", typeString);
    model().set("root", rootNode);

    bool result =  _compositeChildParser.parse(root);
    return result;
  }
};
}
