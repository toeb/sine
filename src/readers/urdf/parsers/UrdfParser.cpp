#include "UrdfParser.h"

#include <fstream>
#include <sstream>

#include <urdfreader/parsers/general/tinyxml2.h>
#include <urdfreader/ModelElements/query.h>

#include <urdfreader/parsers/urdf/structs/Origin.h>

using namespace std;
using namespace mbslib;
using namespace tinyxml2;
using namespace stringHelper;



UrdfModelReader * UrdfModelReader::_instance =0;

UrdfModelReader::UrdfModelReader(){}


void parseName(NamedObject * element, XMLElement * link){
  string name = link->Attribute("name");
  element->setName(name);
}
bool parseVector(Vector3D & v, const char * str){
  if(!str)return false;
  Real x,y,z;
  stringstream ss(str);
  ss>>x; ss >> y; ss >> z;
  v.x()=x;v.y()=y; v.z()=z;
  return true;
}
void parseOrigin(Vector3D & xyz, Vector3D & rpy, XMLElement * parent){
  XMLElement * origin = parent->FirstChildElement("origin");
  if(!origin)return;
  parseVector(xyz, origin->Attribute("xyz"));
  parseVector(rpy, origin->Attribute("rpy"));
  return;
}
void parseMassAndInertia(Real & mass, Matrix3x3 & inertia, XMLElement * parent){
  mass =0;
  inertia.setZero();
   

  XMLElement * massElement = parent->FirstChildElement("mass");

  //get mass
  if(massElement)massElement->QueryDoubleAttribute("value",&mass);

  XMLElement * inertiaElement = parent->FirstChildElement("inertia");
  if(!inertiaElement)return;
  //get the inertia matrix
  Real ixx,iyy,izz,ixy,ixz,iyz;
  ixx=ixy=ixz=iyy=iyz=izz=0;
  inertiaElement->QueryDoubleAttribute("ixx",&ixx);
  inertiaElement->QueryDoubleAttribute("iyy",&iyy);
  inertiaElement->QueryDoubleAttribute("izz",&izz);
  inertiaElement->QueryDoubleAttribute("ixy",&ixy);
  inertiaElement->QueryDoubleAttribute("ixz",&ixz);
  inertiaElement->QueryDoubleAttribute("iyz",&iyz);
  inertia(0,0)=ixx;
  inertia(0,1)=ixy;
  inertia(0,2)=ixz;
  inertia(1,0)=ixy;
  inertia(1,1)=iyy;
  inertia(1,2)=iyz;
  inertia(2,0)=ixz;
  inertia(2,1)=iyz;
  inertia(2,2)=izz;
  
}
void parseInertialFrame(Node * element, XMLElement * link){
  
  
  XMLElement * inertial=link->FirstChildElement("inertial");
  if(!inertial)return;
  Vector3D xyz, rpy;
  Real mass;
  Matrix3x3 inertia;
  parseOrigin(xyz,rpy,inertial);
  
  CoordinateSystem coordinates;


  parseMassAndInertia(mass,inertia,inertial);
  element->set("inertia",inertia);
  element->set("mass",mass);
  element->set("origin",coordinates);
}
void parseGeometry(Node * element, XMLElement * parent){
  XMLElement * geometry= parent->FirstChildElement("geometry");
  if(!geometry){
    cerr << "<visual> element did not have geometry node"<<endl;
    return;
  }
  XMLElement * geom = geometry->FirstChildElement();
  if(!geom){
    cerr << "<geometry> element did have a single child node" <<endl;
    return ;
  }
  string name = geom->Name();
  if(name=="box"){
    Vector3D size;
    const char * sizeString= geom->Attribute("size");
    parseVector(size,sizeString);
  }else if(name=="cylinder"){
    Real radius=0;
    Real size=0;
    geom->QueryDoubleAttribute("radius",&radius);
    geom->QueryDoubleAttribute("length",&size);
  }else if(name=="sphere"){
    Real radius=0;
    geom->QueryDoubleAttribute("radius",&radius);
  }else if(name=="mesh"){
    const char * filename = geom->Attribute("filename");
    Vector3D scale;
    const char * scaleString = geom->Attribute("scale");
    parseVector(scale,scaleString);
  }

}
void parseDoubles(Real * arr, int count, const string & str){
  stringstream stream(str);
  for(int i=0; i< count; i++){
    stream>>arr[i];
  }
}
void parseColor(Real * colorArray, XMLElement * colorNode){
  if(!colorNode)return;
  string colorString = colorNode->Attribute("rgba");
  parseDoubles(colorArray,4,colorString);
}
void parseMaterial(Node * element, XMLElement * parent){
  XMLElement * material = parent->FirstChildElement("material");
  if(!material)return;
  string materialName = material->Attribute("name");
  
  XMLElement * color = material->FirstChildElement("color");
  if(color){
    double colorArray[4];//rgba;
    parseColor(colorArray,color);   
  }


  XMLElement * texture = material->FirstChildElement("texture");
  if(texture){    
    const char * textureFilename = texture->Attribute("filename");
    
  }
}
void parseVisual(Node * element, XMLElement * link){
  
  XMLElement * visual = link->FirstChildElement("visual");
  if(!visual){
    cerr<< "Illegal URDF Link element. Visual element musst be defined.  Continuing anyway"<<endl;
    return;
  }
  //get geometry center
  Vector3D xyz,rpy;
  parseOrigin(xyz,rpy,visual);
  parseGeometry(element,visual);
  parseMaterial(element,visual);
}


