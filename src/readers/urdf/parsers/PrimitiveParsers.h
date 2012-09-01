#pragma once

#include <common/NamedObject.h>
#include <sstream>

namespace nspace{


//sets element's name to the value of xml nodes name attribute
void parseName(NamedObject * object, tinyxml2::XMLElement * node){
  std::string name = node->Attribute("name");
  object->setName(name);
}

// parser vector from const char *
bool parseVector(Vector3D & v, const char * str){
  if(!str)return false;
  Real x,y,z;
  std::stringstream ss(str);
  ss>>x; ss >> y; ss >> z;
  v.x()=x;v.y()=y; v.z()=z;
  return true;
}



}