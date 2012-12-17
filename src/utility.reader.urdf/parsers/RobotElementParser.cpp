#include "RobotElementParser.h"


#include <utility.reader.urdf/parsers/UrdfExtensionParser.h>
#include <utility.reader.urdf/parsers/LinkParser.h>
#include <utility.reader.urdf/parsers/JointParser.h>
#include <utility.reader.urdf/structs/UrdfConnection.h>

using namespace nspace;
using namespace std;


RobotElementParser::RobotElementParser(IModelBuilder & builder):NamedElementParser("robot"),ModelBuilderHolder(builder){
  _children.composite().add(new UrdfExtensionParser(builder));
  //order is important because joint parser needs the links to be present
  _children.composite().add(new LinkParser(builder));
  _children.composite().add(new JointParser(builder));

}
ModelNode * RobotElementParser::findRoot(){
  return model().get<ModelNode*>("root");
}

void RobotElementParser::convertLink(ModelNode * node){
  UrdfLink * link=0;
  node->get(link,"urdflink");
  if(!link)return;

  Body* body = new Body;
  node->set("body",body);
  body->inertia = link->inertia;
  body->mass = link->mass;

  CoordinateSystem preceedingCoordinates;
  ModelNode * connector = node->predecessors().first();
    
  //get preceeding coordinates if they are set
  if(connector){
    CoordinateSystem preceedingCoordinates;
    connector->get(preceedingCoordinates,"initialcoordinates");
  }

  // get relative coordinates
  CoordinateSystem relativeCoordinates = link->origin;
  CoordinateSystem linkCoordinates;
  preceedingCoordinates.fromObjectCoordinates(relativeCoordinates,linkCoordinates);
  node->set("initialcoordinates",linkCoordinates);
  node->set("relativecoordinates",relativeCoordinates);
    
  if(connector){      
    //calculate connectors offset
    Vector3D offset;
    linkCoordinates.toObjectCoordinates(preceedingCoordinates.position(),offset);
    connector->set("offset",offset);      
  }


}
void RobotElementParser::convertConnector(ModelNode * node){
  UrdfConnector* urdfConnector=0;
  node->get(urdfConnector,"urdfconnector");
  if(!urdfConnector)return;

  //create connector
  Connector * connector = new Connector;
  node->set("connector", connector);

  // get preceeding body (urdfconnector always is a successor)
  ModelNode * body = node->predecessors().first();
  if(!body)return;

  // get body coordinates
  CoordinateSystem bodyCoordinates;
  body->get(bodyCoordinates,"initialcoordinates");
    
  //set relative coordinates of connector
  CoordinateSystem relativeCoordinates= urdfConnector->origin;    
  node->set("relativecoordinates",relativeCoordinates);

  // "calculate" connectors offset vector in object coordinates
  connector->offset() = relativeCoordinates.position();
  node->set("offset",connector->offset());
    
  // calculate initial coordinates of current connector
  CoordinateSystem initialCoordinates;
  bodyCoordinates.fromObjectCoordinates(relativeCoordinates,initialCoordinates);
  node->set("initialcoordinates", initialCoordinates);

}
void RobotElementParser::convertConnection(ModelNode * node){
  UrdfConnection * connection =0;
  node->get(connection,"urdfconnection");
  if(!connection )return;

  //todo: implement
}
void RobotElementParser::convertJoint(ModelNode * node){
  UrdfJoint * joint=0;
  node->get(joint,"urdfjoint");
  if(!joint)return;

  //set connection struct
  Connection * connection = new Connection;
  node->set("connection",connection);

  //set struct info
  connection->axis = joint->axis;
  connection->type = joint->type;

    
  // get connectors and bodies
  ModelNode * connectorNodeA = node->predecessors().first();
  ModelNode * connectorNodeB = node->successors().first();

  Connector * connectorA = new Connector;
  Connector * connectorB = new Connector;
    
  connectorNodeA->set("connector",connectorA);
  connectorNodeB->set("connector",connectorB);

  ModelNode * bodyA = connectorNodeA->predecessors().first();
  ModelNode * bodyB = connectorNodeB->successors().first();


  CoordinateSystem bodyCoordinatesA;
  CoordinateSystem bodyCoordinatesB;
  CoordinateSystem connectorCoordinatesA;
  CoordinateSystem connectorCoordinatesB;
  CoordinateSystem coordinatesJ;

  // get initial coordinates of previous body
  bodyA->get(bodyCoordinatesA,"initialcoordinates");

  // calculate position of connectorA
  CoordinateSystem relativeJointCoordinates = joint->origin;
  bodyCoordinatesA.fromObjectCoordinates(relativeJointCoordinates,connectorCoordinatesA);
  coordinatesJ = connectorCoordinatesA;
  connectorCoordinatesB = connectorCoordinatesA;
    
  // calculate offset of connector in object coordinates
  bodyCoordinatesA.toObjectCoordinates(connectorCoordinatesA.position(),connectorA->offset());
    
  connectorNodeA->set("offset",connectorA->offset());
  connectorNodeA->set("initialcoordinates",connectorCoordinatesA);
  connectorNodeA->set("relativecoordinates",relativeJointCoordinates);
    

  node->set("initialcoordinates",coordinatesJ);
  node->set("relativecoordinates",CoordinateSystem::identity());
    
  connectorNodeB->set("initialcoordinates",connectorCoordinatesB);
  connectorNodeB->set("relativecoordinates", relativeJointCoordinates);

}
  
void RobotElementParser::convertSpring(ModelNode * node){
  ExtendedUrdfSpring * urdfSpring ;
  node->get(urdfSpring,"urdfspring");
  if(!urdfSpring)return;



}

void RobotElementParser::convert(){
  ModelNode * root = findRoot();
    
  if(!root){
//   ERROR("could not find root");
   return;
  }
  Origin rootOrigin = model().get<Origin>("origin");
  CoordinateSystem current = rootOrigin;

  //roots position and coordinates initial positions
  root->set("initialcoordinates",(CoordinateSystem)rootOrigin);
  root->set("relativecoordinates", (CoordinateSystem)rootOrigin);
 
  // iterate through the tree depth first (note: dfs currently crashes if cycles exist)
  root->dfs([this](ModelNode * node){
    convertLink(node);
    convertJoint(node);
    convertConnector(node);
    convertSpring(node);
  });    
}

bool RobotElementParser::parseNamedElement(XMLElement * element){
  builder().beginModel();
  //get name for model
  parseName(&model(),element);
    
  // parse children
  _children.parse(element);

  // calculate the positions and convert graph to my data format (connection / connecotr / body)
  convert();

  builder().endModel();
  return true;
}
