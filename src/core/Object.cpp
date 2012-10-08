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

unsigned int TypeData::_typeCounter = 0;
TypeData::TypeData():id(++_typeCounter){ }

TypeData::TypeData(const std::string & name):id(++_typeCounter),name(name){}

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