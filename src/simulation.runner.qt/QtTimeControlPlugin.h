#pragma once


#include <application.qt/Plugin.h>
#include <core/Reflection.h>

Ui
namespace nspace{

  class QtTimeControlPlugin :public Plugin,public virtual PropertyChangingObject{   
    REFLECTABLE_OBJECT(QtTimeControlPlugin)
  private:
  public:
    virtual void install(PluginContainer & container){
          

    }
    virtual void enable(){}
    virtual void disable(){}
    virtual void uninstall(PluginContainer & container){}
  };
}