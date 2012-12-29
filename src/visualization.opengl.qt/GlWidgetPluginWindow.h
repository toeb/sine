#pragma once
#include <application.qt/PluginWindow.h>
#include <visualization.opengl/GlViewport.h>
#include <visualization.opengl.qt/GlWidget.h>
#include <core.hub/CompositeHubObject.h>
#include <core.collection.h>

class Ui_GlViewportWidget;
namespace nspace{
  // the gl widget plugin window is a plugin window which has a renderer and viewport specific options showing
  class GlWidgetPluginWindow :
    public PluginWindow,
    public virtual NamedObject,
    public virtual CompositeHubObject,
    public virtual ObservableCollection<GlViewport*>::Observer{
      Q_OBJECT;
      TYPED_OBJECT(GlWidgetPluginWindow);
  private:
    Set<GlViewport*> & _viewports;
    GlWidget * _glWidget;
    Ui_GlViewportWidget * _ui;
  public:
    GlWidget * glWidget(){return _glWidget;}
    GlWidgetPluginWindow(Set<GlViewport*> & viewports);

    void collectionChanged(ObservableCollection<GlViewport*> * sender){}
    void elementAdded(ObservableCollection<GlViewport*> * sender, GlViewport* element);
    void elementRemoved(ObservableCollection<GlViewport*> * sender, GlViewport* element);
    protected slots:
      void viewportIndexChanged(int newindex);
  };
}