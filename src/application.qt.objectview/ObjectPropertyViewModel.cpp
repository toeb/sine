#include "ObjectPropertyViewModel.h"

#include <application.qt.objectview/ObjectTreeItem.h>
#include <application.qt.objectview/PropertyTreeItem.h>
#include <application.qt.objectview/PropertySetTreeItem.h>

using namespace nspace;







void  ObjectPropertyViewModel::onPropertyChanged(const std::string  & name){
  if(name=="RootItem") reset();      
}
TreeItem* ObjectPropertyViewModel::createItem(Object * object){
  auto propertyAdapter = dynamic_cast<PropertyAdapter*>(object);
  if(!propertyAdapter) {
    auto item = new ObjectTreeItem();
    item->setObject(object);
    item->setModel(this);
    return item;
  }

  auto propertySetInfo =  dynamic_cast<const PropertySetInfo*>(&propertyAdapter->property());
  if(propertySetInfo){
    auto item = new PropertySetTreeItem();
    item->setObject(propertyAdapter);
    item->setModel(this);
    return item;
  }


  auto item = new PropertyTreeItem();
  item->setObject(propertyAdapter);
    item->setModel(this);
  return item;
}

void ObjectPropertyViewModel::propertyChanging(TreeItem*, RootItem){
  debugInfo("RootItem changed - resetting view");
  reset();
}
void ObjectPropertyViewModel::propertyChanging(Object *,CurrentObject){
  if(oldvalue){
    auto pc = dynamic_cast<PropertyChangingObject*>(oldvalue);
    if(pc)pc->listeners()/=this;
  }
  if(newvalue){        
    auto pc = dynamic_cast<PropertyChangingObject*>(newvalue);
    if(pc)pc->listeners()|=this;
  }
  debugInfo("CurrentObject changed");

  auto item = createItem(newvalue);
  setRootItem(item);



}


    void ObjectPropertyViewModel::itemChanged(TreeItem * treeItem){
      emit layoutChanged();
      //reset();
      
    }
TreeItem* ObjectPropertyViewModel::getItem(const QModelIndex & index)const{
  TreeItem* item=0;
  if(index.isValid()){
    item = static_cast<TreeItem*>(index.internalPointer());
  }
  
  if(!item)item = getRootItem();
  if(item)item->setModelIndex(index);
  return item;
}
ObjectPropertyViewModel::ObjectPropertyViewModel():_CurrentObject(0),_RootItem(0){}

QModelIndex  ObjectPropertyViewModel::parent( const QModelIndex& index ) const {
  if(!index.isValid())return QModelIndex();
  auto item = getItem(index);
  auto parent = item->parent();
  if(!parent)return QModelIndex();
  if(parent==getRootItem())return QModelIndex();
  return createIndex(parent->childNumber(),0,parent);

}
bool  ObjectPropertyViewModel:: hasChildren(const QModelIndex& parent)const{      
  if(!getItem(parent))return false;  
  auto item = getItem(parent);  
  if(item) item->expand();
  return !getItem(parent)->successors().empty();

}
const Property*   ObjectPropertyViewModel::getProperty(const QModelIndex & index)const{
  if(!index.isValid())return 0;
  auto object = getCurrentObject();
  if(!object)return 0;
  int row = index.row();
  auto prop = object->getTypeData().Properties().at(row);      
  return prop;
}

bool  ObjectPropertyViewModel::setData(const QModelIndex & index, const QVariant & value, int role){
  auto item = getItem(index);
  if(!item)return false;
  std::string stdstring = value.toString().toUtf8().constData();
  bool result = item->setEditValue(stdstring);
  if(result)emit dataChanged(index,index);
  return result;

}

Qt::ItemFlags  ObjectPropertyViewModel::flags(const QModelIndex & index)const{
  auto item = getItem(index);
  
  if(index.column()==1 && item&&item->isEditable()){
    Qt::ItemFlags result = QAbstractItemModel::flags(index)|Qt::ItemIsEditable;
    return result;
  }
  return QAbstractItemModel::flags(index);
}
QModelIndex  ObjectPropertyViewModel::index(int row, int column, const QModelIndex & parent)const{    
  auto parentItem= getItem(parent);
  if(!parentItem)return QModelIndex();
  auto childItem = parentItem->children().at(row);
  if(!childItem) return QModelIndex();
  return createIndex(row,column,childItem);

}

int  ObjectPropertyViewModel:: rowCount(const QModelIndex &parent)const{
  auto parentItem = getItem(parent);
  return parentItem->children();
}
int  ObjectPropertyViewModel::columnCount(const QModelIndex &parent)const{
  if(!getItem(parent))return 0;
  return 2;
}
QVariant  ObjectPropertyViewModel::data(const QModelIndex & index, int role)const{      
  auto item  =getItem(index);
  if(index.column()==0){
    switch(role){
    case Qt::DisplayRole:
      return QVariant::fromValue(tr(item->getDisplayName().c_str()));
    case Qt::WhatsThisRole:
    case Qt::ToolTipRole:
      return QVariant::fromValue(tr(item->getDescription().c_str()));
    }
    
  }
  if(index.column()==1){
    
    switch(role){
    case Qt::DisplayRole:      
      return QVariant::fromValue(tr(item->getDisplayValue().c_str()));
    case Qt::EditRole:
      return QVariant::fromValue(tr(item->getEditValue().c_str()));
    case Qt::WhatsThisRole:
    case Qt::ToolTipRole:
      return QVariant::fromValue(tr(item->getDescription().c_str()));
    }
  }
  return QVariant();
}


void ObjectPropertyViewModel::onPropertyChanged(Object * sender, const std::string & name){
  //if(result)emit dataChanged(index,index);
  auto object = getCurrentObject();
  const Set<const Property*> properties = object->getTypeData().Properties();

  for(int i=0; i < properties; i++){
    if(properties.at(i)->getName()==name){
      auto idx = index(i,1);
      emit dataChanged(idx,idx);
    }
  }
}