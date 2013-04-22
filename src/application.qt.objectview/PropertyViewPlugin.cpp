#include "PropertyViewPlugin.h"

using namespace nspace;

PropertyViewPlugin::PropertyViewPlugin():_Object(0),_StartVisible(false),_ObjectPropertyView(0){
  setLoggingLevel(1);
}

auto PropertyViewPlugin::before_set(ObjectPropertyView){
  if(_ObjectPropertyView)_ObjectPropertyView->setCurrentObject(0);
}
auto PropertyViewPlugin::after_set(ObjectPropertyView){
  if(_ObjectPropertyView)_ObjectPropertyView->setCurrentObject(getObject());
}
auto PropertyViewPlugin::before_set(Object){
  
  if(nspace::hasObjectName(*newvalue)){
    std::stringstream ss;
    ss << "Properties of ";
    ss << nspace::name(*newvalue);
    setName(ss.str());
  }else{
    setName("Property View");
  }
}
void PropertyViewPlugin::install(PluginContainer & container){
  if(!getObjectPropertyView()){
    setObjectPropertyView(new ObjectPropertyView());
  }
  auto view = getObjectPropertyView();
  PluginWindow * window = new PluginWindow();

  window->setWindowTitle(tr("Property View Window"));
  window->setWidget(view);

  container.setPluginWindow(window);
  if(getStartVisible())container.toggleWindow(true);
}