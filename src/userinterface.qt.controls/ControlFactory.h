#pragma once
#include <core.h>
#include <core.logging.h>

namespace nspace{
  class DynamicWidget;
  // TODO abstract Hint / Taggable interface for Object
  class ControlFactory{
  public:
    SIMPLE_PROPERTY(std::string, Hints){};
    SIMPLE_PROPERTY(const Type *, DataType){};
  public:
    DynamicWidget * createInstance();
  };
  class ControlFactoryRepository  : public virtual PropertyChangingObject, public virtual Log{
    REFLECTABLE_OBJECT(ControlFactory);
    
    PROPERTYSET(ControlFactory* , Factories,{},{});
  public:
    static const ControlFactoryRepository * defaultInstance();

    DynamicWidget *  createInstanceFor(const Type * type, const std::string & hints="");
    DynamicWidget * createInstanceFor(Object * object, const std::string & hints="");
  };
}