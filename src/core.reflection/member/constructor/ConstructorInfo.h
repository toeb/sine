#pragma once

#include <core.reflection/member/MemberInfo.h>

#include <core.reflection/type/Argument.h>

namespace nspace{

struct ConstructorInfo : public MemberInfo{
  typedef std::vector<const Type*> basic_property(ArgumentTypes);
  virtual Argument call(std::vector<Argument> args)const=0;
  template<typename Container>
  Argument call(Container & container)const{
    std::vector<Argument> args;
    for(auto it = std::begin(container); it != std::end(container); it++){
      args.push_back(*it);
    }
    return call(args);
  }
  
};

template<typename ClassType>
struct TypedConstructorInfo : public ConstructorInfo{
  TypedConstructorInfo(){
      auto type = const_cast<Type*>(typeof(ClassType));
      type->Members()|=this;
      setOwningType(type);
      setName("constructor");

  }
};

}