#pragma once
#include <core.h>
#include <core.logging.h>

namespace nspace{
  class DynamicWidget;
  // TODO abstract Hint / Taggable interface for Object
  class ControlFactory{
    reflect_type(ControlFactory);
  public:
    virtual bool match(const Type * type, Object * object=0, const std::string& hints="")=0;
    virtual DynamicWidget * createInstance()=0;
  };
  class ControlFactoryRepository  : public virtual PropertyChangingObject, public virtual Log{
    reflect_type(ControlFactory);
    PROPERTYSET(ControlFactory* , Factories,{},{});
  public:
    static  ControlFactoryRepository * defaultInstance();
    Set<ControlFactory*> getApplicableFactories(const Type * type,Object * object, const std::string & hints ="");
    DynamicWidget * createWidget(const Type * type,Object * object, const std::string & hints ="");
  };
}