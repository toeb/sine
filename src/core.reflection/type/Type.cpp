#include "Type.h"
#include <core.reflection/member/property/PropertyInfo.h>
#include <core.reflection/member/method/MethodInfo.h>
#include <core.reflection/member/constructor/ConstructorInfo.h>
#include <core.reflection/type/TypeRepository.h>
#include <sstream>
using namespace nspace;



bool Type::isStringifyable()const{
  return (bool)getObjectToStringFunction();
}
void Type::objectToString(const void * object, std::ostream & stream)const{
  if(!isStringifyable())return;
  getObjectToStringFunction()(object,stream);
}
std::string Type::objectToString(const void * object)const{
  std::stringstream stream;
  objectToString(object,stream);
  return stream.str();
}
bool Type::isConstructible()const{return  (bool)getCreateInstanceFunction();}

bool Type::isConvertibleToSmartObjectPointer()const{
  return (bool)getSmartObjectPointerConverter();
}
bool Type::isConvertibleToRawObjectPointer()const{
  return (bool)getRawObjectPointerConverter();
}


void * Type::toRawDerivedPointer(Object * object)const{
  if(!isConvertibleToRawObjectPointer())return 0;
  return getRawDerivedPointerConverter()(object);
}

Object * Type::toRawObjectPointer(void * object)const{
  if(!isConvertibleToRawObjectPointer())return 0;
  return getRawObjectPointerConverter()(object);
}
std::shared_ptr<Object> Type::toSmartObjectPointer(std::shared_ptr<void> object)const{
  if(!isConvertibleToSmartObjectPointer())return std::shared_ptr<Object>();
  return getSmartObjectPointerConverter()(object);
}


TypeId Type::_typeCounter=0;
Type::Type():
  _Id(_typeCounter++),
  _CreateInstanceFunction([](){return std::shared_ptr<void>();}),
  _ObjectToStringFunction([](const void*,std::ostream&){})
{
  TypeRepository::registerType(this);
}
namespace nspace{
  bool operator!=(const Type & a, const Type & b) {
    return !(a==b);
  }
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


std::shared_ptr<Object> Type::createObjectInstance()const{
  if(!isConvertibleToSmartObjectPointer())return std::shared_ptr<Object>();
  return getSmartObjectPointerConverter()(createInstance());
}


const MemberInfo * Type::getMember(const std::string & name)const{
  auto member = Members().first([&name](const MemberInfo * member){return member->getName()==name;});
  return member;
}

const MethodInfo * Type::getMethod(const std::string & name)const{
  auto method = dynamic_cast<const MethodInfo*>(getMember(name));
  return method;
}


const ConstructorInfo * Type::getConstructor(const std::vector<const Type*> & types)const{
  return Constructors().first([&types](const ConstructorInfo * info)->bool{
    if(types.size()!=info->getArgumentTypes().size())return false;
    for(int i=0; i < types.size(); i++){
      if(types[i]!=info->getArgumentTypes()[i])return false;
    }
    return true;
  });
}

const PropertyInfo * Type::getProperty(const std::string & name)const{
  auto member = getMember(name);
  if(!member)return 0;
  auto prop = dynamic_cast<const PropertyInfo*>(member);
  return prop;
}
bool Type::isSuperClassOf(const Type * other)const{
  if(!other)return false;  
  if(other == this)return true;
  for(uint i=0; i < other->predecessors(); i++){
    auto current = other->predecessor(i);
    if(isSuperClassOf(current))return true;
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

Set<const ConstructorInfo*> Type::Constructors()const{
  return Members().subset<const ConstructorInfo*>();
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