void parseLinkElement(IModelBuilder & builder, XMLElement * link){
  Node * node = builder.addNode();
  // extract name
  parseName(node,link);  
  parseInertialFrame(node,link);
  parseVisual(node,link);
  //parseCollision();

}
void parseJointElement(Model  & model, XMLElement *joint ){
  if(!joint)return;

  XMLElement * parent = joint->FirstChildElement("parent");
  XMLElement * child = joint->FirstChildElement("child");
  if(!parent){
    cerr << "<joint> element does not contain <parent> element" <<endl;
    return;
  }
  if(!child){
    cerr << "<joint> element does not contain <child> element" <<endl;
    return;
  }
  const char * parentLinkName = parent->Attribute("link");
  const char * childLinkName = child->Attribute("link");
  if(!parentLinkName){
    cerr << "<parent> element does not contain link attribute"<<endl;
    return;
  }
  if(!childLinkName){
    cerr << "<child> element does not contain link attribute"<<endl;
    return;
  }
  
  Node * parentNode = model(parentLinkName);
  Node * childNode = model(childLinkName);
  if(!parentNode){
    ERROR("no parent node");
    return;
  }
  if(!childNode){    
    ERROR("no child node");
    return;
  }

  Connector * cA = new Connector();




}

void parseExtenesions(){

}

class ModelBuilderHolder{
private:
  IModelBuilder & _builder;
public:
  ModelBuilderHolder(IModelBuilder & builder):_builder(builder){

  }
  Model & model(){
    return *_builder.currentModel();
  }
  IModelBuilder &  builder(){
    return _builder;
  }
};


class ElementParser{
public:    
  virtual bool parse(XMLElement * node)=0;
  bool parseChildrenOf(XMLElement * parent){
    return parseSiblingsOf(parent->FirstChildElement());
  }
  bool parseSiblingsOf(XMLElement * sibling){
    bool result = false;
    while(sibling){
      result |= parse(sibling);
      sibling = sibling->NextSiblingElement();
    }
    return result;
  }
};


class NamedElementParser : public ElementParser{
private:
  std::string _name;
public:
  const std::string & elementName()const{return _name;}
  NamedElementParser(const std::string  &name):_name(name){}
  bool parse(XMLElement* node){
    const char * cstr = node->Name();
    if(!cstr)return false;
    string name = cstr;
    if(name!=_name)return false;
    return parseNamedElement(node);
  }
protected:
  virtual bool parseNamedElement(XMLElement* node)=0;
};
class NamedChildParser : public ElementParser{
private:
  std::string _name;
public:
  NamedChildParser(){

  }
  NamedChildParser(const std::string &name):_name(name){}
  std::string & name(){
    return _name;
  }
  bool parse(XMLElement * node){
    XMLElement * child = node->FirstChildElement(_name.c_str());
    if(!child)return false;
    return parseChild(child);
  }
protected:
  virtual bool parseChild(XMLElement * child)=0;
};



