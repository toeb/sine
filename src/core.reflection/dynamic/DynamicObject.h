#pragma once

#include <core.reflection/type/TypeInfo.h>
#include <core.reflection/type/Argument.h>
#include <core.reflection/dynamic/DynamicCallable.h>


namespace nspace{

  struct DynamicObjectImplementation;
  class DynamicObject{
    reflect_type(DynamicObject);
    std::shared_ptr<DynamicObjectImplementation> _implementation;
  public:
    typedef const std::vector<std::string> MemberList;  
    DynamicObject(std::shared_ptr<DynamicObjectImplementation> impl);
    Argument operator[](const std::string & name);
    Argument getProperty(const std::string & name);
    DynamicCallable getMethod(const std::string & name);
    MemberList getMemberNames();
  };


}