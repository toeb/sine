#pragma once

#include <readers/urdf/parsers/ParentLinkParser.h>
#include <readers/urdf/structs/UrdfConnector.h>

namespace nspace{
class ConnectorParser:public NamedElementParser, public ModelBuilderHolder{
public:
  ConnectorParser(IModelBuilder & builder) : NamedElementParser("connector"), ModelBuilderHolder(builder){

  }
protected:
  bool parseNamedElement(XMLElement * element){
    Node * connectorNode = new Node;
    parseName(connectorNode,element);

    // get parent element of connector
    ParentLinkParser parent(builder());
    parent.parse(element);

    // parent node is neaded
    if(!parent.node){
      ERROR("could not find parent '"<< parent.name <<"' of connector "<<connectorNode->name());
      return false;
    }
    
    // get origin
    OriginParser origin;
    origin.parse(element);
    
    // create connector struct and add to node
    UrdfConnector * connector = new UrdfConnector;
    connectorNode->set("urdfconnector", connector);
    
    // set connector data
    connector->origin = origin.origin;
    
    // add connector to parent as successor
    *parent.node >> connectorNode;
    
    //add connector to models node list
    model().nodes() |= connectorNode;   
    
    return true;
  }
};
}