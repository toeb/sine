#include "ObjectViewPlugin.h"

#include <application.qt/PluginContainer.h>
#include "ui_objectview.h"
#include <application.qt/DataBinding.h>
#include <core.utilities.h>
using namespace std;
using namespace nspace;

void ObjectViewPlugin::objectDoubleClicked(QListWidgetItem * qobject){
  auto data= qobject->data(Qt::UserRole);
  void * value =data.value<void*>();
  Object * object = static_cast<Object*>(value);
  _objectPropertyView->setCurrentObject(object);
}

void ObjectViewPlugin::install(PluginContainer & container){
  PluginWindow * window = new PluginWindow();
  window->setWindowTitle(tr("Object View"));
  QWidget * w = new QWidget();
  _ui= new Ui_ObjectView();
  _ui->setupUi(w);
  _objectPropertyView = new ObjectPropertyView();
  //QGridLayout * gridLayout = _ui->gridLayout;
  QSplitter * splitter = _ui->splitter;
  auto binding = new LineEditDataBinding();
  binding->setSource(this);
  binding->setTarget(_ui->searchTextBox);
  binding->setPropertyName("SearchString");
  //gridLayout->addWidget(_objectPropertyView,0,1,2,1);
  splitter->addWidget(_objectPropertyView);
  connect(_ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)),this, SLOT(objectDoubleClicked(QListWidgetItem*)));

  window->setWidget(w);
  container.setPluginWindow(window);

  container.toggleWindow(true);
}
void ObjectViewPlugin::itemAdded(Object * , Objects){
}
void ObjectViewPlugin::itemRemoved(Object * , Objects){
}

void ObjectViewPlugin::onPropertyChanged(const std::string  &name){
  if(name!="SearchString"){return;}
  updateObjectList();
}
void ObjectViewPlugin::updateListView(){
  if(_ui)_ui->listWidget->clear();
  Objects().foreachElement([this](Object * object){
    string n = nspace::name(object);
    QListWidgetItem * item=new QListWidgetItem(tr(n.c_str()));
    QVariant variant = QVariant::fromValue<void*>(object);
    item->setData(Qt::UserRole,variant);

    if(_ui)_ui->listWidget->addItem(item);
  });
}
void ObjectViewPlugin::updateObjectList(){
  auto search = getSearchString();
  if(search==""){
    Objects()=*this;
  }else{
    Objects()=subset([&search](Object * object){
      return nspace::stringtools::containsIgnoreCase(nspace::name(object),search);
    });
  }

  updateListView();
}