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
  class ViewportPlugin : public Plugin,
    public virtual ModuleBase, 
    public virtual CompositeHubObject{
    Q_OBJECT;
    TYPED_OBJECT(ViewportPlugin);
  private:
    // pointer to the currently displaying viewport 
    GlViewport * _glViewport;
    // set of possible viewports
    Set<GlViewport *> _viewports;
    // the plugin window
    GlWidgetPluginWindow * _pluginWindow;

  public:
    GlWidget * glWidget();    
    ViewportPlugin();
    bool accept(Object * object);
    void onAcception(Object * object);
    void onRenounce(Object * object);

    virtual void install(PluginContainer & container);
    virtual void enable();
    virtual void disable();
    virtual void uninstall(PluginContainer & container);

  };
}