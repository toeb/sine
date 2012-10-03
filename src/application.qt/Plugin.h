#pragma once

#include <config.h>
#include <QObject>
#include <core/NamedObject.h>

namespace nspace{
  class PluginApplication;
  class PluginContainer;
  class Plugin : public QObject, public virtual NamedObject{
    Q_OBJECT;
    TYPED_OBJECT(Plugin);
  public:
    virtual const std::string pluginName()const{return name();}
  protected:
    virtual void install(PluginContainer & container){}
    virtual void enable(){}
    virtual void disable(){}
    virtual void uninstall(PluginContainer & container){}

    friend class PluginApplication;
    friend class PluginContainer;

  };
}