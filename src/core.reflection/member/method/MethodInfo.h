#pragma once
#include <core.reflection/member/MemberInfo.h>
#include <core.reflection/type/Argument.h>
namespace nspace{


  class MethodInfo : public MemberInfo{
    DS_CLASS(MemberInfo)
  public:
    template<typename Container> Argument call(void * object, Container & container=std::vector<Argument>())const;
    template<typename Container> Argument call(Object * object, Container & container=std::vector<Argument>())const;
    Argument call(void * object)const;
    Argument call(Object * object);
    typedef std::vector<const Type*> basic_property(ArgumentTypes);
    typedef const Type * basic_property(ReturnType);
    typedef bool basic_property(IsConst);
    //typedef bool basic_property(IsOverride);
    
  protected:
    ArgumentTypesPropertyType & argumentTypes(){return _ArgumentTypes;}
    virtual Argument call(void * object, std::vector<Argument> arguments)const=0;
  };
}


namespace nspace{
  template<typename Container>
  Argument MethodInfo::call(void * object, Container & container)const{
    std::vector<Argument> args;
    for(auto it = std::begin(container); it!=std::end(container);it++){
      args.push_back(*it);
    }
    return call(object,args);
  }
  template<typename Container>
  Argument MethodInfo::call(Object * object, Container & container)const{
    auto ptr = object->getType()->toRawDerivedPointer(object);
    return call<Container>(object,args);
  }
}