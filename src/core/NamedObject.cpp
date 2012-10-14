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
  return _name!=0;
}

bool NamedObject::operator == (const std::string & str)const{
  return name()==str;
}
// equalitiy operator. returns true if this objects name equals the c string
bool NamedObject::operator==(const char * str)const{
  return *this==std::string(str);
}
namespace nspace{
  // equality operator compares a NamedObject's name to a std::string and returns true iff they are equal
  bool operator==(const NamedObject * obj, const std::string & name){
    return *obj==name;
  }

  const std::string & name(Object * object){
    static std::string nullString="null-object";
    static std::string notNamed="unnamed-object";    
    if(!object)return nullString;
    NamedObject* no = dynamic_cast<NamedObject*>(object);
    if(!no)return notNamed;
    return no->name();
  }


}
