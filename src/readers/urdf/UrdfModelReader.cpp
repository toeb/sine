#include "UrdfModelReader.h"
#include <tinyxml2/tinyxml2.h>

#include <fstream>
#include <simulation/model/builder/ModelBuilderHolder.h>
#include <readers/urdf/UrdfModelReader.h>
#include <readers/urdf/parsers/RobotElementParser.h>
#include <common/StringTools.h>

using namespace std;
using namespace nspace;

UrdfModelReader * UrdfModelReader::_instance =0;
UrdfModelReader::UrdfModelReader(){}

bool UrdfModelReader::parse(IModelBuilder & builder, std::istream & data){
  // read all data of inputstream
  string s = readToEnd(data);
  const char * text = s.c_str();

  // parse tinyxml2 document 
  tinyxml2::XMLDocument document;
  int errorCode = document.Parse(text);

  //return false if document could not be parsed (this indicates that xml was not valid
  if(errorCode){
    ERROR("tinyxml2 Parse error number 2"<<errorCode);
    return false;
  }
  
  // create a robot parser and parse all nodes of document
  RobotElementParser robotParser(builder);
  robotParser.parseSiblingsOf(document.FirstChildElement());
  
}




/*
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
*/