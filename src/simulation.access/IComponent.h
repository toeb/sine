#pragma once
#include <string>
#include <config.h>
#include <core/NamedObject.h>
#include <core/Reflection.h>

namespace nspace{

  class IComponent : public virtual NamedObject, public virtual PropertyChangingObject{
    REFLECTABLE_OBJECT(IComponent);
  private:
    PROPERTY(std::string, DisplayName){}
    PROPERTY(std::string, Description){}
    PROPERTY(Object *, Parent){}
  public:
    IComponent(Object * parent=0):_Parent(parent),_DisplayName(""),_Description(""){}
  };
}