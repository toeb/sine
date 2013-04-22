#pragma once
#include <core.h>
#include <core.logging.h>
#include <core.hub.h>
#include <application.qt.h>

#include <application.qt.objectview/ObjectPropertyView.h>
namespace nspace{
  class PropertyViewPlugin :
    public Plugin,
    public virtual PropertyChangingObject,
    public virtual Log {
      Q_OBJECT;
      reflect_type(PropertyViewPlugin);
      reflect_superclasses(Log);
      typedef Object* reflect_property(Object);
      auto before_set(Object);
      auto after_set(Object);
      typedef bool reflect_property(StartVisible);
      typedef ObjectPropertyView* extensible_property(ObjectPropertyView);
      auto before_set(ObjectPropertyView);
      auto after_set(ObjectPropertyView);
  public:
    PropertyViewPlugin();
    virtual void install(PluginContainer & container);
    virtual void enable(){}
    virtual void disable(){}
    virtual void uninstall(PluginContainer & container){}
  };
}
