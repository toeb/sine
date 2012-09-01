#pragma once
#include <urdfreader/parsers/general/NamedChildParser.h>
#include <urdfreader/ModelBuilderHolder.h>
#include <urdfreader/common/Node.h>
namespace mbslib{

class ChildLinkParser : public NamedChildParser, public ModelBuilderHolder{
public:
  ChildLinkParser(IModelBuilder & builder):node(0),ModelBuilderHolder(builder), NamedChildParser("child"){

  }
  std::string name;
  Node * node;
protected:
  bool parseChild(XMLElement * childElement){
    const char * cstr = childElement->Attribute("link");
    if(!cstr)return false;
    name = cstr;

    //lookup node in model
    node =model().nodes()(name);
    return true;
  }
};
}