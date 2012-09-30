#pragma once
#include <application.qt/PluginWindow.h>
#include <visualization.opengl/GlViewport.h>
class Ui_GlViewportWidget;
namespace nspace{
  
  class GlWidgetPluginWindow : public PluginWindow, public virtual ObservableCollection<GlViewport*>::Observer{
    Q_OBJECT;
    TYPED_OBJECT;
  private:
    Set<GlViewport*> & _viewports;
    Ui_GlViewportWidget * _ui;
  public:
    GlWidgetPluginWindow(Set<GlViewport*> viewports);
    
    void collectionChanged(ObservableCollection<GlViewport*> * sender){}
    void elementAdded(ObservableCollection<GlViewport*> * sender, GlViewport* element){}
    void elementRemoved(ObservableCollection<GlViewport*> * sender, GlViewport* element){}
  };
}