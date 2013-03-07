#include "Type.h"
#include <core.reflection/member/property/PropertyInfo.h>
#include <core.reflection/member/method/MethodInfo.h>
#include <core.reflection/member/constructor/ConstructorInfo.h>
#include <core.reflection/type/TypeRepository.h>
#include <sstream>
using namespace nspace;
struct DefaultNS : public Namespace{
  DS_SINGLETON(DefaultNS):Namespace(DS_STRINGIFY(nspace)){};
};
Type::Type(const std::string & name ,const Type * underlyingType):
  _Id(_typeCounter++),
  _IsPointer(false),
  _IsReference(false),
  _IsVolatile(false),
  _IsConst(false),
  _UnderlyingType(0),
  _RawType(0),
  _Namespace( DefaultNS::instance().get())
{
  DefaultNS::instance()->setTypes(DefaultNS::instance()->getTypes() | this);
  if(underlyingType==this || underlyingType==0){
    setUnderlyingType(0);
    setRawType(this);
    setName(name);
  }else{
    setUnderlyingType(underlyingType);
    setRawType(underlyingType->getRawType());
    setName(DS_INLINE_STRING(underlyingType->getName()<<" "<<name));    
  }
}



bool Type::isConstructible()const{return  (bool)getCreateInstanceFunction();}



bool Type::isRawType()const{return getRawType()==this;}


Type::TypeId Type::_typeCounter=0;
Type::Type():
  _Id(_typeCounter++),
  _IsPointer(false),
  _IsReference(false),
  _IsVolatile(false),
  _IsConst(false),
  _UnderlyingType(0),
  _RawType(0),
  _Namespace( DefaultNS::instance().get())
{
  DefaultNS::instance()->setTypes(DefaultNS::instance()->getTypes() | this);
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


bool Type::isSubClassOf(const Type * other)const{
  return other->isSuperClassOf(other);
}



Set<const PropertyInfo*> Type::Properties()const{  
  return Members().subset<const PropertyInfo*>();
}

Set<const MethodInfo*> Type::Methods()const{
  return Members().subset<const MethodInfo*>();
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
  _SuperClasses |=type;
  _RootClasses |=type->getRootClasses();
}
void Type::onPredecessorRemoved(Type* type){
  Members()/=type->Members();
  
  _SuperClasses /=type;
  _RootClasses /=type->getRootClasses();
}

void Type::onSuccessorAdded(Type * type){

}
void Type::onSuccessorRemoved(Type* type){

}