class CompositeElementParser : public Set<ElementParser*>, public ElementParser{
public:
  virtual bool parse(XMLElement * node){
    
    bool result = false;
    reduce<bool>(*&result,[node](bool & res, ElementParser* current){
      res |= current->parse(node);
    });

    return result;
  }
protected:
 

};
class SiblingElementParser: public ElementParser{
  private:
  ElementParser & _siblingParser;
public:
  SiblingElementParser(ElementParser & parser):_siblingParser(parser){}
  virtual bool parse(XMLElement * node){
    while(node){
      _siblingParser.parse(node);
      node = node->NextSiblingElement();
    }
    return true;
  }
};
class ChildElementParser : public SiblingElementParser{
private:
  ElementParser & _childParser;
public:
  ChildElementParser(ElementParser & parser):_childParser(parser),SiblingElementParser(parser){}
  virtual bool parse(XMLElement * node){
    return SiblingElementParser::parse(node->FirstChildElement());
  }
};
class CompositeChildParser : public ElementParser{
private :
  ChildElementParser _childParser;
  CompositeElementParser _compositeParser;
public:
  CompositeElementParser & composite(){return _compositeParser;}
  CompositeChildParser():_childParser(_compositeParser){

  }
  virtual bool parse(XMLElement * node){
    return _childParser.parse(node);
  }
};

class OriginParser : public NamedChildParser{

public:
  OriginParser():NamedChildParser("origin"){
    
  }
  Origin origin;
protected:
  bool parseChild(XMLElement * originElement){    
    if(!parseVector(origin.xyz, originElement->Attribute("xyz")))return false;
    if(!parseVector(origin.rpy, originElement->Attribute("rpy")))return false;
    return true;
  }

};

class RootLinkParser : public NamedElementParser, public ModelBuilderHolder{
private:
  CoordinateSystem _coordinates;
  CompositeChildParser _compositeChildParser;
public:
  RootLinkParser(IModelBuilder & builder):NamedElementParser("root"),ModelBuilderHolder(builder){    

  }
protected:
  bool parseNamedElement(XMLElement * root){
    const char * linkText = root->Attribute("link");
    if(!linkText)return false;
    string linkString = linkText;
    
    const char * typeText = root->Attribute("type");
    if(!typeText)return false;
    string typeString = typeText;


    Node * rootNode = model()(linkString);
    if(!rootNode){
      ERROR("Could not find Node by name of " << linkString);
      return false;
    }

    OriginParser origin;
    origin.parse(root);

    model().set("origin",origin.origin);
    model().set("basetype", typeString);
    model().set("root", rootNode);

    bool result =  _compositeChildParser.parse(root);
    return result;
  }
};
struct UrdfConnector : public UrdfElement{

};
struct UrdfConnection{

};
class ConnectParser: public NamedElementParser, public ModelBuilderHolder{
  Node & _connectionNode;
public:
  ConnectParser(IModelBuilder & builder, Node & connectionNode) : NamedElementParser("connect"), ModelBuilderHolder(builder),_connectionNode(connectionNode){

  }
protected:
   bool parseNamedElement(XMLElement * element){

     const char * cstr = element->Attribute("connector");
     if(!cstr)return false;
     string connectorName = cstr;

     Node * connectorNode = model().nodes()(connectorName);
     if(!connectorNode)return false;

     _connectionNode.predecessors().add(connectorNode);
   }
};
class SpringParser{

};
class ConnectionTypeParser{
public:
};
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



