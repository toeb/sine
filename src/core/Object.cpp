#include "Object.h"
#include <sstream>
#include <string>
#include <core/Property.h>
using namespace nspace;
using namespace std;


const TypeData & TypeData::UnknownType = *new TypeData("Unknown");

std::string Object::toString()const{
  stringstream ss;
  toString(ss);
  return ss.str();
}

 int TypeData::getPropertyCount()const{
    if(!properties)return 0;
    return properties->size();
  }
  const Property * TypeData::getProperty(const std::string & name)const{
    if(!properties)return 0;
    return properties->first([&name](const Property * prop){return prop->getPropertyName()==name;});
  }
  const Property* TypeData::getProperty(int index)const{
    if(!properties)return 0;
    return properties->at(index);
  }

unsigned int TypeData::_typeCounter = 0;
TypeData::TypeData():id(++_typeCounter),properties(0){ }

TypeData::TypeData(const std::string & name):id(++_typeCounter),name(name),properties(0){}

unsigned int TypeData::typeCount(){
  return _typeCounter;
}
  
uint Object::_idCounter=0;
void Object::toString(std::ostream & out)const{
  out << "<object typeid=\""<<getType()<<"\" typename=\""<< getTypeData().name <<"\" id=\""<<_id<<"\"/>";
};
Object::Object():_id(++_idCounter){

}
Object::~Object(){

}
namespace nspace{
  std::ostream & operator << (std::ostream & out, const Object & obj){
    obj.toString(out);
    return out;
  }
  std::ostream & operator << (std::ostream & out, const Object * obj){
    if(!obj)return out << "Null";
    out << *obj;
    return out;
  }

}
