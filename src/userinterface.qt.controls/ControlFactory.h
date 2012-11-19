#pragma once
#include <core.h>
#include <core.logging.h>

namespace nspace{
  class DynamicWidget;
  // TODO abstract Hint / Taggable interface for Object
  class ControlFactory{
    TYPED_OBJECT(ControlFactory);
  public:
    SIMPLE_PROPERTY(std::string, Hints){};
    SIMPLE_PROPERTY(const Type *, DataType){};
  public:
    virtual DynamicWidget * createInstance()=0;
  };
  class ControlFactoryRepository  : public virtual PropertyChangingObject, public virtual Log{
    REFLECTABLE_OBJECT(ControlFactory);
    
    PROPERTYSET(ControlFactory* , Factories,{},{});
  public:
    static  ControlFactoryRepository * defaultInstance();
    Set<ControlFactory*> getFactoriesForType(const Type * type, const std::string & hints ="");
    DynamicWidget *  createInstanceForType(const Type * type, const std::string & hints="");
    DynamicWidget * createInstanceForObject(Object * object, const std::string & hints="");
  };
}