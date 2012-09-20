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
unsigned int TypeData::typeCount(){
  return _typeCounter;
}
  

void Object::toString(std::ostream & out)const{out << "typeID: "<<getType();};


std::ostream & Object::operator<<(std::ostream & out)const{
  toString(out);
  return out;
}