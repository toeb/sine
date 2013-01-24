#pragma once
#include <utility.xml/NamedChildParser.h>
#include <simulation.model/builder/ModelBuilderHolder.h>
#include <core/graph/Node.h>
namespace nspace{
  class ChildLinkParser : public NamedChildParser, public ModelBuilderHolder{
  public:
    ChildLinkParser(IModelBuilder & builder):NamedChildParser("child"),ModelBuilderHolder(builder), node(0){
    }
    std::string name;
    ModelNode * node;
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
