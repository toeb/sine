#include "Object.h"
#include <sstream>
#include <string>
#include <core/Property.h>
using namespace nspace;
using namespace std;


std::string Object::toString()const{
  stringstream ss;
  toString(ss);
  return ss.str();
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