class MassConfiguration{
private:
  Real _mass;
  Matrix3x3 _inertia;
public:
  MassConfiguration(){
    _inertia.setZero();
    _mass=0;
  }
  Real & mass(){
    return _mass;
  }
  Matrix3x3 & inertia(){
    return _inertia;
  }
  const Real & mass()const{
    return _mass;
  }
  const Matrix3x3 & inertia()const{
    return _inertia;
  }
};
class MassParser : public NamedChildParser{
public:
  MassParser():NamedChildParser("mass"){}
  Real mass;
protected:
  bool parseChild(XMLElement * massElement){   
    return massElement->QueryDoubleAttribute("value",&mass)==0;
  }  
};
class InertiaParser : public NamedChildParser{
public:
  InertiaParser():NamedChildParser("inertia"){inertia.setZero();}
  Matrix3x3 inertia;
protected:
  bool parseChild(XMLElement * inertiaElement){
    Real ixx,iyy,izz,ixy,ixz,iyz;
    ixx=ixy=ixz=iyy=iyz=izz=0;
    //get attribute values for the six entries of the symmtetric inertia matrix
    inertiaElement->QueryDoubleAttribute("ixx",&ixx);
    inertiaElement->QueryDoubleAttribute("iyy",&iyy);
    inertiaElement->QueryDoubleAttribute("izz",&izz);
    inertiaElement->QueryDoubleAttribute("ixy",&ixy);
    inertiaElement->QueryDoubleAttribute("ixz",&ixz);
    inertiaElement->QueryDoubleAttribute("iyz",&iyz);
    //set the whole inertia matrix
    inertia(0,0)=ixx;
    inertia(0,1)=ixy;
    inertia(0,2)=ixz;
    inertia(1,0)=ixy;
    inertia(1,1)=iyy;
    inertia(1,2)=iyz;
    inertia(2,0)=ixz;
    inertia(2,1)=iyz;
    inertia(2,2)=izz;
    return true;
  }
};
class MassConfigurationParser : public ElementParser{
public:
  MassConfiguration massConfiguration;
  bool parse(XMLElement* element){
    //create mass and inertia parser
    MassParser mass;
    InertiaParser inertia;
    
    //parse children of current element to find mass and inertia nodes
    if(mass.parse(element)) massConfiguration.mass()=mass.mass;
    if(inertia.parse(element)) massConfiguration.inertia() = inertia.inertia;
    return true;
  }
};
class InertialFrameParser : public NamedChildParser{
public:
  InertialFrameParser(){name() ="inertial";}
  MassConfiguration massConfiguration;
  Origin origin;
protected:
  virtual bool parseChild(XMLElement * inertialElement){
    //create massconfig and origin parser
    MassConfigurationParser mass;
    OriginParser originParser;
    //parse children of inertial element
    originParser.parse(inertialElement);
    mass.parse(inertialElement);
    //set mass config and coordinates
    massConfiguration=mass.massConfiguration;
    origin = originParser.origin;
    return true;
  }
};
class GeometryParser:public NamedElementParser{
public:
  GeometryParser():NamedElementParser("geometry"){
    
  }
protected:
  virtual bool parseNamedElement(XMLElement * geometryNode){
    return true;
  }
};
class MaterialParser : public NamedElementParser{
public:
  MaterialParser():NamedElementParser("material"){
    
  }
protected:
  virtual bool parseNamedElement(XMLElement * materialNode){
    return true;
  }
};
class VisualParser : public NamedElementParser{
public:
  VisualParser():NamedElementParser("visual"){}
  OriginParser origin;
  GeometryParser geometry;
  MaterialParser material;
protected:
  virtual bool parseNamedElement(XMLElement * visualElement){
    origin.parse(visualElement);
    geometry.parseChildrenOf(visualElement);
    material.parseChildrenOf(visualElement);
    return true;
  }
};

