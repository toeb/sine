#include "CustomItemDelegate.h"
#include <QPainter>
using namespace nspace;

CustomItemDelegate::CustomItemDelegate(QObject * object):QStyledItemDelegate(object){
}
QWidget * CustomItemDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index)const{
  // return something else for custom handling
  debugInfo("createEditor");
  auto object= objectFromIndex(index);

  auto value = dynamic_cast<IReadableValue*>(object);
  auto action = dynamic_cast<Action*>(object);

  if(value){ 
    auto type = value->getValueType();
    if(type->getId()==typeof(double)->getId()){
      debugInfo("double");
      DoubleSpinBoxWidget * doubleWidget = new DoubleSpinBoxWidget(parent);
      connect(doubleWidget,SIGNAL(editFinished()),this,SLOT(saveAndCloseEditor()));
      return doubleWidget;
    }

  }
  return QStyledItemDelegate::createEditor(parent,option,index);
}
bool  CustomItemDelegate::editorEvent(QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index){
  debugInfo("editorEvent");
  return false;
}

Object* CustomItemDelegate::objectFromIndex(const QModelIndex & index)const{      
  QVariant variant = index.model()->data(index,Qt::UserRole+5);
  Object * object = reinterpret_cast<Object*>(variant.value<void*>());
  return object;
}

void CustomItemDelegate::setEditorData( QWidget * editor, const QModelIndex & index ) const{
  debugInfo("set editor data");
  auto object = objectFromIndex(index);
  auto dynamicWidget = dynamic_cast<DynamicWidget*>(editor);
  if(!dynamicWidget)return;
  dynamicWidget->setDataContext(object);
}
void CustomItemDelegate::setModelData( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const{
  debugInfo("setModelData");

  auto valueWidget = dynamic_cast<ValueWidget*>(editor);
  if(!valueWidget)return;
  valueWidget->updateValueHolder();
}

void CustomItemDelegate::saveAndCloseEditor(){
  auto widget = sender();
  auto valueWidget = dynamic_cast<ValueWidget*>(widget);
  if(!valueWidget)return;
  emit commitData(valueWidget);
  emit closeEditor(valueWidget);
}