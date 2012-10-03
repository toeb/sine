#pragma once
#include <QGlWidget>
#include <application.qt/PluginWindow.h>
#include <application.qt/PluginContainer.h>
#include <application.qt/Plugin.h>
#include <visualization.opengl/GlViewport.h>
#include <core.hub/ModuleBase.h>
#include <core.hub/CompositeHubObject.h>
#include <visualization.opengl.qt/GlWidgetPluginWindow.h>

namespace nspace{
  class ViewportPlugin : public Plugin,public virtual ModuleBase, public virtual CompositeHubObject{
    Q_OBJECT;
    TYPED_OBJECT(ViewportPlugin);
  private:
    GlViewport * _glViewport;
    Set<GlViewport *> _viewports;
    GlWidgetPluginWindow * _pluginWindow;
  public:
    GlWidget * glWidget(){return _pluginWindow->glWidget();}


    ViewportPlugin():_pluginWindow(0){
      setName("ViewportPlugin");
    }


    bool accept(Object * object){
      return dynamic_cast<GlViewport * > (object)!=0;
    }

    void onAcception(Object * object){      
      _viewports |= dynamic_cast<GlViewport*>(object);

    }
    void onRenounce(Object * object){      
      _viewports /= dynamic_cast<GlViewport*>(object);
    }


    virtual void install(PluginContainer & container){
      _pluginWindow = new GlWidgetPluginWindow(_viewports);
      container.setPluginWindow(_pluginWindow);

      components()|=_pluginWindow;
    }
    virtual void enable(){}
    virtual void disable(){}
    virtual void uninstall(PluginContainer & container){

      components()|=_pluginWindow;
      delete _pluginWindow;
    }

  protected:

  };
}