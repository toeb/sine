#include "Object.h"
#include <sstream>
#include <string>
#include <core/reflection/PropertyInfo.h>
#include <core/NamedObject.h>
using namespace nspace;
using namespace std;


std::string Object::toString()const{
  stringstream ss;
  toString(ss);
  return ss.str();
}

  
void Object::toString(std::ostream & out)const{
    if(nspace::hasObjectName(this)){
        out << name(this);
        return;
    }
  out << "<object typeid=\""<<getType()<<"\" typename=\""<< getType().getName() << "\"/>";
}
Object::Object(){

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
