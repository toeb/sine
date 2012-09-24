#pragma once

#include <utility.xml/NamedElementParser.h>
#include <simulation.model/builder/ModelBuilderHolder.h>
#include <core/Node.h>
#include <utility.reader.urdf/parsers/PrimitiveParsers.h>
#include <utility.reader.urdf/parsers/ConnectParser.h>
#include <utility.reader.urdf/structs/ExtendedUrdfSpring.h>
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

     XMLElement * typeElement = element->FirstChildElement("type");
     if(typeElement){
       XMLElement * springElement = typeElement->FirstChildElement("spring");
       if(springElement){
         ExtendedUrdfSpring * urdfSpring = new ExtendedUrdfSpring;
         
         if(springElement->Attribute("length")){
           urdfSpring->length = springElement->DoubleAttribute("length");
         }
         urdfSpring->k = springElement->DoubleAttribute("k");
         urdfSpring->d = springElement->DoubleAttribute("d");

         connectionNode->set("urdfspring",urdfSpring);
       }
     }

     model().nodes()|=connectionNode;
     return true;
   }
};

}