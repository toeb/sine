#include "CustomItemDelegate.h"
#include <QPainter>
using namespace nspace;

CustomItemDelegate::CustomItemDelegate(QObject * object):QStyledItemDelegate(object){

}
QWidget * CustomItemDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index)const{
  // return something else for custom handling
  debugInfo("createEditor");
  auto object= objectFromIndex(index);


  auto control = ControlFactoryRepository::defaultInstance()->createWidget(0,object,"");
  
  if(control){
    control->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    control->setDataContext(object);
    control->setParent(parent);
    connect(control,SIGNAL(editFinished()),this,SLOT(saveAndCloseEditor()));
    return control;
  }
  return QStyledItemDelegate::createEditor(parent,option,index);
}
bool CustomItemDelegate::editorEvent(QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index){
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
  if(!dynamicWidget){
    QStyledItemDelegate::setEditorData(editor,index);
    return;
  }
  dynamicWidget->setDataContext(object);
}
void CustomItemDelegate::setModelData( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const{
  debugInfo("setModelData");
  auto valueWidget = dynamic_cast<ValueWidget*>(editor);
  if(!valueWidget){
    QStyledItemDelegate::setModelData(editor,model,index);
    return;
  }
  
  valueWidget->updateValueHolder();
}

 void CustomItemDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const{
   //painter->setBrush(option.palette.background());
   //painter->drawRect(option.rect);
   QStyledItemDelegate::paint(painter,option,index);
 }

void CustomItemDelegate::saveAndCloseEditor(){
  auto widget = sender();
  auto valueWidget = dynamic_cast<ValueWidget*>(widget);
  if(!valueWidget)return;
  emit commitData(valueWidget);
  emit closeEditor(valueWidget);
}

void CustomItemDelegate::updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const{
  //debugInfo(option.rect.size().width() << " x " << option.rect.size().height()<<" @ "<< option.rect.left() <<", "<<option.rect.top());
  QRect rect =  option.rect;
  editor->setGeometry(option.rect);
  editor->update();
 // debugInfo(editor->geometry().width()<<" vs "<<option.rect.size().width());
}