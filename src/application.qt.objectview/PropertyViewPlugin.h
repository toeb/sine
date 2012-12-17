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
    REFLECTABLE_OBJECT(PropertyViewPlugin)
    SUBCLASSOF(Log);
    PROPERTY(Object*, Object);
    PROPERTY(bool, StartVisible){}
    SIMPLE_PROPERTY(ObjectPropertyView*, ObjectPropertyView);
  public:
    PropertyViewPlugin();
    virtual void install(PluginContainer & container);
    virtual void enable(){}
    virtual void disable(){}
    virtual void uninstall(PluginContainer & container){}   
  };
}
