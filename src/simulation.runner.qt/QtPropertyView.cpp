#include "QtPropertyView.h"
#include "ui_propertyWindow.h"

#include <iostream>

#include <application.qt/PluginContainer.h>
#include <application.qt/PluginWindow.h>
using namespace std;
using namespace nspace;

QtPropertyView::QtPropertyView(){
  setName("PropertyView Plugin");
  _ui = new Ui_PropertyWindow();
}
QtPropertyView::~QtPropertyView(){
  delete _ui;
  _ui=0;
}
void QtPropertyView::install(PluginContainer & container){
  auto window = new PluginWindow();
  _ui->setupUi(window);
  container.setPluginWindow(window);

}
void  QtPropertyView::enable(){}
void  QtPropertyView::disable(){}
void  QtPropertyView::uninstall(PluginContainer & container){


}
void  QtPropertyView::loadSettings(QSettings & settings){}
void  QtPropertyView::saveSettings(QSettings & settings){}

void  QtPropertyView::onElementAdded(IComponent * component){
  cout << *component << endl;
}
void  QtPropertyView::onElementRemoved(IComponent * component){}