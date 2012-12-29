#include "ViewportPlugin.h"

using namespace nspace;

GlWidget * ViewportPlugin::glWidget(){return _pluginWindow->glWidget();}

ViewportPlugin::ViewportPlugin():_pluginWindow(0){
  setName("ViewportPlugin");
}

bool ViewportPlugin::accept(Object * object){
  return dynamic_cast<GlViewport * > (object)!=0;
}

void ViewportPlugin::onAcception(Object * object){
  _viewports |= dynamic_cast<GlViewport*>(object);
}
void ViewportPlugin::onRenounce(Object * object){
  _viewports /= dynamic_cast<GlViewport*>(object);
}

void ViewportPlugin::install(PluginContainer & container){
  _pluginWindow = new GlWidgetPluginWindow(_viewports);
  _pluginWindow->setWindowTitle(name().c_str());
  container.setPluginWindow(_pluginWindow);

  container.toggleWindow(true);

  Components()|=_pluginWindow;
}
void ViewportPlugin::enable(){}
void ViewportPlugin::disable(){}
void ViewportPlugin::uninstall(PluginContainer & container){
  Components()|=_pluginWindow;
  delete _pluginWindow;
}