#include "Object.h"
#include <sstream>
#include <string>
using namespace nspace;
using namespace std;

std::string Object::toString()const{
  stringstream ss;
  toString(ss);
  return ss.str();
}

NamedObject::~NamedObject(){
  if(_name)delete _name;
  _name=0;
}

const string & NamedObject::DefaultName=*new string("<DEFAULTOBJECTNAME>");
NamedObject::NamedObject(const string & name):_name(new string(name)){}
NamedObject::NamedObject():_name(0){}
const std::string & NamedObject::getName()const{
  if(!_name)return NamedObject::DefaultName;  
  return *_name;
}
void NamedObject::setName(const std::string & name){
  if(!_name)_name = new string;
  _name->assign(name);
}
void NamedObject::setName(const std::string * name){
  if(!name){
    _name=0;
    return;
  }
  setName(*name);
}
bool NamedObject::hasName()const{
  return _name;
}