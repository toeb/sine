#include "ObjectPropertyView.h"

#include <application.qt/DataBinding.h>
#include "ui_objectpropertyview.h"
#include <QLabel>
#include <QTreeView>
using namespace nspace;

ObjectPropertyView::ObjectPropertyView(QWidget*parent):QWidget(parent),_CurrentObject(0){  
  _ui = new Ui_ObjectPropertyView();  
  _ui->setupUi(this);
  _model = new ObjectPropertyViewModel();
  QTreeView* tv =_ui->treeView;
  tv->setModel(_model);

}

void ObjectPropertyView::propertyChanging(Object*, CurrentObject){
  _model->setCurrentObject(newvalue);
  Widgets().clear();

  auto properties =newvalue->getTypeData().properties;
  if(!properties)return;

  properties->foreachElement([this](const Property * prop){
    auto label = new QLabel();
    label->setText(tr(prop->getPropertyDisplayName().c_str()));
    Widgets()|= label;
    
  });


}
void ObjectPropertyView::itemAdded(QWidget*,Widgets){

}
void ObjectPropertyView::itemRemoved(QWidget*,Widgets){
}
