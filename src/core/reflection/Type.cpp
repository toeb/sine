#include "Type.h"
#include <core/reflection/PropertyInfo.h>
#include <core/reflection/MethodInfo.h>
#include <sstream>
#include <core/reflection/TypeRepository.h>
using namespace nspace;
void Type::objectToString(const void * object, std::ostream & stream)const{
  getObjectToStringFunction()(object,stream);
}
std::string Type::objectToString(const void * object)const{
  std::stringstream stream;
  objectToString(object,stream);
  return stream.str();
}


TypeId Type::_typeCounter=0;
Type::Type():
  _Id(_typeCounter++),
  _IsConstructible(false),
  _CreateInstanceFunction([](){return std::shared_ptr<void>();}),
  _ObjectToStringFunction([](const void*,std::ostream&){})
{
  TypeRepository::registerType(this);
}
namespace nspace{
  bool operator==(const Type & a, const Type & b){
    return a._Id==b._Id;
  }
  std::ostream & operator <<(std::ostream & out, const Type & type){
    out << "<Type name='"<< type.getName()<<"' id='"<< type.getId()<<"'/>";
    return out;
  }
  std::ostream & operator <<(std::ostream & out, const Type * type){
    if(type) out << *type;
    return out;
  }
}

std::shared_ptr<void> Type::createInstance()const{
  return getCreateInstanceFunction()();
}



const MemberInfo * Type::getMember(const std::string & name)const{
  auto member = Members().first([&name](const MemberInfo * member){return member->getName()==name;});
  return member;
}

const MethodInfo * Type::getMethodInfo(const std::string & name)const{
  auto method = dynamic_cast<const MethodInfo*>(getMember(name));
  return method;
}

const PropertyInfo * Type::getProperty(const std::string & name)const{
  auto member = getMember(name);
  if(!member)return 0;
  auto prop = dynamic_cast<const PropertyInfo*>(member);
  return prop;
}
bool Type::isSuperClassOf(const Type & other)const{
  if(&other == this)return true;
  for(uint i=0; i < other.predecessors(); i++){
    auto current = other.predecessor(i);
    if(isSuperClassOf(*current))return true;
  }
  return false;
}

Set<const PropertyInfo*> Type::Properties()const{
  Set<const PropertyInfo*> result;
  for(uint i=0; i < Members(); i++){
    auto prop = dynamic_cast<const PropertyInfo*>(Members().at(i));
    if(!prop)continue;
    result|=prop;
  }
  return result;
}

void Type::itemAdded(const MemberInfo * , Members){
}
void Type::itemRemoved(const MemberInfo * , Members){
}

void Type::onPredecessorAdded(Type* type){
  Members()|=type->Members();
  //std::cout << this->getName() << "  is subclass of "<<type->getName()<<std::endl;
}
void Type::onPredecessorRemoved(Type* type){
  Members()/=type->Members();
}