class LinkParser : public NamedElementParser, public ModelBuilderHolder{
private:
public:
  LinkParser(IModelBuilder & builder):NamedElementParser("link"),ModelBuilderHolder(builder){
    
  }
  protected:
  virtual bool parseNamedElement(XMLElement * linkElement){
    //create node
    Node * node=new Node;

    //set nodes name
    parseName(node,linkElement);
    

    //create and set struct holding link information
    UrdfLink * link = new UrdfLink;
    node->set("urdflink",link);
    
    // create inertial fram parser and parse children of link element
    InertialFrameParser inertialFrame;
    inertialFrame.parse(linkElement);
    link->mass = inertialFrame.massConfiguration.mass();
    link->inertia = inertialFrame.massConfiguration.inertia();
    link->origin = inertialFrame.origin;


    VisualParser visual;
    visual.parse(linkElement);

    
    //add new node to current model
    model().nodes().add(node);


    return true;
  }
};


class ParentLinkParser : public NamedChildParser, public ModelBuilderHolder{
public:
  ParentLinkParser(IModelBuilder & builder):node(0),ModelBuilderHolder(builder), NamedChildParser("parent"){

  }
  string name;
  Node * node;
protected:
  bool parseChild(XMLElement * parentElement){
    const char * cstr = parentElement->Attribute("link");
    if(!cstr)return false;
    name = cstr;
    node =model().nodes()(name);
    return true;
  }
};
class ChildLinkParser : public NamedChildParser, public ModelBuilderHolder{
public:
  ChildLinkParser(IModelBuilder & builder):node(0),ModelBuilderHolder(builder), NamedChildParser("child"){

  }
  string name;
  Node * node;
protected:
  bool parseChild(XMLElement * childElement){
    const char * cstr = childElement->Attribute("link");
    if(!cstr)return false;
    name = cstr;
    node =model().nodes()(name);
    return true;
  }
};
class AxisParser : public NamedChildParser{
public:
  Vector3D direction;
  AxisParser(): NamedChildParser("axis"){

  }
protected:
  bool parseChild(XMLElement * axisElement){
    if(!parseVector(direction,axisElement->Attribute("xyz")))return false;
    return true;
  }
};


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

    if(!parent.node){
      ERROR("could not find parent '"<< parent.name <<"' of connector "<<connectorNode->name());
      return false;
    }
    
    OriginParser origin;
    origin.parse(element);
    
    // create connector
    UrdfConnector * connector = new UrdfConnector;

    connector->origin = origin.origin;
    connectorNode->set("urdfconnector", connector);
    
    parent.node->successors().add(connectorNode);
    
    model().nodes() |= connectorNode;
    
    
    return true;
  }
};

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

class UrdfExtensionParser:public NamedElementParser, public ModelBuilderHolder{
private:
  CompositeChildParser _childParser;
  RootLinkParser _rootParser;
  ConnectorParser _connectorParser;
  ConnectionParser _connectionParser;
public:
  UrdfExtensionParser(IModelBuilder & builder):NamedElementParser("extensions"),ModelBuilderHolder(builder),_rootParser(builder),_connectorParser(builder),_connectionParser(builder){
    _childParser.composite().add(&_rootParser);
    _childParser.composite().add(&_connectorParser);
    _childParser.composite().add(&_connectionParser);
  }
protected:
  virtual bool parseNamedElement(XMLElement * node){
    bool result = _childParser.parse(node);
    return true;
  }
};

class RobotElementParser : public NamedElementParser, public ModelBuilderHolder{
private:
  CompositeChildParser _children;
public:

  RobotElementParser(IModelBuilder & builder):ModelBuilderHolder(builder),NamedElementParser("robot"){
    _children.composite().add(new UrdfExtensionParser(builder));
    //order is important because joint parser needs the links to be present
    _children.composite().add(new LinkParser(builder));
    _children.composite().add(new JointParser(builder));

  }
protected:
  
  Node * findRoot(){
    return model().get<Node*>("root");
  }

