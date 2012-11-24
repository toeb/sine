#include "PropertyViewPlugin.h"

using namespace nspace;

PropertyViewPlugin::PropertyViewPlugin():_ObjectPropertyView(0){

}
void PropertyViewPlugin::propertyChanging(ObjectPropertyView*, ObjectPropertyView){
  if(oldvalue){
    oldvalue->setCurrentObject(0);
  }
  if(newvalue){
    newvalue->setCurrentObject(getObject());
  }
}
void PropertyViewPlugin::propertyChanging(Object*, Object){
  if(nspace::hasObjectName(newvalue)){
    std::stringstream ss;
    ss << "Properties of ";
    ss << nspace::name(newvalue);    
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
  window->show();

  window->setWindowTitle(tr("Property View Window"));
  window->setWidget(view);

  container.setPluginWindow(window);


}