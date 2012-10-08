#pragma once
#include <utility.xml/NamedChildParser.h>
#include <simulation.model/builder/ModelBuilderHolder.h>
#include <core/Node.h>

namespace nspace{


// parses the passed xml node and extracts the link attribute. then looks up the correct node in the model
class ParentLinkParser : public NamedChildParser, public ModelBuilderHolder{
public:
  std::string name;
  ModelNode * node;

  ParentLinkParser(IModelBuilder & builder):node(0),ModelBuilderHolder(builder), NamedChildParser("parent"){

  }
protected:
  bool parseChild(XMLElement * parentElement){
    const char * cstr = parentElement->Attribute("link");
    if(!cstr)return false;
    name = cstr;
    node =model().nodes()(name);
    return true;
  }
};
}