  void convertLink(Node * node){
    UrdfLink * link=0;
    node->get(link,"urdflink");
    if(!link)return;

    Body* body = new Body;
    node->set("body",body);
    body->inertia = link->inertia;
    body->mass = link->mass;

    CoordinateSystem preceedingCoordinates;
    Node * connector = node->predecessors().first();
    
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
  void convertConnector(Node * node){
    UrdfConnector* urdfConnector=0;
    node->get(urdfConnector,"urdfconnector");
    if(!urdfConnector)return;

    //create connector
    Connector * connector = new Connector;
    node->set("connector", connector);

    // get preceeding body (urdfconnector always is a successor)
    Node * body = node->predecessors().first();
    if(!body)return;

    // get body coordinates
    CoordinateSystem bodyCoordinates;
    body->get(bodyCoordinates,"initialcoordinates");
    
    //set relative coordinates of connector
    CoordinateSystem relativeCoordinates= urdfConnector->origin;    
    node->set("relativecoordinates",relativeCoordinates);

    // "calculate" connectors offset vector in object coordinates
    connector->offset = relativeCoordinates.position();
    node->set("offset",connector->offset);
    
    // calculate initial coordinates of current connector
    CoordinateSystem initialCoordinates;
    bodyCoordinates.fromObjectCoordinates(relativeCoordinates,initialCoordinates);
    node->set("initialcoordinates", initialCoordinates);

  }
  void convertConnection(Node * node){
    UrdfConnection * connection =0;
    node->get(connection,"urdfconnection");
    if(!connection )return;

    //todo: implement
  }
  void convertJoint(Node * node){
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
    Node * connectorNodeA = node->predecessors().first();
    Node * connectorNodeB = node->successors().first();

    Connector * connectorA = new Connector;
    Connector * connectorB = new Connector;
    
    connectorNodeA->set("connector",connectorA);
    connectorNodeB->set("connector",connectorB);

    Node * bodyA = connectorNodeA->predecessors().first();
    Node * bodyB = connectorNodeB->successors().first();


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
    bodyCoordinatesA.toObjectCoordinates(connectorCoordinatesA.position(),connectorA->offset);
    
    connectorNodeA->set("offset",connectorA->offset);
    connectorNodeA->set("initialcoordinates",connectorCoordinatesA);
    connectorNodeA->set("relativecoordinates",relativeJointCoordinates);
    

    node->set("initialcoordinates",coordinatesJ);
    node->set("relativecoordinates",CoordinateSystem::identity());
    
    connectorNodeB->set("initialcoordinates",connectorCoordinatesB);
    connectorNodeB->set("relativecoordinates", relativeJointCoordinates);

  }
  

  void calculatePositions(){
    Node * root = findRoot();
    
    if(!root)return;
    Origin rootOrigin = model().get<Origin>("origin");
    CoordinateSystem current = rootOrigin;

    //roots position and coordinates initial positions
    root->set("initialcoordinates",(CoordinateSystem)rootOrigin);
    root->set("relativecoordinates", (CoordinateSystem)rootOrigin);
 
    // iterate through the tree depth first (note: dfs currently crashes if cycles exist)
    root->dfs([this](bool & cont, Node * node){
      convertLink(node);
      convertJoint(node);
      convertConnector(node);
    });    
  }
protected:

  bool parseNamedElement(XMLElement * element){
    builder().beginModel();
    //get name for model
    parseName(&model(),element);
    
    // parse children
    _children.parse(element);

    // calculate the positions and convert graph to my data format (connection / connecotr / body)
    calculatePositions();

    builder().endModel();
    return true;
  }
};


bool UrdfModelReader::parse(IModelBuilder & builder, std::istream & data){
  XMLDocument document;
  string s = readToEnd(data);
  const char * text = s.c_str();
  int errorCode = document.Parse(text);
  if(errorCode)return false;
  

  RobotElementParser robotParser(builder);
  SiblingElementParser siblingParser(robotParser);  
  siblingParser.parse(document.FirstChildElement());

  /*
  XMLElement * robotElement = document.FirstChildElement("robot");
  if(!robotElement){
    cerr << " UrdfModelReader :: parse cannot find <robot> node " << endl; 
    return false;
  }
  
  // iterate through all robot nodes
  do{
    parseRobotElement(builder,robotElement);
  }while(robotElement = robotElement->NextSiblingElement("robot"));

  */


}



