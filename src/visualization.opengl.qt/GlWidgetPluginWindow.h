#pragma once
#include <application.qt/PluginWindow.h>
#include <visualization.opengl/GlViewport.h>
#include <visualization.opengl.qt/GlWidget.h>
#include <core.hub/CompositeHubObject.h>
class Ui_GlViewportWidget;
namespace nspace{
  
  class GlWidgetPluginWindow : public PluginWindow, public virtual CompositeHubObject, public virtual ObservableCollection<GlViewport*>::Observer{
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

  protected:
    
  };
}