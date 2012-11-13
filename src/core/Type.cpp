#include "Type.h"
#include <core/Property.h>

using namespace nspace;


const TypeData & TypeData::UnknownType = *new TypeData("Unknown");

void TypeData::onPredecessorAdded(TypeData* typedata){
 //std::cout << name <<" is subclass of " <<typedata->name<<std::endl;
  Properties()|=typedata->Properties();
  Members()|=typedata->Members();
}
void TypeData::onPredecessorRemoved(TypeData* typedata){
  Properties()/=typedata->Properties();
  Members()/=typedata->Members();
}


void TypeData::itemAdded(const MemberInfo* ,DirectMembers){
  Members().add(item);
}
void TypeData::itemRemoved(const MemberInfo* ,DirectMembers){
  Members().remove(item);
}

void TypeData::itemAdded(const MemberInfo* ,Members){ 
}
void TypeData::itemRemoved(const MemberInfo* ,Members){
}

void TypeData::itemAdded(const Property* ,DirectProperties){
  Properties().add(item);
  DirectMembers().add(item);
}
void TypeData::itemRemoved(const Property* ,DirectProperties){
  Properties().remove(item);
  DirectMembers().remove(item);
}
void TypeData::itemAdded(const Property* ,Properties){
  Members().add(item);
}
void TypeData::itemRemoved(const Property* ,Properties){
  Members().add(item);
}

const MemberInfo * TypeData::getMember(const std::string & name)const{
  const MemberInfo* member= Members().first([&name](const MemberInfo * member){return member->getName()==name;});
  return member;
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