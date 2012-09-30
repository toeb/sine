#include "GlWidgetPluginWindow.h"

#include "ui_glviewportwidget.h"

using namespace nspace;

GlWidgetPluginWindow::GlWidgetPluginWindow(Set<GlViewport*> viewports):PluginWindow(0),_ui(0),_viewports(viewports){
  _ui = new Ui_GlViewportWidget();
  _ui->setupUi(this);
}