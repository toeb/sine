#pragma once

#include <urdfreader/parsers/general/NamedElementParser.h>
#include <urdfreader/ModelBuilderHolder.h>
#include <urdfreader/common/Node.h>
#include <urdfreader/parsers/urdf/PrimitiveParsers.h>
#include <urdfreader/parsers/urdf/ConnectParser.h>

namespace mbslib{

class ConnectionParser: public NamedElementParser, public ModelBuilderHolder{
public:
  ConnectionParser(IModelBuilder & builder) : NamedElementParser("connection"), ModelBuilderHolder(builder){
    
  }
protected:
   bool parseNamedElement(XMLElement * element){
     Node * connectionNode = new Node;
     parseName(connectionNode,element);

     ConnectParser p(builder(),*connectionNode);
     p.parseChildrenOf(element);

     model().nodes()|=connectionNode;
     return true;
   }
};

}