#pragma once
#include <readers/urdf/structs/UrdfJoint.h>
#include <utility/xml/NamedElementParser.h>
#include <simulation/model/builder/ModelBuilderHolder.h>
#include <readers/urdf/parsers/ChildLinkParser.h>
#include <readers/urdf/parsers/AxisParser.h>

namespace nspace{

class JointParser : public NamedElementParser, public ModelBuilderHolder{
private:
public:
  JointParser(IModelBuilder & builder):NamedElementParser("joint"),ModelBuilderHolder(builder){

  }
protected:
   virtual bool parseNamedElement(XMLElement * jointElement){
     
     //create two connectors and a connetion 
     Node * connectorA = new Node;
     Node * connectorB = new Node;
     Node * connection = new Node;

     UrdfJoint * joint = new UrdfJoint;
     UrdfLink * parentLink;
     UrdfLink * childLink;


     //set name of joint
     parseName(connection,jointElement);

     // get type string 
     const char * cstr = jointElement->Attribute("type");
     if(!cstr){
       ERROR(" no type specified for joint " << connection->name() );
       return false;
     }
     joint->type = cstr;
     
     // get child and parent urdf links
     ParentLinkParser parent(builder());
     ChildLinkParser child(builder());
     parent.parse(jointElement);
     child.parse(jointElement);

     if(!child.node) {
       ERROR("No child node found joint "<<connection->name());
       return false;
     }
     if(!parent.node) {
       ERROR("No parent node found joint "<<connection->name());
       return false;
     }
     // get the link structs from parent and child node (not needed currently)
     parent.node->get(parentLink,"urdflink");
     child.node->get(childLink,"urdflink");
               
     //get origin of joint
     OriginParser originParser;
     originParser.parse(jointElement);
     Origin origin= originParser.origin;
     joint->origin = origin;

     //get axis of joint
     AxisParser axisParser;
     axisParser.parse(jointElement);
     Vector3D axis = axisParser.direction;
     axis.normalize();
     joint->axis = axis;

     //set connector names
     connectorA->setName("connector_"+parent.node->name()+"_"+child.node->name());
     connectorB->setName("connector_"+child.node->name()+"_"+parent.node->name());
     
     // set parent as predecessor of connector a
     *connectorA << parent.node;
     //set child as successor of connector b
     *connectorB >> child.node;
     
     //set connection as successor of connector a and predecessor of connectorb
     *connection << connectorA >> connectorB;
     
     //set urdf joint and link structs
     connection->set("urdfjoint",joint);

     //add created nodes to the model
     model().nodes() |= connection,connectorA,connectorB;


     return true;
  }
};
}