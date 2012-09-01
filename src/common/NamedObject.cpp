#include "NamedObject.h"

using namespace nspace;
using namespace std;


NamedObject::~NamedObject(){
  if(_name)delete _name;
  _name=0;
}

const string & NamedObject::DefaultName=*new string("<DEFAULTOBJECTNAME>");
NamedObject::NamedObject(const string & name):_name(new string(name)){}
NamedObject::NamedObject():_name(0){}
const string & NamedObject::name()const{
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