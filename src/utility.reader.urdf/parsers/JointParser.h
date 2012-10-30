#pragma once
#include <utility.reader.urdf/structs/UrdfJoint.h>
#include <utility.xml/NamedElementParser.h>
#include <simulation.model/builder/ModelBuilderHolder.h>
#include <utility.reader.urdf/parsers/ChildLinkParser.h>
#include <utility.reader.urdf/parsers/AxisParser.h>

namespace nspace{

class JointParser : public NamedElementParser, public ModelBuilderHolder{
private:
public:
  JointParser(IModelBuilder & builder):NamedElementParser("joint"),ModelBuilderHolder(builder){

  }
protected:
   virtual bool parseNamedElement(XMLElement * jointElement){
     
     //create two connectors and a connetion 
     ModelNode * connectorA = new ModelNode;
     ModelNode * connectorB = new ModelNode;
     ModelNode * connection = new ModelNode;

     UrdfJoint * joint = new UrdfJoint;
     UrdfLink * parentLink;
     UrdfLink * childLink;


     //set name of joint
     parseName(connection,jointElement);

     // get type string 
     const char * cstr = jointElement->Attribute("type");
     if(!cstr){
//       ERROR(" no type specified for joint " << connection->name() );
       return false;
     }
     joint->type = cstr;
     
     // get child and parent urdf links
     ParentLinkParser parent(builder());
     ChildLinkParser child(builder());
     parent.parse(jointElement);
     child.parse(jointElement);

     if(!child.node) {
     //  ERROR("No child node found joint "<<connection->name());
       return false;
     }
     if(!parent.node) {
//       ERROR("No parent node found joint "<<connection->name());
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
     
     // parse joint limits  (yeah, i know its redundant but for completeness both the urdflimits and 
     //TODO put this into another parser class
     XMLElement * limitsElement = jointElement->FirstChildElement("limit");
     if(limitsElement){
       JointLimit * limits = new JointLimit;
       UrdfJointLimits * urdfLimits = new UrdfJointLimits;

       if(limitsElement->Attribute("effort")){
         limits->effort() = limitsElement->DoubleAttribute("effort");
         urdfLimits->effortLimit = limitsElement->DoubleAttribute("effort");
       }

       if(limitsElement->Attribute("velocity")){
         limits->velocity() = limitsElement->DoubleAttribute("velocity");
         urdfLimits->velocityLimit = limitsElement->DoubleAttribute("velocity");
       }

       if(limitsElement->Attribute("lower")){
         limits->lowerPosition() = limitsElement->DoubleAttribute("lower");
         urdfLimits->lowerPositionLimit = limitsElement->DoubleAttribute("lower");
       }

       if(limitsElement->Attribute("upper")){
         limits->upperPosition() = limitsElement->DoubleAttribute("upper");
         urdfLimits->upperPositionLimit = limitsElement->DoubleAttribute("upper");
       }

       joint->limits = urdfLimits;

       

       
     }


     //set urdf joint and link structs
     connection->set("urdfjoint",joint);




     //add created nodes to the model
     model().nodes() |= connection,connectorA,connectorB;


     return true;
  }
};
}