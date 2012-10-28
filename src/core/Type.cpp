#include "Type.h"
#include <core/Property.h>

using namespace nspace;


const TypeData & TypeData::UnknownType = *new TypeData("Unknown");

void TypeData::onPredecessorAdded(TypeData* typedata){
  //std::cout << name <<" is subclass of " <<typedata->name<<std::endl;
  Properties()|=typedata->Properties();
}
void TypeData::onPredecessorRemoved(TypeData* typedata){
  Properties()/=typedata->Properties();
}


void TypeData::itemAdded(const Property* ,DirectProperties){
  Properties().add(item);
}
void TypeData::itemRemoved(const Property* ,DirectProperties){
  Properties().remove(item);
}
void TypeData::itemAdded(const Property* ,Properties){
}
void TypeData::itemRemoved(const Property* ,Properties){
}

const Property * TypeData::getProperty(const std::string & name)const{  
  const Property* prop= Properties().first([&name](const Property * prop){return prop->getName()==name;});
  return prop;
}

unsigned int TypeData::_typeCounter = 0;
TypeData::TypeData():id(++_typeCounter){ }

TypeData::TypeData(const std::string & name):id(++_typeCounter),name(name){}

unsigned int TypeData::typeCount(){
  return _typeCounter;
}