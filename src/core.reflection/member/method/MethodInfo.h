#pragma once
#include <core.reflection/member/MemberInfo.h>
#include <core.reflection/type/Argument.h>
#include <core.reflection/function/ArgumentInfo.h>
namespace nspace{


  class MethodInfo : public MemberInfo{
  public:
    static bool initializeType();

    typedef std::shared_ptr<ArgumentInfo> argument_ptr;
    typedef std::shared_ptr<const ArgumentInfo> const_argument_ptr;

    template<typename Container> Argument call(void * object, Container & container=std::vector<Argument>())const;
    template<typename Container> Argument call(const void * object, Container & container=std::vector<Argument>())const;
    Argument call(void * object)const;
    Argument call(const void * object)const;

    // signature elements
    propdef std::vector<argument_ptr> basic_property(Arguments);
    basic_references(Arguments);
    argument_ptr argument(unsigned int index);
    const_argument_ptr argument (unsigned int index)const;
    propdef std::vector<const Type*> basic_property(ArgumentTypes);
    propdef const Type * basic_property(ReturnType);
    propdef bool basic_property(IsConst);
    // gets/sets the pure name part of the method 
    //   e.g.  pure name of &std::vector<int>::at(size_t i)const is simply "at"
    // this part of the name is generally not unique because of method overloading
    propdef std::string basic_property(PureName);


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
