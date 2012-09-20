#pragma once

#include <utility.xml/NamedElementParser.h>
#include <simulation.model/builder/ModelBuilderHolder.h>
#include <core/Node.h>
#include <utility.reader.urdf/parsers/PrimitiveParsers.h>
#include <utility.reader.urdf/parsers/ConnectParser.h>

namespace nspace{

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