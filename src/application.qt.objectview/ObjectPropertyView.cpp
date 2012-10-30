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
    connect(_model,SIGNAL(modelReset()),this,SLOT(autoresize()));
  connect(_ui->treeView,SIGNAL(expanded(const QModelIndex &)),this,SLOT(onModelLayoutChanged(const QModelIndex &)));
  connect(_ui->treeView,SIGNAL(collapsed(const QModelIndex &)),this,SLOT(onModelLayoutChanged(const QModelIndex &)));
  QTreeView* tv =_ui->treeView;
  tv->setModel(_model);
}

void ObjectPropertyView::propertyChanging(Object*, CurrentObject){
  _model->setCurrentObject(newvalue);
  Widgets().clear();

  auto properties = & newvalue->getTypeData().Properties();

  properties->foreachElement([this](const Property * prop){
    auto label = new QLabel();
    label->setText(tr(prop->getDisplayName().c_str()));
    Widgets()|= label;
    
  });


}
void ObjectPropertyView::autoresize(){
  
  _ui->treeView->resizeColumnToContents(0);
  _ui->treeView->resizeColumnToContents(1);
}
void ObjectPropertyView::onModelLayoutChanged(const QModelIndex & index){
  autoresize();
}
void ObjectPropertyView::itemAdded(QWidget*,Widgets){

}
void ObjectPropertyView::itemRemoved(QWidget*,Widgets){
}
