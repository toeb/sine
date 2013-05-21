#pragma once

#include <core.reflection/dynamic/DynamicReflectedObjectImplementation.h>
#include <map>
namespace nspace{

  class DynamicMappedObjectImplementation :public DynamicReflectedObjectImplementation{
    std::map<std::string,Argument> _map;
  public:  
    DynamicMappedObjectImplementation();

    Argument __get_property(const std::string & name);
    bool __set_property(const std::string & name, Argument argument);
  };

}