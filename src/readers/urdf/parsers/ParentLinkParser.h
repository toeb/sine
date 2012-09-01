#pragma once
#include <urdfreader/parsers/general/NamedChildParser.h>
#include <urdfreader/ModelBuilderHolder.h>
#include <urdfreader/common/Node.h>

namespace mbslib{


// parses the passed xml node and extracts the link attribute. then looks up the correct node in the model
class ParentLinkParser : public NamedChildParser, public ModelBuilderHolder{
public:
  std::string name;
  Node * node;

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