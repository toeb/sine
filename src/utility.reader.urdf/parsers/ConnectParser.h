#pragma once
#include <utility.xml/NamedElementParser.h>
#include <simulation.model/builder/ModelBuilderHolder.h>
#include <core/Node.h>

namespace nspace{
class ConnectParser: public NamedElementParser, public ModelBuilderHolder{
  Node & _connectionNode;
public:
  ConnectParser(IModelBuilder & builder, Node & connectionNode) : 
      NamedElementParser("connect"), 
        ModelBuilderHolder(builder),
        _connectionNode(connectionNode){

  }
protected:
   bool parseNamedElement(XMLElement * element){

     const char * cstr = element->Attribute("connector");
     if(!cstr)return false;
     std::string connectorName = cstr;

     Node * connectorNode = model().nodes()(connectorName);
     if(!connectorNode)return false;

     _connectionNode.predecessors().add(connectorNode);

     return true;
   }
};
}