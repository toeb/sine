#include "QtPropertyView.h"
#include "ui_propertyView.h"

#include <iostream>
#include <simulation.runner.qt/ValueItemFactory.h>
#include <application.qt/PluginContainer.h>
#include <application.qt/PluginWindow.h>
#include <simulation.runner.qt/ValueItemDelegate.h>
using namespace std;
using namespace nspace;

QtPropertyView::QtPropertyView():
  _ui(0),
  _refreshTimer(0),
  _itemModel(0),
  _rootNode(0)
{
  setName("PropertyView Plugin");
  setRefreshRate(25);
}
QtPropertyView::~QtPropertyView(){
}
void QtPropertyView::propertyChanging(int ,RefreshRate){
  logInfo("Changing RefreshRate from "<<oldvalue<< " to "<<newvalue);
  updateTimer(newvalue);
  
}
void QtPropertyView::updateTimer(int refreshrate){  
  if(!_refreshTimer)return;
  int intTimeout= 0;
  if(refreshrate<1){
    double refreshTimeout = 1.0 / getRefreshRate();
    intTimeout = 1000*refreshTimeout;
  }
  logInfo("  setting interval to"<<intTimeout);
  _refreshTimer->setInterval(intTimeout);
}

void QtPropertyView::install(PluginContainer & container){
  logInfo("installing plugin");

  auto window = new PluginWindow();
  _ui = new Ui_PropertyWindow();
  _ui->setupUi(window);
  
  
  _refreshTimer = new QTimer(this);
  // TODO no static fields please
  ValueItem::refreshTimer=_refreshTimer;
  updateTimer(getRefreshRate());
  connect(_refreshTimer,SIGNAL(timeout()),this,SLOT(refreshProperties()));
  _refreshTimer->start();
  
  _itemModel = new QStandardItemModel();
  _rootNode = _itemModel->invisibleRootItem();
  
  _ui->treeView->setItemDelegate(new ValueItemDelegate());
  _ui->treeView->setModel(_itemModel);
  _ui->treeView->header()->setResizeMode(QHeaderView::ResizeToContents);
  container.setPluginWindow(window);
}
void QtPropertyView::refreshProperties(){
  ValueItems().foreachElement([](ValueItem * item){
    item->refresh();
  });
}
void  QtPropertyView::enable(){}
void  QtPropertyView::disable(){}
void  QtPropertyView::uninstall(PluginContainer & container){
  logInfo("uninstalling plugin");
  _refreshTimer->stop();
  delete _refreshTimer;
  _refreshTimer=0;
  
  delete _ui;
  _ui=0;


}
void  QtPropertyView::loadSettings(QSettings & settings){}
void  QtPropertyView::saveSettings(QSettings & settings){}

void  QtPropertyView::onElementAdded(IComponent * component){
  logInfo("adding component: "<<*component);

  ValueItems()|=ValueItemFactory::create(*_rootNode,component);

}
void  QtPropertyView::onElementRemoved(IComponent * component){
  logInfo("removing component: "<<*component);


}

void  QtPropertyView::itemAdded(ValueItem*,ValueItems){
  
}
void  QtPropertyView::itemRemoved(ValueItem*,ValueItems){

}