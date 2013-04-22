#pragma once
#include <core.reflection/member/MemberInfo.h>
#include <core.reflection/type/Argument.h>
namespace nspace{


  class MethodInfo : public MemberInfo{
    DS_CLASS(MethodInfo)
  public:
    template<typename Container> Argument call(void * object, Container & container=std::vector<Argument>())const;
    template<typename Container> Argument call(const void * object, Container & container=std::vector<Argument>())const;
    Argument call(void * object)const;
    Argument call(const void * object)const;
    propdef std::vector<const Type*> basic_property(ArgumentTypes);
    propdef const Type * basic_property(ReturnType);
    propdef bool basic_property(IsConst);
    //typedef bool basic_property(IsOverride);
    
    virtual Argument call(void * object, std::vector<Argument> arguments)const{return call((const void*)object,arguments);};
    virtual Argument call(const void * object, std::vector<Argument> arguments)const{std::cerr<<"const call not implemented"<<std::endl;throw(0);};
  protected:
    ArgumentTypesPropertyType & argumentTypes(){return _ArgumentTypes;}
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
  Argument MethodInfo::call(const void * object, Container & container)const{
    std::vector<Argument> args;
    for(auto it = std::begin(container); it!=std::end(container);it++){
      args.push_back(*it);
    }
    return call(object,args);
  }
}
